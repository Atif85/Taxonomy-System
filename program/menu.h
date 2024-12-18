#ifndef MENU_H
#define MENU_H

#include "taxManager.h"

class Menu {
private:
    TaxManager& taxManager;

public:
    // Constructor
    Menu(TaxManager& taxManager);

    // Main menu loop
    void showMenu();

    // Add a rank
    void addRankMenu();

    // Add an entry
    void addEntryMenu();

    // Display taxonomy
    void displayTaxonomy();

    // Serch Recursively
    Entry* searchEntryRecursively(vector<Entry*> entries, const string& name);

    // Sreach rank or entry
    void searchMenu();

    // Save to file
    void saveTaxonomyToFile();

    // Load from file
    void loadTaxonomyFromFile();
};

#endif
