#include "SecurityCamera.h"
#include <iostream>
using namespace std;

SecurityCamera::SecurityCamera(int id, const string &name, const string &manufacturer,
    const string &cameraQuality, const string &power)
    : Device(id, name, manufacturer), cameraQuality(cameraQuality), power(power) { }

void SecurityCamera::InteractionEvent() {
    if (status) {
        cout << "Now viewing camera: " << name << endl;
    } else {
        cout << "Camera " << name << " is inactive. Please activate first." << endl;
    }
}

void SecurityCamera::ViewInfo() {
    cout << "=============================" << endl;
    cout << "   Security Camera Info      " << endl;
    cout << "=============================" << endl;
    cout << "ID            : " << id << endl;
    cout << "Name          : " << name << endl;
    cout << "Manufacturer  : " << manufacturer << endl;
    cout << "Camera Quality: " << cameraQuality << endl;
    cout << "Power         : " << power << endl;
    cout << "Status        : " << (status ? "Active" : "Inactive") << endl;
    cout << "Connection    : " << (isConnected ? "Connected" : "disconnected") << endl;
    cout << "=============================" << endl;
}
