// Pointer to data for duplicate tree
// Created by Victor La
 
#ifndef _ITEM_POINTER
#define _ITEM_POINTER

#include "Country.h"

class ItemPointer
{   
private:
	Country * itemPointer;         // Pointer to data

public:
	// constructors
	ItemPointer()	{ itemPointer = 0; }
	ItemPointer(Country * pointerData) { itemPointer = pointerData; }
	
	// accessors
	Country *getItem() const{ return itemPointer; }
	void setItem(Country *item) { itemPointer = item; }
	void setCompare(string compare) { itemPointer->setCompare(compare); }
	string getCompare() { return itemPointer->getCompare(); }

	// overloaded operators
	bool operator < (const ItemPointer & other)
		const { return itemPointer->getName() < other.itemPointer->getName(); };
	bool operator > (const ItemPointer & other)
		const { return itemPointer->getName() > other.itemPointer->getName(); };
	bool operator == (const ItemPointer & other)
		const {	return itemPointer->getName() == other.itemPointer->getName(); };
	bool operator <= (const ItemPointer & other)
		const {	return itemPointer->getName() <= other.itemPointer->getName(); };
	bool operator >= (const ItemPointer & other)
		const {	return itemPointer->getName() >= other.itemPointer->getName(); };
	friend ostream& operator<<(ostream& os, const ItemPointer & ptr);
	ItemPointer & operator=(const ItemPointer * source) { 
		this->setItem(source->getItem());
	};
	
}; 

ostream& operator<<(ostream& os, const ItemPointer & ptr)
{
	os << ptr.getItem()->getName() << endl;
	return os;
}
#endif 
