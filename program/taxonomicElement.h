#ifndef TAXONOMICELEMENT_H
#define TAXONOMICELEMENT_H

#include <string>
using namespace std;

class TaxElement {
protected:
    string name;
    string description;

public:

    // Constructor
    TaxElement(const string& name, const string& description);

    // Getters
    string getName() const;
    string getDescription() const;

    // Setters
    void setName(const string& name);
    void setDescription(const string& description);
};

#endif