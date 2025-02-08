#include "Thermostat.h"
#include <iostream>
using namespace std;

Thermostat::Thermostat(int id, const string &name, const string &manufacturer, double targetTemperature)
    : Device(id, name, manufacturer), targetTemperature(targetTemperature) { }

void Thermostat::InteractionEvent() {
    if (status) {
        cout << "Current target temperature for " << name << " is " << targetTemperature << "°C." << endl;
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
    cout << "Thermostat Info:" << endl;
    cout << "ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Manufacturer: " << manufacturer << endl;
    cout << "Target Temperature: " << targetTemperature << "°C" << endl;
    cout << "Status: " << (status ? "Active" : "Inactive") << endl;
}
