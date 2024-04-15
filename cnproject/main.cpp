#include "protocol.cpp"

int main()
{
  NetworkComponent network;
  //  StarTopology starTopology;
  Hub hubDevice;
  // starTopology.setCenter(hubDevice);
  // MeshTopology obj;
  EndDevice endDevice0("End Device 1");
  EndDevice endDevice1("End Device 2");
  EndDevice endDevice2("End Device 3");
  EndDevice endDevice3("End ice 3");
  EndDevice endDevice4("End Deve 3");
  Switch s1("switch1");
  s1.switchtableentry(endDevice0);
  s1.switchtableentry(endDevice1);
  s1.switchtableentry(endDevice2);
  s1.switchtableentry(endDevice3);
  s1.switchtableentry(endDevice4);
  network.addEndDevice(endDevice1);
  network.addEndDevice(endDevice2);
  network.addEndDevice(endDevice0);
  network.addEndDevice(endDevice3);
  network.addEndDevice(endDevice4);
  network.addHub(hubDevice);
  network.addSwitch(s1);
  s1.printTable();
  // network.displayData();
  //    vector<vector<int>> adjacencyMatrix = network.topologyRepresentation();
  // topologyRepresentation();
  // sendDatastar(endDevice1, endDevice3, "Hello Center Hub!");
  // sendDatastar(endDevice1, endDevice2, "Hello mesh king");
}
