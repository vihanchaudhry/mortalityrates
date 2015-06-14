// Binary tree abstract base class
// Created by: Frank M. Carrano and Tim Henry
// Modified by: Jason Tiu



#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"
#include "Queue.h"
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <string>
#include <iostream>
using namespace std;
template <class ItemType>
class BinaryTree
{
protected:

	string compare;

	//Pointer to root node
    BinaryNode<ItemType>* rootPtr;

	//Number of nodes in the tree
    int count;							
    
public:

    // Constructor
    BinaryTree() {rootPtr = 0; count = 0;}
	BinaryTree(const BinaryTree<ItemType> & tree){rootPtr = tree.rootPtr; count = tree.size();}     
	
	BinaryTree(const BinaryTree<ItemType> & tree, string compareCode){ rootPtr = tree.rootPtr; count = tree.size(); compare = compareCode; }

	//Destructor
	~BinaryTree() {destroyTree(rootPtr); rootPtr = NULL; count = 0;}    

	//Overloade Operator
	BinaryTree & operator=(const BinaryTree & sourceTree);                                 

    // Binarytree functions
    bool isEmpty() const	{return count == 0;}
    int size() const	    {return count;}
    void clear()			{destroyTree(rootPtr); rootPtr = 0; count = 0;}          

	//Tree traversals
	void breadthFirst(void visit(ItemType )) const {_breadthFirst(visit, rootPtr); }
	void preOrder(void visit(ItemType )) const {_preorder(visit, rootPtr);}                
    void inOrder(void visit(ItemType )) const  {_inorder(visit, rootPtr);}                
    void postOrder(void visit(ItemType )) const{_postorder(visit, rootPtr);}  

	//Special functions for the project
	void print(){ _print(rootPtr); };
	void range(void visit(ItemType ), ItemType smallest, ItemType largest) const{ _range(visit, rootPtr, smallest, largest); }

    //Functions implemented by the derived class
    virtual bool insert(const ItemType & newData) = 0;
    virtual bool remove(const ItemType & data) = 0;
	virtual bool getEntry(const ItemType & anEntry, ItemType & returnedItem, void visit(ItemType)) const = 0;
    
private:
	//Functions within this class are declared to protect the rootptr from the main

	//Delete all the nodes from a tree
    void destroyTree(BinaryNode<ItemType>* nodePtr);  

	//Internal CopyTree
	BinaryNode<ItemType>* copyTree(const BinaryNode<ItemType>* nodePtr);

	//Internal Range and Print Functions
	void _range(void visit(ItemType ), BinaryNode<ItemType>* nodePtr, ItemType smallest, ItemType largest) const;
	void _print(BinaryNode<ItemType> *, int n = 1);
	
    //Internal Traversal Functions
	void _breadthFirst(void visit(ItemType ), BinaryNode<ItemType> *nodePtr) const;
    void _preorder(void visit(ItemType ), BinaryNode<ItemType>* nodePtr) const;            
    void _inorder(void visit(ItemType ), BinaryNode<ItemType>* nodePtr) const;             
    void _postorder(void visit(ItemType ), BinaryNode<ItemType>* nodePtr) const;           
	
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//											BINARY TREE FUNCTIONS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

//****************************************************************************************
//	The function takes a pointer that is the rootPtr of a tree and duplicates the		 *
//	entire tree onto a new dynamically allocated tree									 *
//****************************************************************************************
template<class ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::copyTree(const BinaryNode<ItemType>* nodePtr)
{
    BinaryNode<ItemType> *TempPtr;
	//If the pointer is null then a null value is returned to the caller
	if (!nodePtr)
	{
		return NULL;
	}

	//Otherwise we copy the value of the pointer and save it into a new pointer
	//The program then goes recursively through the tree setting the left and right
	//pointers to the previous node
	else
	{
		TempPtr = new BinaryNode<ItemType>(nodePtr->getItem());
		TempPtr->setLeftPtr(copyTree(nodePtr->getLeftPtr()));
		TempPtr->setRightPtr(copyTree(nodePtr->getRightPtr()));
		//return TempPtr;		
	}
	return TempPtr;
}

//****************************************************************************************
//	The function takes a pointer which is the rootPtr of a tree and recursively deletes  *
//	each node starting from the leaves to the root										 *
//****************************************************************************************
template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{

    //If the nodePtr is null then we return to the call
    if (!nodePtr)                                                                   
      return;

	//If the node is a leaf then we delete it and decrement the count
    if (nodePtr->isLeaf())
	{
        delete nodePtr;
        count--;
        return;
    }

	//Otherwise we go through the rest of the tree by doing recursive calls on each of the pointers
    destroyTree(nodePtr->getRightPtr());
    destroyTree(nodePtr->getLeftPtr());
    
    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//													TRAVERSALS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//****************************************************************************************
//	This function is a breadth first traversal implementation. The function takes in a	 *
//	a function pointer and a pointer that is the rootPtr of the tree. The function uses	 *
//	a queue to keep track of each of the node in the tree for each level. A node is		 *
//	inserted into the queue and is popped. The pointers of the node is then placed into	 *
//	the queue if it isn't null/															 *
//****************************************************************************************
template<class ItemType>
void BinaryTree<ItemType>::_breadthFirst(void visit(ItemType ), BinaryNode<ItemType> *nodePtr) const {

	//Variable declaration
	Queue<BinaryNode<ItemType> *> q1;
	BinaryNode<ItemType> *item;

	//If the tree is empty then nothing is printed
	if (!nodePtr)
		return;

	//Queue the root ptr
	q1.enqueue(nodePtr);

	//While the queue is populated dequeue the first item and print. Enqueue the pointers associated with this pointer starting from left to right.

    while (!q1.isEmpty())
	{

		q1.dequeue(item);
		visit(item->getItem());
		
		if (item->getLeftPtr())
			q1.enqueue(item->getLeftPtr());
		
		if (item->getRightPtr())
			q1.enqueue(item->getRightPtr());

	}
	/*
    Queue<BinaryNode<ItemType>*> q;
    q.enqueue(rootPtr);
    
    BinaryNode<ItemType> *nodePtr2;
    
    ItemType item;
    
    while(!q.isEmpty())
    {
        q.dequeue(nodePtr);
        item = nodePtr2->getItem();
        visit(item);
        if (nodePtr->getLeftPtr() != NULL)
            q.enqueue(nodePtr2->getLeftPtr());
        if (nodePtr->getRightPtr() != NULL)
            q.enqueue(nodePtr2->getRightPtr());
    }
	*/
}

//****************************************************************************************
//	This function is an implementation of a preorder traversal. The function takes in a	 *
//	pointer that is the root of the tree. The function then goes through the tree		 *
//	recursively																			 *
//****************************************************************************************
template<class ItemType>
void BinaryTree<ItemType>::_preorder(void visit(ItemType ), BinaryNode<ItemType>* nodePtr) const
{
	//If the pointer isn't null then the value of the pointer is extracted and printed
	//The function then goes recursively through the tree starting with the left pointer then
	//the righ pointer as in a preorder traversal
    if (nodePtr != 0)
    {
        ItemType item = nodePtr->getItem();
        visit(item);
        _preorder(visit, nodePtr->getLeftPtr());
        _preorder(visit, nodePtr->getRightPtr());
    }
}


//****************************************************************************************
//	This function is an implementation of a inorder traversal. The function takes in a	 *
//	pointer that is the root of the tree. The function then goes through the tree		 *
//	recursively																			 *
//****************************************************************************************
template<class ItemType>
void BinaryTree<ItemType>::_inorder(void visit(ItemType ), BinaryNode<ItemType>* nodePtr) const
{
	//If the pointer isn't null then the value of the current node is extracted. The function then
	//makes a recursive call passing in the left pointer. It then prints the value of the node
	//then make a recursive call passing in the right pointer as in a inorder traversal
	if (nodePtr != 0)
    {
        ItemType item = nodePtr->getItem();
        _inorder(visit, nodePtr->getLeftPtr());
        visit(item);
        _inorder(visit, nodePtr->getRightPtr());
    }
}

//****************************************************************************************
//	This function is an implementation of a postorder traversal. The function takes in a *
//	pointer that is the root of the tree. The function then goes through the tree		 *
//	recursively																			 *
//****************************************************************************************
template<class ItemType>
void BinaryTree<ItemType>::_postorder(void visit(ItemType ), BinaryNode<ItemType>* nodePtr) const
{
	//If the pointer isn't null then the value of the current node is extracted. The function then
	//makes a recursivel call passing in the left pointer. It then makes a recursive call passing in
	//the right pointer and then finally printing the value of the node as in a post order traversal
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		_postorder(visit, nodePtr->getLeftPtr());
		_postorder(visit, nodePtr->getRightPtr());
		visit(item);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//													SPECIAL AUXILLARY FUNCTIONS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//*******************************************************************************
//	The function takes in a function pointer, a pointer that is the root of the *
//	tree, and 2 itemtypes. The function goes throug the tree inorder and		*
//	displays the value of the items that are greater than or equal to the		*
//	smallest value and that are less than or equal to the largest value			*
//*******************************************************************************
template<class ItemType>
void BinaryTree<ItemType>::_range(void visit(ItemType ), BinaryNode<ItemType>* nodePtr, ItemType smallest, ItemType largest) const
{
	//If the node pointer isn't null then the item of the current node is extracted and stored
	//the function the goes recursively through the list in an inorder traversal. The function
	//then prints the value of the item if it is greater than or equal to the smallest item
	//that was passed in the function and is less than or equal to the largest item
	if (nodePtr != NULL)
	{
		ItemType item = nodePtr->getItem();

		_range(visit, nodePtr->getLeftPtr(), smallest, largest);

		if (*item >= *smallest && *item <= *largest)
			visit(item);
		
		
		_range(visit, nodePtr->getRightPtr(), smallest, largest);
	}
}

//*******************************************************************************
//	The function takes in a node pointer and an int that has a default			*
//	parameter. The function then goes through the tree in a reverse inorder		*
//	traversal and prints out the value of the item if it is a leaf. It then		*
//	prints the value of the current node with the appropraiate level numbers	*
//	it utilises the setw function to format the data							*
//*******************************************************************************
template<class ItemType>
void BinaryTree<ItemType>::_print(BinaryNode<ItemType> *nodePtr, int n ){

	//If node pointer is null then the function returns to the caller
	if (!nodePtr)
		return;
	
	//If the nodePointer is a leaf then it prints the value with the approriate width
	if (nodePtr->isLeaf())
	{
		cout << setw((n-1)*5) << n << ". " << *(nodePtr->getItem()) << endl;
		return;
	}

	//Otherwise the function goes through a recursive call passing in the incremented level variable
	else
	{
		_print(nodePtr->getRightPtr(), n + 1);
		cout << setw((n-1)*5) << n << ". " << *(nodePtr->getItem())<< endl;
		_print(nodePtr->getLeftPtr(), n + 1);

	}

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//															OVERLOADED OPERATOR
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//**************************************************************************************************
//	The function overloads the '=' operator of the class it takes in a binary tree. It first	   *
//	destroys the tree on the pointer on the left side of the operator. The rootpointer of the      *
//	tree is then set to a duplicate of the tree by use of the copyTree function. The count function*
//	is set to the count function of the sourceTree.                                                *
//**************************************************************************************************
template<class ItemType>
BinaryTree<ItemType> & BinaryTree<ItemType>::operator=(const BinaryTree<ItemType> & sourceTree)
{
	//The tree is destroyed
    destroyTree(rootPtr);

	//The root pointer is set to a replica of the sourceTree
	rootPtr = copyTree(sourceTree.rootPtr);

	//Count is set to the corresponding tree
    count = sourceTree.count;

	//The rootPointer is dereferenced and returned as a Tree
	return *this;
}  

#endif
