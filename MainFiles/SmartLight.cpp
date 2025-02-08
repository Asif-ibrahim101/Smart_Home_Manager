#include "SmartLight.h"
#include <iostream>
using namespace std;

SmartLight::SmartLight(int id, const string &name, const string &manufacturer, int brightnessLevel, const string &colourType)
    : Device(id, name, manufacturer), brightnessLevel(brightnessLevel), colourType(colourType) { }

void SmartLight::InteractionEvent() {
    if (status) {
        cout << "Current brightness for " << name << " is " << brightnessLevel << "." << endl;
        cout << "Enter new brightness level (0-100): ";
        int newBrightness;
        cin >> newBrightness;
        if (newBrightness < 0 || newBrightness > 100) {
            cout << "Invalid brightness level. Please enter a value between 0 and 100." << endl;
        } else {
            brightnessLevel = newBrightness;
            cout << "Brightness updated to " << brightnessLevel << "." << endl;
        }
        // If the device supports RGB, allow colour change.
        if (colourType == "RGB") {
            cout << "Current colour: " << colourType << endl;
            cout << "Enter new colour description (e.g., Red, Blue, etc.): ";
            string newColour;
            cin >> newColour;
            colourType = newColour;
            cout << "Colour updated to " << colourType << "." << endl;
        }
    } else {
        cout << "Smart Light " << name << " is inactive. Please activate first." << endl;
    }
}

void SmartLight::ViewInfo() {
    cout << "Smart Light Info:" << endl;
    cout << "ID: " << id << ", Name: " << name << ", Manufacturer: " << manufacturer << endl;
    cout << "Brightness Level: " << brightnessLevel << ", Colour Type: " << colourType << endl;
    cout << "Status: " << (status ? "Active" : "Inactive") << endl;
}
