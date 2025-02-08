#ifndef SMART_LIGHT_H
#define SMART_LIGHT_H

#include "Device.h"
#include <string>
using namespace std;

// Derived class for Smart Light devices.
class SmartLight : public Device {
private:
    int brightnessLevel;    // Brightness level (0-100).
    string colourType;      // Colour type (e.g., "RGB", "warm white").

public:
    SmartLight(int id, const string &name, const string &manufacturer, int brightnessLevel, const string &colourType);
    void InteractionEvent() override;
    void ViewInfo() override;
};

#endif
