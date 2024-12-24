#ifndef TAXMANAGER_H
#define TAXMANAGER_H

#include <unordered_map>
#include "rank.h"
#include "entry.h"

class TaxManager
{
    
private:
    unordered_map<string, Rank*> Ranks;    // List of top-level ranks (e.g., Domain, Kingdom)
    unordered_map<string, Entry*> Entries; // List of top-level entries (e.g., Eukaryota, Animalia)

public:
    // Constructor
    TaxManager();

    // Destructor 
    ~TaxManager();

    // Add a new rank to the system
    void addRank(const string& name, const string& description, Rank* parent = nullptr);

    // Add an entry to a specific rank
    void addEntry(const string& name, const string& description, Rank* rank, Entry* parent = nullptr);

    // Get all top-level ranks
    unordered_map<string, Rank*> getTopRanks() const;

    // Get all top-level entries
    unordered_map<string, Entry*> getTopEntries() const;

    // Search for a rank by name
    Rank* searchRank(const string& name);

    // Search for an entry by name
    Entry* searchEntry(const string& name);

    // Display all ranks and entries in the system
    void displayTaxonomy() const;

    // Save taxonomy data to a file
    void saveToFile(const string& filename) const;

    // Load taxonomy data from a file
    void loadFromFile(const string& filename);
};
#endif
