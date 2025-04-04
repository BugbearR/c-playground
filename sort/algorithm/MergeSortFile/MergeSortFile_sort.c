#include "MergeSortFile.h"

#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define NUM_MERGE_WAYS 2
#define NUM_TEMP_FILES 4

#ifdef MYDEBUG
    #define DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
    #define DEBUG_PRINT(...)
#endif

static char TEMPFILE_TEMPLATE[] = "%s/tempfile.XXXXXX";

static int readExact(int fd, void *buf, size_t count) {
    size_t totalRead = 0;
    ssize_t bytesRead;

    DEBUG_PRINT("readExact: fd=%d, buf=%p, count=%zu\n", fd, buf, count);
    while (totalRead < count) {
        bytesRead = read(fd, (char *)buf + totalRead, count - totalRead);
        if (bytesRead == -1) {
            if (errno == EINTR) {
                continue; // Interrupted by signal, try again
            }
            perror("read");
            return -1; // Error occurred
        }
        if (bytesRead == 0) {
            break; // End of file
        }
        totalRead += bytesRead;
    }

    return totalRead;
}

static int writeExact(int fd, const void *buf, size_t count) {
    size_t totalWritten = 0;
    ssize_t bytesWritten;

    DEBUG_PRINT("writeExact: fd=%d, buf=[%.10s], count=%zu\n", fd, buf, count);
    while (totalWritten < count) {
        bytesWritten = write(fd, (const char *)buf + totalWritten, count - totalWritten);
        if (bytesWritten == -1) {
            if (errno == EINTR) {
                continue; // Interrupted by signal, try again
            }
            perror("write");
            return -1; // Error occurred
        }
        totalWritten += bytesWritten;
    }

    return totalWritten;
}

int MergeSortFile_sort(
    const char *pInputFilePath,
    const char *pOutputFilePath,
    size_t recordSize,
    int (*fnCompare)(const void *pRecord1, const void *pRecord2, void *pContext),
    void *pContext,
    const char *pTempDirPath
)
{
    int result = -1;
    char *pPathBuf[4] = {NULL, NULL, NULL, NULL};
    int fd[2][NUM_MERGE_WAYS] = { {-1, -1}, {-1, -1} };
    int inIdx = 0;
    int outIdx = 1;
    char *pBuffer[NUM_MERGE_WAYS] = { NULL, NULL };
    char *pPrevBuffer = NULL;
    char *pTempBuffer = NULL;
    int outDir = 0;
    int inputFd = -1;
    int outputFd = -1;
    int recordCount = 0;
    int i;
    int j;
    int ret;

    if (pTempDirPath == NULL) {
        pTempDirPath = "/tmp";
    }

    for (i = 0; i < NUM_MERGE_WAYS; i++) {
        pBuffer[i] = malloc(recordSize);
        if (pBuffer[i] == NULL) {
            perror("malloc");
            goto EXIT_FUNC;
        }
    }
    pPrevBuffer = malloc(recordSize);
    if (pPrevBuffer == NULL) {
        perror("malloc");
        goto EXIT_FUNC;
    }

    inputFd = open(pInputFilePath, O_RDONLY);
    if (inputFd == -1) {
        perror("open");
        goto EXIT_FUNC;
    }

    size_t tempDirPathLen = strlen(pTempDirPath);
    size_t tempTemplateLen = strlen(TEMPFILE_TEMPLATE);
    size_t tempPathLen = tempDirPathLen + tempTemplateLen - 2; // -2 for %s
    for (i = 0; i < NUM_TEMP_FILES; i++) {
        pPathBuf[i] = malloc(tempPathLen + 1);
        if (pPathBuf[i] == NULL) {
            goto EXIT_FUNC; // Memory allocation failed
        }
        memset(pPathBuf[i], 0, tempPathLen + 1);
        snprintf(pPathBuf[i], tempPathLen + 1, TEMPFILE_TEMPLATE, pTempDirPath);
        fd[i/2][i%2] = mkstemp(pPathBuf[i]);
        if (fd[i/2][i%2] == -1) {
            perror("mkstemp");
            goto EXIT_FUNC;
        }
    }

    DEBUG_PRINT("--- step 1\n");
    // divide the input file to 2 work files.
    ssize_t bytesRead;
    ssize_t bytesWritten;
    outDir = 0;
    while (1) {
        bytesRead = readExact(inputFd, pBuffer[0], recordSize);
        if (bytesRead == -1) {
            goto EXIT_FUNC;
        }
        if (bytesRead == 0) {
            break; // End of file
        }
        if (bytesRead != recordSize) {
            memset(&(pBuffer[0]) + bytesRead, 0, recordSize - bytesRead);
        }

        DEBUG_PRINT("inIdx: %d, outDir: %d, fd[inIdx][outDir]: %d\n", inIdx, outDir, fd[inIdx][outDir]);

        bytesWritten = writeExact(fd[inIdx][outDir], pBuffer[0], recordSize);
        if (bytesWritten == -1) {
            goto EXIT_FUNC;
        }

        outDir = (outDir + 1) % NUM_MERGE_WAYS;
        recordCount++;
    }
    close(inputFd);
    inputFd = -1;

    if (recordCount == 0) {
        outputFd = open(pOutputFilePath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (outputFd == -1) {
            perror("open");
            goto EXIT_FUNC;
        }
        close(outputFd);
        result = 0;
        goto EXIT_FUNC;
    }

    bool isEof[NUM_MERGE_WAYS] = {false, false};
    bool isEmpty[NUM_MERGE_WAYS] = {true, true};
    bool isRunBoundaryDetected[NUM_MERGE_WAYS] = {false, false};
    if (recordCount > 2) {
        DEBUG_PRINT("--- step 2\n");
        while (true) {
            int outputRunSwitchCount = 0;
            bool isRunStart = true;
            for (i = 0; i < NUM_MERGE_WAYS; i++) {
                isEof[i] = false;
                ret = ftruncate(fd[outIdx][i], 0);
                if (ret == -1) {
                    perror("ftruncate");
                    goto EXIT_FUNC;
                }
                for (j = 0; j < 2; j++) {
                    ret = lseek(fd[j][i], 0, SEEK_SET);
                    if (ret == -1) {
                        perror("lseek");
                        goto EXIT_FUNC;
                    }
                }
                isEmpty[i] = true;
            }

            while (true) {
                int fromIdx;
                for (i = 0; i < NUM_MERGE_WAYS; i++) {
                    DEBUG_PRINT("--- isEof[i]: %d, isEmpty[i]: %d, isRunBoundaryDetected[i]: %d\n", isEof[i], isEmpty[i], isRunBoundaryDetected[i]);
                    if (!isEof[i] && isEmpty[i]) {
                        DEBUG_PRINT("--- read from fd[%d][%d].\n", inIdx, i);
                        bytesRead = readExact(fd[inIdx][i], pBuffer[i], recordSize);
                        if (bytesRead == -1) {
                            goto EXIT_FUNC;
                        }
                        if (bytesRead == 0) {
                            DEBUG_PRINT("--- read buffer %d EOF.\n", i);
                            isEof[i] = true;
                        }
                        else {
                            DEBUG_PRINT("--- read buffer %d [%.10s].\n", i, pBuffer[i]);
                            isEmpty[i] = false;
                        }
                    }
                }

                if (isEof[0] && isEof[1]) {
                    DEBUG_PRINT("--- Both buffers are empty\n");
                    break; // Both buffers are empty
                }


                if (isEof[0] || isEmpty[0]) {
                    DEBUG_PRINT("--- buffer 0 none.\n");
                    fromIdx = 1;
                }
                else if (isEof[1] || isEmpty[1]) {
                    DEBUG_PRINT("--- buffer 1 none.\n");
                    fromIdx = 0;
                }
                else if (isRunBoundaryDetected[0]) {
                    DEBUG_PRINT("--- buffer 0 is run boundary.\n");
                    fromIdx = 1;
                }
                else if (isRunBoundaryDetected[1]) {
                    DEBUG_PRINT("--- buffer 1 is run boundary.\n");
                    fromIdx = 0;
                }
                else {
                    // compare two buffers
                    DEBUG_PRINT("--- compare buffer buf[0]:[%.10s] buf[1]:[%.10s].\n", pBuffer[0], pBuffer[1]);
                    int cmp = fnCompare(pBuffer[0], pBuffer[1], pContext);
                    if (cmp <= 0) {
                        fromIdx = 0;
                    } else {
                        fromIdx = 1;
                    }
                    DEBUG_PRINT("--- buffer %d selected.\n", fromIdx);
                }

                if (isRunStart) {
                    isRunStart = false;
                }
                else {
                    // check if run boundary is detected
                    DEBUG_PRINT("--- check run boundary.\n");
                    if (fnCompare(pPrevBuffer, pBuffer[fromIdx], pContext) > 0) {
                        DEBUG_PRINT("--- boundary found.\n");
                        int notFromIdx = (fromIdx + 1) % NUM_MERGE_WAYS;
                        if (isEof[notFromIdx] || isRunBoundaryDetected[notFromIdx]) {
                            DEBUG_PRINT("--- new run.\n");
                            // new run detected
                            isRunBoundaryDetected[0] = false;
                            isRunBoundaryDetected[1] = false;
                            outDir = (outDir + 1) % NUM_MERGE_WAYS;
                            outputRunSwitchCount++;
                        }
                        else {
                            DEBUG_PRINT("--- stop output %d.\n", fromIdx);
                            isRunBoundaryDetected[fromIdx] = true;
                            continue;
                        }
                    }
                }

                bytesWritten = writeExact(fd[outIdx][outDir], pBuffer[fromIdx], recordSize);
                if (bytesWritten == -1) {
                    goto EXIT_FUNC;
                }
                isEmpty[fromIdx] = true;

                // swap the previous buffer with the current buffer
                pTempBuffer = pPrevBuffer;
                pPrevBuffer = pBuffer[fromIdx];
                pBuffer[fromIdx] = pTempBuffer;
            }

            // exchange in/out files
            inIdx = (inIdx + 1) % 2;
            outIdx = (outIdx + 1) % 2;

            // check if two work files are sorted.
            if (outputRunSwitchCount < 2) {
                break;
            }
        }
    }

    DEBUG_PRINT("--- step 3\n");

    // Merge the sorted two files into the output file
    outputFd = open(pOutputFilePath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (outputFd == -1) {
        perror("open");
        goto EXIT_FUNC;
    }

    // merge the two work files to output file
    for (i = 0; i < NUM_MERGE_WAYS; i++) {
        ret = lseek(fd[inIdx][i], 0, SEEK_SET);
        if (ret == -1) {
            perror("lseek");
            goto EXIT_FUNC;
        }
        isEof[i] = false;
        isEmpty[i] = true;
    }
    while (true) {
        int fromIdx;
        for (i = 0; i < NUM_MERGE_WAYS; i++) {
            if (!isEof[i] && isEmpty[i]) {
                bytesRead = readExact(fd[inIdx][i], pBuffer[i], recordSize);
                if (bytesRead == -1) {
                    goto EXIT_FUNC;
                }
                if (bytesRead == 0) {
                    isEof[i] = true;
                }
                else {
                    isEmpty[i] = false;
                }
            }
        }

        if (isEof[0] && isEof[1]) {
            break; // Both buffers are empty
        }

        if (isEof[0] || isEmpty[0]) {
            fromIdx = 1;
        }
        else if (isEof[1] || isEmpty[1]) {
            fromIdx = 0;
        }
        else {
            int cmp = fnCompare(pBuffer[0], pBuffer[1], pContext);
            if (cmp <= 0) {
                fromIdx = 0;
            } else {
                fromIdx = 1;
            }
        }

        bytesWritten = writeExact(outputFd, pBuffer[fromIdx], recordSize);
        if (bytesWritten == -1) {
            goto EXIT_FUNC;
        }
        isEmpty[fromIdx] = true;
    }

    close(outputFd);
    outputFd = -1;

    result = 0;

EXIT_FUNC:
    if (inputFd != -1) {
        close(inputFd);
    }
    if (outputFd != -1) {
        close(outputFd);
    }

    if (pBuffer[0] != NULL) {
        free(pBuffer[0]);
    }
    if (pBuffer[1] != NULL) {
        free(pBuffer[1]);
    }
    if (pPrevBuffer != NULL) {
        free(pPrevBuffer);
    }

    for (i = 0; i < NUM_TEMP_FILES; i++) {
        if (fd[i/2][i%2] != -1) {
            close(fd[i/2][i%2]);
            unlink(pPathBuf[i]);
        }

        if (pPathBuf[i] != NULL) {
            free(pPathBuf[i]);
        }
    }

    return result;
}
