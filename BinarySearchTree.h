// Binary Search Tree ADT
// Created by: Frank M. Carrano and Tim Henry
// Modified by: Jason Tiu

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"

template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{
private:
    using BinaryTree<ItemType>::rootPtr;
    using BinaryTree<ItemType>::count;
   
	// internal insert node: insert newNode in nodePtr subtree
    BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode);            
    
    // internal remove node: locate and delete target node under nodePtr subtree
    BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, const ItemType target, bool & success);
    
    // delete target node from tree, called by internal remove node
    BinaryNode<ItemType>* deleteNode(BinaryNode<ItemType>* targetNodePtr);
    
    // remove the leftmost node in the left subtree of nodePtr
    BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType & successor);
    
    // search for target node
    BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr, const ItemType & target) const;
    
public:
    // insert a node at the correct location
    bool insert(const ItemType & newEntry);
    // remove a node if found
    bool remove(const ItemType & anEntry);
    // find a target node
	bool getEntry(const ItemType & target, ItemType & returnedItem) const;	
};

//************************************************************************************
// The function takes an item and allocates a node for the item. The node is then    *
//	passed to the internal insert function. The function the returns true if it      *
//	was successful																	 *
//************************************************************************************
template <class ItemType>
bool BinarySearchTree<ItemType>::insert(const ItemType & newEntry)
{
    BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
	rootPtr = _insert(rootPtr, newNodePtr);
	return true;
}

//**************************************************************************************
//	The function takes an item and finds the item in the tree and removes it. If it    *
//	finds the value and removes it then it returns a true otherwise it returns a false *
//**************************************************************************************
template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType & target)
{
    bool isSuccessful = false;
    rootPtr = _remove(rootPtr, target, isSuccessful);
    return isSuccessful;
}

//************************************************************************************
//	The function takes in two items. The function goes through the tree depending on *
//	the value it goes through the right or left pointer. If it finds it then it		 *
//	returns true otherwise it returns false											 *
//************************************************************************************
template<class ItemType>
bool BinarySearchTree<ItemType>::getEntry(const ItemType& anEntry, ItemType & returnedItem) const
{
	BinaryNode<ItemType>* nodePtr = rootPtr;

	while (nodePtr != NULL)
	{
		if (nodePtr->getItem() == anEntry)
		{
			returnedItem = nodePtr->getItem();
			return true;
		}
		else if (anEntry < nodePtr->getItem())
			nodePtr = nodePtr->getLeftPtr();
		else
			nodePtr = nodePtr->getRightPtr();
	}

	return false;
}




//************************************************************************************
//	The function takes in a nodePtr that is the rootPtr of the tree and a pointer to *
//	a dynamically allocated node. The function then recursively goes through the tree*
//	to find where it should set the node.											 *
//************************************************************************************
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr,
                                                          BinaryNode<ItemType>* newNodePtr)
{
	//If the nodePtr is null then it increments the count and returns the newNodePtr to the call
    if (!nodePtr)
    {
		count++;
        return newNodePtr;
    }
    
	//Otherwise it compares the vale of the newNode to the current node and if it is less than
	//the currentNode then it goes through the currentNode's left pointer. the current pointer's left
	//value is then set to the return statement of the recursive function call. Otherwise it goes through
	//the right pointer
    if (newNodePtr->getItem() < nodePtr->getItem())
    {
        nodePtr->setLeftPtr(_insert(nodePtr->getLeftPtr(), newNodePtr));
    }
    else
    {
        nodePtr->setRightPtr(_insert(nodePtr->getRightPtr(), newNodePtr));
    }
    return nodePtr;
}


//************************************************************************************
//	The function takes in a pointer to the node that is the rootPtr, a itemtype,	 *
//	and a boolean. If the nodePtr is null then the boolean is set to false.			 *
//	Otherwise the value of the nodePointer is compared to the item and depending	 *
//	on the whether it is greater than or equal to or less than it goes through the	 *
//	right pointer and left pointer respectively.									 *
//************************************************************************************
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr,
                                                          const ItemType target,
                                                          bool & success)

{
	//If the pointer is null that means that no node in the traversal matched the target therfore return false
    if (nodePtr == 0)
    {
        success = false;
        return 0;
    }

	//If the node is greater than the target then we go through the left subtree
    if (nodePtr->getItem() > target)
        nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
    
	//If the node is less than the target then we go through the right subtree
	else if (nodePtr->getItem() < target)
        nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
    
	//Otherwise the node has the value we are looking for and we delete the node
	else
    {
        nodePtr = deleteNode(nodePtr);
        success = true;
    }
    return nodePtr;
}

//************************************************************************************
//	Delete function came with the BST library										 *
//************************************************************************************
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::deleteNode(BinaryNode<ItemType>* nodePtr)
{
    if (nodePtr->isLeaf())
    {
        delete nodePtr;
        nodePtr = 0;
        return nodePtr;
    }
    else if (nodePtr->getLeftPtr() == 0)
    {
        BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getRightPtr();
        delete nodePtr;
        nodePtr = 0;
        return nodeToConnectPtr;
    }
    else if (nodePtr->getRightPtr() == 0)
    {
        BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getLeftPtr();
        delete nodePtr;
        nodePtr = 0;
        return nodeToConnectPtr;
    }
    else
    {
        ItemType newNodeValue;
        nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
        nodePtr->setItem(newNodeValue);
        return nodePtr;
    }
}

//************************************************************************************
//	The function goes recursively through the tree and finds the leftmost node and   *
//	deletes it																		 *
//************************************************************************************
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
                                                                     ItemType & successor)
{
    if (nodePtr->getLeftPtr() == 0)
    {
        successor = nodePtr->getItem();
        return deleteNode(nodePtr);
    }
    else
    {
        nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
        return nodePtr;
    }       
}

//************************************************************************************
//	The function takes in two arguements a node pointer that is the root of the tree *
//	and a item. The function goes through the tree while the node isn't null to find *
//	the item																		 *
//************************************************************************************
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* nodePtr,
                                                           const ItemType & target) const 
{
	//While the nodePtr isn't null compare the value of the nodePtr to the the target
	//If the nodePtr value is the target return the pointer othewise compare if the
	// nodePtr's value is greater than the targer if it is then go through the left
	//sub tree otherwise go through the right subtree
	while (nodePtr){

		if (nodePtr->getItem == target)
			return nodePtr;

		else if (nodePtr->getItem() > target)
			nodePtr = nodePtr->getLeftPtr();
		
		else
			nodePtr = nodePtr->getRightPtr();
		
	}

}  


#endif