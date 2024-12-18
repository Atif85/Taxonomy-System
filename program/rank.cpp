#include "rank.h"
#include <iostream>

using namespace std;

// Constructor
Rank::Rank(const string& name, const string& description, Rank* parent) : TaxElement(name, description) , parent(parent) {}

// Getters
Rank* Rank::getParent() const {
    return parent;
}

// Setters
void Rank::setParent(Rank* parent) {
    this->parent = parent;
}

// Display rank info
void Rank::displayRankInfo() const {
    cout << "Rank: " << name << "\nDescription: " << description;
    if (parent) {
        cout << "\nParent Rank: " << parent->getName();
    } else {
        cout << "\nThis is a top-level rank (no parent).";
    }
    cout << endl;
}

