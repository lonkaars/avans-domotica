<div class="docintro">
  <span class="left">
    Pakket van eisen<br/>
    Project Domotica
  </span>
  <span class="right">
    Joshua Regnier <b>(2183008)</b><br/>
    Loek Le Blansch <b>(2180996)</b><br/>
    Niels Stunnebrink <b>(2184532)</b>
  </span>
</div>

# Introduction
node = one node that contains both a button and a LED  
SE = self explanatory 

# Requirements

## Functional requirements
| ID  | Name                          | Description                                       | MoCoW |
| --- | ----------------------------- | ------------------------------------------------- | ----- |
| 01  | 3 Nodes                       | Have atleast 3 or more nodes in the network       | Must  |
| 02  | Button and LED                | Each node has 1 button and 1 LED                  | Must  |
| 09  | Nodes are mesh network        | SE                                                | Must  |
| 10  | Client connection             | Client is connected to both the mesh and internet | Must  |
| 13  | Node sensor/actuator          | A node contains atleast one sensor or actuator    | Must  |
| 14  | Node send/receive other nodes | SE                                                | Must  |

## Technical requirements
| ID  | Name                            | Description                                                           | MoCoW |
| --- | ------------------------------- | --------------------------------------------------------------------- | ----- |
| 03  | Controlling mulitple nodes      | One or more buttons can control one or more LEDs                      | Must  |
| 04  | Simulate node                   | The application can at least simulate 1 button and 1 LED              | Must  |
| 05  | Virtual node                    | The simulated node can interect and be interacted with physical nodes | Must  |
| 06  | Dynamic node (un)registration   | Nodes can dynamically be registered during runtime                    | Could |
| 07  | Nodes can register other nodes  | Nodes can be provisioned by other nodes                               | Could |
| 08  | Smart interface node and client | Wireless conection over BLE or J-link                                 | Could |
| 11  | Monitor and control             | Client can monitor and control mesh network                           | Must  |
| 12  | Groups                          | Nodes (inputs/outputs) can be bound to groups                         | Must  |
| 15  | Nodes can sign (in/out)         | (via Client)                                                          | Must  |
| 16  | Read sensor via mesh network    | SE                                                                    | Must  |
| 17  | Read actuator via mesh network  | SE                                                                    | Must  |
| 18  | Nodes share configuration       | Nodes share configuration over mesh network                           | Must  |
| 19  | Client read and control nodes   | SE                                                                    | Must  |
| 20  | Border router in mesh network   | SE                                                                    | Must  |
| 21  | Client can connect nodes        | SE                                                                    | Must  |
| 22  | Dynamically (dis)connect nodes  | Nodes functionality can be (dis)connected during runtime              | Must  |

## Boundary conditions
| ID  | Name         | Description   | MoCoW |
| --- | ------------ | ------------- | ----- |
| 23  | Git/gitflow  | Mandatory use | Must  |
| 24  | Raspberry PI | SE            | Won’t |
