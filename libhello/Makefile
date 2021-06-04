BUILD_CONF=release
TARGET=libhello.a
OBJS=$(WORK_DIR)/hello.o

SRC_DIR=src
WORK_DIR=work
DIST_DIR=dist
DIST_FULL=$(DIST_DIR)/$(BUILD_CONF)
TARGET_FULL=$(DIST_FULL)/$(TARGET)
INCLUDE_DIR=include
CFLAGS=-I $(INCLUDE_DIR)

.PHONY: all
all: $(TARGET_FULL)

.PHONY: clean
clean:
	-rm -f $(OBJS)

$(TARGET_FULL): $(OBJS)
	$(AR) -r $@ $(OBJS)

$(WORK_DIR)/hello.o: $(SRC_DIR)/hello.c
	$(CC) $(CFLAGS) -c -o $@ $<
