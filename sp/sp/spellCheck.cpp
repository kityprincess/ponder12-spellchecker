/***********************************************************************
* Module:
*    Week 12, Spell Check
*    Brother Helfrich, CS 235
* Author:
*    <your name here>
* Summary:
*    This program will implement the spellCheck() function
************************************************************************/
#ifdef DEBUG
#define Debug(x) (x);
#else
#define Debug(x)
#endif

#include <iostream>
#include <iomanip>
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
   // Lets create a table to store the words.
   // tested bucket counts between 2 and 256
   // and found 179 has the best range and no
   // empty buckets
   SHash dictionaryTable = SHash(179);

   // Lets store the strings in a vector
   vector <string> missSpelled = vector <string>();
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
* READ DICTIONARY
* Opens and reads the dictionary file
*********************************************************/
void readDictionary(SHash & dictionaryTable)
{
   string word;

   // since the dictionary file is always the same, we just
   // enter it into the ifstream ourselves
   //
#ifdef DEBUG
   ifstream fin("dictionary.txt");
#else
   ifstream fin("/home/cs235/week12/dictionary.txt");
#endif
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
   Debug(cout << "Empty Bucket Count: " << dictionaryTable.emptyBucketCount() << endl);
#ifdef DEBUG
   int min, max, range;
   range = dictionaryTable.bucketCountRange(min, max); 
   cout << "Bucket Range: " << range << "(" << min << ".." << max << ")\n";
#endif
   Debug(dictionaryTable.displayDistribution());
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

#ifdef DEBUG
/****************************************************************************
* SHASH :: EMPTY BUCKET COUNT
* For debugging purposes only. Counts the number of buckets in the hash table
* that are empty
****************************************************************************/
int SHash::emptyBucketCount() const
{
   int countBucket = 0;

   for (int i = 0; i < numBuckets; i++)
   {
      if (table[i].size() == 0)
         countBucket++;
   }

   return countBucket++;
}

/****************************************************************************
* SHASH :: BUCKET COUNT RANGE
* For debugging purposes only. Gets the range of the length of chains in each
* bucket of a hash table.
****************************************************************************/
int SHash::bucketCountRange(int & min, int & max) const
{
   for (int i = 0; i < numBuckets; i++)
   {
      if (i == 0)
         min = max = table[i].size();
      else if (table[i].size() < min)
            min = table[i].size();
      else if (table[i].size() > max)
            max = table[i].size();
   }

   return max - min;
}

/****************************************************************************
 * SHASH :: DISPLAY DISTRIBUTION
 * For debugging purposes only. Shows a "graph of the distribution of a hash
 * table's buckets
 ****************************************************************************/
void SHash :: displayDistribution() const
{
   int cols = 50;
   for (int i = 0; i < capacity(); i++)
   {
      cout << "[" << setw(3) << i << "]: ";
      int j;
      for (j = 1; j <= table[i].size(); j++)
      {
         if (j == cols)
            break;

         cout << ".";
      }

      if (j < table[i].size())
         cout << "+" << table[i].size() - cols;

      cout << endl;
   }
}
#endif
