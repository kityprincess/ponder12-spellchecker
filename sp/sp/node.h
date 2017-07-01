/***********************************************************************
* Header:
*    Node
* Summary:
*    This class contains a node for use in a linked-list.
* Author:
*
************************************************************************/

#ifndef NODE_H
#define NODE_H

#include <cassert>
#include <iostream>

/************************************************
 * NODE
 * A class that constructs a node.
 ***********************************************/
template <class T>
class Node
{
public:
   // default constructor
   Node() : pPrev(NULL), pNext(NULL) { }

   // non-default constructor
   Node(const T & t, Node * in_pPrev = 0, Node * in_pNext = 0)
      : data(t), pPrev(in_pPrev), pNext(in_pNext) { }

   // member variables
   T data;
   Node * pPrev;
   Node * pNext;
};

///************************************************
// * COPY
// * Copies a linked list.
// ***********************************************/
//template <class T>
//Node <T> * copy(Node <T> * pSource) throw (const char *)
//{
//   if (pSource == NULL)
//      return NULL;

//   // create a destination list
//   Node <T> * pDestination = new Node <T> (pSource->data);

//   // use recursion to copy over the list
//   pDestination->pNext = copy(pSource->pNext);
//   return pDestination;
//}

///************************************************
// * INSERT
// * Insert a node into a linked list.
// ***********************************************/
//template <class T>
//Node <T> * insert(const T & t, Node <T> * & pNode, bool isHead = false)
//{
//   // if inserting at the head
//   if (isHead || pNode == NULL)
//   {
//      // allocate and initialize a new node
//      Node <T> * pNew = new Node <T> (t);

//      // put pNode in line after the new node
//      pNew->pNext = pNode;

//      // pNew is the new head
//      pNode = pNew;

//      return pNew;
//   }

//   // inserting everywhere else
//   else
//   {
//      // allocate and initialize a new node
//      Node < T> * pNew = new Node <T> (t);

//      // fix the pNext pointer from pNew to the spot after it in the list
//      pNew->pNext = pNode->pNext;

//      // get pNode->pNext to point to pNew instead of the old node
//      pNode->pNext = pNew;

//      return pNew;
//   }
//}

///************************************************
// * FIND
// * Find an element in a linked list.
// ***********************************************/
//template <class T>
//Node <T> * find(Node <T> * pHead, const T & t)
//{
//   if (pHead == NULL)
//      return pHead;

//   // search through the linked list
//   for (Node <T> * p = pHead; p; p = p->pNext)
//      if (p->data == t)
//         return p;                      // if found, return it

//   return NULL;                         // return NULL if no node exists
//}

///************************************************
// * INSERTION OPERATOR
// * Overload the insertion operator to display
// * a linked list.
// ***********************************************/
//template <class T>
//std::ostream & operator << (std::ostream & out, const Node <T> * pHead)
//{
//   for (const Node <T> * p = pHead; p; p = p->pNext)
//   {
//      out << p->data;
//      if (p->pNext)
//         out << ", ";
//   }
//   return out;
//}

///************************************************
// * FREE DATA
// * Release the memory in a linked list.
// ***********************************************/
//template <class T>
//void freeData(Node <T> * & pHead)
//{
//   while (pHead != NULL)
//   {
//      // use pDelete to hold the data to be deleted
//      Node <T> * pDelete = pHead;
//      pHead = pHead->pNext;
//      delete pDelete;
//   }
//}

#endif // NODE_H
