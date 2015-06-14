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
const int BUCKET_SIZE = 4;

template <class T>
class HashTable
{
private:
    vector<T *> *table;
    vector<T *> *overflow;
    int collisionCount;
    int elementsFilled;
    int fullBuckets;
public:
    HashTable();
    ~HashTable();
    
    int getCollisionCount() {return collisionCount;}
    int getElementsFilled() {return elementsFilled;}
    int getFullBuckets() {return fullBuckets;}
    int getOverflowCount() {return overflow->size();}
    
    vector<T *> *getTable() {return table;}
    vector<T *> *getOverflow() {return overflow;}
    
    double getLoadFactor() {return (double)elementsFilled / HASH_TABLE_SIZE;}
    double getAverageNodesInBucket();
    
    int getHash(string key);
    bool insert(T *itemPtr);
    T *search(string name);
	bool deleteItem(string key);
};

// Function Definitions

/*~~~~~~
 Default constructor for preparing hash table to be used.
 Dynamically allocate an array of vectors, and set all statistic fields to 0.
*/
template <class T>
HashTable<T>::HashTable()
{
    table = new vector<T *>[HASH_TABLE_SIZE];
	overflow = new vector<T *>;
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
    
    for (int i = 0; i < overflow->size(); i++)
    {
        delete (*overflow)[i];
    }
    
    overflow->clear();
<<<<<<< HEAD
    
    //delete table;
    //delete overflow;
=======
>>>>>>> 08ae1b9950351e4e8f9d6e579cd8d871c30d1d10
}

/*~~~~
 Return on average how many nodes are in each bucket.
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
 Hash function returns a suitable key.
*/
template <class T>
int HashTable<T>::getHash(string key)
{
    int sum = 0;
    
    for (int i = 0; i < key.length(); i++)
    {
        sum += (key[i]*key[i] *key[i]);
    }
    
    return (sum % HASH_TABLE_SIZE);
}

/*~~~~~~~~~~~
 Insert into hash table.  If inserted into overflow, return false, else true.
*/
template <class T>
bool HashTable<T>::insert(T *itemPtr)
{
    int address = getHash(itemPtr->getID());
    if (table[address].size() < BUCKET_SIZE)
    {
        table[address].push_back(itemPtr);
        
        if (table[address].size() == 1)     // First element in vector is filled,
            elementsFilled++;
        else                                // else collision occured.
            collisionCount++;
        
        if (table[address].size() == BUCKET_SIZE)       // Bucket is full.
            fullBuckets++;
        
        return true;
    }
    else                                        // Push into overflow.
    {
        overflow->push_back(itemPtr);
        collisionCount++;                       // else collision occured.
        return false;
    }
}

/*~~~~~~~~~~~~~~
 Delete a particular item in the hash table.
*/
template <class T>
bool HashTable<T>::deleteItem(string ID)
{
	int address = getHash(ID);
    
	for (int i = 0; i < table[address].size(); i++)
    {
		if (table[address][i]->getID() == ID)
        {
			delete table[address][i];
			table[address].erase(table[address].begin() + i);
			return true;
		}
	}

	for (int i = 0; i < (*overflow).size(); i++)
	{
		if ((*overflow)[i]->getID() == ID)
		{
			delete (*overflow)[i];
			(*overflow).erase((*overflow).begin() + i);
			return true;
		}
	}
	return false;
}

/*~~~~~~~~~~~~
 Search the hash table for item identified by the argument.
 Return the pointer to the object.
 */
template <class T>
T *HashTable<T>::search(string ID)
{
    int address = getHash(ID);
    
    for (int i = 0; i < table[address].size(); i++)
    {
        if (table[address][i]->getID() == ID )
        {
            return table[getHash(ID)][i];
        }
    }
    
    // Not found in buckets; check overflow
    
    for (int i = 0; i < overflow->size(); i++)
    {
        if ((*overflow)[i]->getID() == ID)
        {
            return (*overflow)[i];
        }
    }
    
    return NULL;        // not found.
}

#endif /* defined(__Jason_Liang_HW5_22C_HashTableWithVectors__HashTable__) */
