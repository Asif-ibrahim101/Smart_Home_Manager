#include <iostream>
#include <vector>
#include <memory>
#include <limits>
#include <random>

// All the header files
#include "SecurityCamera.h"
#include "Thermostat.h"
#include "SmartSpeaker.h"
#include "SmartLight.h"

using namespace std;

// Helper function: Get a validated integer input.
int getValidatedInt(const string &prompt)
{
    int value;
    while (true)
    {
        cout << prompt;
        if (cin >> value)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear leftover input.
            return value;
        }
        else
        {
            cout << "Invalid input. Please enter an integer value." << endl;
            cin.clear();                                         // Reset error state.
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input.
        }
    }
}

// Helper function: Generate a random ID between 1000 and 9999.
int generateRandomID()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(1000, 9999);
    return dis(gen);
}

// Display the main menu.
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
    cout << "10. Search for a device\n";
    cout << "11. Exit\n";
    cout << "Enter your choice: ";
}

// Display the individual device operations menu.
void displayIndividualMenu()
{
    cout << "\n--- Individual Device Operations ---\n";
    cout << "1. Activate device\n";
    cout << "2. Deactivate device\n";
    cout << "3. Interaction event\n";
    cout << "4. View device info\n";
    cout << "Enter your choice: ";
}

// List all devices with their information.
void listDevices(const vector<unique_ptr<Device>> &devices)
{
    cout << "\n--- Device List ---\n";
    for (size_t i = 0; i < devices.size(); i++)
    {
        cout << i + 1 << ".\n";
        devices[i]->ViewInfo();
        cout << "--------------------------------------------------------------\n";
    }
}

// Search for a device (by ID or name) and offer individual operations.
void searchDevice(vector<unique_ptr<Device>> &devices)
{
    cout << "\n--- Device Search ---\n";
    cout << "Search by:\n";
    cout << "1. Device ID\n";
    cout << "2. Device Name\n";
    int searchChoice = getValidatedInt("Enter choice: ");

    Device *foundDevice = nullptr;
    if (searchChoice == 1)
    {
        cout << "Enter device ID to search: ";
        int searchId;
        cin >> searchId;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        for (auto &device : devices)
        {
            if (device->GetID() == searchId)
            {
                foundDevice = device.get();
                break;
            }
        }
        if (!foundDevice)
        {
            cout << "No device found with ID " << searchId << ".\n";
            return;
        }
    }
    else if (searchChoice == 2)
    {
        cout << "Enter device name to search: ";
        string searchName;
        getline(cin, searchName);
        for (auto &device : devices)
        {
            if (device->GetName() == searchName)
            {
                foundDevice = device.get();
                break;
            }
        }
        if (!foundDevice)
        {
            cout << "No device found with name \"" << searchName << "\".\n";
            return;
        }
    }
    else
    {
        cout << "Invalid search choice.\n";
        return;
    }

    // Device found, display its info.
    cout << "\nDevice found:\n";
    foundDevice->ViewInfo();

    int opChoice = getValidatedInt("\nWould you like to perform operations on this device?\n1. Yes\n2. No\nEnter choice: ");
    if (opChoice != 1)
        return;

    displayIndividualMenu();
    int subChoice = getValidatedInt("Enter your choice: ");
    switch (subChoice)
    {
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

int main()
{
    // Create a vector of unique pointers to manage devices.
    vector<unique_ptr<Device>> devices;

    // Pre-populate the system with some devices.
    devices.push_back(make_unique<SecurityCamera>(generateRandomID(), "FrontDoorCamera", "CamCorp", "1080p", "battery"));
    devices.push_back(make_unique<Thermostat>(generateRandomID(), "LivingRoomThermostat", "HeatTech", 22.5));
    devices.push_back(make_unique<SmartSpeaker>(generateRandomID(), "KitchenSpeaker", "SoundInc", 50));
    devices.push_back(make_unique<SmartLight>(generateRandomID(), "BedroomLight", "BrightCo", 75, "RGB"));

    bool running = true;
    while (running)
    {
        displayMainMenu();
        int choice = getValidatedInt("");

        switch (choice)
        {
        case 1: // Activate all devices.
            for (auto &device : devices)
                device->Activate();
            break;

        case 2: // Deactivate all devices.
            for (auto &device : devices)
                device->Deactivate();
            break;

        case 3: // Trigger interaction event for all devices.
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
            int devNum = getValidatedInt("Select device number: ");
            if (devNum < 1 || devNum > (int)devices.size())
            {
                cout << "Invalid device number.\n";
                break;
            }
            auto &selectedDevice = devices[devNum - 1];
            displayIndividualMenu();
            int subChoice = getValidatedInt("Enter your choice: ");
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
            int typeChoice = getValidatedInt("Enter choice: ");
            int id = generateRandomID();
            string name, manufacturer;
            cout << "Enter device name: ";
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
                devices.push_back(make_unique<SecurityCamera>(id, name, manufacturer, quality, power));
            }
            else if (typeChoice == 2)
            {
                double temp;
                cout << "Enter target temperature: ";
                cin >> temp;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                devices.push_back(make_unique<Thermostat>(id, name, manufacturer, temp));
            }
            else if (typeChoice == 3)
            {
                int volume = getValidatedInt("Enter volume level (0-100): ");
                devices.push_back(make_unique<SmartSpeaker>(id, name, manufacturer, volume));
            }
            else if (typeChoice == 4)
            {
                int brightness = getValidatedInt("Enter brightness level (0-100): ");
                cout << "Enter colour type (e.g., RGB): ";
                string colour;
                getline(cin, colour);
                devices.push_back(make_unique<SmartLight>(id, name, manufacturer, brightness, colour));
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
            int devNum = getValidatedInt("Select device number to edit: ");
            if (devNum < 1 || devNum > (int)devices.size())
            {
                cout << "Invalid device number.\n";
                break;
            }
            cout << "Enter new name: ";
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
        case 8:
        { // Delete a device.
            listDevices(devices);
            int devNum = getValidatedInt("Select device number to delete: ");
            if (devNum < 1 || devNum > (int)devices.size())
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
                cout << "Connection status: " << (device->CheckConnection() ? "Connected" : "Disconnected") << "\n";
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
    }
    cout << "Program terminated. Goodbye!" << endl;
    return 0;
}
