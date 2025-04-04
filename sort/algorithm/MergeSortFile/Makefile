TARGET=MergeSortFile
#SRCS=main.c MergeSortFile_sort.c
OBJS=main.o MergeSortFile_sort.o

.PHONY: all
all: $(TARGET)

.PHONY: clean
clean:
	-rm -f $(OBJS)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

MergeSortFile_sort.o: MergeSortFile_sort.c MergeSortFile.h
	$(CC) $(CFLAGS) -c -g -o $@ $<

main.o: main.c MergeSortFile.h
	$(CC) $(CFLAGS) -c -g -o $@ $<
