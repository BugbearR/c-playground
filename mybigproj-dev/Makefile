# DON'T EDIT THIS Makefile!

ifndef MYBIGPROJ_DEV_DIR
	$(error ERROR: Please set environment variable MYBIGPROJ_DEV_DIR)
endif

include $(MYBIGPROJ_DEV_DIR)/builder/common.mk

.PHONY: all
all:
	list="$(MAKE_SUBDIRS)" ; \
	for subdir in $$list ; do \
	$(MAKE) -C $$subdir ; \
	done

#	rc=$$? \
#	[ "$(RUN_FORCE)x" != "x" && $$rc -ne 0 ] && exit 1 \
#	echo $(MAKE_SUBDIRS)

#	echo $(MAKEFILE_DIR)
#	echo $(MY_LOCAL_VAR)

#$(MAKE_SUBDIRS):
#	$(MAKE) -C $@

#    $(MAKE) -C proj
