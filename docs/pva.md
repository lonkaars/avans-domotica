[Trello]: https://trello.com/b/LSiYzM8C/casadomotica

# Backgrounds

## Project

The concept of mesh structure already existed at the beginning of the turn of the millennium. The first step in this is internet standard 802.15.4. This includes both the physical layer and the mac layer.

The protocols evolved in the years that followed. 6LowPan, Zigbee and other implementations were the results. Zigbee has evolved and Thread/OpenThread has been added with major companies supporting it.

Zigbee has been on the market for some time, being used in products such as the Philips HUE and IKEA's Trådfri. The number of products made with OpenThread is more limited. BT mesh applications are still mostly in development.

In the project we use a mesh network to realize a home automation system.

# Project result

## Problem analysis

## Issue

## Objective

## Final result

# Phasing

## Description phases

### Plan

### To demand

### Design

### Manufacture

### Qualification

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
