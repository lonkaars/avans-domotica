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

|code|name|implemented|directions|full name|
|--:|---|:-:|:-:|---|
|`0x00`|[PING](#ping)|yes|`r <=> c`|<u>ping</u>
|`0x02`|[EXPT](#expt)|yes|`r --> c`|<u>ex</u>ce<u>pt</u>ion

### PING

#### ping (`r <=> c`) (2 bytes)

|type|description|
|-:|-|
|`uint8_t`|opcode (`0x00 + 0` or `0x00 + 1`)|
|`uint8_t`|ping id|

**ping** sends back an identical message either way with the **same** direction
bit. _ping id_ is a random 8-bit value that identifies the ping message. this
is the only command that makes either the robot or client send a message with
an opcode not matching the respective sender. the direction bit indicates which
device initiated the ping message.

### EXPT

#### exception (`r --> c`) (3+ bytes)

|type|description|
|-:|-|
|`uint8_t`|opcode (`0x02 + 1`)|
|`uint8_t`|error code|
|`uint8_t`|length|
|`uint8_t[length]`|message contents|

the **exception** instruction is used by the robot to send errors, warnings,
and other messages back to the client. an error can also optionally contain a
message between 0 and 255 characters long. message length is sent before the
message, and can be 0 in case of no message.

