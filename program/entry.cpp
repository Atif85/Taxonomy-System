#include "entry.h"
#include <iostream>

using namespace std;

// Constructor 
Entry::Entry(const string& name, const string& description, Rank* rank, Entry* parent): TaxElement(name, description), rank(rank), parent(parent) {}

// Getters 
Rank* Entry::getRank() const
{
    return rank;
}

Entry* Entry::getParent() const
{
    return parent;
}

string Entry::getClassification() const
{
    if (!parent)
    {
        return rank->getName() + ": " + name;  // Top-level entry
    }
;   return parent->getClassification() + " -> " + rank->getName() + ": " + name;
}

// Setters
void Entry::setRank(Rank* rank)
{
    this->rank = rank;
}


void Entry::setParent(Entry* parent)
{
    this->parent = parent;
}

// Display entry info
void Entry::displayEntryInfo() const
{
    cout << "Entry: " << name << endl;
    cout << "Description: " << description << endl;
    cout << "Rank: " << rank->getName() << endl;
    cout << "Classification: " << getClassification() << "\n";
    cout << endl;
}
