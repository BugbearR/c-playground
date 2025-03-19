TARGET=pthread_rwlock_init_sysv_shm
OBJS=main.o
CFLAGS=-g
LDFLAGS=-lrt

.PHONY: all
all: $(TARGET)

.PHONY: run
run: $(TARGET)
	./$(TARGET)

.PHONY: clean
clean:
	-rm -f $(OBJS)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

main.o: main.c
	$(CC) $(CFLAGS) -c -o $@ $<
