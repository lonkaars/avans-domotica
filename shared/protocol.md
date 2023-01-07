# protocol specs

## commands

each command consists of a start byte, opcode, and a payload. each opcode
defines logic to handle payload length, so certain commands might expect a
fixed-length payload, a variable-length payload, or none at all. the start byte
is `0xff`, and because most data sent is in binary format, if the data contains
an `0xff` byte, it will be escaped by replacing it with two `0xff` bytes. this
is converted to a single `0xff` on the receiving end, so these duplicated bytes
and the starting byte don't count towards message length.

opcodes are picked sequentially, and are stored as enum constants inside
shared/protocol.h for code readability.

