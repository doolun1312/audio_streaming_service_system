/*
hashTable.cpp
Author: M00835210
Created: 11/04/2023
Updated: 20/04/2023
*/

#include "hashTable.h"
#include <vector>

hashTable::hashTable(unsigned inputSize) {
    this->size = inputSize;
    this->total = 0;
    this->table = new Pair*[size];
    for (unsigned i = 0; i < size; i++) {
        table[i] = nullptr;
    }
}

hashTable::~hashTable() {
    for (unsigned i = 0; i < size; i++) {
        if (table[i] != nullptr) {
            delete table[i];
        }
    }
    delete[] table;
}

/* 
    Display the table containing the pairs of the hash table
    @param none
    @return table
*/
Pair** hashTable::getTable() {
    return table;
}

/* 
    Display the size of the hash table containing the pairs 
    @param none
    @return size
*/
unsigned hashTable::getSize() {
    return size;
}

/* 
    Display the total number of elements that are in the hash table
    @param none
    @return total
*/
unsigned hashTable::getTotal() {
    return total;
}

/* 
    Get the hash table key 
    @param key
    @return hashTable % size
*/
unsigned hashTable::hashTableKey(std::string key) {
    unsigned hashTable = 0;
    for (char c : key) {
        if (c != ' ') { // ignore spaces in the key
            hashTable = hashTable * 31 + c;
        }
    }
    return hashTable % size;
}

/* 
    Add a pair to the hash table
    @param key, value
    @return none
*/
void hashTable::add(std::string key, Track value) {
    Pair* pair = new Pair(key, value);
    unsigned index = hashTableKey(key);
    while (table[index] != nullptr) {
        index = (index + 1) % size;
    }
    table[index] = pair;
    total++;
}

/* 
    Remove a pair from the hash table
    @param position
    @return none
*/
void hashTable::remove(unsigned position) {
    if (table[position] != nullptr) {
        delete table[position];
        table[position] = nullptr;
        total--;
    }
}

/* 
    Resize the hash table
    @param newSize
    @return none
*/
void hashTable::resize(unsigned newSize) {
    Pair** newTable = new Pair*[newSize];
    for (unsigned i = 0; i < newSize; i++) {
        newTable[i] = nullptr;
    }
    for (unsigned i = 0; i < size; i++) {
        if (table[i] != nullptr) {
            unsigned newIndex = hashTableKey(table[i]->key);
            while (newTable[newIndex] != nullptr) {
                newIndex = (newIndex + 1) % newSize;
            }
            newTable[newIndex] = table[i];
        }
    }
    delete[] table;
    table = newTable;
    size = newSize;
}

/* 
    Get the index of a pair
    @param key, title
    @return index or -1 if pair is not found
*/
int hashTable::index(std::string key, std::string title) {
    unsigned index = hashTableKey(key);
    while (table[index] != nullptr) {
        if (table[index]->key == key && table[index]->value.getTitle() == title) {
            return index;
        }
        index = (index + 1) % size;
    }
    return -1; 
}

/* 
    Find pairs in the hash table and store them in a vector
    @param key
    @return results (vector of pairs found)
*/
std::vector<Pair*> hashTable::find(std::string key) {
    std::vector<Pair*> results;
    unsigned index = hashTableKey(key);
    unsigned startingIndex = index;
    
    do {
        if (table[index] != nullptr && table[index]->key == key) {
            results.push_back(table[index]);
        }
        index = (index + 1) % size;
    } while (index != startingIndex);
    
    return results;
}

/* 
    Find pairs in the hash table for the delete function and store them in a vector
    @param key
    @return results (vector of pairs found)
*/
std::vector<Pair*> hashTable::finddel(std::string key) {
    std::vector<Pair*> pairs;
    unsigned index = hashTableKey(key);
    while (table[index] != nullptr) {
        if (table[index]->key == key) {
            pairs.push_back(table[index]);
        }
        index = (index + 1) % size;
    }
    return pairs;
}

/* 
    Find pairs in the hash table and store them in a vector
    @param key, title
    @return results (vector of pairs found)
*/
std::vector<Pair*> hashTable::findPair(std::string key, std::string title) {
    std::vector<Pair*> results;
    unsigned index = hashTableKey(key);
    unsigned startingIndex = index;
    
    do {
        if (table[index] != nullptr && table[index]->key == key && table[index]->value.getTitle() == title) {
            results.push_back(table[index]);
        }
        index = (index + 1) % size;
    } while (index != startingIndex);
    
    return results;
}