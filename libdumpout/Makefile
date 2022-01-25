TARGET=../lib/libdumpout.a
OBJS=dumpout.o

.PHONY: all
all: $(TARGET)

.PHONY: clean
clean:
	-rm -f $(OBJS)

$(TARGET): $(OBJS)
	$(AR) -r $@ $(OBJS)

main.o: main.c
	$(CC) $(CFLAGS) -c -o $@ $<
