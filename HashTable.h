//
//  HashTable.h
//  Jason_Liang_HW5_22C_HashTableWithVectors
//
//  Created by Jason Liang on 6/6/15.
//  Copyright (c) 2015 JasonLiang. All rights reserved.
//

#ifndef __Jason_Liang_HW5_22C_HashTableWithVectors__HashTable__
#define __Jason_Liang_HW5_22C_HashTableWithVectors__HashTable__

#include <stdio.h>
#include <iostream>
#include "Country.h"
#include <vector>

using namespace std;

const int HASH_TABLE_SIZE = 776;
const int BUCKET_SIZE = 10;

template <class T>
class HashTable
{
private:
    vector<T *> *table;
    vector<T *> overflow;
    int collisionCount;
    int elementsFilled;
    int fullBuckets;
public:
    HashTable();
    ~HashTable();
    
    int getCollisionCount() {return collisionCount;}
    int getElementsFilled() {return elementsFilled;}
    int getFullBuckets() {return fullBuckets;}
    int getOverflowCount() {return overflow.size();}
    
    vector<T *> *getTable() {return table;}
    vector<T *> getOverflow() {return overflow;}
    
    double getLoadFactor() {return (double)elementsFilled / HASH_TABLE_SIZE;}
    double getAverageNodesInBucket();
    
    int getHash(string key);
    bool insert(T *itemPtr);
    T *search(string name);
};

// Function Definitions

/*~~~~~~
 Default constructor for preparing hash table to be used.
 */
template <class T>
HashTable<T>::HashTable()
{
    table = new vector<T *>[HASH_TABLE_SIZE];
    collisionCount = 0;
    elementsFilled = 0.0;
    fullBuckets = 0;
}

/*~~~~~~~~
 Destructor for destroying all dynamically allocated data.
*/
template <class T>
HashTable<T>::~HashTable()
{
    
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        for (int j = 0; j < table[i].size(); j++)
        {
            delete table[i][j];
        }
        
        table[i].clear();
    }
    
    for (int i = 0; i < overflow.size(); i++)
    {
        delete overflow[i];
    }
    
    overflow.clear();
}

/*~~~~
 return on average how many nodes are in each bucket.
 */
template <class T>
double HashTable<T>::getAverageNodesInBucket()
{
    int sum = 0;
    
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        for (int j = 1; j < table[i].size(); j++)
        {
            sum += 1;
        }
    }
    
    return (double)sum / elementsFilled;
}

/*~~~~~~~~~~~~~
 Hash function returns a suitable key
 */
template <class T>
int HashTable<T>::getHash(string key)
{
    int sum = 0;
    
    for (int i = 0; i < key.length(); i++)
    {
        sum += (key[i]*key[i] *key[i]);
    }
    
    return sum % HASH_TABLE_SIZE;
}

/*~~~~~~~~~~~
 insert into hash table.  If inserted into overflow, return false, else true.
 */
template <class T>
bool HashTable<T>::insert(T *itemPtr)
{
    if (table[getHash(itemPtr->getName())].size() < BUCKET_SIZE)
    {
        table[getHash(itemPtr->getName())].push_back(itemPtr);
        
        if (table[getHash(itemPtr->getName())].size() == 1)
            elementsFilled++;
        else
            collisionCount++;
        
        if (table[getHash(itemPtr->getName())].size() == BUCKET_SIZE)
            fullBuckets++;
        
        return true;
    }
    else
    {
        overflow.push_back(itemPtr);
        collisionCount++;
        return false;
    }
}

/*~~~~~~~~~~~~
 Search the hash table for item identified by the argument.
 */
template <class T>
T *HashTable<T>::search(string name)
{
    
    for (int i = 0; i < table[getHash(name)].size(); i++)
    {
        if (table[getHash(name)][i]->getName() == name)
        {
            return table[getHash(name)][i];
        }
    }
    
    // Not found in buckets; check overflow
    
    for (int i = 0; i < overflow.size(); i++)
    {
        if (overflow[i]->getName() == name)
        {
            return overflow[i];
        }
    }
    
    return NULL;
}

#endif /* defined(__Jason_Liang_HW5_22C_HashTableWithVectors__HashTable__) */
