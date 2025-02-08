#ifndef SMART_SPEAKER_H
#define SMART_SPEAKER_H

#include "Device.h"

// Derived class for Smart Speaker devices
class SmartSpeaker : public Device {
private:
    int volumeLevel;  // Volume level (0-100)

public:
    SmartSpeaker(int id, const string &name, const string &manufacturer, int volumeLevel);

    // Allow the user to set the volume level via interaction
    void InteractionEvent() override;

    // Display information about the smart speaker
    void ViewInfo() override;
};

#endif
