#ifndef PARCEL_H
#define PARCEL_H

#include <string>
using namespace std;

class Parcel {
public:
    int shipmentID;
    string region;
    string city;
    string zone;
    int priority;
    Parcel* next;

    Parcel(int id, string r, string c, string z, int p)
        : shipmentID(id), region(r), city(c), zone(z), priority(p), next(nullptr) {}
};

#endif
