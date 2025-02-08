#include "Device.h"

// Constructor implementation
Device::Device(int _id, const string & _name, const string & _manufacturer)
    : id(_id), name(_name), manufacturer(_manufacturer), status(false) { }

// Virtual destructor
Device::~Device() { }

// Activate the device
void Device::Activate() {
    status = true;
    cout << name << " activated." << endl;
}

// Deactivate the device
void Device::Deactivate() {
    status = false;
    cout << name << " deactivated." << endl;
}
