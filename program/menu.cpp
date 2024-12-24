#include "menu.h"
#include <iostream>
#include <limits>

using namespace std;

// Constructor
Menu::Menu(TaxManager& taxManager) : taxManager(taxManager) {}

// Show menu and handle user input
void Menu::showMenu() {
    int choice = 0;
    do {
        cout << "\n--- Taxonomy System Menu ---\n";
        cout << "1. Add Rank\n";
        cout << "2. Add Entry\n";
        cout << "3. Search Rank/Entry\n";
        cout << "4. Display Taxonomy\n";
        cout << "5. Save to File\n";
        cout << "6. Load from File\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";

        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch (choice) {
            case 1:
                addRankMenu();
                break;
            case 2:
                addEntryMenu();
                break;
            case 3:
                searchMenu();
                break;
            case 4:
                displayTaxonomy();
                break;
            case 5:
                saveTaxonomyToFile();
                break;
            case 6:
                loadTaxonomyFromFile();
                break;
            case 7:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
                break;
        }
    } while (choice != 7);
}

// Add a rank
void Menu::addRankMenu() {
    string name, description;
    cout << "Enter the rank name: ";
    getline(cin, name);
    cout << "Enter the rank description: ";
    getline(cin, description);

    if (taxManager.searchRank(name) == nullptr)
    {
        taxManager.addRank(name, description); // No parent specified for simplicity
        cout << "Rank added successfully.\n";
    }
    else
    {
        cout << "Rank already exists.\n";
    }
    
}

// Add an entry
void Menu::addEntryMenu() {
    string name, description;
    string rankName, parentEntryName;
    
    cout << "Enter the entry name: ";
    getline(cin, name);
    cout << "Enter the entry description: ";
    getline(cin, description);
    cout << "Enter the rank for the entry: ";
    getline(cin, rankName);
    
    cout << "Enter the parent entry name (or press Enter if this is a top-level entry): ";
    getline(cin, parentEntryName);


    if (taxManager.searchEntry(name) == nullptr)
    {
            // Find the rank by name
        Rank* rank = taxManager.searchRank(rankName);

        if (!rank)
        {
            cout << "Rank not found.\n";
            // Prompt user to add the rank
            cout << "Would you like to add the rank? (y/n): ";
            string response;
            getline(cin, response);
            if (response == "y" || response == "Y")
            {
                addRankMenu();  // Call the add rank menu
                rank = taxManager.searchRank(rankName);
            } else
            {
                return;
            }
        }

        // Find the parent entry if specified
        Entry* parentEntry = nullptr;
        if (!parentEntryName.empty()) {
            // Search for the parent entry in the top-level entries
            parentEntry = taxManager.searchEntry(parentEntryName);

            if (!parentEntry) {
                cout << "Parent entry not found.\nWould you like to add this parent entry? (y/n): ";
                string response;
                getline(cin, response);
                if (response == "y" || response == "Y") {
                    addEntryMenu();  // Recursively add the parent entry
                    parentEntry = taxManager.searchEntry(parentEntryName);
                } else {
                    return;
                }
            }
        }

        // Add the new entry
        taxManager.addEntry(name, description, rank, parentEntry); // Pass the found parentEntry (or nullptr if it's top-level)
        cout << "Entry added successfully.\n";
    }
    else
    {
        cout << "Rank already exists.\n";
    }
}

// The search menu to search for a rank or an entry
void Menu::searchMenu()
{
    string name;
    cout << "Enter name of rank or entry: ";
    getline(cin, name);

    // Search for the rank first
    Rank* rank = taxManager.searchRank(name);

    if (rank) {
        cout << "RANK FOUND\n";
        rank->displayRankInfo();
    } else {
        // Rank not found, search for entry (including children)
        Entry* entry = taxManager.searchEntry(name);

        if (entry) {
            cout << "ENTRY FOUND\n";
            entry->displayEntryInfo();
        } else {
            // Neither rank nor entry found, ask to add it
            cout << "Neither rank nor entry found with that name.\n";
            cout << "Would you like to add it? (y/n): ";
            string response;
            getline(cin, response);

            if (response == "y" || response == "Y") {
                cout << "Is this a Rank or an Entry? (r/e): ";
                string type;
                getline(cin, type);

                if (type == "r" || type == "R") {
                    addRankMenu();  // Call the add rank menu to add a new rank
                } else if (type == "e" || type == "E") {
                    addEntryMenu();  // Call the add entry menu to add a new entry
                } else {
                    cout << "Invalid choice. Returning to menu.\n";
                }
            } else {
                cout << "Returning to menu.\n";
            }
        }
    }
}

// Display taxonomy
void Menu::displayTaxonomy() {
    cout << "\n--- Taxonomy ---\n";
    taxManager.displayTaxonomy();
}

// Save to file
void Menu::saveTaxonomyToFile() {
    string filename;
    cout << "Enter filename to save data: ";
    getline(cin, filename);

    taxManager.saveToFile(filename + ".csv");
    cout << "Data saved successfully.\n";
}

// Load from file
void Menu::loadTaxonomyFromFile() {
    string filename;
    cout << "Enter filename to load data: ";
    getline(cin, filename);

    taxManager.loadFromFile(filename);
    cout << "Data loaded successfully.\n";
}
