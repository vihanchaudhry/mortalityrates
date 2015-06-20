// Specification and implementation file for the HashTable ADT class
/*
	Description:
		The hashtable ADT stores country objects into a two dimensional vector
		with a specific address obtained from a hash function. This allows for 
		data to be found either instantaneously or with few steps.

	Added by: Jason Liang
*/
#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <iostream>
#include <vector>
#include "Country.h"
using namespace std;

const int BUCKET_SIZE = 4;

template <class T>
class HashTable
{
private:
    int hashTableSize;
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
	int getHashTableSize() { return hashTableSize; }
    
    vector<T *> *getTable() {return table;}
    vector<T *> *getOverflow() {return overflow;}
    
	double getLoadFactor() { return (double)elementsFilled / hashTableSize; }
    double getAverageNodesInBucket();
    
    int getHash(string key);
    bool insert(T *itemPtr);
    T *search(string name);
	bool deleteItem(string key);
	int getPrime(int num);
    // Rehash
    void rehash();
};

// Function Definitions

/*~~~~~~
 Default constructor for preparing hash table to be used.
 Dynamically allocate an array of vectors, and set all statistic fields to 0.
*/
template <class T>
HashTable<T>::HashTable()
{
	hashTableSize = 400;          // Arbitrary 400.
	table = new vector<T *>[hashTableSize];
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
	for (int i = 0; i < hashTableSize; i++)
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
}

/*~~~~
 Return on average how many nodes are in each bucket.
 */
template <class T>
double HashTable<T>::getAverageNodesInBucket()
{
    int sum = 0;
    
	for (int i = 0; i < hashTableSize; i++)
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
    // Sum up the cubes of the ASCII values 
	// of each character of the string given
    for (int i = 0; i < key.length(); i++)
    {
        sum += (key[i] * key[i] * key[i]);
    }
	// Perform modulo division on the
	// generated key and return it
	return (sum % hashTableSize);
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

template <class T>
int HashTable<T>::getPrime(int num){
	while (true){

		int i = 2;
		for (; i < num; i++){
			if (num%i == 0)
				break;
		}
		if (i == num){
			return num;
		}
		num++;

	}
}


/*~~~~~~~~
 This function recreates a hash table so that the overflow is empty.
*/
template <class T>
void HashTable<T>::rehash()
{
	vector<T *> *temp = new vector<T *>;
	// Store every pointer in overflow vector, and clear hash table.
	for (int i = 0; i < hashTableSize; i++)
    {

        for (int j = 0; j < table[i].size(); j++)
        {
            temp->push_back(table[i][j]);
        }
		
        table[i].clear();
    }
	for (int i = 0; i < overflow->size(); i++){
		temp->push_back((*overflow)[i]);
	}
	overflow->clear();

	// Increase size so to get less overflow.
	hashTableSize = getPrime(hashTableSize*2);     

	// create a new Hash Table
	table = new vector<T *>[hashTableSize];       
    collisionCount = 0;
    elementsFilled = 0.0;
    fullBuckets = 0;

	// Refill the Hash table.
	for (int i = 0; temp->size() > 0; )     
    {
		insert((*temp)[i]);
		(*temp).erase((*temp).begin());
    }
}


#endif
