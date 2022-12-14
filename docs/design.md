# QT Serial port communication (joshua)
# General system architecture (loek)
# Custom serial protocol (loek)


# Mesh network
In mesh networking, there are a few choices made. 

## Nodes
Every node has a total of three elements which consist of one button and two lights. The software is made to make the primary element always a generic on-off client with a configuration server and a health server. Additionally, the second and third elements are only generic on-off servers. 

## Provisioning
The provisioner uses the PB-ADV instead of the PB-GATT provisioning protocol. This might change in the future depending on the beacon information and if there is enough time to switch from PB-ADV to PB-GATT.

## Semaphore
For now, there are two semaphores created in the provisioner software. The first one is created for an unprovisioned beacon signal from the provisionee. Also, the second semaphore is used for adding a node to the network. All these semaphores are to make sure there is only one signal at a time.

# Used software and library versions ()

## Niels
* Visual studio code (1.73.1)
* Zephyr (3.2.99)
* nRf Connect SDK (v2.1.2)
* PuTTY (Release 0.78)


