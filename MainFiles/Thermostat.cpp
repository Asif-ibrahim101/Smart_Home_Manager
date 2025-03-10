#include "Thermostat.h"
#include <iostream>
using namespace std;

Thermostat::Thermostat(int id, const string &name, const string &manufacturer, double targetTemperature)
    : Device(id, name, manufacturer), targetTemperature(targetTemperature) { }

void Thermostat::InteractionEvent() {
    if (status) {
        cout << "Current target temperature for " << name << " is " << targetTemperature << "C." << endl;
        cout << "Enter new target temperature: ";
        double newTemp;
        cin >> newTemp;
        targetTemperature = newTemp;
        cout << "Target temperature updated to " << targetTemperature << "°C." << endl;
    } else {
        cout << "Thermostat " << name << " is inactive. Please activate first." << endl;
    }
}

void Thermostat::ViewInfo() {
    cout << "=============================" << endl;
    cout << "      Thermostat Info        " << endl;
    cout << "=============================" << endl;
    cout << "ID            : " << id << endl;
    cout << "Name          : " << name << endl;
    cout << "Manufacturer  : " << manufacturer << endl;
    cout << "-----------------------------" << endl;
    cout << "Target Temp   : " << targetTemperature << "°C" << endl;
    cout << "Status        : " << (status ? "Active" : "Inactive") << endl;
    cout << "Connection    : " << (isConnected ? "Connected" : "disconnected") << endl;
    cout << "=============================" << endl;
}
