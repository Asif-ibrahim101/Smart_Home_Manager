// importing all the classses
#include "SecurityCamera.h"
#include "Thermostat.h"
#include "SmartSpeaker.h"
#include "SmartLight.h"

#include <iostream>
#include <vector>
#include <math.h>
#include <memory> //useing for smart pointers
#include <random>
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
    cout << "10. Search for a device\n";
    cout << "11. Exit\n";
    cout << "Enter your choice: ";
}

// function to display the indivisual infos
void displayIndividualMenu()
{
    cout << "\n--- Individual Device Operations ---\n";
    cout << "1. Activate device\n";
    cout << "2. Deactivate device\n";
    cout << "3. Interaction event\n";
    cout << "4. View device info\n";
    cout << "Enter your choice: ";
};

// listing all the devicess with all the infos
void listDevices(const vector<unique_ptr<Device>> &devices)
{
    cout << "\n--- Device List ---\n";
    for (int i = 0; i < devices.size(); i++)
    {
        cout << i + 1 << ".\n";
        devices[i]->ViewInfo();
        cout << "---------------------\n";
    };
};


// Function to generate a random ID
// taken form the internet
int generateRandomID() {
    static std::random_device rd; // Seed
    static std::mt19937 gen(rd()); // Mersenne Twister engine
    static std::uniform_int_distribution<> dis(1000, 9999); // Random ID between 1000 and 9999
    return dis(gen);
}

// Function to search for a device by ID or name.
// Updated searchDevice function that allows individual operations on the found device.
void searchDevice(vector<unique_ptr<Device>>& devices) {
    cout << "\n--- Device Search ---\n";
    cout << "Search by:\n";
    cout << "1. Device ID\n";
    cout << "2. Device Name\n";
    cout << "Enter choice: ";
    int searchChoice;
    cin >> searchChoice;
    
    // Variable to hold pointer to the found device.
    Device* foundDevice = nullptr;
    
    if (searchChoice == 1) {
        cout << "Enter device ID to search: ";
        int searchId;
        cin >> searchId;
        for (auto &device : devices) {
            if (device->GetID() == searchId) {
                foundDevice = device.get();
                break;
            }
        }
        if (!foundDevice) {
            cout << "No device found with ID " << searchId << ".\n";
            return;
        }
    } else if (searchChoice == 2) {
        cout << "Enter device name to search: ";
        string searchName;
        cin >> ws; // skip any leading whitespace
        getline(cin, searchName);
        for (auto &device : devices) {
            if (device->GetName() == searchName) {
                foundDevice = device.get();
                break;
            }
        }
        if (!foundDevice) {
            cout << "No device found with name \"" << searchName << "\".\n";
            return;
        }
    } else {
        cout << "Invalid search choice.\n";
        return;
    }
    
    // If a device was found, display its info.
    cout << "\nDevice found:\n";
    foundDevice->ViewInfo();
    
    // Ask if the user wants to perform individual operations on the found device.
    cout << "\nWould you like to perform operations on this device?\n";
    cout << "1. Yes\n2. No\nEnter choice: ";
    int opChoice;
    cin >> opChoice;
    if (opChoice != 1) {
        return;
    }
    
    // Display the individual operations menu.
    displayIndividualMenu();
    int subChoice;
    cin >> subChoice;
    switch(subChoice) {
        case 1:
            foundDevice->Activate();
            break;
        case 2:
            foundDevice->Deactivate();
            break;
        case 3:
            foundDevice->InteractionEvent();
            break;
        case 4:
            foundDevice->ViewInfo();
            break;
        default:
            cout << "Invalid individual operation choice.\n";
    }
}


// the main function
int main()
{
    vector<unique_ptr<Device>> devices;

    // Allocating all the devicess on a Heap memory
    devices.push_back(unique_ptr<Device>(new SecurityCamera(generateRandomID(), "FrontDoorCamera", "CamCorp", "1080p", "battery")));
    devices.push_back(unique_ptr<Device>(new Thermostat(generateRandomID(), "LivingRoomThermostat", "HeatTech", 22.5)));
    devices.push_back(unique_ptr<Device>(new SmartSpeaker(generateRandomID(), "KitchenSpeaker", "SoundInc", 50)));
    devices.push_back(unique_ptr<Device>(new SmartLight(generateRandomID(), "BedroomLight", "BrightCo", 75, "RGB")));

    // Choose
    int Choice;

    // crating a base case
    bool running = true;

    // Main loop for the interface
    while (running)
    {
        displayMainMenu();
        cin >> Choice;

        switch (Choice)
        {
        case 1: // Activate all devices.
            for (auto &device : devices)
                device->Activate();
            break;

        case 2: // Deactivate all devices.
            for (auto &device : devices)
                device->Deactivate();
            break;

        case 3: // Trigger InteractionEvent for all devices.
            for (auto &device : devices)
                device->InteractionEvent();
            break;

        case 4: // View info for all devices.
            for (auto &device : devices)
            {
                device->ViewInfo();
                cout << "---------------------\n";
            }
            break;

        case 5:
        { // Individual device operations.
            listDevices(devices);
            cout << "Select device number: ";
            int devNum;
            cin >> devNum;

            // cheker for selection
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
        case 6:
        { // Add a new device.
            cout << "\nSelect device type to add:\n";
            cout << "1. Security Camera\n";
            cout << "2. Thermostat\n";
            cout << "3. Smart Speaker\n";
            cout << "4. Smart Light\n";
            cout << "Enter choice: ";

            int typeChoice;
            cin >> typeChoice;

            int id = generateRandomID();
            string name, manufacturer;

            // for cheking for uniqe id
            // bool idExits = false;

            cout << "Enter device name: ";
            cin >> name; // Skip any leading whitespace.

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
        case 7:
        { // Edit an existing device.
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
            string newName;

            cin >> newName;
            getline(cin, newName);

            cout << "Enter new manufacturer: ";
            string newManufacturer;
            getline(cin, newManufacturer);

            devices[devNum - 1]->SetName(newName);
            devices[devNum - 1]->SetManufacturer(newManufacturer);
            cout << "Device updated.\n";
            break;
        }
        case 8:
        { // Delete a device.
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
        case 9:
        { // View devices by connection status.
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
        case 10:
            searchDevice(devices);
            break;
        case 11:
            running = false;
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    };

    cout << "Program terminated. Goodbye!" << endl;
    return 0;
}