# for GNU make
include Makefile.local.mk
BUILD_CONF ?= release
CFLAGS ?= -g -DHAVE_PRAGMA_ONCE=1
CUR_DIR = $(dir $(realpath $(firstword $(MAKEFILE_LIST))))
TEST_TARGET_DIR = $(realpath $(CUR_DIR)/..)
TEST_TARGET_LIB_FULL_NAME = $(notdir $(TEST_TARGET_DIR:%/=%))
TEST_TARGET_LIB_NAME = $(patsubst lib%,%,$(TEST_TARGET_LIB_FULL_NAME))
TARGET_BASE_NAME ?= test_$(TEST_TARGET_LIB_FULL_NAME)
TARGET ?= $(TARGET_BASE_NAME)

SRC_DIR ?= src
BUILD_DIR ?= build
DIST_DIR ?= dist
INCLUDE_DIR ?= include

BUILD_FULL_DIR = $(BUILD_DIR)/$(BUILD_CONF)
DIST_FULL_DIR = $(DIST_DIR)/$(BUILD_CONF)

TEST_TARGET_INCLUDE_DIR = $(TEST_TARGET_DIR)/$(INCLUDE_DIR)
TEST_TARGET_DIST_DIR = $(TEST_TARGET_DIR)/$(DIST_DIR)
TEST_TARGET_LIB_DIR = $(TEST_TARGET_DIST_DIR)/$(BUILD_CONF)/lib

TARGET_DIR = $(DIST_FULL_DIR)

SRCS = $(wildcard $(SRC_DIR)/**/*.c $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%,$(BUILD_FULL_DIR)/%,$(patsubst %.c,%.o,$(SRCS)))
DEPENDS = $(patsubst $(SRC_DIR)/%,$(BUILD_FULL_DIR)/%,$(patsubst %.c,%.d,$(SRCS)))

FULL_CFLAGS = $(CFLAGS) -I$(TEST_TARGET_INCLUDE_DIR) -I$(INCLUDE_DIR) $(INCLUDE_DIRS:%=-I%) $(DEFINES:%=-D%)

TARGET_FULL = $(TARGET_DIR)/$(TARGET)

.PHONY: all
all: $(TARGET_FULL)

.PHONY: clean
clean:
	-rm -rf $(BUILD_FULL_DIR)

.PHONY: test
test: $(TARGET_FULL)
	$(TARGET_FULL)

$(TARGET_FULL): $(OBJS) $(TEST_TARGET_LIB_DIR)/$(TEST_TARGET_LIB_FULL_NAME).a
	@mkdir -p $$(dirname "$@")
	$(CC) -o $@ $(OBJS) -L$(TEST_TARGET_LIB_DIR) -l$(TEST_TARGET_LIB_NAME)

$(BUILD_FULL_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $$(dirname "$@")
	$(CC) $(FULL_CFLAGS) -c -o $@ $<

$(BUILD_FULL_DIR)/%.d: $(SRC_DIR)/%.c
	@mkdir -p $$(dirname "$@")
	$(CC) $(FULL_CFLAGS) -c -fsyntax-only -MMD -MF $@ -MT $(patsubst %.d,%.o,$@) $<

ifneq ($(MAKECMDGOALS),clean)
-include $(DEPENDS)
endif
