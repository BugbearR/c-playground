EXE=server
OBJS=server.o

.PHONY: all
all: $(EXE)

.PHONY: all
clean:
	-rm -f $(OBJS)

$(EXE): $(OBJS)
	$(CC) -o $@ $(OBJS)

main.o: main.c
	$(CC) $(CFLAGS) -c -o $@ $<
