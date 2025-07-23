TARGET=hello
OBJS=main.o
CFLAGS=-g -std=c89 -Wall

.PHONY: all
all: $(TARGET)

.PHONY: run
run: $(TARGET)
	./$(TARGET)

.PHONY: clean
clean:
	-rm -f $(OBJS)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

main.o: main.c
	$(CC) $(CFLAGS) -c -o $@ $<
