#ifndef _StringMap
#define _StringMap

#include "iostream"
#include "Node.hpp"

class StringMap
{
private: 
	static const int size= 16; //the size of the map 
	int numCountries;          //an int to store the number of countries
	int numCities;             //an int to store the number of cities 
	Node* stringArray[size];   //an array of pointers which will point to nodes 
	

public:  
	StringMap(); //constructor 
	StringMap(const StringMap& oldMap); //copy constructor 
	StringMap &operator=(const StringMap& oldMap); //overloading the assignment operator 
	int hash(std::string aCountry); //the hash function which will convert strings to index numbers
	void dm(); //displays everything in the map
	bool isEmpty(); //If the Map contains no elements, this should return true; otherwise, returns false.
    int getSize(); // Returns the number of key-value pairs (elements) stored in the Map
    bool addValue(std::string aCountry, std::string aCity); // if the key AND value is valid, stores the valid key-value pair, and returns true, if key or value is invalid (empty string), returns false
    std::string getValue(std::string key); // If a value associated with the given key exists, returns it; otherwise throws an exception
	bool deleteValue(std::string key);// If a value associated with the given key exists, removes it, and returns true; otherwise, returns false.
	void clear(); //Removes all elements. Subsequent call to isEmpty() should yield true
	bool contains(std::string key); // If a value associated with the given key exists, returns true; otherwise, returns false.
	~StringMap(); //the destructor 






};



#endif