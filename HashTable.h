//Mayada El-Ghamry 900152853
//Habiba Gamal 900151007
//Farah Seif El-din 900160195
//Assignment #5

#pragma once
#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <string>
using namespace std;
template <class keyType, class dataType>

class HashTable
{
private:
	
	//node 
	class node
	{
	public:
		keyType key;
		dataType data;
		node* next;
	};
	//table array of pointers to node
	node** table;
	//size of table
	int size;
	//occupancy (number of not null pointers in table)
	int occupancy;
	int c;//number of nodes in table

	//hashing functions
	long long  h1(string k);
	int h2(long long k);
	int hashFunc(string k);	

	//hamming distance function
	int distance(string s1, string s2);

public:
	//farah
	HashTable(int s = 24); //constructor
	int Occupancy(); //returns occupancy
	bool retrieve(keyType k, dataType &d); //retrieves data at key=k
	void traverse(); //displays the whole table
	//mayada
	void insert(keyType k, dataType d); //inserts new element
	bool search(keyType k, dataType d); //searches if element with key=k exists
	bool isEmpty();	//returns true if table is empty
	bool isFull();	//returns true if table is full
	//habiba
	~HashTable(); //destructor
	void makeTableEmpty(); //makes the whole table empty by deleting pointers and reinitializing the table to null
	bool update(keyType k, dataType d); //updates data part at key=k with new data d
	
	//takes word w and returns s[] with 5 closest suggestions
	void closest(string w, string s[]);

};
#endif
#include "Hashtable.cpp"