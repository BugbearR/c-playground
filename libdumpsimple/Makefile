TARGET=libdumpsimple.a
OBJS=dumpsimple.o

.PHONY: all
all: $(TARGET)

.PHONY: clean
clean:
	-rm -f $(OBJS)

$(TARGET): $(OBJS)
	$(AR) -r -u $@ $(OBJS)

main.o: main.c
	$(CC) $(CFLAGS) -c -o $@ $<
