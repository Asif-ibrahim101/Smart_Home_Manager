#ifndef DEVICE_H
#define DEVICE_H

#include <string>
#include <iostream>
using namespace std;

// Base class for all devices
class Device {
protected:
    int id;                    // Unique identifier for the device
    string name;               // Device name
    string manufacturer;       // Manufacturer name
    bool status;               // Activation status: false = inactive, true = active

public:
    // Constructor: initializes id, name, manufacturer and sets status to inactive.
    Device(int id, const string &name, const string &manufacturer);

    // Virtual destructor
    virtual ~Device();

    // Activate the device (sets status to true)
    void Activate();

    // Deactivate the device (sets status to false)
    void Deactivate();

    // Pure virtual function to simulate user interaction
    virtual void InteractionEvent() = 0;

    // Pure virtual function to display device information
    virtual void ViewInfo() = 0;
};

#endif