#ifndef SMART_LIGHT_H
#define SMART_LIGHT_H

#include "Device.h"
#include <string>
using namespace std;

// Derived class for Smart Light devices
class SmartLight : public Device {
private:
    int brightnessLevel;    // Brightness level (0-100)
    string colourType;      // e.g., "warm white", "cool white", "RGB"

public:
    SmartLight(int id, const string &name, const string &manufacturer, int brightnessLevel, const string &colourType);

    // Allow the user to set brightness and (if applicable) change the colour
    void InteractionEvent() override;

    // Display information about the smart light
    void ViewInfo() override;
};

#endif
