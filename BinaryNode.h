// Specification and implementation file for the BinaryNode ADT class
/*
	Description:
		The BinaryNode class holds pointers country objects created during the file read 
		process. They are then inserted into two BSTs sorted by different keys.

	Added by: Jaison Tiu
	Using: CIS22C Original File
*/
#ifndef BINARYNODE_H
#define BINARYNODE_H

template<class ItemType>
class BinaryNode
{
private:
	//Data portion
    ItemType              item;         

	// Pointer to left child
    BinaryNode<ItemType>* leftPtr;		
    
	// Pointer to right child
	BinaryNode<ItemType>* rightPtr;		
    
public:
    // Constructors
    BinaryNode(const ItemType & anItem)	{item = anItem; leftPtr = 0; rightPtr = 0;}
    BinaryNode(const ItemType & anItem,
               BinaryNode<ItemType>* left,
               BinaryNode<ItemType>* right) {item = anItem; leftPtr = left; rightPtr = right;}
    // Setters
    void setItem(const ItemType & anItem) {item = anItem;}
    void setLeftPtr(BinaryNode<ItemType>* left) {leftPtr = left;}
    void setRightPtr(BinaryNode<ItemType>* right) {rightPtr = right;}
    
	// Getters
    ItemType getItem() const    {return item;}
    BinaryNode<ItemType>* getLeftPtr() const  {return leftPtr;}
    BinaryNode<ItemType>* getRightPtr() const {return rightPtr;}
    
	//isLeaf function returns whether the node has any children
    bool isLeaf() const {return (leftPtr == 0 && rightPtr == 0);}
}; 

#endif 
