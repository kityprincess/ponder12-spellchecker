#ifndef LISTITERATOR_H
#define LISTITERATOR_H

#include "node.h"
// class inside my node class for listIterator
template <class T>
class List;

template <class T>
class ListIterator
{

   friend class List<T>;

public:

   // default constructor
      ListIterator() : p(NULL)
   {
   }
   
   // initialize to direct p to some item
   ListIterator(Node<T> * p) : p(p)
   {
   }
   
   // copy constructor
   ListIterator(const ListIterator & rhs)
   {
      *this = rhs;
   }

   // assignment operator
   ListIterator & operator = (const ListIterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }
   
   bool operator == (const ListIterator & rhs) const
   {
      return rhs.p == this->p;
   }
   
   // not equals operator
   bool operator != (const ListIterator & rhs) const
   {
      return rhs.p != this->p;
   }

   // dereference operator
   T & operator * ()
   {
      return p->data;
   }

   // prefix increment
   ListIterator <T> & operator ++ ()
   {
      p = p->pNext;
      return *this;
   }

   // postfix increment
   ListIterator <T> operator++(int postfix)
   {
      ListIterator tmp(*this);
      p = p->pNext;
      return tmp;
   }

   // prefix decrement
   ListIterator <T> & operator -- ()
   {
      p = p->pPrev;
      return *this;
   }

   // postfix decrement
   ListIterator <T> operator -- (int postfix)
   {
      ListIterator tmp(*this);
      p = p->pPrev;
      return tmp;
   }

private:
   Node<T> * p;
};

#endif
