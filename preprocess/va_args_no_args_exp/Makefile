TARGET=va_args_no_args_exp
OBJS=main.o
#CFLAGS=-g
CFLAGS=-g -DDEBUG

.PHONY: all
all: $(TARGET)

.PHONY: clean
clean:
	-rm -f $(OBJS)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

main.o: main.c
	$(CC) $(CFLAGS) -c -o $@ $<
