#include "Device.h"

Device::Device(int _id, const string &_name, const string &_manufacturer)
    : id(_id), name(_name), manufacturer(_manufacturer), status(false), isConnected(false) { }

Device::~Device() {}

void Device::Activate() {
    status = true;
    isConnected = true;
    cout << name << " activated and connected" << endl;
}

void Device::Deactivate() {
    status = false;
    isConnected = false;
    cout << name << " deactivated and disconnected" << endl;
}

bool Device::CheckConnection() {
    return isConnected;
}
