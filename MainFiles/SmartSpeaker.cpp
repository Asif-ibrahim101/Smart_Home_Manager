#include "SmartSpeaker.h"
#include <iostream>
using namespace std;

SmartSpeaker::SmartSpeaker(int id, const string &name, const string &manufacturer, int volumeLevel)
    : Device(id, name, manufacturer), volumeLevel(volumeLevel) { }

void SmartSpeaker::InteractionEvent() {
    if (status) {
        cout << "Current volume for " << name << " is " << volumeLevel << "." << endl;
        cout << "Enter new volume level (0-100): ";
        int newVolume;
        cin >> newVolume;
        if (newVolume < 0 || newVolume > 100) {
            cout << "Invalid volume level. Please enter a value between 0 and 100." << endl;
        } else {
            volumeLevel = newVolume;
            cout << "Volume updated to " << volumeLevel << "." << endl;
        }
    } else {
        cout << "Smart Speaker " << name << " is inactive. Please activate first." << endl;
    }
}

void SmartSpeaker::ViewInfo() {
    cout << "Smart Speaker Info:" << endl;
    cout << "ID: " << id << ", Name: " << name << ", Manufacturer: " << manufacturer << endl;
    cout << "Volume Level: " << volumeLevel << endl;
    cout << "Status: " << (status ? "Active" : "Inactive") << endl;
}
