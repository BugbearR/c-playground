TARGET=tmpnam_exp
OBJS=main.o

.PHONY: all
all: $(TARGET)

.PHONY: clean
clean:
	-rm -f $(OBJS)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) -L../../lib

main.o: main.c
	$(CC) $(CFLAGS) -c -o $@ $<
