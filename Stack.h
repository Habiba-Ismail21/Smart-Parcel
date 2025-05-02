#ifndef STACK_H
#define STACK_H

#include "Parcel.h"
#include <iostream>
using namespace std;

class Stack {
public:
    Parcel* top;

    Stack() : top(nullptr) {}

    // Push a parcel onto the stack (makes a copy)
    void push(Parcel* parcel) {
        Parcel* copy = new Parcel(parcel->shipmentID, parcel->region, parcel->city, parcel->zone, parcel->priority);
        copy->next = top;
        top = copy;
    }

    // Pop a parcel from the stack
    Parcel* pop() {
        if (!top) return nullptr;
        Parcel* temp = top;
        top = top->next;
        temp->next = nullptr;
        return temp;
    }

    // Display stack contents
    void display() {
        if (!top) {
            cout << "Stack is empty.\n";
            return;
        }
        Parcel* current = top;
        cout << "Stack (top to bottom):\n";
        while (current) {
            cout << "ID: " << current->shipmentID << ", Region: " << current->region
                 << ", City: " << current->city << ", Zone: " << current->zone
                 << ", Priority: " << current->priority << endl;
            current = current->next;
        }
    }

    // Reverse the stack
    void reverse() {
        Parcel* prev = nullptr;
        Parcel* current = top;
        Parcel* next = nullptr;
        while (current) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        top = prev;
        cout << "Stack reversed!\n";
    }

    // Destructor to free memory
    ~Stack() {
        while (top) {
            Parcel* temp = top;
            top = top->next;
            delete temp;
        }
    }
};

#endif
