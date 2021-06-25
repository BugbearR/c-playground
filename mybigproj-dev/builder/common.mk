MAKEFILE_DIR=$(dir $(realpath $(firstword $(MAKEFILE_LIST))))

include $(MAKEFILE_DIR)/make.local.mk

MAKE_SUBDIRS=$(dir $(wildcard $(MAKEFILE_DIR)*/Makefile))
