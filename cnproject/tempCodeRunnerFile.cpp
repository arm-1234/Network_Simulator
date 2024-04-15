#include "topology.cpp"

int main()
{   
    NetworkComponent network;
    StarTopology starTopology;
    Hub hubDevice;
    starTopology.setCenter(hubDevice);
    
    EndDevice endDevice1("End Device 1");
    EndDevice endDevice2("End Device 2");
    EndDevice endDevice3("End Device 3");

    network.addEndDevice(endDevice1);
    network.addEndDevice(endDevice2);
    network.addEndDevice(endDevice3);
    network.addHub(hubDevice);
     network.displayData();
      vector<vector<int>> adjacencyMatrix = network.topologyRepresentation();
       starTopology.sendData(endDevice1, endDevice3, "Hello Center Hub!");
}
