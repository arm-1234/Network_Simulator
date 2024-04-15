#include "topology.cpp"
string crcGenerator(string dataStr, string polynomialStr)
{
    // Calculate the number of zeroes to be added to the data
    int k = polynomialStr.size();

    // Append zeroes to the data
    dataStr += string(k - 1, '0');

    // Perform Modulo-2 Division
    for (int i = 0; i < dataStr.size() - (k - 1); ++i)
    {
        if (dataStr[i] == '1')
        {
            for (int j = 0; j < k; ++j)
            {
                dataStr[i + j] = (dataStr[i + j] == polynomialStr[j]) ? '0' : '1';
            }
        }
    }

    // Extract the remainder
    string remainder = dataStr.substr(dataStr.size() - (k - 1));

    // Append the remainder to the original data
    string transmittedData = dataStr.substr(0, dataStr.size() - (k - 1)) + remainder;

    return transmittedData;
}

// CRC checker function (Receiver side)
bool crcChecker(string receivedDataStr, string polynomialStr)
{
    // Perform Modulo-2 Division
    for (int i = 0; i < receivedDataStr.size() - (polynomialStr.size() - 1); ++i)
    {
        if (receivedDataStr[i] == '1')
        {
            for (int j = 0; j < polynomialStr.size(); ++j)
            {
                receivedDataStr[i + j] = (receivedDataStr[i + j] == polynomialStr[j]) ? '0' : '1';
            }
        }
    }

    // Check if the remainder is all zeroes
    for (char bit : receivedDataStr.substr(receivedDataStr.size() - (polynomialStr.size() - 1)))
    {
        if (bit == '1')
        {
            return false; // Data contains errors
        }
    }

    return true; // Data is error-free
}

const int MAX_BACKOFF_ATTEMPTS = 10;
const int MAX_BACKOFF_DELAY_MS = 100;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> dis(0, MAX_BACKOFF_DELAY_MS);

// string data = "Hello, world!";
// handleCollision(sourceDevice, destinationDevice, data);

bool csmacd(EndDevice &sourceDevice, EndDevice &destinationDevice, const string &data)
{
    bool collisionDetected = false;
    int backoffAttempts = 0;

    while (backoffAttempts < MAX_BACKOFF_ATTEMPTS)
    {
        // Carrier sense: Check if the medium is idle
        if (isMediumIdle())
        {
            // Attempt to transmit data
            bool success = sendData(sourceDevice, destinationDevice, data);
            if (success)
            {
                // Transmission successful
                return true;
            }
            else
            {
                // Collision detected during transmission
                collisionDetected = true;
            }
        }

        // If collision detected or medium is busy, perform backoff
        if (collisionDetected || !isMediumIdle())
        {
            int backoffDelay = dis(gen);
            cout << "Collision detected or medium busy. Device " << sourceDevice.mac << " backing off for " << backoffDelay << " ms." << endl;
            this_thread::sleep_for(chrono::milliseconds(backoffDelay));
            backoffAttempts++;
            collisionDetected = false;
        }
    }

    // Maximum backoff attempts reached
    cout << "Failed to transmit data from Device " << sourceDevice.mac << " to Device " << destinationDevice.mac << " after " << MAX_BACKOFF_ATTEMPTS << " attempts." << endl;
    return false;
}

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

// ... (Rest of the code remains the same) ...

// Function to check if the medium is idle
bool isMediumIdle()
{
    // Assuming a star topology with a central hub
    Hub &centralHub = NetworkComponent::componentHubs[0];

    // Check if any device is currently transmitting data to the central hub
    if (centralHub.buffer.empty())
    {
        // No ongoing transmission, the medium is idle
        return true;
    }
    else
    {
        // Transmission in progress, the medium is busy
        return false;
    }
}

// Function to send data and check for collisions
bool sendData(EndDevice &sourceDevice, EndDevice &destinationDevice, const string &data)
{
    // Assuming a star topology with a central hub
    Hub &centralHub = NetworkComponent::componentHubs[0];

    // Send data from the source device to the central hub
    sourceDevice.outBuffer = data;
    centralHub.buffer = data;

    // Broadcast data from the central hub to all connected devices except the sender
    for (auto &device : centralHub.connectedPorts)
    {
        if (device.mac != sourceDevice.mac)
        {
            device.inBuffer = centralHub.buffer;
        }
    }

    // Clear the buffers after successful transmission
    sourceDevice.outBuffer.clear();
    centralHub.buffer.clear();

    // No collision detected in this implementation
    return true;
}

const int TIMEOUT_DURATION = 5000; // Timeout duration in milliseconds

// Simulate data transmission with a probability of corruption
bool transmitData(const string &data)
{
    bool isCorrupted = (rand() % 10 == 0); // 10% probability of corruption
    cout << "Transmitting data: " << data << endl;
    return !isCorrupted;
}

// Simulate data reception and acknowledgment
bool receiveData(const string &data, bool isCorrupted)
{
    if (isCorrupted)
    {
        cout << "Received corrupted data: " << data << endl;
        return false;
    }
    else
    {
        cout << "Received data successfully: " << data << endl;
        cout << "Sending acknowledgment..." << endl;
        return true;
    }
}

// Implement the Stop-and-Wait protocol
void stopAndWait(const string &data)
{
    bool isAcknowledged = false;
    int attempts = 0;
    const int MAX_ATTEMPTS = 5;

    while (!isAcknowledged && attempts < MAX_ATTEMPTS)
    {
        if (transmitData(data))
        {
            // Start timer for acknowledgment
            auto startTime = chrono::steady_clock::now();

            // Wait for acknowledgment
            while (!isAcknowledged)
            {
                isAcknowledged = receiveData(data, false); // Assuming no corruption during acknowledgment

                // Check for timeout
                auto currentTime = chrono::steady_clock::now();
                auto elapsedTime = chrono::duration_cast<chrono::milliseconds>(currentTime - startTime).count();
                if (elapsedTime > TIMEOUT_DURATION)
                {
                    cout << "Timeout occurred. Retransmitting data..." << endl;
                    break;
                }

                // Simulate a delay for acknowledgment
                this_thread::sleep_for(chrono::milliseconds(500));
            }
        }

        attempts++;
    }

    if (isAcknowledged)
    {
        cout << "Data transmission successful." << endl;
    }
    else
    {
        cout << "Data transmission failed after maximum attempts." << endl;
    }
}

// string data = "Hello, World!";
//     stopAndWait(data);