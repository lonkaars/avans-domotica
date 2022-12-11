all: confui

ifeq ($(wildcard confui.mk),)
confui.mk:
	qmake confui.pro -o confui.mk
endif

include confui.mk

FMT_FILES := $(DIST)
FMT_FILES := $(filter-out .%,$(FMT_FILES)) # filter hidden files
FMT_FILES := $(filter-out /%,$(FMT_FILES)) # filter files outside working directory
FMT_FILES := $(filter-out %.conf,$(FMT_FILES)) # filter *.conf
FMT_FILES := $(filter-out %.pri,$(FMT_FILES)) # filter *.pri
FMT_FILES := $(filter-out %.prf,$(FMT_FILES)) # filter *.prf
FMT_FILES := $(filter-out %.pro,$(FMT_FILES)) # filter *.pro

format:
	clang-format -i $(FMT_FILES)
	clang-tidy --fix-errors $(FMT_FILES)
