#ifndef SECURITY_CAMERA_H
#define SECURITY_CAMERA_H

#include "Device.h"
#include <string>

// Derived class for Security Camera devices
class SecurityCamera : public Device {
private:
    string cameraQuality;  // e.g., "720p", "1080p", "4K"
    string power;          // e.g., "mains powered", "battery", "battery+solar"

public:
    SecurityCamera(int id, const string &name, const string &manufacturer,
                   const string &cameraQuality, const string &power);

    // Simulate user interaction with the security camera
    void InteractionEvent() override;

    // Display information about the security camera
    void ViewInfo() override;
};

#endif
