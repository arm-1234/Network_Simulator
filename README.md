#  Network_Simulator
# Introduction
This project is a network simulation tool developed in C++. It features various components such as end devices, hubs, and switches, and can simulate network configurations like star and mesh topologies.

Git Repository
The source code for this project is available on Github.

# Codes
The project comprises 4 files:

component.cpp
topology.cpp
protocol.cpp
main.cpp
# To run the simulator:

Open main.cpp.
Create end devices, hubs, and switches as required.
Add them to the network component.
Choose the desired topology.
Start data transmission.
Check error control using CRC.
Implement access control using CSMA.
Use the Stop-and-Wait sliding window protocol.
#  Network Topology
The simulator supports two network topologies: star and mesh. In a star topology, all end devices are connected to a central hub. In a mesh topology, each end device is connected to every other device.

# Data Transmission Protocols
CSMA/CD (Carrier Sense Multiple Access with Collision Detection) is a protocol employed to manage collisions in shared media networks.
