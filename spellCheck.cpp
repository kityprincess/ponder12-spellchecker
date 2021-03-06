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
#include <vector>
using namespace std;

void readDictionary(SHash & dictionaryTable);
void readFile(SHash & dictionaryTable, vector <string> & missSpelled);

/****************************************
 * SPELL CHECK
 * Prompt the user for a file to spell-check
 ****************************************/
void spellCheck()
{
   // Lets create a table to store the words.  Perhaps
   // 100 is a bit much, but I don't know how many words are in the file
   SHash dictionaryTable = SHash(100); 
   
   // Lets store the strings in a vector
   vector <string> missSpelled = vector <string> ();
   readDictionary(dictionaryTable);
   readFile(dictionaryTable, missSpelled);
   
   // Time to check for misspelled words and go through them one by one
   if (missSpelled.size() > 0)
   {
   cout << "Misspelled: ";
   
   // Going through the misspelled words and showing them
   cout << missSpelled[0];
   for (int i = 1; i < missSpelled.size(); i++)
   {
      cout << ", ";
      cout << missSpelled[i];
   }
   cout << endl;
   }
   
   // If there are no misspelled words, we will let them know
   else
   cout << "File contains no spelling errors\n";
}

/*******************************************************
 * READ FILE
 * Opens and reads the dictionary file
 *********************************************************/
void readDictionary(SHash & dictionaryTable)
{
   string word;
   
   // since the dictionary file is always the same, we just
   // enter it into the ifstream ourselves
   ifstream fin("/home/cs235/week12/dictionary.txt");
   if (fin.fail())
   {
      cout << "Error, cannot read file";
      fin.close();
   }
   // lets bring the whole file in now
   while (!fin.eof() && fin >> word)
   {
      // lets insert our incoming data into the table
      dictionaryTable.insert(word);
   }
   fin.close();
}
/*******************************************************
 * READ FILE
 * Opens and reads a file
 *********************************************************/
void readFile(SHash & dictionaryTable, vector <string> & missSpelled)
{
   string word;
   string fileName;
   string lowerCaseWord;
   
   // lets pull in the file from the user and make sure it opens
   cout << "What file do you want to check? ";
   cin >> fileName;
   ifstream fin(fileName.c_str());
   if (fin.fail())
   {
      cout << "Error, cannot read file";
      fin.close();
   }
   // It opened so we are going to bring in the file
   while (!fin.eof() && fin >> word)
   {
      // Lets make sure the file converts our letters to lowercase 
      // since that is what compares to the dictionary words
      lowerCaseWord = word;
      lowerCaseWord[0] = tolower(lowerCaseWord[0]);
      // If the user file doesn't match the dictionary file, lets
      // separate it so we can keep track
      if (!dictionaryTable.find(lowerCaseWord))
      {
         missSpelled.push_back(word);
      }
   }
   fin.close();
}
