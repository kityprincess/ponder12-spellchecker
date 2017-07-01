/***********************************************************************
* Header:
*    List
* Summary:
*    Implements a List class. With acknowledgement to Nyhoff's
*    textbook for ideas around embedding the Node<T> class and
*    approaches to handling the various push/pull functions as
*    well as other functions.
* Author:
*     Matthew Burr, Shayla Nelson, Bryan Lopez & Kimberly Stowe
************************************************************************/

#ifndef LIST_H
#define LIST_H

#include "node.h"
#include <cassert>
#include <new>
#include "listIterator.h"

/************************************************
 * LIST
 * A class encapsulating the notion of a list.
 ***********************************************/
template <class T>
class List
{
public:
   // default constructor
   List <T>()  throw (const char*);

   // copy constructor
   List <T> (List<T> & source) throw (const char *);

   // destructor
   ~List();

   // assignment operator
   List <T> & operator = (const List<T> & source);

   // additional methods
   bool empty() const { return numElements == 0; }
   int size() const      { return numElements;      }

   // clears the contents of list
   void clear();
   
   //adds a value to the back of the list 
   void push_back(T item) throw (const char *);

   //adds a value to the front of the list
   void push_front(T item) throw (const char *);

   // removes an item from a list using the iterator
   void remove(ListIterator <T> & item) throw (const char *);

   // returns the front item of a list
   T & front() const throw (const char *);

   // returns the back item of a list
   T & back() const throw (const char *);

   // inserts an item into a list
   void insert(ListIterator <T> location, const T & item) throw (const char *);

   // starts at the beginning of the list
   ListIterator <T> begin() const throw (const char *);

   // starts at the end of the list
   ListIterator <T> end() const;

   // returns an iterator to the last element in the list
   ListIterator <T> rbegin() const;

   //returns an iterator to past the front element in the list
   ListIterator <T> rend() const;

private:
   // checks structure
   bool isValid() const;
   
   // member variables
   Node <T> * m_node;
   int numElements;
};
/*******************************************
* LIST :: DEFAULT CONSTRUCTOR
*******************************************/
template <class T>
List <T> ::List() throw (const char*)
   : numElements(0), m_node(NULL)
{
   try
   {
      m_node = new Node <T>(T());
      m_node->pNext = m_node;
      m_node->pPrev = m_node;
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: unable to allocate a new node for a list";
   }
}

/*******************************************
 * LIST :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
List <T> :: List(List <T> & source) throw (const char *)
    : numElements(0), m_node(NULL)
{
   // attempt to allocate
   try
   {
      m_node = new Node <T>(T());
      m_node->pNext = m_node;
      m_node->pPrev = m_node;
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: unable to allocate a new node for a list";
   }
   
   // copy over the data
   for (ListIterator <T> it = source.begin();
        it != source.end();++it)
   {
      push_back(*it);
   }
}

/*******************************************
 * LIST :: ASSIGNMENT OPERATOR
 *******************************************/
template <class T>
List <T> & List <T> :: operator = (const List<T> & source)
{
   clear();
   numElements = 0;

   // copy over the data
   for (ListIterator <T> it = source.begin();
        it != source.end();it++)
   {
      push_back(*it);
   }

   return *this;
}

/*******************************************
 * LIST :: DESTRUCTOR
 *******************************************/
template <class T>
List <T> :: ~List()
{
   clear();
}

/*****************************************************************************
* LIST :: CLEAR
* Empty the LIST of all its contents
*****************************************************************************/
template<class T>
void List<T> :: clear()
{
   // if we're already empty, then we don't need to do anything
   if (empty())
      return;

   // iterate through the list, using remove() to clear the elements
   for (ListIterator<T> it = begin();
      it != end();)
      remove(it);

   // and make sure we're valid after all this
   assert(isValid());
}

/*****************************************************************************
* LIST :: PUSH BACK
* Pushes an item onto the back of the list.
*****************************************************************************/
template<class T>
void List<T> :: push_back(T item) throw (const char *)
{
   try
   {
      insert(end(), item);
   }

   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a new node for a list";
   }
}

/*****************************************************************************
* LIST :: PUSH FRONT
* Pushes an item onto the front of the list.
*****************************************************************************/
template<class T>
void List<T> :: push_front(T item) throw (const char *)
{
   try
   {
      insert(begin(), item);
   }

   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a new node for a list";
   }
}

/*****************************************************************************
* LIST :: REMOVE
* Removes an item from the list.
*****************************************************************************/
template <class T>
void List <T> :: remove(ListIterator <T> & item) throw (const char *)
{
   if (item == end())
      throw "ERROR: unable to remove from an invalid location in a list";

   Node<T> * ptr = item.p;

   if (NULL == ptr)
      return;

   if (NULL != ptr->pNext)
      ptr->pNext->pPrev = ptr->pPrev;

   if (NULL != ptr->pPrev)
      ptr->pPrev->pNext = ptr->pNext;

   item.p = ptr->pNext;

   delete ptr;

   numElements--;
}

/*****************************************************************************
* LIST :: FRONT
* Returns the item at the front of the list
*****************************************************************************/
template<class T>
T & List<T> :: front() const throw (const char *)
{
   if (!empty())
   {
      return *(begin());
   }
   else
   {
      throw "ERROR: unable to access data from an empty list";
   }
}

/*****************************************************************************
* List :: BACK
* Returns an item from the back of the list
*****************************************************************************/
template<class T>
T & List<T> :: back() const throw (const char *)
{
   if (!empty())
   {
      return *(--end());
   }
   else
   {
      throw "ERROR: unable to access data from an empty list";
   }
}

/***************************************************************************
* List :: INSERT
* Inserts an item into the middle of the list
***************************************************************************/
template <class T>
void List<T> :: insert(ListIterator <T> location, const T & item) throw (const char *)
{
   Node<T> * newNode;

   try
   {
      newNode = new Node<T>(item);
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: unable to allocate a new node for a list";
   }

   Node<T> * ptr = location.p;

   if (NULL == ptr)
      throw "ERROR: invalid pointer";

   newNode->pPrev = ptr->pPrev;
   newNode->pNext = ptr;
   ptr->pPrev->pNext = newNode;
   ptr->pPrev = newNode;

   numElements++;
}

/***************************************************************************
* List :: BEGIN
* Starts at the beginning of the list
***************************************************************************/
template <class T>
ListIterator <T> List<T> :: begin() const throw (const char *)
{
   return ListIterator <T>(m_node->pNext);
}

/***************************************************************************
* List :: END
* Starts at the end of the list
***************************************************************************/
template <class T>
ListIterator <T> List <T> :: end() const
{
   return ListIterator <T>(m_node);
}

/****************************************************************************
* List :: RBEGIN
* Returns an iterator to the last element in the list
****************************************************************************/
template <class T>
ListIterator <T> List <T> :: rbegin() const
{
   return --end();
}

/****************************************************************************
* List :: REND
* Returns an iterator to past the front element in the list
****************************************************************************/
template <class T>
ListIterator <T> List <T> :: rend() const
{
   return --begin();
}

/*****************************************************************************
* List :: IS VALID
* Checks to see that the List is in a valid state
*****************************************************************************/
template<class T>
bool List<T> ::isValid() const
{
   bool valid = true;

   return valid;
}

#endif // LIST_H