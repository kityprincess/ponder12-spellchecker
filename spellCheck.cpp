/***********************************************************************
 * Module:
 *    Week 12, Spell Check
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name here>
 * Summary:
 *    This program will implement the spellCheck() function
 ************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include "spellCheck.h"
#include "hash.h"
using namespace std;

/****************************************
 * SPELL CHECK
 * Prompt the user for a file to spell-check
 ****************************************/
void spellCheck()
{
}

/*******************************************************
 * READ FILE
 * Opens and reads a file
 *********************************************************/
void readFile(SHash & dictionaryTable, const string & fileName)
{
   string word;
   
   cout << "What file do you want to check?";
   ifstream fin(fileName.c_str());
   if (fin.fail())
   {
      cout << "Error, cannot read file";
      fin.close();
   }

   while (!fin.eof() && fin >> word)
   {
      dictionaryTable.insert(word);
   }
   fin.close();
}
