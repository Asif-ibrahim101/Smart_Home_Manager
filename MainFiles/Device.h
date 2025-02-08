#ifndef DEVICE_H
#define DEVICE_H

#include <string>
#include <iostream>
using namespace std;

// Base class for all devices.
class Device {
protected:
    int id;                     // Unique identifier for the device.
    string name;                // Device name.
    string manufacturer;        // Manufacturer name.
    bool status;                // Activation status: false = inactive, true = active.
    bool isConnected;           // Connection status (simulated).

public:
    // Constructor initializes id, name, manufacturer, sets status to false and isConnected to true.
    Device(int id, const string &name, const string &manufacturer);
    virtual ~Device();

    // Activate and deactivate the device.
    void Activate();
    void Deactivate();

    // Check connection status.
    bool CheckConnection();

    // Pure virtual methods for device-specific behavior.
    virtual void InteractionEvent() = 0;
    virtual void ViewInfo() = 0;

    // Setter methods for editing device attributes.
    void SetName(const string &newName) { name = newName; }
    void SetManufacturer(const string &newManufacturer) { manufacturer = newManufacturer; }
};

#endif
