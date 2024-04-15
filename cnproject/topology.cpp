#include "component.cpp"

// Class representing a star topology network
class StarTopology : public NetworkComponent
{
public:
    Hub centerHub;
    Switch centerSwitch;

    StarTopology()
    {
        setTopology("star");
    }

    void setCenter(Hub &hub)
    {
        centerHub = hub;
    }

    void setCenter(Switch &sw)
    {
        centerSwitch = sw;
    }

    void displayCenterHub()
    {
        cout << "Center Hub MAC: " << centerHub.mac << '\n';
    }

    void displayCenterSwitch()
    {
        cout << "Center Switch MAC: " << centerSwitch.mac << '\n';
    }
};

// Class representing a mesh topology network
class MeshTopology : public NetworkComponent
{
public:
    MeshTopology()
    {
        setTopology("mesh");
    }
};

vector<vector<int>> topologyRepresentation()
{
    if (NetworkComponent::topology == "mesh")
    {
        cout << "mesh topology" << '\n';
        int n = NetworkComponent::componentEndDevices.size();
        vector<vector<int>> adjacencyMatrix(n, vector<int>(n));

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (i == j)
                {
                    adjacencyMatrix[i][j] = 0;
                }
                else
                {
                    // Add port representing connection to device j
                    NetworkComponent::componentEndDevices[i].ports.push_back(NetworkComponent::componentEndDevices[j]);
                    adjacencyMatrix[i][j] = 1;
                }
            }
        }

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < NetworkComponent::componentEndDevices[i].ports.size(); j++)
            {
                cout << "End Device with MAC: " << NetworkComponent::componentEndDevices[i].mac << " connected with " << NetworkComponent::componentEndDevices[i].ports[j].mac << endl;
            }
        }
        return adjacencyMatrix;
    }
    else if (NetworkComponent::topology == "star")
    {
        // Get the number of end devices
        int n = NetworkComponent::componentEndDevices.size();
        cout << "star topology" << '\n';
        // Connect all end devices to the center hub
        for (int i = 0; i < n; ++i)
        {
            // Connect end device i to the center hub (first hub)
            NetworkComponent::componentHubs[0].connectedPorts.push_back(NetworkComponent::componentEndDevices[i]);
        }

        // Print the MAC addresses and port numbers of devices connected to the center hub
        for (int i = 0; i < n; i++)
        {
            cout << "End Device connected to the central hub with MAC address: " << NetworkComponent::componentHubs[0].mac << " is " << NetworkComponent::componentHubs[0].connectedPorts[i].mac;
            cout << " at port number: " << i << endl;
        }
    }

    return {{}};
}

void sendDatastar(EndDevice sourceDevice, EndDevice destinationDevice, string data)
{
    // Simulate sending data from source device to the hub
    cout << "Sending data from End Device " << sourceDevice.mac << " to Center Hub " << NetworkComponent::componentHubs[0].mac << ": " << data << endl;
    NetworkComponent::componentHubs[0].buffer = data;
    cout << "Number of devices connected to the hub: " << NetworkComponent::componentHubs[0].connectedPorts.size() << endl;
    // Simulate broadcasting data from the hub to all connected devices except the sender
    for (auto &device : NetworkComponent::componentHubs[0].connectedPorts)
    {
        if (device.mac != sourceDevice.mac) // Exclude the sender device
        {
            device.inBuffer = NetworkComponent::componentHubs[0].buffer;
            cout << "Receiving data at End Device " << device.mac << " from Center Hub " << NetworkComponent::componentHubs[0].mac << ": " << device.inBuffer << endl;
        }
    }
}

void sendDataMesh(EndDevice sourceDevice, EndDevice destinationDevice, string data)
{
    // Simulate sending data from Device A to Device B
    cout << "Sending data from Device " << sourceDevice.mac << " to Device " << destinationDevice.mac << ": " << data << endl;

    // Find the port on the source device that is connected to the destination device
    int sourcePortIndex = -1;
    for (int i = 0; i < NetworkComponent::componentEndDevices.size(); ++i)
    {
        if (NetworkComponent::componentEndDevices[i].mac == sourceDevice.mac)
        {
            sourcePortIndex = i;
            break;
        }
    }

    // If the source device is not found, exit the function
    if (sourcePortIndex == -1)
    {
        cout << "Error: Source device not found." << endl;
        return;
    }

    // Find the port on the source device connected to the destination device
    int destinationPortIndex = -1;
    for (int i = 0; i < NetworkComponent::componentEndDevices[sourcePortIndex].ports.size(); ++i)
    {
        if (NetworkComponent::componentEndDevices[sourcePortIndex].ports[i].mac == destinationDevice.mac)
        {
            destinationPortIndex = i;
            // Store the data in the input buffer of the destination device
            NetworkComponent::componentEndDevices[sourcePortIndex].ports[destinationPortIndex].inBuffer = data;
            break;
        }
    }

    // If the destination device is not found, exit the function
    if (destinationPortIndex == -1)
    {
        cout << "Error: Destination device not found on the specified port." << endl;
        return;
    }

    // Print the port number of the destination device inside the source device
    cout << "Port number of output Device " << destinationDevice.mac << " in source Device " << sourceDevice.mac << " is " << destinationPortIndex << endl;
    cout << "Data stored in the input buffer of Device " << destinationDevice.mac << " is " << NetworkComponent::componentEndDevices[sourcePortIndex].ports[destinationPortIndex].inBuffer << endl;
}
