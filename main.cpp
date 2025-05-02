#include <iostream>
#include <algorithm>
#include "Parcel.h"
#include "Queue.h"
#include "BST.h"
#include "Stack.h"

using namespace std;

// --- Region and city validation arrays ---
const string REGIONS[] = {"North", "South", "East", "West"};
const string CITIES[4][3] = {
    {"Arar", "Tabuk", "Sakakah"},
    {"Abha", "Najran", "Jizan"},
    {"Dammam", "Khobar", "Hofuf"},
    {"Jeddah", "Mecca", "Medina"}
};

// --- Function Prototypes ---
bool isValidRegion(const string& region);
bool isValidCity(const string& region, const string& city);
bool isIDUnique(int id, Queue& q1, Queue& q2);
void searchByID(int id, Queue& q1, Queue& q2);
void searchByRegion(const string& region, Queue& q);

int main() {
    Queue outForDelivery;
    Queue delivered;
    BST parcelBST;
    Stack deliveryStack;
    int choice, id, priority;
    string region, city, zone;

    while (true) {
        cout << "\n-----------------------------Parcel Management System -----------------------------\n";
        cout << "1. Add Parcel\n";
        cout << "2. Mark Parcel as Delivered\n";
        cout << "3. Cancel Delivery\n";
        cout << "4. Display All Shipments Out for Delivery\n";
        cout << "5. Display All Delivered Shipments\n";
        cout << "6. Search by Shipment ID\n";
        cout << "7. Search by Region\n";
        cout << "8. Display BST Hierarchy\n";
        cout << "9. Push All Out-for-Delivery Parcels to Stack\n";
        cout << "10. Display Delivery Stack\n";
        cout << "11. Reverse Delivery Stack\n";
        cout << "12. Exit\n";
        cout << "-------------------------------------------------------------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cout << "-------------------------------------------------------------------------------------------\n";

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Try again.\n";
            continue;
        }

        switch (choice) {
        case 1: {
            cout << "Enter 4-digit Shipment ID: ";
            cin >> id;
            while (cin.fail() || id < 1000 || id > 9999) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid ID! Enter 4 digits: ";
                cin >> id;
            }
            if (!isIDUnique(id, outForDelivery, delivered)) {
                cout << "ID already exists!\n";
                break;
            }

            cout << "Enter Region (North/South/East/West): ";
            cin.ignore();
            getline(cin, region);
            while (!isValidRegion(region)) {
                cout << "Invalid region! Valid: North, South, East, West: ";
                getline(cin, region);
            }

            int regionIndex = distance(REGIONS, find(REGIONS, REGIONS + 4, region));
            cout << "Select City: ";
            for (int i = 0; i < 3; i++) cout << CITIES[regionIndex][i] << (i < 2 ? ", " : "");
            cout << "\nEnter City: ";
            getline(cin, city);
            while (!isValidCity(region, city)) {
                cout << "Invalid city for " << region << "! Valid cities: ";
                for (int i = 0; i < 3; i++) cout << CITIES[regionIndex][i] << (i < 2 ? ", " : "");
                cout << "\nRe-enter city: ";
                getline(cin, city);
            }

            cout << "Select Zone (A, B, C): ";
            getline(cin, zone);
            while (!(zone == "A" || zone == "B" || zone == "C")) {
                cout << "Invalid zone! Enter A, B, or C: ";
                getline(cin, zone);
            }

            cout << "Enter Priority (1 - High, 2 - Medium, 3 - Low): ";
            cin >> priority;
            while (cin.fail() || priority < 1 || priority > 3) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid! Enter 1 (High), 2 (Medium), or 3 (Low): ";
                cin >> priority;
            }

            outForDelivery.enqueue(id, region, city, zone, priority);
            parcelBST.insert(outForDelivery.rear);
            cout << "-------------------------------------------------------------------------------------------\n";
            cout << "Parcel added successfully!\n";
            break;
        }
        case 2: {
            Parcel* deliveredParcel = outForDelivery.dequeue();
            if (deliveredParcel) {
                delivered.enqueue(deliveredParcel->shipmentID, deliveredParcel->region,
                                  deliveredParcel->city, deliveredParcel->zone, deliveredParcel->priority);
                cout << "Marked as delivered: ID " << deliveredParcel->shipmentID << endl;
                parcelBST.deleteByID(deliveredParcel->shipmentID);
                delete deliveredParcel;
            } else {
                cout << "-------------------------------------------------------------------------------------------\n";
                cout << "No parcels in delivery queue!\n";
            }
            break;
        }
        case 3: {
            cout << "Enter Shipment ID to cancel: ";
            cin >> id;
            if (outForDelivery.deleteByID(id)) {
                cout << "-------------------------------------------------------------------------------------------\n";
                cout << "Parcel canceled and removed from queue.\n";
                parcelBST.deleteByID(id);
            } else {
                cout << "-------------------------------------------------------------------------------------------\n";
                cout << "Parcel not found in out-for-delivery queue.\n";
            }
            break;
        }
        case 4: {
            outForDelivery.displayQ();
            break;
        }
        case 5: {
            delivered.displayQ();
            break;
        }
        case 6: {
            cout << "Enter shipment ID to search: ";
            cin >> id;
            cout << "-------------------------------------------------------------------------------------------\n";
            searchByID(id, outForDelivery, delivered);
            break;
        }
        case 7: {
            cout << "-------------------------------------------------------------------------------------------\n";
            cout << "Search in (1) Out-for-Delivery or (2) Delivered? ";
            int which;
            cin >> which;
            cin.ignore();
            cout << "Enter region: ";
            getline(cin, region);
            cout << "-------------------------------------------------------------------------------------------\n";
            if (which == 1) searchByRegion(region, outForDelivery);
            else searchByRegion(region, delivered);
            break;
        }
        case 8: {
            cout << "-------------------------------------------------------------------------------------------\n";
            parcelBST.display();
            break;
        }
        case 9: {
            // Push all out-for-delivery parcels to stack
            // Clear stack first
            while (deliveryStack.top) {
                Parcel* temp = deliveryStack.pop();
                delete temp;
            }
            Parcel* current = outForDelivery.front;
            while (current) {
                deliveryStack.push(current);
                current = current->next;
            }
            cout << "-------------------------------------------------------------------------------------------\n";
            cout << "All out-for-delivery parcels pushed to stack.\n";
            break;
        }
        case 10: {
            deliveryStack.display();
            break;
        }
        case 11: {
            deliveryStack.reverse();
            break;
        }
        case 12: {
            cout << "-------------------------------------------------------------------------------------------\n";
            cout << "Exiting. Goodbye!\n";
            return 0;
        }
        default:
        cout << "-------------------------------------------------------------------------------------------\n";
            cout << "Invalid choice. Try again.\n";
        }
    }
    return 0;
}

// --- Helper Functions ---

bool isValidRegion(const string& region) {
    for (int i = 0; i < 4; i++) {
        if (REGIONS[i] == region) return true;
    }
    return false;
}

bool isValidCity(const string& region, const string& city) {
    int regionIndex = -1;
    for (int i = 0; i < 4; i++) {
        if (REGIONS[i] == region) {
            regionIndex = i;
            break;
        }
    }
    if (regionIndex == -1) return false;
    for (int i = 0; i < 3; i++) {
        if (CITIES[regionIndex][i] == city) return true;
    }
    return false;
}

bool isIDUnique(int id, Queue& q1, Queue& q2) {
    Parcel* current = q1.front;
    while (current) {
        if (current->shipmentID == id) return false;
        current = current->next;
    }
    current = q2.front;
    while (current) {
        if (current->shipmentID == id) return false;
        current = current->next;
    }
    return true;
}

void searchByID(int id, Queue& q1, Queue& q2) {
    Parcel* current = q1.front;
    while (current) {
        if (current->shipmentID == id) {
            cout << "Found in Out-for-Delivery Queue:\n";
            cout << "ID: " << current->shipmentID << ", Region: " << current->region
                 << ", City: " << current->city << ", Zone: " << current->zone
                 << ", Priority: " << current->priority << endl;
            return;
        }
        current = current->next;
    }
    current = q2.front;
    while (current) {
        if (current->shipmentID == id) {
            cout << "Found in Delivered Queue:\n";
            cout << "ID: " << current->shipmentID << ", Region: " << current->region
                 << ", City: " << current->city << ", Zone: " << current->zone
                 << ", Priority: " << current->priority << endl;
            return;
        }
        current = current->next;
    }
    cout << "Shipment ID " << id << " not found in any queue." << endl;
}

void searchByRegion(const string& region, Queue& q) {
    Parcel* current = q.front;
    bool found = false;
    cout << "Parcels in region " << region << ":\n";
    while (current) {
        if (current->region == region) {
            cout << "ID: " << current->shipmentID << ", City: " << current->city
                 << ", Zone: " << current->zone << ", Priority: " << current->priority << endl;
            found = true;
        }
        current = current->next;
    }
    if (!found) cout << "No parcels found in this region.\n";
}
