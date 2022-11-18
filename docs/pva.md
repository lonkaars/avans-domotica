[Trello]: https://trello.com/b/LSiYzM8C/casadomotica

# Backgrounds

## Project

The concept of mesh structure already existed at the beginning of the turn of the millennium. The first step in this is internet standard 802.15.4. This includes both the physical layer and the mac layer.

The protocols evolved in the years that followed. 6LowPan, Zigbee and other implementations were the results. Zigbee has evolved and Thread/OpenThread has been added with major companies supporting it.

Zigbee has been on the market for some time, being used in products such as the Philips HUE and IKEA's Trådfri. The number of products made with OpenThread is more limited. BT mesh applications are still mostly in development.

In the project we use a mesh network to realize a home automation system.

# Project result
In year 2 of avans hogeschool blok 2 is the project is domitica. With this project we are going to realise a domotica system using bluetooth mesh.
## Problem analysis
Most household don't have a domitica system. The ligtswitches turn the light on by a physical connection and can only do that, But with a domitica system this can by solved.
## Issue
The question arises, why there isn't more households that uses a domotica system? The answer to that question is, The system is for most people confusing, But with the right explenation and easy-to-use can everyone have a domotica system in their household.
## Objective
Our objective is to make a working domotica system with the use of bluetooth mesh. the system consists of minimal three sensors and three lights that comminicate in a mesh network. This can then by implemented in a household.
## Final result
With our domotica system that is user friendly and easy-to-use everybody can make their house a domotica system
# Phasing
For project casaDomitica are we using scrum as our tool for planning.

## Description phases
There are different steps were taking for this project. The first step is Plan van Aanpak also know as Plan. Then were describing the requirements. After the requirments comes our sprints. there are a total of three sprints were doing this project.


### Plan
For the planning and our actions see our trello bord with this link.

### Requirements


### Sprint 1
In this sprint were mostly doing research about different subjects of domitca. Additionally, are we testing the different subjects to further understand domitca. For exaample, researching and testing bluetooth mesh.

### Sprint 2
In this sprint were using the knowlodge of sprint 1 to start building our domitica system. Also, if further research is needed this sprint can be used for this.

### Sprint 3
In this Sprint were finishing the domitca system if finishing is needed. Most of the time is needed for testig and debugging.

# Quality

## Quality of product

- The mesh network once established is stable, and packets can be sent and received reliably (>95% of the time).
- Actions within the network should be propagated after less than 500ms.

## Quality of documentation

- Source code usage is documented using doxygen-style comments in the header files, describing usage, call signature and optionally edge cases, example usage and/or other details.
- Obscure or ambiguous syntax usage is explained using line comments in source files.
- General software architecture will be documented in following design documents.
- Design documents will be proofread by peers to verify if the explanation is comprehensible.

# Confidentiality
This project is MIT licensed.
# Project organization

## Organization

This project has three main roles: developer, integrator and scrummaster. In the following section, a fourth role "Project owner" is also included for completeness. Because the project owner is not involved during project development, "all" roles in the following sections refers to only the main three.

## Roles and personal details

| Name   | Role                                |
| ------ | ----------------------------------- |
| Joan   | Project owner                       |
| Joshua | Developer                           |
| Loek   | Integrator, scrummaster & developer | 
| Niels  | Developer                           |

## Information

While the roles in the table above describe a hierarchial system, all planning and architecture decisions are made democratically.

### Developer
- Research (during sprint 1)
- Implement user stories in code
- Send pull requests to integrators

### Integrator
- Merge pull requests
- Version tagging
- Verification

### Scrummaster
- Track and manage project progress
- Create user stories

# Schedule

As mentioned before, we're using Trello for managing a scrum-based planning. The user stories are scheduled a week before the sprint assessment by default. For a detailed up-to-date version of the schedule, see [Trello].

# Project boundaries
The project has a few bounderies. The minimal requirements is that is works with three switches and three lights. Therefore using our domitica system for relaying numeric values is not possible, for now atleast. additionally, it is an domotica system which means it cannot be used in a industrial environment. And the last bounderie, Is the system needs to use our GUI and does not work with other GUI.
# Cost-benefit

## Risks

### Technical risks

### Project management risks

### Measures

