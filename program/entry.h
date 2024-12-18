#ifndef ENTRY_H
#define ENTRY_H

#include <vector>
#include <string>
#include "taxonomicElement.h"
#include "rank.h"
using namespace std;

class Entry : public TaxElement {
private:

    Rank* rank;      // Pointer to the rank the entry belongs to
    Entry* parent;   // Parent entry, null if it's the first entry in the hierarchy

public:
    // Constructor with optional parent
    Entry(const string& name, const string& description, Rank* rank, Entry* parent = nullptr);

    // Getters
    Rank* getRank() const;
    Entry* getParent() const;
    string getClassification() const;

    // Setters
    void setRank(Rank* rank);
    void setParent(Entry* parent);

    // Display entry info
    void displayEntryInfo() const;
};

#endif
