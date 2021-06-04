EXE=hello
OBJS=main.o

.PHONY: all
all: $(EXE)

.PHONY: clean
clean:
	-rm -f $(OBJS)

$(EXE): $(OBJS)
	$(CC) -o $@ $(OBJS)

main.o: main.c
	$(CC) $(CFLAGS) -c -o $@ $<
