TARGET=BinarySearch
#SRCS=BinarySearch_search.c BinarySearch_test.c
OBJS=BinarySearch_search.o BinarySearch_test.o

.PHONY: all
all: $(TARGET)

.PHONY: clean
clean:
	-rm -f $(OBJS)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

BinarySearch_search.o: BinarySearch_search.c BinarySearch.h
	$(CC) $(CFLAGS) -c -g -o $@ $<

BinarySearch_test.o: BinarySearch_test.c BinarySearch.h
	$(CC) $(CFLAGS) -c -g -o $@ $<
