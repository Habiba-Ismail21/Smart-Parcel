#ifndef QUEUE_H
#define QUEUE_H

#include "Parcel.h"
#include <iostream>
#include <iomanip>
using namespace std;

class Queue {
public:
    Parcel* front;
    Parcel* rear;

    Queue() : front(nullptr), rear(nullptr) {}

    void enqueue(int id, string region, string city, string zone, int priority) {
        Parcel* newParcel = new Parcel(id, region, city, zone, priority);

        if (isEmpty()) {
            front = rear = newParcel;
            return;
        }

        Parcel* current = front;
        Parcel* prev = nullptr;
        while (current && current->priority <= priority) {
            prev = current;
            current = current->next;
        }

        if (!prev) { // Insert at front
            newParcel->next = front;
            front = newParcel;
        } else { // Insert after prev
            prev->next = newParcel;
            newParcel->next = current;
            if (!current) rear = newParcel;
        }
    }

    Parcel* dequeue() {
        if (isEmpty()) return nullptr;

        Parcel* temp = front;
        front = front->next;
        if (!front) rear = nullptr;
        temp->next = nullptr;
        return temp;
    }

    void displayQ() {
        if (isEmpty()) {
            cout << "No shipments in queue\n";
            return;
        }
        Parcel* current = front;
        cout << "Shipments in queue:\n";
        while (current) {
            cout << "Shipment ID: " << setfill('0') << setw(4) << current->shipmentID
                 << " | Region: " << current->region
                 << " | City: " << current->city
                 << " | Zone: " << current->zone
                 << " | Priority: " << current->priority << endl;
            current = current->next;
        }
    }

    bool isEmpty() {
        return front == nullptr;
    }

    bool deleteByID(int id) {
        Parcel* current = front;
        Parcel* prev = nullptr;
        while (current) {
            if (current->shipmentID == id) {
                if (prev) prev->next = current->next;
                else front = current->next;
                if (current == rear) rear = prev;
                delete current;
                return true;
            }
            prev = current;
            current = current->next;
        }
        return false;
    }
};

#endif
