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

# Asynchronous QT Serial port

The serial data communication is done in an asynchronous manner, which allows the program to efficiently handle data that is arriving on a serial port.

## Benefits

Using an asynchronous approach allows the program to efficiently handle incoming data from the serial port, while still allowing the UI to remain responsive. This also prevents the program from having to continuously poll the serial port to check for new data. Without an asynchronous approach, this could freeze the UI and consume a lot of CPU resources. By using an asynchronous approach, the application can handle incoming data as soon as it arrives, without blocking the UI or consuming excessive CPU resources.

## Data processing

When new data arrives at the serial port, it sends out a "ready read" signal. This signal tells the Qt event loop to call the asynchronous serial data read function, which processes the data at the next available opportunity. This ensures that the data is handled efficiently and asynchronously, without blocking the UI or consuming excessive CPU resources.

# Mesh network

In mesh networking, there are a few choices made. 

## Nodes

Every node has a total of three elements which consist of one button and two lights. The software is made to make the primary element always a generic on-off client with a configuration server and a health server. Additionally, the second and third elements are only generic on-off servers. 

## Provisioning

The provisioner uses the PB-ADV instead of the PB-GATT provisioning protocol. This might change in the future depending on the beacon information and if there is enough time to switch from PB-ADV to PB-GATT.

## Semaphore

For now, there are two semaphores created in the provisioner software. The first one is created for an unprovisioned beacon signal from the provisionee. Also, the second semaphore is used for adding a node to the network. All these semaphores are to make sure there is only one signal at a time.

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

