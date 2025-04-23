TARGET=BinarySearchRange
#SRCS=BinarySearchRange_search.c BinarySearchRange_test.c
OBJS=BinarySearchRange_search.o BinarySearchRange_test.o

.PHONY: all
all: $(TARGET)

.PHONY: clean
clean:
	-rm -f $(OBJS)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

BinarySearchRange_search.o: BinarySearchRange_search.c BinarySearchRange.h
	$(CC) $(CFLAGS) -c -g -o $@ $<

BinarySearchRange_test.o: BinarySearchRange_test.c BinarySearchRange.h
	$(CC) $(CFLAGS) -c -g -o $@ $<
