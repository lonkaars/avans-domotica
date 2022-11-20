.PHONY: format

SRCS :=

SRCS += $(wildcard *.c)
SRCS += $(wildcard *.h)

format:
	clang-format -i $(SRCS)
	clang-tidy --fix-errors $(SRCS)
