all: confui

ifeq ($(wildcard confui.mk),)
confui.mk:
	qmake confui.pro -o confui.mk
endif

include confui.mk

OBJECTS += $(patsubst %.c,%.o, $(wildcard ../shared/*.c))
confui: $(OBJECTS)

../shared/%.o: ../shared/%.c
	$(CC) -c $(CFLAGS) -w $< -o $@
