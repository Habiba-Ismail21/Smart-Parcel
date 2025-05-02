#ifndef BST_H
#define BST_H

#include "Parcel.h"
#include <iostream>
using namespace std;

class BSTNode {
public:
    Parcel* data;
    BSTNode* left;
    BSTNode* right;

    BSTNode(Parcel* parcel)
        : data(parcel), left(nullptr), right(nullptr) {}
};

class BST {
private:
    BSTNode* root;

    void insertHelper(BSTNode*& node, Parcel* parcel) {
        if (!node) {
            node = new BSTNode(parcel);
            return;
        }
        if (parcel->region < node->data->region) {
            insertHelper(node->left, parcel);
        } else if (parcel->region > node->data->region) {
            insertHelper(node->right, parcel);
        } else {
            if (parcel->city < node->data->city) {
                insertHelper(node->left, parcel);
            } else if (parcel->city > node->data->city) {
                insertHelper(node->right, parcel);
            } else {
                if (parcel->zone < node->data->zone) {
                    insertHelper(node->left, parcel);
                } else if (parcel->zone > node->data->zone) {
                    insertHelper(node->right, parcel);
                } else {
                    if (parcel->shipmentID < node->data->shipmentID)
                        insertHelper(node->left, parcel);
                    else
                        insertHelper(node->right, parcel);
                }
            }
        }
    }

    void inOrderDisplay(BSTNode* node) {
        if (node) {
            inOrderDisplay(node->left);
            cout << "Region: " << node->data->region
                 << " | City: " << node->data->city
                 << " | Zone: " << node->data->zone
                 << " | ID: " << node->data->shipmentID
                 << " | Priority: " << node->data->priority << endl;
            inOrderDisplay(node->right);
        }
    }

    void destroyTree(BSTNode* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node->data;
            delete node;
        }
    }

    BSTNode* deleteByID(BSTNode* node, int id) {
        if (!node) return nullptr;
        if (id < node->data->shipmentID) {
            node->left = deleteByID(node->left, id);
        } else if (id > node->data->shipmentID) {
            node->right = deleteByID(node->right, id);
        } else {
            if (!node->left && !node->right) {
                delete node->data;
                delete node;
                return nullptr;
            } else if (!node->left) {
                BSTNode* temp = node->right;
                delete node->data;
                delete node;
                return temp;
            } else if (!node->right) {
                BSTNode* temp = node->left;
                delete node->data;
                delete node;
                return temp;
            } else {
                BSTNode* succParent = node;
                BSTNode* succ = node->right;
                while (succ->left) {
                    succParent = succ;
                    succ = succ->left;
                }
                node->data->shipmentID = succ->data->shipmentID;
                node->data->region = succ->data->region;
                node->data->city = succ->data->city;
                node->data->zone = succ->data->zone;
                node->data->priority = succ->data->priority;
                if (succParent != node)
                    succParent->left = deleteByID(succParent->left, succ->data->shipmentID);
                else
                    succParent->right = deleteByID(succParent->right, succ->data->shipmentID);
            }
        }
        return node;
    }

public:
    BST() : root(nullptr) {}

    void insert(Parcel* parcel) {
        Parcel* copy = new Parcel(parcel->shipmentID, parcel->region, parcel->city, parcel->zone, parcel->priority);
        insertHelper(root, copy);
    }

    void display() {
        cout << "\n--- Parcel Hierarchy (BST In-Order) ---\n";
        inOrderDisplay(root);
    }

    void deleteByID(int id) {
        root = deleteByID(root, id);
    }

    ~BST() { destroyTree(root); }
};

#endif
