// importing all the classses
#include "SecurityCamera.h"
#include "Thermostat.h"
#include "SmartSpeaker.h"
#include "SmartLight.h"


#include <iostream>
#include <vector>
#include <math.h>
#include <memory> //useing for smart pointers
using namespace std;

// Displaying the main menu
void displayMainMenu() {
    cout << "\n--- Smart Home Automation Manager ---\n";
    cout << "1. Activate all devices\n";
    cout << "2. Deactivate all devices\n";
    cout << "3. Interaction event for all devices\n";
    cout << "4. View info for all devices\n";
    cout << "5. Individual device operations\n";
    cout << "6. Add new device\n";
    cout << "7. Edit an existing device\n";
    cout << "8. Delete a device\n";
    cout << "9. View devices by connection status\n";
    cout << "10. Exit\n";
    cout << "Enter your choice: ";
}


// function to display the indivisual infos
void displayIndividualMenu() {
    cout << "\n--- Individual Device Operations ---\n";
    cout << "1. Activate device\n";
    cout << "2. Deactivate device\n";
    cout << "3. Interaction event\n";
    cout << "4. View device info\n";
    cout << "Enter your choice: ";
};

// the main function
int main() {
    vector<unique_ptr<Device>> devices;

    // Allocating all the devicess on a Heap memory
    devices.push_back(unique_ptr<Device>(new SecurityCamera(1, "Cam1", "CamCorp", "1080p", "battery")));
    devices.push_back(unique_ptr<Device>(new Thermostat(2, "Thermo1", "HeatTech", 22.5)));
    devices.push_back(unique_ptr<Device>(new SmartSpeaker(3, "Speaker1", "SoundInc", 50)));
    devices.push_back(unique_ptr<Device>(new SmartLight(4, "Light1", "BrightCo", 75, "RGB")));

    // Choose
    int Choice;
    
    // crating a base case
    bool running = true;

    // Main loop for the interface
    while (running) {
        displayMainMenu();
        cin >> Choice;

        switch (Choice) {
            case 1:
                // Activate all devices
                for (auto &device : devices)
                    device->Activate();
                break;
            case 2:
                // Deactivate all devices
                for (auto &device : devices)
                    device->Deactivate();
                break;
            case 3:
                // Call InteractionEvent for all devices
                for (auto &device : devices)
                    device->InteractionEvent();
                break;
            case 4:
                // Call ViewInfo for all devices
                for (auto &device : devices) {
                    device->ViewInfo();
                    cout << "---------------------" << endl;
                }
                break;
            case 5:
                // Exit the program
                running = false;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    };
    
        cout << "Program terminated. Goodbye!" << endl;
        return 0;
    

}