# project domotica

still WIP

## terminology

|verb/acronym|description|
|-|-|
|dongle|USB stick with a nRF52833 or nRF52840 module|
|bts|Border Transport Server|
|node|A dongle running in node mode|
|border router|A dongle running in border router mode|

## architecture

<div align="center">
  <img src="assets/fig-architecture.svg"/>
</div>

Above is a draft version of the system architecture.

- Each node runs the same firmware, and is capable of being a border router.
- Each dongle starts in "node mode" by default, and only turns into border
  router mode once it receives a special command over the USB serial bus.
- A node can turn into a border router, but will still keep functioning as a
  normal node as well.
- All blocks in the desktop computer zone can be run on different computers
  over the network.
- The BTS creates a TCP socket which sends data to the client on incoming
  events from the mesh network, and broadcasts any data received from the
  client back to the mesh network.
- The configuration UI / action handler server sends and receives events
  to/from the TCP socket API, and will decide which actions should be taken for
  each event.
- The protocol used for communicating between network nodes is preferably in a
  binary format to save on bandwidth.
- The protocol used by the TCP socket API is text-based, as it's used to
  communicate between userspace services on desktop computers.
- Each node sends a button event to the border router when it's button is
  pressed.
- Each node sets it's LED's status upon receiving an LED event.
- Each node has it's own ID (this is probably going to be it's bluetooth MAC
  address for simplicity).

