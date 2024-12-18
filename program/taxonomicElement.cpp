#include "taxonomicElement.h"



// Constructor
TaxElement::TaxElement(const string& name, const string& description) : name(name), description(description) {}

string TaxElement::getName() const {
    return name;
}

string TaxElement::getDescription() const {
    return description;
}

// Setters
void TaxElement::setName(const string& name) {
    this->name = name;
}
void TaxElement::setDescription(const string& description) {
    this->description = description;
}