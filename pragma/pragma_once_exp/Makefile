TARGET=pragma_once_exp
OBJS=main.o
CFLAGS=-g

.PHONY: all
all: $(TARGET)

.PHONY: test
test: $(TARGET)
	@./$(TARGET) >result.txt
	@diff expected.txt result.txt
	@echo OK
	@rm result.txt

.PHONY: clean
clean:
	-rm -f $(OBJS)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

main.o: main.c
	$(CC) $(CFLAGS) -c -o $@ $<
