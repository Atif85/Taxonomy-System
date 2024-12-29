#include "taxmanager.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <tuple>
#include <unordered_map>



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
unordered_map<string, Rank*> TaxManager::getTopRanks() const
{
    return Ranks;
}

// Get all top-level entries
unordered_map<string, Entry*> TaxManager::getTopEntries() const
{
    return Entries;
}

// Search for a rank by name
Rank* TaxManager::searchRank(const string& name)
{
    auto pair = Ranks.find(name);
    
    if (pair != Ranks.end())
        return pair->second;
    else 
        return nullptr;
}

// Search for an entry by name
Entry* TaxManager::searchEntry(const string& name)
{
    auto pair = Entries.find(name);

    if (pair != Entries.end()) 
        return pair->second;
    else
        return nullptr;
}

// Display the whole taxonomy structure
void TaxManager::displayTaxonomy() const
{
    cout << "RANKS\n";

    for (const auto& pair : Ranks) // This iterates over the unordered_map
    { 
        const Rank* rank = pair.second; // pair.second is the Rank pointer
        rank->displayRankInfo();
    }

    cout << "\nENTRIES\n";

    for (const auto& pair : Entries) //  This iterates over the unordered_map
    { 
        const Entry* entry = pair.second; // pair.second is the Entry pointer
        entry->displayEntryInfo();
    }
}


// Save taxonomy data to a file
void TaxManager::saveToFile(const string& filename) const
{
    ofstream outFile(filename); // Open the file for writing
    if (outFile.is_open())
    {
        outFile << "__RANKS__\nNAME,DESCRIPTION,PARENT\n"; // Header line for ranks

        for (const auto& pair : Ranks) // Adding each rank to the file
        {
            outFile << pair.second->getName() << ",";
            outFile << pair.second->getDescription() << ",";
            if (pair.second->getParent() != nullptr)
            {
                outFile << (pair.second->getParent())->getName() <<"\n";
            }
            else
            {
                outFile << "NULL\n";
            }
        }

        outFile << "\n__ENTRIES__\nNAME,DESCRIPTION,RANK,PARENT\n"; // Header line for entries

        for (const auto& pair : Entries) // Adding each entry to the file
        {
            outFile << pair.second->getName() << ",";
            outFile << pair.second->getDescription() << ",";
            outFile << (pair.second->getRank())->getName() << ",";
            if (pair.second->getParent() != nullptr)
            {
                outFile << (pair.second->getParent())->getName() <<"\n";
            }
            else
            {
                outFile << "NULL\n";
            }
        }

        outFile.close();

        cout << "Data successfully saved to " << filename << ".\n";
    }
    else
    {
        cout << "Error opening file to save data!" << endl;
    }
}



void TaxManager::loadFromFile(const string& filename)
{
    // Open the file as infile
    ifstream inFile(filename);
    if (inFile.is_open())
    {
        string tempLine;
        vector<tuple<string, string, string>> rankData; // Temporarily storing rank data
        vector<tuple<string, string, string, string>> entryData; // Temporarily storing entry data

        // Read the file line by line
        while(getline(inFile, tempLine))
        {
            if(tempLine == "__RANKS__") // Checking for ranks 
            {
                
                getline(inFile, tempLine); // Skip the header line

                while (getline(inFile, tempLine) && !tempLine.empty())
                {
                    string name, description, parentName;
                    stringstream tempSS(tempLine);
                    getline(tempSS, name, ',');
                    getline(tempSS, description, ',');
                    getline(tempSS, parentName);
                    rankData.push_back(make_tuple(name, description, parentName));
                }
            }
            else if (tempLine == "__ENTRIES__") // Checking for entries
            { 
        
                getline(inFile, tempLine); // Skip the header line

                while (getline(inFile, tempLine) && !tempLine.empty())
                {
                    string name, description, rankName, parentName;
                    stringstream tempSS(tempLine);
                    getline(tempSS, name, ',');
                    getline(tempSS, description, ',');
                    getline(tempSS, rankName, ',');
                    getline(tempSS, parentName);
                    entryData.push_back(make_tuple(name, description, rankName, parentName));
                }
            }

        }

        unordered_map<string, Rank*> rankMap; // Temporarily store ranks
        unordered_map<string, Entry*> entryMap; // Temporarily store entries

        // Create temporary Rank objects without resolving parents
        for (const auto& rankTuple : rankData)
        {
            string name = get<0>(rankTuple);
            string description = get<1>(rankTuple);
            // Not adding parent yet
            Rank* newRank = new Rank(name, description, nullptr);
            rankMap[name] = newRank;
        }

        // Create temporary Entry objects without resolving parents
        for (const auto& entryTuple : entryData)
        {
            string name = get<0>(entryTuple);
            string description = get<1>(entryTuple);
            string rankName = get<2>(entryTuple);
            // Not adding parent yet
            Entry* newEntry = new Entry(name, description, rankMap[rankName], nullptr);
            entryMap[name] = newEntry;
        }

        // Resolve parent relationships for ranks
        for (const auto& rankTuple : rankData)
        {
            string name = get<0>(rankTuple);
            string parentName = get<2>(rankTuple);
            if (parentName != "NULL")
            {
                rankMap[name]->setParent(rankMap[parentName]);
            }
        }

        // Resolve parent relationships for entries
        for (const auto& entryTuple : entryData)
        {
            string name = get<0>(entryTuple);
            string parentName = get<3>(entryTuple);
            if (parentName != "NULL")
            {
                entryMap[name]->setParent(entryMap[parentName]);
            }
        }

        // Add the resolved ranks to the main Ranks map
        for (const auto& pair : rankMap)
        {
            if (Ranks.find(pair.first) == Ranks.end()) // If rank does not exist add it
            {
                addRank(pair.second->getName(), pair.second->getDescription(), pair.second->getParent());
            }
        }
        
        // Add the resolved entries to the main Entries map
        for (const auto& pair : entryMap)
        {
            if (Entries.find(pair.first) == Entries.end()) // If entry does not exist add it
            {
                addEntry(pair.second->getName(), pair.second->getDescription(), pair.second->getRank(), pair.second->getParent());
            }
        }
        
        
    }
    else
    {
        cout << "Error opening file to load data!" << endl;
    }
}

