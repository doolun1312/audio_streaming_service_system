#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_
/*
hashTable.h
Author: M00835210
Created: 11/04/2023
Updated: 17/04/2023
*/

#include "tracks.h"
#include <vector>

/*Pair class defining the key and value of a pair in the hash table*/
struct Pair {
    std::string key; 
    Track value; 

    Pair(std::string key, Track value) {
        this->key = key;
        this->value = value; 
    }
};

/*Hashtable class defining and handling thourght functions, add, remove, resize, index and find the hash table */
class hashTable {
private: 
    Pair** table;
    unsigned size; 
    unsigned total; 

public:
    hashTable(unsigned inputSize); 
    ~hashTable(); 

    Pair** getTable(); 
    unsigned getSize(); 
    unsigned getTotal(); 

    unsigned hashTableKey(std::string key); 
    void add(std::string key, Track value);
    void remove(unsigned position);
    void resize(unsigned size);
    int index(std::string key, std::string value); 
    std::vector<Pair*> find(std::string key);
    std::vector<Pair*> finddel(std::string key);
    std::vector<Pair*> findPair(std::string key, std::string title);

};

#endif
