# Bluetooth mesh
One of the most important parts of a domotica system is bluetooth mesh. So then the fist question arises, what is bluetooth mesh?

## Mesh
Bluetooth Mesh is a networking standard that operates on a flood network principle. It's based on the nodes relaying the messages. Bluetooth mesh networking enables many-to-many (m:m) device communications and is optimized for creating large-scale device networks. It is ideally suited for control monitoring and automation solutions that require tens, hundreds or thousands of devices to communicate with one another.

### flood network principle
Flooding is used in computer networks routing algorithm in which every incoming packet is sent through every outgoing link except the one it arrived on.

## Nodes 
A device is named "node" when it is added to a network. A node can contain several components that can be controlled independently of each other. For example, a luminaire can contain several lamps that can be switched on/off independently of each other. The different parts of a "single node" are called elements (figure 1).

![](/img/nodeMeshNetwork.PNG)

### Elements.
Some nodes, such as sensors, run off batteries while other nodes, like light fixtures, manufacturing machinery, and security cameras, draw power from the main grid. Some nodes have more processing power than others. These nodes can take on more complex tasks within the mesh network, assuming different roles and possessing any of the following five node features.

Some nodes are more complicated than others and consist of multiple independent parts called elements. Each node has at least one element, known as the primary element, and may have additional elements (Figure 2).
![Figure 2](/img/nodeCompesition.PNG "Figure 2")

#### Low power node
Power constrained nodes may use the low-power feature to reduce radio-on time and conserve power. Low-power nodes (LPNs) work in conjunction with friend nodes.
#### Friend node
Nodes without power constraints are great candidates for being friend nodes. Friend nodes store incoming messages and security updates destined for LPNs; when the LPN requests these messages, the friend node delivers the stored information to the LPN.
#### Relay node
Some nodes can act as “relays”. however Relays retransmit messages so that they
can travel further, in a number of “hops”. These messages get sent to other nodes that are in dierct radio tange of the publishing node.
#### Proxy node
Proxy nodes enable transmitting and receiving mesh messages between GATT and Bluetooth mesh nodes. Bluetooth low energy devices like smartphones can communicate with a mesh network via a proxy node.
#### Node
This feature has nothing special like the other four. It can communicate and send messages in a mesh network.



#### Models and states
Models define and implement the functionality and behavior of a node while states define the condition of elements. For the models implies the states, messages, state transistions and behaviors. while states define contents of the message. For example, generic on/off state.

There are in total 3 model types a client, server and control type. A server model defines messages the model may transmit/receive and defines the element’s behavior given these messages. A client model defines the set of messages used by the client to request, change or consume corresponding states of a server. The control model has the client's and servers functionality.

## Concepts
Bluetooth mesh concepts is an overview of the operation and capabilities of the profile, as well as the life cycle of a mesh device. There are two different applications, the first is Bluetooth mesh and the second one  is bluetooth low energy (Figure 3).
![Figure 3](/img/relationsApplications.PNG)

For a more detailed understanding of concepts look for link number 11.


## Configuration

## Security

## Demo

# Links
These are the links used for bluetooth mesh research
1. [bluetooth mesh order of messagaging:](https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/nrf/ug_bt_mesh_architecture.html)
2. [overall information:](https://www.bluetooth.com/learn-about-bluetooth/recent-enhancements/mesh/)
3. [what is bluetooth mesh(dutch version):](https://www.mokoblue.com/nl/what-is-bluetooth-mesh/)
4. [what is bluetooth mesh(dutch version):](https://www.intellicht.org/sturing/draadloos/bluetooth-mesh/)
5. [what is bluetooth mesh(english):](https://en.wikipedia.org/wiki/Bluetooth_mesh_networking)
6. [link for everything:](https://www.bluetooth.com/bluetooth-resources/bluetooth-mesh-developer-study-guide/)
7. [easier to understand bluetooth mesh and example code:](https://events19.linuxfoundation.org/wp-content/uploads/2017/12/Bluetooth-Mesh-and-Zephyr-V1.0_Martin-Wooley.pdf)
8. [zephyr repo:](https://github.com/zephyrproject-rtos/zephyr)
9. [repairing dongle:](https://devzone.nordicsemi.com/guides/short-range-guides/b/getting-started/posts/nrf52840-dongle-programming-tutorial)
10. [repairing dongle:](https://devzone.nordicsemi.com/f/nordic-q-a/40924/how-can-i-restore-the-original-bootloader-of-a-pca10059)
11. [Mesh concepts](https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/nrf/ug_bt_mesh_concepts.html#mesh-concepts)