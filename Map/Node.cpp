#include "Node.hpp"
#include "iostream"
#include "cstddef"
#include "string"
using namespace std;

//default constructor
Node::Node() //next(nullptr), backPtr(nullptr)
{
	//set all pointers to null
	next=nullptr; 
	backPtr=nullptr; 

	//set the length of all chains to 0 
	length=0; 
}



// set the country value 
void Node::setCountry(const std::string& aCountry)
{
   Country=aCountry;  
} 

//set the city value 
void Node::setCity(const std::string& aCity)
{
   City=aCity; 
}

// setNext
void Node::setNext(Node* nextNodePtr) //setNext takes a pointer as a parameter 
{
   next = nextNodePtr; //the current Node's "Next" points to whatever nextNodePtr points to
} 


//get the city value 
std::string Node::getCity() const
{
   return City;
} 

//get the country value 
std::string Node::getCountry() const
{
   return Country;
} 


// getNext
Node* Node::getNext() const
{
   return next;
} 

Node::~Node() //the destructor 
{
	delete next; 
}

