/***********************************************************************
* Module:
*    Week 12, Hash
*    Brother Helfrich, CS 235
* Author:
*    <your name>
* Summary:
*    The Hash class creates a base template class to be used by the derived
*    hash classes.
************************************************************************/

#ifndef HASH_H
#define HASH_H

#include <cassert>
#include "list.h"

/*************************************************************************
* CLASS: HASH
* A Hash
**************************************************************************/
template <class T>
class Hash
{
public:
   // constructors and destructor
   Hash(const int num) throw (const char *);
   Hash(const Hash <T> & rhs) throw (const char *);
   ~Hash() { clear(); }

   // assignment operator
   Hash & operator = (const Hash & rhs) throw (const char *);

   // other class methods
   bool empty() const { return numElements == 0; }
   int size() const { return numElements; }
   int capacity() const { return numBuckets; }
   void clear();
   bool find(T value);
   void insert(T value);

   // pure virtual hash function
   virtual int hash(const T & value) const = 0;

protected:
   // memeber variables
   int numElements;
   int numBuckets;
   List <T> * table;
};

/*******************************************
* Hash :: NON-DEFAULT CONSTRUCTOR
*******************************************/
template <class T>
Hash <T> :: Hash(const int num) throw (const char *)
{
   numBuckets = num;
   numElements = 0;

   // attempt to allocate
   try
   {
      table = new List <T> [num];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate memory for the hash";
   }
}

/*******************************************
* Hash :: COPY CONSTRUCTOR
*******************************************/
template <class T>
Hash <T> :: Hash(const Hash <T> & rhs) throw (const char *)
{
   assert(rhs.numBuckets >= 0);

   // do nothing if there is nothing to do
   if (rhs.numBuckets == 0)
   {
      numBuckets = numElements = 0;
      table = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      table = new List <T> [rhs.numBuckets];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate memory for the hash";
   }

   // set variables
   numBuckets = rhs.numBuckets;
   numElements = rhs.numElements;

   // copy over the data
   for (int i = 0; i < numBuckets; i++)
      table[i] = rhs.table[i];
}

/*******************************************
* Hash :: ASSIGNMENT OPERATOR
*******************************************/
template <class T>
Hash <T> & Hash <T> :: operator = (const Hash & rhs) throw (const char *)
{
   assert(rhs.numBuckets >= 0);

   // do nothing if there is nothing to do
   if (rhs.numBuckets == 0)
   {
      numBuckets = numElements = 0;
      table = NULL;
   }

   // attempt to allocate
   try
   {
      table = new List <T> [rhs.numBuckets];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate memory for the hash";
   }

   // set variables
   numBuckets = rhs.numBuckets;
   numElements = rhs.numElements;

   // copy over the data
   for (int i = 0; i < numBuckets; i++)
      table[i] = rhs.table[i];

   return *this;
}

/*******************************************
* Hash :: CLEAR
*******************************************/
template <class T>
void Hash <T> :: clear()
{
   table->clear();
   numElements = 0;
}

/*******************************************
* Hash :: FIND
*******************************************/
template <class T>
bool Hash <T> :: find(T value)
{
   List <T> sublist = table[hash(value)];

   // iterate over the list to find the value
   for (ListIterator <T> it = sublist.begin(); it != sublist.end(); it++)
   {
      if (*it == value)
         return true;
   }
   return false;
}

/*******************************************
* Hash :: INSERT
*******************************************/
template <class T>
void Hash <T> :: insert(T value)
{
   table[hash(value)].push_back(value);
   numElements++;
}

#endif // HASH_H
