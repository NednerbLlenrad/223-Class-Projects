/*
 *  Separate chaining hashtable
 */

#ifndef __CHAINING_HASH_H
#define __CHAINING_HASH_H

 // Standard library includes
#include <iostream>
#include <vector>
#include <list>
#include <stdexcept>

// Custom project includes
#include "Hash.h"

// Namespaces to include
using std::vector;
using std::list;
using std::pair;

using std::cout;
using std::endl;

//
// Separate chaining based hash table - derived from Hash
//
template<typename K, typename V>
class ChainingHash : public Hash<K, V> {
private:
    vector<list<pair<K, V>>> hashTable;
    int tableSize;
public:
    //Constructor
    ChainingHash(int n = 11) : tableSize(n) {
        hashTable.resize(n);
    }

    //Destructor
    ~ChainingHash() {
        this->clear();
    }

    //Gets the size through iteration
    int size() {
        int count = 0;
        for (const auto& bucket : hashTable)
        {
            count += bucket.size();
        }
        return count;
    }

    //Gets the V value from the key
    V operator[](const K& key) {
        int index = hash(key);
        for (const auto& entry : hashTable[index])
        {
            if (entry.first == key)
            {
                return entry.second;
            }
        }
    }

    //Inserts the value pair using push_back and vectors
    bool insert(const std::pair<K, V>& pair) {
        int index = hash(pair.first);
        auto& bucket = hashTable[index];
        for (auto& entry : bucket) {
            if (entry.first == pair.first) {
                entry.second = pair.second; // Update the value for an existing key
                return true;
            }
        }
        // Key not found, add a new entry
        bucket.push_back(pair);
        return true;
    }

    //Erases tthe value
    void erase(const K& key) {
        int index = hash(key);
        auto& bucket = hashTable[index];
        bucket.remove_if([key](const std::pair<K, V>& entry) {
            return entry.first == key;
            });
    }

    //Clears the whole table
    void clear() {
        for (auto& bucket : hashTable)
        {
            bucket.clear();
        }
    }

    //Returns bucket count
    int bucket_count() {
        return tableSize;
    }

    //Returns load factorl
    float load_factor() {
        return static_cast<float>(size()) / tableSize;
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
        return key % tableSize;
    }

};

#endif //__CHAINING_HASH_H
