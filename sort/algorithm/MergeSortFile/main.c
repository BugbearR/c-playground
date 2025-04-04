#include "MergeSortFile.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Context {
    size_t recordSize;
} Context_t;

int compare(const void *a, const void *b, void *pContext) {
    Context_t *pContextWk = (Context_t *)pContext;
    // printf("compare: a=[%.10s], b=[%.10s], recordSize=%zu\n", a, b, pContextWk->recordSize);
    return memcmp(a, b, pContextWk->recordSize);
}

int main(int argc, char *argv[]) {
    Context_t context;
    // 引数の数をチェック
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <input_file> <output_file> <record_size>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // 入力ファイルと出力ファイルの名前を取得
    const char *input_file = argv[1];
    const char *output_file = argv[2];
    size_t recordSize = atoi(argv[3]); // レコードサイズを指定 (例: 100バイト)
    context.recordSize = recordSize;

    // マージソートを実行
    int ret = MergeSortFile_sort(input_file, output_file, recordSize, compare, &context, NULL);
    if (ret != 0) {
        fprintf(stderr, "Error: MergeSortFile failed with error code %d\n", ret);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
