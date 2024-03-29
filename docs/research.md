# Bluetooth mesh

One of the most important parts of a domotica system is Bluetooth mesh. So then the fist question arises, what is Bluetooth mesh?

## Mesh

Bluetooth Mesh is a networking standard that operates on a flood network principle. It's based on the nodes relaying the messages. Bluetooth mesh networking enables many-to-many (m:m) device communications and is optimized for creating large-scale device networks. It is ideally suited for control monitoring and automation solutions that require tens, hundreds or thousands of devices to communicate with one another.

### Flood network principle

Flooding is used in computer networks routing algorithm in which every incoming packet is sent through every outgoing link except the one it arrived on.

## Nodes 

A device is named "node" when it is added to a network. A node can contain several components that can be controlled independently of each other. For example, a luminaire can contain several lamps that can be switched on/off independently of each other. The different parts of a "single node" are called elements (figure 1).

![Node mesh network diagram](img/node_mesh_network.png)

### Elements

Some nodes, such as sensors, run off batteries while other nodes, like light fixtures, manufacturing machinery, and security cameras, draw power from the main grid. Some nodes have more processing power than others. These nodes can take on more complex tasks within the mesh network, assuming different roles and possessing any of the following five node features.

Some nodes are more complicated than others and consist of multiple independent parts called elements. Each node has at least one element, known as the primary element, and may have additional elements (Figure 2).

![Node composition](img/node_composition.png)

#### Low power node

Power constrained nodes may use the low-power feature to reduce radio-on time and conserve power. Low-power nodes (LPNs) work in conjunction with friend nodes.

#### Friend node

Nodes without power constraints are great candidates for being friend nodes. Friend nodes store incoming messages and security updates destined for LPNs; when the LPN requests these messages, the friend node delivers the stored information to the LPN.

#### Relay node

Some nodes can act as "relays". However, Relays retransmit messages so that they can travel further, in a number of "hops". These messages get sent to other nodes that are in direct radio range of the publishing node.

#### Proxy node

Proxy nodes enable transmitting and receiving mesh messages between GATT and Bluetooth mesh nodes. Bluetooth low energy devices like smartphones can communicate with a mesh network via a proxy node.

#### Node

This feature has nothing special like the other four. It can communicate and send messages in a mesh network.

#### Models and states

Models define and implement the functionality and behavior of a node while states define the condition of elements. For the models implies the states, messages, state transitions and behaviors. While states define contents of the message. For example, generic on/off state.

There are in total 3 model types a client, server and control type. A server model defines messages the model may transmit/receive and defines the element's behavior given these messages. A client model defines the set of messages used by the client to request, change or consume corresponding states of a server. The control model has the client's and servers functionality.

## Concepts

Bluetooth mesh concepts is an overview of the operation and capabilities of the profile, as well as the life cycle of a mesh device. There are two different applications, the first is Bluetooth mesh and the second one  is Bluetooth low energy (Figure 3).

![Relations and applications](img/relations_applications.png)

For a more detailed understanding of concepts look for link number 11.

## Security

In a Bluetooth mesh network are 3 different types of security, also know as keys. There is a network key also know as NetKey,  application key also know as AppKey and lastly device key know as Devkey. For more reference check number 4 in links, but it is a dutch version so below is a translated version.

### NetKey

All nodes in a mesh network own the network key (NetKey). If a device owns this shared key, it is officially a node and part of a network. The network encryption key and the privacy key are derived from this Netkey. Once in possession of the NetKey, it grants the node access to the network layer. In this network layer it can pass on and perform network functions such as relaying (forwarding packets further in the network). The node cannot yet decrypt application data with the NetKey.
The network can be divided into subnets and each subnet has its own NetKey, which is owned only by the nodes that are members of that subnet. For example, it can be used to isolate specific physical areas, such as each room in a hotel.

### Appkey

Application data for a specific application can only be decrypted by nodes that have the correct application key (AppKey). For example, lighting and light switches have the AppKey of the lighting application, but not the AppKey for the heating system, which is only owned by thermostats, taps on radiators and so on.

AppKeys are used by the upper transport layer to decrypt and authenticate messages before passing them to the access layer. AppKeys are associated with only one NetKey, meaning that specific applications can only run on one specific network.

### DevKey

The last type of key is the device key (DevKey). This is a special type of application key. Each node has a unique DevKey known to the commissioner and no other. The DevKey is used in the commissioning process and is specifically for securing the communication between the commissioner and the node.

## Configuration

For more reference to configurations the links used are numbers 3, 4, 7 and 12.

### Addresses

Messages must be sent to and from an address. Bluetooth mesh defines three types of addresses.

#### Unicast address

During provisioning, a provisioner assigns a unicast address to each element in a node. Unicast addresses can appear in the source address field of a message, the destination address field of a message, or both. Messages sent to unicast addresses are processed by only one element.

#### Group address

Group addresses are types of multicast addresses that represent multiple elements from one or more nodes. Group addresses can be fixed (allocated by Bluetooth SIG) or dynamically assigned.

#### Virtual address

A virtual address represents a set of destination addresses. Each virtual address logically represents a 128-bit label universally unique identifier (UUID). The Bluetooth nodes can publish or subscribe to these addresses.

### Publish and subscribe

Bluetooth mesh networking implements a publish/subscribe message-oriented communication system. Such an approach ensures that different types of products can coexist in a mesh network without being affected by messages from devices they do not need to listen to. The act of sending a message is known as publishing. Based on the configuration, the mesh nodes select messages sent to specific addresses for processing. This technique is known as subscribing. A publisher node sends messages to those nodes that have subscribed to the publisher. Typically, mesh messages are addressed to group or virtual addresses. For example, look at figure 4.

![Publish and subscribe](img/publish_subscribe.png)

### Provisioning

Provisioning is the process by which a Bluetooth device (un-provisioned device) joins the mesh network and becomes a Bluetooth mesh node. This process is controlled by a provisioner. A provisioner and the un-provisioned device follow a fixed procedure as defined in the Bluetooth Mesh Profile [4]. A provisioner is typically a smartphone running a provisioning application. For a more in-depth look at different aspects of provisioning see links number 13.

## Demo

For this demo we are trying to understand the basics behind bluetooth mesh (picture below).

![Demo set-up](img/demo.png)

### Difficulties

There were three difficulties for this demo: making the dongle work, making Bluetooth work on the dongle, and lastly debugging with RTT. The main problem was making the dongle work.

After accidentally removing the bootloader in the dongle, it wasn't working properly. To solve this, a bootloader hex file is needed to erase and write in the dongle with a segger j-link and the nrf connect for desktop programmer. The bootloader will be referenced in GitHub.

To make example `nrf/samples/bluetooth/mesh/light` or `switch` work with the dongle a change is needed in the `.conf` file.

![Dongle configuration](img/bluetooth_dongle_problem.png)

After removing these two lines from the .conf file it will work exactly as you’d expect. For the development kit, it doesn't need to change.

Lastly to make debugging work with the RTT viewer there needs to be configurations added to the .conf file(see below).

![RTT viewer configuration](img/rtt_viewer_conf.png)

# Manual nRF toolchain installation

Installing the nRF toolchain can usually be done through Nordic's [nRF Connect
for
Desktop](https://www.nordicsemi.com/Products/Development-tools/nrf-connect-for-desktop)
application. This program is shipped as an AppImage file for Linux users, and
though AppImage files are supposed to be containerized applications that will
run in any environment, the latest nRF connect application is broken on Arch
Linux as of November 20th 2022.

Nordic also provides [manual installation
instructions](https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/nrf/gs_installing.html)
for generic Linux distro's, but here is a more specific guide for Arch users
(assuming [yay](https://github.com/Jguer/yay) is installed):

```bash
# 1. install the required tools
yay -S cmake python python-pip dtc

# 2. install west
pip3 install --user west
# make sure to add ~/.local/bin to PATH in your shell's startup/environment

# 3. nRF sdk code (change ~/.local/share/ncs if you want to install elsewhere)
mkdir -p ~/.local/share/ncs
cd ~/.local/share/ncs
west init -m https://github.com/nrfconnect/sdk-nrf --mr v2.1.2
west update
west zephyr-export

# 4. install other python dependencies (also in ncs folder)
pip3 install --user -r zephyr/scripts/requirements.txt
pip3 install --user -r nrf/scripts/requirements.txt
pip3 install --user -r bootloader/mcuboot/scripts/requirements.txt

# 5. install a toolchain
yay -S zephyr-sdk

# copy zephyrrc
cp /usr/share/zephyr-sdk/zephyrrc ~/.zephyrrc
```

## Additional notes

- The toolchain installation process takes up a lot of space (around 15G on my
  system, excluding python packages)
- The examples in `ncs/zephyr/samples/` are for any zephyr-compatible boards,
  and require extra configuration before they'll compile without errors. To
  test if you've set up the toolchain correctly, running `west build` in the
  `ncs/nrf/samples/bluetooth/mesh/light/` sample should work

# Async connection
This chapter is focused on the communication between the border router node and the client desktop. The main focus lays on a wired connection over UART(USB).


## UART 

### libuv
[libuv Cross-platform asynchronous I/O](https://github.com/libuv/libuv) is a C library that offers support for TCP & UDP sockets and more as listed on the github. This library is mainly focused on communication-protocols, but does not clearly support a general style of async interrupts.

### libasync
The [libasync](https://github.com/mkschreder/libasync) library offers a way to do asynchronous tasks in C. This library can be useful, but has not been updated for the last 8 years. Furthermore the implementation of UART communication is still required by the user as this library is build for generic tasks and not only communication protocols.

### Qt6
[Qt](https://qt.io/blog/asynchronous-apis-in-qt-6) offers que-able async tasks, see blog for more details. Further more, [Qt](https://doc.qt.io/qt-6/qserialport.html) also directly supports asynchronous reading of an (UART) port. When also taking into account that in this project we are likely to also produce a client application (with Qt) using this build-in Qt feature seems the most logical.

## Bluetooth
In the school provided documentation over bluetooth mesh there is a section which describes possible methods of connecting to a border router, one of these is a configuration that allows a wireless connection over bluetooth. This would require a node to be configured to be on the bluetooth network and no longer on bluetooth mesh. In order to make the bluetooth mesh communicate with the 'normal' bluetooth node it requires set to be a proxy node.

### Qt6
Qt also has support for a cross-platform bluetooth connection, more details about capabilities are stated in the [Qt6 docs](https://doc.qt.io/qt-6/qtbluetooth-index.html).

## Summary
There are multiple ways to connect to the bluetooth mesh border router, mainly: USB, UART or Bluetooth. For any of these options the best implementation for this project will be via Qt6 due to it being highly likely that this will also be the used for the application

# Links

These are the links used for Bluetooth mesh research

1. [Bluetooth mesh order of messaging](https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/nrf/ug_bt_mesh_architecture.html)
2. [Overall information](https://www.bluetooth.com/learn-about-bluetooth/recent-enhancements/mesh/)
3. [What is Bluetooth mesh(Dutch version)](https://www.mokoblue.com/nl/what-is-bluetooth-mesh/)
4. [What is Bluetooth mesh(Dutch version)](https://www.intellicht.org/sturing/draadloos/bluetooth-mesh/)
5. [What is Bluetooth mesh(English)](https://en.wikipedia.org/wiki/Bluetooth_mesh_networking)
6. [Link for everything](https://www.bluetooth.com/bluetooth-resources/bluetooth-mesh-developer-study-guide/)
7. [Easier to understand Bluetooth mesh and example code](https://events19.linuxfoundation.org/wp-content/uploads/2017/12/Bluetooth-Mesh-and-Zephyr-V1.0_Martin-Wooley.pdf)
8. [Zephyr repo](https://github.com/zephyrproject-rtos/zephyr)
9. [Repairing dongle](https://devzone.nordicsemi.com/guides/short-range-guides/b/getting-started/posts/nrf52840-dongle-programming-tutorial)
10. [Repairing dongle](https://devzone.nordicsemi.com/f/nordic-q-a/40924/how-can-i-restore-the-original-bootloader-of-a-pca10059)
11. [Mesh concepts](https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/nrf/ug_bt_mesh_concepts.html#mesh-concepts)
12. [Mesh networking](https://www.mathworks.com/help/bluetooth/ug/bluetooth-mesh-networking.html)
13. [Provision Mesh network](https://www.bluetooth.com/blog/provisioning-a-bluetooth-mesh-network-part-1/)
