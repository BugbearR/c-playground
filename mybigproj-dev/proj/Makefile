ifndef MYBIGPROJ_DEV_DIR
    $(error ERROR: Please set environment variable MYBIGPROJ_DEV_DIR)
endif

include $(MYBIGPROJ_DEV_DIR)/builder/common.mk

.PHONY: all
all:
	list="$(MAKE_SUBDIRS)" ; \
	for subdir in $$list ; do \
	echo $$subdir ; \
	done

#	$(MAKE) -C $$subdir ;
# rc=$?
# [ $(RUN_FORCE) -ne 1 && rc -ne 0 ] && exit 1
