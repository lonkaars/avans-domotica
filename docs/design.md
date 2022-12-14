# QT Serial port communication (joshua)
# General system architecture

![System architecture](img/fig-architecture.svg)

Above is a diagram that shows the component layout of the end product. Notable
details are:

- The use of bluetooth mesh to establish connections between nodes in the
  network.
  
  Bluetooth mesh was chosen because it provides an abstraction layer between
  the node behaviour and low-level bluetooth protocol routines.
- The use of a J-Link debugger for connecting the border router node to a
  desktop computer running the configuration utility.
  
  The use of the J-Link debugger was chosen because it requires no additional
  USB controller setup on the node side to communicate.
  
  Because the network should continue functioning even without the
  configuration utility connected to the border router, all network
  configuration (which buttons control which lights) is stored on the border
  router. The configuration utility is only a 'viewer' for the network with
  features to edit the configuration and node state, but all action handling is
  happening on the nodes.

# Custom serial protocol

The border router node communicates with the QT application using a USART
interface, over which our custom protocol is used to send and receive formatted
data.

The protocol itself is in a binary format to save on bandwidth and memory
consumption on the node side. Messages consist of a single starting byte
(0xff), and following data which is derived from packed structs (a struct of
which each field is adjacent in memory, without padding).

All data that is sent starts with an opcode to represent the message type, and
a message id to uniquely identify each message for the purpose of replying to a
specific message or request. Most messages are fixed-length, but messages that
have variable-length fields have extra logic in the parser module to handle
memory allocation. All message types implement their own handler function which
decodes the message back into a regular struct.

Exact specifications of the protocol can be found in the source tree in
markdown format, with included client and parser libaries.

# Multitasking on nodes (niels)

# Used software and library versions

<figure>
|Library|Version|
|-------|-------|
|Git|2.39.0|
|GCC|12.2.0|
|Qt|6.0.0|
|Zephyr|3.1|
|nRF SDK|2.1.2|
<figcaption>Software and library functions</figcaption>
</figure>

