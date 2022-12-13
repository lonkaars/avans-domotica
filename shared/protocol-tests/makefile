XXD := xxd
RM := rm -f

SRCS := $(wildcard *.src)
TARGET := $(SRCS:.src=.bin)

.PHONY: all clean

all: $(TARGET)

%.bin: %.src
	$(XXD) -r -c1 $< $@

clean:
	$(RM) $(TARGET)
