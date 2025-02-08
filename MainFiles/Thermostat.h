#ifndef THERMOSTAT_H
#define THERMOSTAT_H

#include "Device.h"

// Derived class for Thermostat devices.
class Thermostat : public Device {
private:
    double targetTemperature;  // Target temperature setting.

public:
    Thermostat(int id, const string &name, const string &manufacturer, double targetTemperature);
    void InteractionEvent() override;
    void ViewInfo() override;
};

#endif
