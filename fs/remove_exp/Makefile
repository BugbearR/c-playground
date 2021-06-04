TARGET=remove_exp
OBJS=main.o

.PHONY: all
all: $(TARGET)

.PHONY: all
clean:
	-rm -f $(OBJS)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

main.o: main.c
	$(CC) $(CFLAGS) -c -o $@ $<
