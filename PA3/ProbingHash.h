#ifndef __PROBING_HASH_H
#define __PROBING_HASH_H

#include <vector>
#include <stdexcept>

#include "Hash.h"

using std::vector;
using std::pair;

// Can be used for tracking lazy deletion for each element in your table
enum EntryState {
    EMPTY = 0,
    VALID = 1,
    DELETED = 2
};

template<typename K, typename V>
class ProbingHash : public Hash<K, V> { // derived from Hash
private:
    // Needs a table and a size.
    // Table should be a vector of std::pairs for lazy deletion
    vector<pair<K, V>> table;
    vector<EntryState> entryStates;
    int tableSize;
    int currSize;

public:
    //Constructor
    ProbingHash(int n = 11) : tableSize(n), currSize(0) {
        table.resize(n);
        entryStates.resize(n, EntryState::EMPTY);
    }
    //Destructor
    ~ProbingHash() {
        this->clear();
    }
    //Returns current size
    int size() {
        return currSize;
    }
    //Returns V value from key
    V operator[](const K& key) {
        int index = hash(key);
        int initialIndex = index;
        int i = 1;
        while (entryStates[index] != EntryState::EMPTY) {
            /*std::cout << "Checking index: " << index << " with key: " << table[index].first << std::endl;*/
            if (entryStates[index] == EntryState::VALID && table[index].first == key) {
                /*std::cout << "Found key: " << key << " at index: " << index << " with value: " << table[index].second << std::endl;*/
                return table[index].second;
            }
            index = (initialIndex + i) % tableSize;
            i++;
            if (index == initialIndex) {
                std::cout << "Key not found: " << key << std::endl;
                return V();
            }
        }
        cout << "Key not found: " << key << endl;
        return V();
    }

    //Inserts a key and value
    bool insert(const std::pair<K, V>& pair) {
        try {
            /*std::cout << "Inserting key: " << pair.first << " value: " << pair.second << std::endl;*/
            if (currSize >= tableSize / 2) {
                rehash();
            }
            int index = hash(pair.first);
            int initialIndex = index;
            int i = 1;
            while (entryStates[index] == EntryState::VALID) {
                /* std::cout << "Collision at index: " << index << std::endl;*/
                if (table[index].first == pair.first) {
                    /*std::cout << "Updating an existing key" << std::endl;*/
                    table[index].second = pair.second;
                    return true;
                }
                index = (initialIndex + i) % tableSize;
                i++;
            }
            /*std::cout << "Inserting at index: " << index << std::endl;*/
            table[index] = pair;
            entryStates[index] = EntryState::VALID;
            currSize++;
            return true;
        }
        //Error catching for invalid values
        catch (const std::exception& e) {
            std::cerr << "ProbingHash exception: " << e.what() << std::endl;
            return false;
        }
    }

    //Erases a value from table using key
    void erase(const K& key) {
        try {
            int index = findIndex(key);
            if (index != -1) {
                entryStates[index] = EntryState::DELETED;
                currSize--;
            }
        }
        catch (const std::exception& e) {
            std::cerr << "ProbingHash exception: " << e.what() << std::endl;
        }
    }

    //Clears whole table
    void clear() {
        table.assign(tableSize, pair<K, V>());
        entryStates.assign(tableSize, EntryState::EMPTY);
        currSize = 0;
    }

    //Gets bucket count
    int bucket_count() {
        return tableSize;
    }

    //Gets load factor
    float load_factor() {
        return static_cast<float>(currSize) / tableSize;
    }

private:
    int findNextPrime(int n)
    {
        while (!isPrime(n))
        {
            n++;
        }
        return n;
    }

    int isPrime(int n)
    {
        for (int i = 2; i <= sqrt(n); i++)
        {
            if (n % i == 0)
            {
                return false;
            }
        }

        return true;
    }

    //Hash algorithm
    int hash(const K& key) {
        return std::hash<K>{}(key) % tableSize;
    }

    //Finds the index of a key
    int findIndex(const K& key)
    {
        int index = hash(key);
        int initialIndex = index;
        int i = 1;
        while (entryStates[index] != EntryState::EMPTY)
        {
            if (entryStates[index] == EntryState::VALID && table[index].first == key)
            {
                return index;
            }
            index = (initialIndex + i) % tableSize;
            i++;
        }
        return -1;
    }

    //Rehashes the table
    void rehash() {
        /* std::cout << "Rehashing..." << std::endl;*/
        int newTableSize = findNextPrime(tableSize * 2);
        std::vector<std::pair<K, V>> newTable(newTableSize);
        std::vector<EntryState> newEntryStates(newTableSize, EntryState::EMPTY);

        for (int i = 0; i < tableSize; i++) {
            if (entryStates[i] == EntryState::VALID) {
                int newIndex = hash(table[i].first) % newTableSize;  // Use the new table size to recalculate the hash
                int initialIndex = newIndex;  // Use the new table size for initial index
                int j = 1;
                while (newEntryStates[newIndex] == EntryState::VALID) {
                    newIndex = (initialIndex + j) % newTableSize;  // Use the new table size for newIndex
                    j++;
                }
                newTable[newIndex] = table[i];
                newEntryStates[newIndex] = EntryState::VALID;
            }
        }

        table = newTable;
        entryStates = newEntryStates;
        tableSize = newTableSize;
        /*std::cout << "Rehash complete." << std::endl;*/
    }



};


#endif //__PROBING_HASH_H
