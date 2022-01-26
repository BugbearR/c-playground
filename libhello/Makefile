# for GNU make
include Makefile.local.mk
BUILD_CONF ?= release
#BUILD_CONF = debug
CFLAGS ?= -g
CUR_DIR = $(dir $(realpath $(firstword $(MAKEFILE_LIST))))
TARGET_BASE_NAME = $(notdir $(CUR_DIR:%/=%))
TARGET ?= $(TARGET_BASE_NAME).a
SO_MAJOR_VERSION = 1
SO_MINOR_VERSION = 0
SO_PATCH_VERSION = 0
TARGET_SO ?= $(TARGET_BASE_NAME).so.$(SO_MAJOR_VERSION).$(SO_MINOR_VERSION).$(SO_PATCH_VERSION)
SONAME = $(TARGET_BASE_NAME).so.$(SO_MAJOR_VERSION)

SRC_DIR ?= src
BUILD_DIR ?= build
DIST_DIR ?= dist
INCLUDE_DIR ?= include

BUILD_FULL_DIR = $(BUILD_DIR)/$(BUILD_CONF)
DIST_FULL_DIR = $(DIST_DIR)/$(BUILD_CONF)
TARGET_FULL = $(DIST_FULL_DIR)/$(TARGET)
TARGET_SO_FULL = $(DIST_FULL_DIR)/$(TARGET_SO)

SRCS = $(wildcard $(SRC_DIR)/**/*.c $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%,$(BUILD_FULL_DIR)/%,$(patsubst %.c,%.o,$(SRCS)))
DEPENDS = $(patsubst $(SRC_DIR)/%,$(BUILD_FULL_DIR)/%,$(patsubst %.c,%.d,$(SRCS)))

MY_CFLAGS = $(CFLAGS) -I $(INCLUDE_DIR)

.PHONY: all
all: $(TARGET_FULL) $(TARGET_SO_FULL)

.PHONY: clean
clean:
	-rm -rf $(BUILD_FULL_DIR)

$(TARGET_SO_FULL): $(OBJS)
	@mkdir -p $$(dirname "$@")
	$(CC) -shared -fPIC -Wl,-soname,$(SONAME) -o $@ $(OBJS)

$(TARGET_FULL): $(OBJS)
	@mkdir -p $$(dirname "$@")
	$(AR) -r $@ $(OBJS)

$(BUILD_FULL_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $$(dirname "$@")
	$(CC) $(MY_CFLAGS) -c -fPIC -o $@ $<

$(BUILD_FULL_DIR)/%.d: $(SRC_DIR)/%.c
	@mkdir -p $$(dirname "$@")
	$(CC) $(MY_CFLAGS) -c -fsyntax-only -MMD -MF $@ -MT $(patsubst %.d,%.o,$@) $<

ifneq ($(MAKECMDGOALS),clean)
-include $(DEPENDS)
endif
