TARGET=BinarySearchElement
#SRCS=BinarySearch_search.c BinarySearch_test.c
OBJS=BinarySearchElement_search.o BinarySearchElement_test.o

.PHONY: all
all: $(TARGET)

.PHONY: clean
clean:
	-rm -f $(OBJS)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

BinarySearchElement_search.o: BinarySearchElement_search.c BinarySearchElement.h
	$(CC) $(CFLAGS) -c -g -o $@ $<

BinarySearchElement_test.o: BinarySearchElement_test.c BinarySearchElement.h
	$(CC) $(CFLAGS) -c -g -o $@ $<
