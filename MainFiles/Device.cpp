#include "Device.h"

Device::Device(int _id, const string &_name, const string &_manufacturer)
    : id(_id), name(_name), manufacturer(_manufacturer), status(false), isConnected(true) { }

Device::~Device() {}

void Device::Activate() {
    status = true;
    cout << name << " activated." << endl;
}

void Device::Deactivate() {
    status = false;
    cout << name << " deactivated." << endl;
}

bool Device::CheckConnection() {
    return isConnected;
}
