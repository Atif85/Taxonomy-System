#ifndef RANK_H
#define RANK_H

#include <string>
#include "taxonomicElement.h"

using namespace std;

class Rank : public TaxElement {
private:
    Rank* parent;  // Pointer to the parent rank (could be nullptr for the highest rank)

public:
    // Constructor
    Rank(const string& name, const string& description, Rank* parent = nullptr);

    // Getters
    Rank* getParent() const;

    // Setters
    void setParent(Rank* parent);

    // Display rank info (for debugging or display)
    void displayRankInfo() const;
};

#endif
