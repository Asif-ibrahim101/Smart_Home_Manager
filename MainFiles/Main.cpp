// Importing all the necessary classes
#include "SecurityCamera.h"
#include "Thermostat.h"
#include "SmartSpeaker.h"
#include "SmartLight.h"

#include <iostream>
#include <vector>
#include <math.h>
#include <memory> // Using for smart pointers
using namespace std;

// Function to display the main menu
void displayMainMenu()
{
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

// Function to display the individual device operations menu
void displayIndividualMenu()
{
    cout << "\n--- Individual Device Operations ---\n";
    cout << "1. Activate device\n";
    cout << "2. Deactivate device\n";
    cout << "3. Interaction event\n";
    cout << "4. View device info\n";
    cout << "Enter your choice: ";
}

// Function to list all devices with their information
void listDevices(const vector<unique_ptr<Device>> &devices)
{
    cout << "\n--- Device List ---\n";
    for (size_t i = 0; i < devices.size(); i++)
    {
        cout << i + 1 << ".\n";
        devices[i]->ViewInfo();
        cout << "---------------------\n";
    }
}

// Main function
int main()
{
    vector<unique_ptr<Device>> devices;

    // Allocating all devices on the heap memory
    // Not using make_unique because of compiler limitations
    devices.push_back(unique_ptr<Device>(new SecurityCamera(1, "Cam1", "CamCorp", "1080p", "battery")));
    devices.push_back(unique_ptr<Device>(new Thermostat(2, "Thermo1", "HeatTech", 22.5)));
    devices.push_back(unique_ptr<Device>(new SmartSpeaker(3, "Speaker1", "SoundInc", 50)));
    devices.push_back(unique_ptr<Device>(new SmartLight(4, "Light1", "BrightCo", 75, "RGB")));

    int choice; // Variable to store user choice
    bool running = true; // Flag to control the main loop

    // Main loop for the interface
    while (running)
    {
        displayMainMenu();
        cin >> choice;

        switch (choice)
        {
        case 1: // Activate all devices
            for (auto &device : devices)
                device->Activate();
            break;

        case 2: // Deactivate all devices
            for (auto &device : devices)
                device->Deactivate();
            break;

        case 3: // Trigger interaction event for all devices
            for (auto &device : devices)
                device->InteractionEvent();
            break;

        case 4: // View info for all devices
            for (auto &device : devices)
            {
                device->ViewInfo();
                cout << "---------------------\n";
            }
            break;

        case 5: // Individual device operations
        {
            listDevices(devices);
            cout << "Select device number: ";
            int devNum;
            cin >> devNum;

            if (devNum < 1 || devNum > devices.size())
            {
                cout << "Invalid device number.\n";
                break;
            }

            auto &selectedDevice = devices[devNum - 1];
            displayIndividualMenu();

            int subChoice;
            cin >> subChoice;

            switch (subChoice)
            {
            case 1:
                selectedDevice->Activate();
                break;

            case 2:
                selectedDevice->Deactivate();
                break;

            case 3:
                selectedDevice->InteractionEvent();
                break;

            case 4:
                selectedDevice->ViewInfo();
                break;

            default:
                cout << "Invalid individual operation choice.\n";
            }
            break;
        }

        case 6: // Add a new device
        {
            cout << "\nSelect device type to add:\n";
            cout << "1. Security Camera\n";
            cout << "2. Thermostat\n";
            cout << "3. Smart Speaker\n";
            cout << "4. Smart Light\n";
            cout << "Enter choice: ";
            int typeChoice;
            cin >> typeChoice;

            int id;
            string name, manufacturer;
            cout << "Enter device ID (integer): ";
            cin >> id;
            cout << "Enter device name: ";
            cin >> ws; // Skip any leading whitespace
            getline(cin, name);
            cout << "Enter manufacturer: ";
            getline(cin, manufacturer);

            if (typeChoice == 1)
            {
                string quality, power;
                cout << "Enter camera quality (e.g., 1080p): ";
                getline(cin, quality);
                cout << "Enter power source (e.g., battery): ";
                getline(cin, power);
                devices.push_back(unique_ptr<Device>(new SecurityCamera(id, name, manufacturer, quality, power)));
            }

            else if (typeChoice == 2)
            {
                double temp;
                cout << "Enter target temperature: ";
                cin >> temp;
                devices.push_back(unique_ptr<Device>(new Thermostat(id, name, manufacturer, temp)));
            }

            else if (typeChoice == 3)
            {
                int volume;
                cout << "Enter volume level (0-100): ";
                cin >> volume;
                devices.push_back(unique_ptr<Device>(new SmartSpeaker(id, name, manufacturer, volume)));
            }

            else if (typeChoice == 4)
            {
                int brightness;
                string colour;
                cout << "Enter brightness level (0-100): ";
                cin >> brightness;
                cout << "Enter colour type (e.g., RGB): ";
                cin >> ws;
                getline(cin, colour);
                devices.push_back(unique_ptr<Device>(new SmartLight(id, name, manufacturer, brightness, colour)));
            }

            else
            {
                cout << "Invalid device type.\n";
            }
            break;
        }

        case 7: // Edit an existing device
        {
            listDevices(devices);
            cout << "Select device number to edit: ";
            int devNum;
            cin >> devNum;
            if (devNum < 1 || devNum > devices.size())
            {
                cout << "Invalid device number.\n";
                break;
            }

            cout << "Enter new name: ";
            cin >> ws;
            string newName;
            getline(cin, newName);
            cout << "Enter new manufacturer: ";
            string newManufacturer;
            getline(cin, newManufacturer);
            devices[devNum - 1]->SetName(newName);
            devices[devNum - 1]->SetManufacturer(newManufacturer);
            cout << "Device updated.\n";
            break;
        }

        case 8: // Delete a device
        {
            listDevices(devices);
            cout << "Select device number to delete: ";
            int devNum;
            cin >> devNum;
            if (devNum < 1 || devNum > devices.size())
            {
                cout << "Invalid device number.\n";
                break;
            }
            devices.erase(devices.begin() + (devNum - 1));
            cout << "Device deleted.\n";
            break;
        }

        case 9: // View devices by connection status
        {
            cout << "\n--- Devices by Connection Status ---\n";
            for (auto &device : devices)
            {
                device->ViewInfo();
                cout << "Connection status: "
                     << (device->CheckConnection() ? "Connected" : "Disconnected") << "\n";
                cout << "---------------------\n";
            }
            break;
        }

        case 10: // Exit the program
            running = false;
            break;
            
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    cout << "Program terminated. Goodbye!" << endl;
    return 0;
}
