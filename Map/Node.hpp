#ifndef _NODE
#define _NODE 

#include "string"
class Node
{
private:
	  
    std::string Country;   //this is the key- the country 
	std::string City;  //this is the item to be stored- the city within the country
	Node* next;  //pointer to the next node 

public: 
	int length; //how many nodes are in this particular chain of nodes 
	Node* backPtr; //pointer pointing to the last added node 
	Node(); //default constructor 
	void setCountry(const std::string& aCountry); //sets the "Country"
	void setCity (const std::string& aCity); //sets the "item" member for whatever node the pointer is pointing to
	void setNext (Node* nextNodePtr);  //points the current node to whatever "nextNodePtr" points to
	std::string getCity() const; //returns the value stored in the node
	std::string getCountry() const; //returns the key store in the node 
	Node* getNext() const ; //returns a pointer to the next node
    
    ~Node();
};

#endif 