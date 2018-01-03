/*Mayada El-Ghamry, 900152853
Habiba Gamal,900151007
Farah Seif El-Din,900160195
Assignment#4
*/
#include <iostream>
#include "HashTable.h"
#include <string>
#include <fstream>
using namespace std;
void readFile(ifstream& inp, HashTable<string, string> & t);//insert each word in the Hash table
void fillTable(string filename, HashTable<string, string> & t);//open the file and call readFile
void spellcheck(string filename, HashTable<string, string> t);//check for spelling in file, if it's not found 

int main()
{
	string filename = "wordList.txt",f;//filname for wordlist, f fis the file to check the spelling of words in
	cout << "Please enter file name\n";
	cin >> f;
	HashTable <string, string> t(26*26*26);//creating hash table
	fillTable(filename, t);//open the word list and place words in the hash table
	spellcheck(f, t);//check for word spellings of words in file f

	system("PAUSE");
	return 0;
}


void fillTable(string filename, HashTable<string, string> & t)
{
	ifstream inp;//ifstream for wordlist
	string s;//string to get input from file
	int size = 0; //number of words in the table
	inp.open(filename.c_str());//open file
	if (!inp.is_open())//checks whether file opened or failed

	{
		cout << "failure to open file" << endl;
	}

	else

	{
		inp >> s;
		size = stoi(s);//convert s to integer
		readFile(inp, t);//inserts each word in table
		inp.close();//close file
	}
}

void readFile(ifstream& inp, HashTable <string, string> & t)
{
	string s;
	while (!inp.eof())//checks if we reached the end of file
	{
		inp >> s;//input data words
		t.insert(s,s);//insert word in the hash table
	} 
}
void spellcheck(string filename, HashTable<string, string> t)
{
	ifstream inp;//ifstreams for file that its words will be checked
	string s;//string to input words
	string words[5];//array to store the 5 closest suggestions if the word is misspelled
	inp.open(filename.c_str());//open file
	if (!inp.is_open())//checks if file opened or failed
		cout << "failure to open file" << endl;
	else
	{
		while (!inp.eof())//checks we did not reach the end of the file
		{
			inp >> s;//input words
		
				for (int i = 0; i < s.length(); i++)
					s[i] = tolower(s[i]);
			
			if (!t.search(s, s))//checks if the word exists or misspelled
			{
				t.closest(s, words);//get the 5 closest suggestions
				cout << "This word is incorrect: " << s << "." << endl;//cout the suggestions
				cout << "Here are the five closest suggestions: " << words[0] << ", " << words[1] << ", "<< words[2] << ", " << words[3] << ", " << words[4] << "." << endl;
			}
		}
		inp.close();//close file
	}
}

