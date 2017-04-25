#include "iostream"
#include "StringMap.hpp"
#include "Node.hpp"
#include "stdexcept"

using namespace std; 

StringMap::StringMap() //default constructor
{

	numCountries=0;  //there are no keys yet
	numCities=0;     //there are no values yet 


	for (int i=0; i<size; i++)
	{
		stringArray[i]=nullptr; //the pointers in the arra of pointers all point to null
	    

	}
}


StringMap::StringMap(const StringMap& oldMap) //copy constructor
{
	Node* oldMapPtr;   //a pointer that traverses the old map to be copied
	Node* newMapPtr;   //a pointer that traverses the new map 
	numCities=0;       //initializing the number of values to 0
	numCountries=0;    //initializing the number of keyes to 0
	int itemCount=oldMap.size; //an integer holding the size of the oldMap array
	

	for (int i=0; i<itemCount; i++)    
	{
		 
		oldMapPtr=oldMap.stringArray[i]; //sequentially going through the entire array using the oldMap pointer	

		if (oldMapPtr == nullptr) 
		{
			stringArray[i]=nullptr; //if the oldMap array has nothing stored at that index, so will the new array
			 
		}
		else
		{

			stringArray[i]= new Node;                              //if the old array does have something stored, a new node will be made in the new array 
			stringArray[i]-> setCountry(oldMapPtr->getCountry());  //the key will be carried over
			stringArray[i]-> setCity(oldMapPtr->getCity()); 	   //the value will be carried over 
			stringArray[i]->backPtr=stringArray[i];                //set the back pointer to point to the newly crated node 
			numCountries++;                                        //increment the number of keyes
			numCities++;                                           //increment the number of values 
			stringArray[i]->length++;                              //increment the length of the chain 
			

			for (int j=1; j<oldMap.stringArray[i]->length; j++)    
			{
				
				oldMapPtr=oldMapPtr->getNext();                    //after the first node is copied over, copy over the rest of the chain at that particular index
				newMapPtr= new Node; 
				newMapPtr-> setCountry(oldMapPtr->getCountry());
				newMapPtr-> setCity(oldMapPtr->getCity());
				stringArray[i]->backPtr->setNext(newMapPtr); 
				stringArray[i]->backPtr=newMapPtr; 
				stringArray[i]->length++; 
				numCities++; 
				
			}
			 
		}
	}
	//set both of the newly allocated pointers to null
	oldMapPtr=nullptr; 
	newMapPtr=nullptr; 
	
}


StringMap &StringMap::operator=(const StringMap& oldMap) //overloaing the assignment operator
{
	//again, two new pointers, one for the old map, one for the new 
	Node* oldMapPtr; 
	Node* newMapPtr; 

	//setting the #cities and # countries equal to 0
	numCities=0;
	numCountries=0;  

	//getting the item count
	int itemCount=oldMap.size; 
	

	for (int i=0; i<itemCount; i++) //runing throgh the entire oldMap's stringArray
	{
		//the oldmapPtr now points to the index corresponding to the key in question  
		oldMapPtr=oldMap.stringArray[i]; 
		if (oldMapPtr == nullptr) //if the pointer at the index points to nothing, ie the chain is empty 
		{
			stringArray[i]=nullptr; //then the pointer at the new map will be empty as well 
			 
		}
		else //if the pointer at the index points to something, ie there is a node 
		{
			//copy that first node 
			stringArray[i]= new Node;                               
			stringArray[i]-> setCountry(oldMapPtr->getCountry());
			stringArray[i]-> setCity(oldMapPtr->getCity()); 	
			stringArray[i]->backPtr=stringArray[i]; 
			numCountries++;
			numCities++;
			stringArray[i]->length++; 
			
			//then copy the rest of the nodes 
			for (int j=1; j<oldMap.stringArray[i]->length; j++)
			{
				//this->addValue(oldMap.stringArray[i]->getCountry(), oldMap.stringArray[i]->getCity()); 
				oldMapPtr=oldMapPtr->getNext(); 
				newMapPtr= new Node; 
				newMapPtr-> setCountry(oldMapPtr->getCountry());
				newMapPtr-> setCity(oldMapPtr->getCity());
				stringArray[i]->backPtr->setNext(newMapPtr); 
				stringArray[i]->backPtr=newMapPtr; 
				stringArray[i]->length++; 
				numCities++; 
				
			}
			 
		}
		//nulling the temporary pointers
		oldMapPtr=nullptr; 
		newMapPtr=nullptr; 
	}

}


int StringMap::hash(std::string aCountry) //the hash function 
{
	int index;                          //the end result that we want 
    int keyLength=aCountry.length();    //getting the length of the input key
    int sum=0;                          //a running variable 

    //adding up the ASCII values of each letter in the key
    for (int i=0; i<keyLength; i++)     
    {
    	sum = sum + aCountry[i]; 
    }

    //using a relatively complicated formula to get a random index number that is then modded to fit within the size of the array
    index=(((sum+aCountry[0])*aCountry[0])+keyLength)%size; 
     
    return index; 
}


void StringMap::dm() //the function used to display the map, for my own use to observe what is happening
{
	Node* tempPtr; 

	for(int i=0; i<size; i++)
	{
		tempPtr=stringArray[i]; 
		if (tempPtr != nullptr)
		{
		cout<<i<<": "<<endl; 
		cout<<tempPtr->getCountry()<<" ";  
		cout<<tempPtr->getCity()<<" "<<endl;

		if (tempPtr->getNext() != nullptr)
		{
			tempPtr=tempPtr->getNext(); 
			for (int j=1; j<stringArray[i]->length; j++)
			{	
				cout<<tempPtr->getCountry(); 
				cout<<" ";  
				cout<<tempPtr->getCity()<<" ";
				tempPtr=tempPtr->getNext();
				cout<<endl;
			}
			cout<<endl;
		}
	    }
	    else
	    {
	    	cout<<i<<": "<<endl; 
	    	cout<<"No Country,"<<" No City"<<endl; 
	    }
		cout<<endl;
	}
	tempPtr=nullptr; 
	cout<<"number of cities: "<<numCities<<endl; 
}


bool StringMap::isEmpty() //checks if the stringMap is empty or not 
{
	//numCities is incremented each time a key-value pair is added, and decremented if a value is removed. so if it is 0 then the map is empty
	if (numCities==0)
	{
		return true; 
	}
	else
	{
		return false; 
	}
	
}


int StringMap::getSize()
{
	//the number of cities represents the number of key-value pairs
	return numCities; 
}


bool StringMap::addValue(std::string aCountry, std::string aCity) //adding key-value pairs
{
	
	int index=hash(aCountry); //the hash function is run on the aCountry string to get an index value
	
	if(aCountry=="" || aCity=="") //if either the key or the value are empty strings, return false 
	{
		return false;
	}

	else //if valid key/value are entered:
	{

		if (stringArray[index] == nullptr) //if the pointer at the index in question points to nothing, ie the chain is empty
		{
			stringArray[index] = new Node;                    //create a new node 
			stringArray[index]->setCity(aCity);               //set the city of that node equal to the input city 
			stringArray[index]->setCountry(aCountry);         //set the country of that node equal to the input country 
			numCities++;                                      //increment the number of cities 
			numCountries++;                                   //increment the number of countries 
			stringArray[index]->length++;                     //increment the length of the chain 
			stringArray[index]->backPtr=stringArray[index];   //set the backPtr to point to the newly added chain 
		}
		//COLLISION HANDLING 
		else //if the pointer at the index points to something, ie the chain isnt empty (there have been previous additions)
		{
			Node* tempNode = new Node();                      //create a new node 
			tempNode->setCity(aCity);                         //set the city of the node equal to the input city 
			tempNode->setCountry(aCountry);                   //set the country of the node equal to the input country
			stringArray[index]->backPtr->setNext(tempNode);   //use the backPtr, which points to the last node on the list, to point that last node to the  new node above
			stringArray[index]->length++;                     //increment the length of the chain 
			stringArray[index]->backPtr=tempNode;             //now set the backPtr to the newly added node, since it is now the last node of the chain                                 
			numCities++;                                      //increment the number of cities 
			tempNode=nullptr;                                 //set the temporary pointer equal to null 
		
		} 
    	return true; //return true if the values were added successfully
	}  
}


std::string StringMap::getValue(std::string key)
{
	int index=hash(key);       //run the hash ufnction on the key to get the index we should look at 
	std::string city;          //a variable to hold the city value were looking for 
	Node*tempPtr;              //a temporary pointer to traverse the index
	int counter=0;             //a counter for the number of times a vertain key value shows up 
	tempPtr=stringArray[index];//the tempPtr points to the index in question  

if(tempPtr != nullptr)         //if the index is not empty 
{
	for (int j=0; j<stringArray[index]->length; j++) //run through the entire length of the chain
	{
		
		if (tempPtr->getCountry()==key) //if the country of the node matches the key 
		{
			counter++;                 //increment the counter-at least one key-value pair has been found pertaining to the key
			city=tempPtr->getCity();   //record the value associated with that key 
			
		}
		tempPtr=tempPtr->getNext();    //move to the next node 
	}
	
}
else 
{
	throw runtime_error("There are no values with this key."); //if the index is empty, throw an exception 
}

if (counter>0)
{
	return city; //if the counter is more than 0; return the value associated with the key 
}
else
{
	throw runtime_error("There are no values with this key.");  //if there is no value associated with that key, throw an exception 
}

tempPtr=nullptr; 


}


bool StringMap::deleteValue(std::string key)
{
	int index=hash(key);        //use the hash function to get the index that the key maps to
	Node* tempPtr;              //create a temporary pointer 

	tempPtr=stringArray[index]; //point tempPtr to the index

	if (tempPtr==nullptr)       //if the index is empty 
	{
		return false;           //return false
	}
	else
	{
		int b=stringArray[index]->length; //recording the length of the chain at the index 
		
		for (int j=0; j<b; j++)           //running through the length of the chain 
		{


			stringArray[index]=stringArray[index]->getNext(); //point the head pointer, ie the pointer at the index, to the second node of the chain
			
			//the first node of the chain is then deleted
			tempPtr->setNext(nullptr);                        
			tempPtr->setCity(""); 
			tempPtr->setCountry("");

			//decrement the number of cities
			numCities--; 
			
			//this is repeated until the index points to nothing 
		}
		//decrement the number of countries 
		numCountries--;
		return true;
	}
	 
	tempPtr=nullptr; //set the temporary pointer equal to null 


}

void  StringMap::clear()
{
	Node* tempPtr;  //a temporary pointer

	for (int i=0; i<size; i++) //running through the entire stringMap 
	{
		if (stringArray[i] != nullptr)  //if the index is not empty 
		{
			
			int b=stringArray[i]->length; //record the length of the chain 

			for (int j=0; j<b; j++)  //run through the length of the chain 
			{
				
				tempPtr=stringArray[i]; //set the tempPtr to point to the top of the chain 
				
				//the headptr, or the ptr at the index, will point to the node next in line to the one it was pointing to before
				stringArray[i]=stringArray[i]->getNext(); 
				
				//the node at the top of the chain is then deleted 
				tempPtr->setNext(nullptr); 
				tempPtr->setCity(""); 
				tempPtr->setCountry(""); 
				
				//decrement the number of cities
				numCities--; 
			}
			numCountries--;
			//decrememnt the number of countries 
		}
		
		
	}
	 
	tempPtr=nullptr; //set the temporary pointer to null 
	
}



bool StringMap::contains(std::string key)
{ 

	int index=hash(key);       //get the index the key maps to 
 
	Node*tempPtr;              //create a temporary pointer 
	int counter=0;             //a counter variable 
	tempPtr=stringArray[index];//point to the index 

	if(tempPtr != nullptr)     //if the index is not empty 
		{
	
			for (int j=0; j<stringArray[index]->length; j++) //run through the chain at the index 
			{
		
				if (tempPtr->getCountry()==key)  //if the country present is the same as the key 
				{
					counter++;  //increment the counter 
				}
					tempPtr=tempPtr->getNext(); //move to the next node in the chain 
			}
	
		}
	else //if the index is empty, return false 
		{
			return false; 
		}



	if (counter>0) //if the counter is more than 0 return true, ie there is at least one node with that key 
		{
			return true;
		}
	else           //if not, return false 
		{
			return false; 
		}
	

}

StringMap::~StringMap() //the destructor 
{
	clear(); //calls the clear function to remove all the nodes and pointers
}