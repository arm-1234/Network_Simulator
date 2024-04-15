# Network_Simulator
Introduction
This project is a network simulation tool made with C++. It has different components like end devices, hubs, and
switches, and can simulate network setups like star and mesh.
Git Repository
The project’s source code is available on Github.
Codes
The project consists of 4 files:
• component.cpp
• topology.cpp
• protocol.cpp
• main.cpp
To run the simulator:
1. Open main.cpp.
2. Create end devices, hubs, and switches as needed.
3. Add them to the network component.
4. Select the desired topology.
5. Initiate data transmission.
6. Verify error control using CRC.
7. Implement access control using CSMA
8. Stop-and-Wait sliding window protocol.
Network Topology
The simulator supports two network topologies: star and mesh. In a star topology, all end devices connect to a
central hub. In a mesh topology, each end device connects to every other device.
Data Transmission Protocols
CSMA/CD (Carrier Sense Multiple Access with Collision Detection) is a protocol used to manage collisions in
shared media networks.
