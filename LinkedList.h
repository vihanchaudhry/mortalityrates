// A class template for holding a linked list.
// The node type is also a class template.

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

//*********************************************
// The ListNode class creates a type used to  *
// store a node of the linked list.           *
//*********************************************

template <class T>
class ListNode
{
public:
    T value;           // Node value
    ListNode<T> *next; // Pointer to the next node

    // Constructor
    ListNode (T nodeValue){ value = nodeValue; next = NULL;}
};

//*********************************************
// LinkedList class                           *
//*********************************************

template <class T>
class LinkedList
{
private:
    ListNode<T> *head;   // List head pointer
    int count;

public:
    // Constructor
    LinkedList(){ head = NULL; count = 0; }

   // Destructor
   ~LinkedList();

   // Linked list operations
   int getCount() {return count;}
   void insertNode(T);
   // delete
   // search
   // other linked list operations ...
   // ...
   void displayList() const;
};

//**************************************************
// The insertNode function inserts a node with     *
// newValue copied to its value member.            *
//**************************************************

template <class T>
void LinkedList<T>::insertNode(T newValue)
{
    ListNode<T> *newNode;             // A new node
    ListNode<T> *nodePtr;             // To traverse the list
    ListNode<T> *previousNode = NULL; // The previous node

    newNode = new ListNode<T>(newValue); // Allocate a new node and store newValue there.
    nodePtr = head;                      // Position nodePtr at the head of list.
    previousNode = NULL;                 // Initialize previousNode to NULL.

    // Skip all nodes whose value is less than newValue.
    while (nodePtr != NULL && nodePtr->value < newValue)
    {
         previousNode = nodePtr;
         nodePtr = nodePtr->next;
    }

    // If the new node is to be the 1st in the list,
    // insert it before all other nodes.
    if (previousNode == NULL)
    {
        head = newNode;
    }
    else  // Otherwise insert after the previous node.
    {
        previousNode->next = newNode;
    }
    newNode->next = nodePtr;
    count++;
}

//**************************************************
// displayList shows the value stored in each node *
// of the linked list pointed to by head.          *
//**************************************************

template <class T>
void LinkedList<T>::displayList() const
{
    ListNode<T> *nodePtr;  // To move through the list

    // Position nodePtr at the head of the list.
    nodePtr = head;

    // While nodePtr points to a node, traverse
    // the list.
    while (nodePtr)
    {
        std::cout << nodePtr->value << std::endl;  // Display the value in this node.
        nodePtr = nodePtr->next;         // Move to the next node.
   }
}

//**************************************************
// Destructor                                      *
// This function deletes every node in the list.   *
//**************************************************

template <class T>
LinkedList<T>::~LinkedList()
{
   ListNode<T> *nodePtr;   // To traverse the list
   ListNode<T> *nextNode;  // To point to the next node

   // Position nodePtr at the head of the list.
   nodePtr = head;

   // While nodePtr is not at the end of the list...
   while (nodePtr != NULL)
   {
      // Save a pointer to the next node.
      nextNode = nodePtr->next;

      // Delete the current node.
      delete nodePtr;

      // Position nodePtr at the next node.
      nodePtr = nextNode;
   }
}
#endif
