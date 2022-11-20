TARGET=fnv1a
OBJS=main.o
INCLUDE_DIR_FLAG=-I../../include
CFLAGS=-g
LIB_DIR_FLAG=-L../../lib
LIB_FLAG=-lcplayground

.PHONY: all
all: $(TARGET)

.PHONY: run
run: $(TARGET)
	./$(TARGET)

.PHONY: clean
clean:
	-rm -f $(OBJS)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIB_DIR_FLAG) $(LIB_FLAG)

main.o: main.c
	$(CC) $(CFLAGS) $(INCLUDE_DIR_FLAG) -c -o $@ $<
