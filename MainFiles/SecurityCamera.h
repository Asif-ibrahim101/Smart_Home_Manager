#ifndef SECURITY_CAMERA_H
#define SECURITY_CAMERA_H

#include "Device.h"
#include <string>

// Derived class for Security Camera devices.
class SecurityCamera : public Device {
private:
    string cameraQuality;  // e.g., "1080p", "4K"
    string power;          // e.g., "battery", "mains powered"

public:
    SecurityCamera(int id, const string &name, const string &manufacturer,
                   const string &cameraQuality, const string &power);
                   
    void InteractionEvent() override;
    void ViewInfo() override;
};

#endif
