# for GNU make
include Makefile.local.mk

LIB_DIRS ?= $(CUR_DIR)/../lib
INCLUDE_DIRS ?= $(CUR_DIR)/../include
LIBS ?= cplayground
INSTALL_BIN_DIR ?= $(CUR_DIR)/../bin

BUILD_CONF ?= release
CFLAGS ?= -g
CUR_DIR = $(dir $(realpath $(firstword $(MAKEFILE_LIST))))
TARGET_BASE_NAME ?= $(notdir $(CUR_DIR:%/=%))
TARGET ?= $(TARGET_BASE_NAME)

SRC_DIR ?= src
BUILD_DIR ?= build
DIST_DIR ?= dist
INCLUDE_DIR ?= include

BUILD_FULL_DIR = $(BUILD_DIR)/$(BUILD_CONF)
DIST_FULL_DIR = $(DIST_DIR)/$(BUILD_CONF)
TARGET_BIN_FULL = $(DIST_FULL_DIR)/bin/$(TARGET)

SRCS = $(wildcard $(SRC_DIR)/**/*.c $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%,$(BUILD_FULL_DIR)/%,$(patsubst %.c,%.o,$(SRCS)))
DEPENDS = $(patsubst $(SRC_DIR)/%,$(BUILD_FULL_DIR)/%,$(patsubst %.c,%.d,$(SRCS)))

FULL_CFLAGS = $(CFLAGS) -I$(INCLUDE_DIR) $(INCLUDE_DIRS:%=-I%) $(DEFINES:%=-D%)

.PHONY: build
build: $(TARGET_BIN_FULL)

.PHONY: test
test: build
	$(TARGET_BIN_FULL)

#.PHONY: install
#install: all
#	cp -p $(TARGET_BIN_FULL) $(INSTALL_BIN_DIR)

.PHONY: clean
clean:
	-rm -rf $(BUILD_FULL_DIR)

$(TARGET_BIN_FULL): $(OBJS)
	@mkdir -p $$(dirname "$@")
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIB_DIRS:%=-L%) $(LIBS:%=-l%)

$(BUILD_FULL_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $$(dirname "$@")
	$(CC) $(FULL_CFLAGS) -c -fPIC -o $@ $<

$(BUILD_FULL_DIR)/%.d: $(SRC_DIR)/%.c
	@mkdir -p $$(dirname "$@")
	$(CC) $(FULL_CFLAGS) -c -fsyntax-only -MMD -MF $@ -MT $(patsubst %.d,%.o,$@) $<

ifneq ($(MAKECMDGOALS),clean)
-include $(DEPENDS)
endif
