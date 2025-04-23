TARGET=BinarySearchBoundary
#SRCS=BinarySearchBoundary_search.c BinarySearchBoundary_test.c
OBJS=BinarySearchBoundary_search.o BinarySearchBoundary_test.o

.PHONY: all
all: $(TARGET)

.PHONY: clean
clean:
	-rm -f $(OBJS)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

BinarySearchBoundary_search.o: BinarySearchBoundary_search.c BinarySearchBoundary.h
	$(CC) $(CFLAGS) -c -g -o $@ $<

BinarySearchBoundary_test.o: BinarySearchBoundary_test.c BinarySearchBoundary.h
	$(CC) $(CFLAGS) -c -g -o $@ $<
