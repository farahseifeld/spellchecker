//Mayada El Ghamry 900152853
//Habiba Gamal  900151007
//Farah Seif El-din  900160195
//Assignment #4

#include <stdio.h>
#include <string>
#include <iostream>
#include <cmath>
#include<algorithm>
using namespace std;

//farah 
//constructor
template <class keyType, class dataType>
HashTable <keyType, dataType>::HashTable(int s)
{
	size = s;

	table = new node*[size];
	//initialize all table pointers to null
	for (int i = 0; i<size; i++)
		table[i] = NULL;
}

//returns the number of occupied locations in table
template <class keyType, class dataType>
int HashTable <keyType, dataType>::Occupancy() 
{
	//loop through table and increment occupancy everytime table[i] is not null
	for (int i = 0; i < size; i++)
		if (table[i] != NULL)
			occupancy++;

	//return occupancy
	return occupancy;
}

//loops through the whole table and every chain and prints the elements at every index
template <class keyType, class dataType>
void HashTable <keyType, dataType>::traverse() 
{
	node* cursor = NULL;
	//loops through the whole table
	for (int i = 0; i < size; i++)
	{
		cursor = table[i];
		cout << "Entry at " << i << ": ";
		if (cursor == NULL)
			cout << "NULL" << endl;
		else 
		{
			//loops through chain
			while (cursor != NULL)
			{
				cout << cursor->key << " " << cursor->data << endl;
				cursor = cursor->next;
			}
		}
	}
}

//retrieves the data part of the specified key
//returns true if the key exists and if the operation was successful,
//otherwise returns false
template <class keyType, class dataType>
bool HashTable <keyType, dataType> ::retrieve(keyType k, dataType &d) { 

	node* cursor = NULL;
	int h = hashFunc(k);

	cursor = table[h];

	if (cursor != NULL) 
	{
		//loops through the chain and stops when if it reaches the last node or if current key is equal to k
		while (cursor->next != NULL && cursor->key != k)
			cursor = cursor->next;
		//checks why it stopped, either k is found or it reached the last element without finding it
		if (cursor->key == k) 
		{
			//return the data part at key=k
			d = cursor->data;
			//return true since operation is successful, and the key exists
			return true;
		}
		//return false if key does not exist and data was not retrieved
		else return false;

	}
	//return false if key does not exist and data was not retrieved
	else
		return false;


}

//habiba
template <class keyType, class dataType>
HashTable<keyType, dataType>:: ~HashTable() //destructor
{
	node *entry, *prev = NULL;
	for (int i = size - 1; i >= 0; i--)
	{
		entry = table[i];
		//delete all nodes in the chain
		while (entry != NULL)
		{
			prev = entry;
			entry = entry->next;
			delete prev;
		}
		//set table[i] pointer to null
		table[i] = NULL;
	}
	//reset number of nodes to zero
	//reset occupancy to zero
	occupancy = 0;
	c = 0;
}

//deletes all nodes and sets every table[] location to null
template <class keyType, class dataType>
void HashTable <keyType, dataType> ::makeTableEmpty() 
{
	node* entry, prev = NULL;
	for (int i = size - 1; i >= 0; i--)
	{
		entry = table[i];
		//delete all nodes in the chain
		while (entry != NULL)
		{
			prev = entry;
			entry = entry->next;
			delete prev;
		}
		//set table[i] pointer to null
		table[i] = NULL;
	}
	//reset number of nodes to zero
	//reset occupancy to zero
	occupancy = 0;
	c = 0;
}

//updates data part at current key (k) with data d
template <class keyType, class dataType>
bool  HashTable<keyType, dataType>::update(keyType k, dataType d)
{
	bool update = false;
	int h = hashFunc(k);
	node* entry = table[h];
	//loops through chain till it finds the element with key=k
	while (entry != NULL) //Unique key
	{
		if (entry->key == k)
		{
			//if key is found, the function will return true
			update = true;
			//update the data part of the element to the new data
			entry->data = d;
			//stop searching for key 
			return update;
		}
		entry = entry->next;
	}
	//if key is not found return false
	return update;
}

 //hashing function
template <class keyType, class dataType>
int  HashTable<keyType, dataType>::hashFunc(string k)
{
	long long  s = 0;
	int r = 0;
	char c;
	int i = 0;
	//convert k to be all lowercase
	for(i=0;i<k.length();i++)
		k[i]= tolower( k[i]);

	//summation formula
	s = h1(k);
	//compress
	r = h2(s);

	//return the compressed key
	return r;
}

//first part of hashing function
template <class keyType, class dataType>
long long   HashTable<keyType, dataType>::h1(string k) 
{
	long long sum = 0;
	int l = k.length();

	// if the size of the string is more than 12 characters, sum will not fit in 64 bits (long long)
	// so we only consider the first 12 characters in our calculation of sum
	if (l > 12) {
		for (int i = 0; i < 12; i++)
			//formula sum= summation of ascii of k[i] * 26^i
			sum += ((int)k.at(i))*pow(26, i);
	}
	else 
	{
		for (int i = 0; i < l; i++)
			sum += ((int)k.at(i))*pow(26, i);
	}
	return sum;
}

//compression function (reduces the sum by modding it with the size)
template <class keyType, class dataType>
int  HashTable<keyType, dataType>::h2(long long k)
{
	return (k % (size));
}

//mayada
//inserts new element with key and data into the table
template <class keyType, class dataType>
void HashTable <keyType, dataType> ::insert(keyType k, dataType d) 
{
	int h = hashFunc(k);
	node *cur = table[h];//cursor to current node
	node *last = NULL;
	while (cur != NULL)
	{
		last = cur;
		cur = cur->next;
	}
	cur = new node;

	for (int i = 0; i < k.length(); i++)
		k[i] = tolower(k[i]);

	cur->key=k;
	cur->data=d;
	cur->next = NULL;
	if (last == NULL)
		table[h] = cur;
	else
		last->next = cur;
	//increment c everytime you add a node
	c++;
}

//searches the table for the element with key=k
template <class keyType, class dataType>
bool HashTable <keyType, dataType> ::search(keyType k, dataType d)
{
	int h = hashFunc(k); 
	node* cur = table[h];
	node* last = NULL;
	while (cur != NULL)
	{
		//if k exists, then return true
		if (cur->key == k)
			return true;
		last = cur;
		cur = cur->next;
	}
	return false;
}

//if the number of nodes in the table is not equal to 0, return false, else return true
template <class keyType, class dataType>
bool HashTable <keyType, dataType> ::isEmpty() 
{
	return c == 0;//number of nodes in table
}


template <class keyType, class dataType>
bool HashTable <keyType, dataType>::isFull() // return true if the occupancy equals size (if all locations of table are not null)
{
	//loop through table (without chains) and check if current location is null
	//if yes, then return false (table is not full)
	//return true in the end (table is full)
	for (int i = 0; i < size; i++)
		if (table[i] == NULL)
			return false;
	return true;

}

template <class keyType, class dataType>
int HashTable <keyType, dataType>::distance(string s1, string s2) //return the hamming distance between two strings
{
	//c is the number of matches
	int length = min(s1.length(), s2.length()), c=0;
	//loop until the length of the smaller string
	for (int i = 0; i < length; i++)
	{
		if (s1[i] == s2[i])
			c++;
	}
	//distance = length of bigger string - the number of matches
	return max(s1.length(),s2.length())-c;
	

}

//takes string w as input and array s then returns s with the 5 closest suggestions
template <class keyType, class dataType>
void HashTable <keyType, dataType>::closest(string w, string s[]) 
{	
	node *cur=NULL;
	//arr[5] will have the shortest hamming distances
	//c is a counter
	//d will store the hamming distance between w and each word iteration
	int arr[5] = { 100,100,100,100,100 }, c = 0, d = 0;

	//loop through every element in table
	for (int i = 0; i < size; i++)
	{
		cur = table[i];
		//loop through each chain and only check elements that begin with the same letter as w
		while (cur != NULL && cur->key[0] == w[0])
		{
			//get hamming distance between current word and w
			d = distance(cur->key, w);
			//add first five words to s[] and their corresponding distances to arr[]
			if (c < 5)
			{
				s[c] = cur->key;
				arr[c] = d;
				if (c > 0)
					//sort the first 5 entries such that arr[4] will have the greatest distance
					if (arr[c] < arr[c - 1])
					{
						swap(arr[c], arr[c - 1]);
						swap(s[c], s[c - 1]);
					}
						c++;
			}
			//if current distance is less than the last element in arr[] then arr[4]=d and s[4]=current word
			if (arr[4] > d)
			{
				arr[4] = d;
				s[4] = cur->key;
			}

			//sort arr[] from smallest distance to largest distance and change s[] accordingly
			for (int j = 4; j > 0; j--)
			{
				if (arr[j] < arr[j - 1])
				{
					swap(arr[j], arr[j - 1]);
					swap(s[j], s[j - 1]);
				}
			}
			//updates cursor to move to next node
			cur = cur->next;
		}
	}

	//after the loop is finished, s[] will have the 5 closest suggestions

	
}
