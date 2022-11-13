CC = gcc
LD = gcc
RM = rm -f
CFLAGS =
LFLAGS =
TARGET = bts

SRCS := $(wildcard *.c)
OBJS := $(patsubst %.c,%.o, $(SRCS))

all: $(TARGET)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(TARGET): $(OBJS)
	$(LD) $^ $(LFLAGS) -o $@

clean:
	$(RM) $(TARGET) $(OBJS)

compile_commands: clean
	compiledb make

