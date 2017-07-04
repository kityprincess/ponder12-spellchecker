/***********************************************************************
* Module:
*    Week 12, Spell Check
*    Brother Helfrich, CS 235
* Author:
*    Br. Helfrich
* Summary:
*    This program will implement the spellCheck() function
************************************************************************/

#ifndef SPELL_CHECK_H
#define SPELL_CHECK_H

#include <string>
#include "hash.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

void spellCheck();
void readFile(string counts, const string & fileName);

/******************************************************
* S HASH
* A simple hash of integers
*******************************************************/
class SHash : public Hash <string>
{
public:
   SHash(int numBuckets)    throw (const char *) : Hash <string>(numBuckets) {}
   SHash(const SHash & rhs) throw (const char *) : Hash <string>(rhs) {}

   // hash function for integers is simply to take the modulous
   int hash(const string & value) const
   {
      int collision = 12;

      for (int i = 0; i < value.length(); i++)
      {
         // converts to int in order to store data
         collision = (int)value[i] + collision;
      }
      return abs(collision) % capacity();
   }
};
#endif // SPELL_CHECK_H