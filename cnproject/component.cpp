#include <bits/stdc++.h>
using namespace std;

// Function to generate a random MAC address
string generateRandomMac()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, 255);

    std::stringstream ss;
    for (int i = 0; i < 6; i++)
    {
        if (i > 0)
            ss << ":";
        ss << std::hex << std::setw(2) << std::setfill('0') << dis(gen);
    }
    return ss.str();
}

// Class representing an end device
class EndDevice
{
public:
    string mac;
    string name = "0";
    string inBuffer;
    string outBuffer;
    vector<EndDevice> ports;

    EndDevice()
    {
        this->mac = generateRandomMac();
    }

    EndDevice(string name)
    {
        this->name = name;
        this->mac = generateRandomMac();
    }
};

// Class representing a hub
class Hub
{
public:
    vector<EndDevice> connectedPorts;
    string mac;
    string name = "0";
    string buffer;

    Hub(string name)
    {
        this->name = name;
        this->mac = generateRandomMac();
    }

    Hub()
    {
        this->mac = generateRandomMac();
    }
};

// Class representing a switch
class Switch
{
public:
    string mac;
    string name = "0";
    string buffer;
    static unordered_map<string, int> switchingTable;

    Switch()
    {
        this->mac = generateRandomMac();
    }

    Switch(string name)
    {
        this->name = name;
        this->mac = generateRandomMac();
    }
    void switchtableentry(EndDevice a)
    {
        int n = switchingTable.size();
        switchingTable[a.mac] = n + 1;
    }
    void printTable()
    {
        cout << "Switching Table:" << endl;
        cout << "================" << endl;
        cout << "MAC Address\t|\tPort Number" << endl;
        cout << "----------------|----------------" << endl;
        for (auto entry : switchingTable)
        {
            cout << entry.first << "\t|\t" << entry.second << endl;
        }
    }
};

unordered_map<string, int> Switch::switchingTable;

// Class representing the network component
class NetworkComponent
{
public:
    static vector<Hub> componentHubs;
    static vector<Switch> componentSwitches;
    static vector<EndDevice> componentEndDevices;
    static string topology;

    // Function to add a hub to the network component
    void addHub(Hub hub)
    {
        NetworkComponent::componentHubs.push_back(hub);
    }

    // Function to add a switch to the network component
    void addSwitch(Switch s)
    {
        NetworkComponent::componentSwitches.push_back(s);
    }

    // Function to add an end device to the network component
    void addEndDevice(EndDevice endDevice)
    {
        NetworkComponent::componentEndDevices.push_back(endDevice);
    }

    // Function to set the topology of the network component
    void setTopology(string t)
    {
        NetworkComponent::topology = t;
    }

    // Function to display data about network components
    void displayData()
    {
        for (auto endDevice : NetworkComponent::componentEndDevices)
            cout << "End Device with MAC: " << endDevice.mac << '\n';
        for (auto hub : NetworkComponent::componentHubs)
            cout << "Hub with MAC: " << hub.mac << '\n';
        for (auto s : NetworkComponent::componentSwitches)
            cout << "Switch with MAC: " << s.mac << '\n';
    }
};

vector<Hub> NetworkComponent::componentHubs;
vector<Switch> NetworkComponent::componentSwitches;
vector<EndDevice> NetworkComponent::componentEndDevices;
string NetworkComponent::topology;
