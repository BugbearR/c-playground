EXE=hello_signal
OBJS=main.o

.PHONY: all
all: $(EXE)

.PHONY: clean
clean:
	-rm -f $(OBJS)

run: $(EXE)
	./$(EXE)

$(EXE): $(OBJS)
	$(CC) -o $@ $(OBJS)

main.o: main.c
	$(CC) $(CFLAGS) -c -o $@ $<
