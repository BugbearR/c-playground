EXE=unixdomsock_client_exp
OBJS=main.o

.PHONY: all
all: $(EXE)

.PHONY: all
clean:
	-rm -f $(OBJS)

$(EXE): $(OBJS)
	$(CC) -o $@ $(OBJS)

main.o: main.c
	$(CC) $(CFLAGS) -c -o $@ $<
