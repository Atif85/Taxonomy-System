#include "taxmanager.h"
#include <iostream>
#include <fstream>

using namespace std;

// Constructor
TaxManager::TaxManager() {}

TaxManager::~TaxManager() {
    // Clean up all allocated Rank objects
    for (auto& pair : Ranks) {
        delete pair.second; // pair.second is the pointer to Rank
    }

    // Clean up all allocated Entry objects
    for (auto& pair : Entries) {
        delete pair.second; // pair.second is the pointer to Entry
    }
}


// Add a new rank
void TaxManager::addRank(const string& name, const string& description, Rank* parent) {
    Rank* newRank = new Rank(name, description);
    newRank->setParent(parent);
    Ranks[name] = newRank; // Store in the map
}

// Add an entry to a specific rank
void TaxManager::addEntry(const string& name, const string& description, Rank* rank, Entry* parent) {
    Entry* newEntry = new Entry(name, description, rank);
    if (parent) {
        newEntry->setParent(parent); // Set parent of the new entry
    } 
    Entries[name] = newEntry; // If no parent, add to top-level entries

}


// Get all top-level ranks
unordered_map<string, Rank*> TaxManager::getTopRanks() const {
    return Ranks;
}

// Get all top-level entries
unordered_map<string, Entry*> TaxManager::getTopEntries() const {
    return Entries;
}

// Search for a rank by name
Rank* TaxManager::searchRank(const string& name) {
    auto pair = Ranks.find(name);
    return (pair != Ranks.end()) ? pair->second : nullptr;
}

// Search for an entry by name
Entry* TaxManager::searchEntry(const string& name) {
    auto pair = Entries.find(name);
    return (pair != Entries.end()) ? pair->second : nullptr;
}

// Display the whole taxonomy structure
void TaxManager::displayTaxonomy() const {
    cout << "RANKS\n";
    for (const auto& pair : Ranks) { // This iterates over the unordered_map
        const Rank* rank = pair.second; // pair.second is the Rank pointer
        rank->displayRankInfo();
        // Expand here if you want to display additional details.
    }

    cout << "\nENTRIES\n";
    for (const auto& pair : Entries) { //  This iterates over the unordered_map
        const Entry* entry = pair.second; // pair.second is the Entry pointer
        entry->displayEntryInfo();
    }
}


// Save taxonomy data to a file (for simplicity, just saving rank and entry names)
void TaxManager::saveToFile(const string& filename) const {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << "Ranks:\n";
        for (const auto& pair : Ranks) {
            outFile << pair.first << "\n";
        }

        outFile << "\nEntries:\n";
        for (const auto& pair : Entries) {
            outFile << pair.first << "\n";
        }

        outFile.close();
        cout << "Data successfully saved to " << filename << ".\n";
    } else {
        cout << "Error opening file to save data!" << endl;
    }
}

// Load taxonomy data from a file
void TaxManager::loadFromFile(const string& filename) {
    ifstream inFile(filename);
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            if (line == "Ranks:") {
                // Parse ranks
                while (getline(inFile, line) && !line.empty()) {
                    addRank(line, "");  // Add ranks with placeholder descriptions
                }
            } else if (line == "Entries:") {
                // Parse entries
                while (getline(inFile, line) && !line.empty()) {
                    // Assuming you already have a rank to assign the entry to
                    addEntry(line, "", nullptr);  // Add entries with placeholder descriptions
                }
            }
        }
        inFile.close();
    } else {
        cout << "Error opening file to load data!" << endl;
    }
}
