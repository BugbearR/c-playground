TARGET=write_full_exp
OBJS=main.o

.PHONY: run
run: $(TARGET)
	mkdir -p /tmp/write_full_exp_tmpfs
	sudo mount -t tmpfs -o size=1M tmpfs /tmp/write_full_exp_tmpfs
	sudo chmod 777 /tmp/write_full_exp_tmpfs
	./write_full_exp /tmp/write_full_exp_tmpfs/test.dat

.PHONY: all
all: $(TARGET)

.PHONY: clean
clean:
	-rm -f $(OBJS)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

main.o: main.c
	$(CC) $(CFLAGS) -c -o $@ $<
