#include "iostream"
#include "string"
#include "StringMap.hpp"
#include "cassert"
#include <sstream>

using namespace std; 

int main ()
{
	
	
	StringMap testMap1;

	//
	// PART 1 -- Test the Basic Operations
	//
	
	// map should be all empty
	assert(testMap1.isEmpty());
	assert(testMap1.getSize()==0);

	// map should be all empty still
	testMap1.clear();
	assert(testMap1.isEmpty());
	assert(testMap1.getSize()==0);

	// invalid additions should not work
	// and map should be empty
	assert(testMap1.addValue("","")==false);
	assert(testMap1.addValue("","a")==false);
	assert(testMap1.addValue("a","")==false);
	assert(testMap1.isEmpty());
	assert(testMap1.getSize()==0);

	// not expecting these keys to be present
	assert(testMap1.contains("usa")==false);
	assert(testMap1.contains("japan")==false);	
	
	// add two key-value pairs
	assert(testMap1.addValue("usa","washington dc"));
	assert(testMap1.addValue("japan","tokyo"));
	
	// test the map in various ways now
	assert(testMap1.isEmpty()==false);
	assert(testMap1.getSize()==2);
	assert(testMap1.contains("usa")==true);
	assert(testMap1.contains("japan")==true);	
	assert((testMap1.getValue("usa")).compare("washington dc")==0);
	assert((testMap1.getValue("usa")).compare("tokyo")!=0);
	assert((testMap1.getValue("japan")).compare("tokyo")==0);
	assert((testMap1.getValue("japan")).compare("washington dc")!=0);

	// test key deletes
	assert(testMap1.deleteValue("usa")==true);
	assert(testMap1.contains("usa")==false);
	assert(testMap1.getSize()==1);
	assert(testMap1.deleteValue("canada")==false);
	assert(testMap1.getSize()==1);
	testMap1.clear();
	assert(testMap1.contains("japan")==false);
	assert(testMap1.getSize()==0);
	
	
	// PART 2 -- Start of Stress Testing
	//
	
	//
	// do a stress test of add, get, size
	// also do a test on copy constructor and assignment operator
	//
	int STRESS_TEST_SIZE=1500; // during your initial tests try smaller value, (e.g. 11)

	// test add key-value pairs
	// test size
	for(int i=0;i<STRESS_TEST_SIZE;i++) {
		ostringstream keyStream;
		keyStream << "key:" << i;
		string key = keyStream.str();
		
		ostringstream valStream;
		valStream << "there are " << i << " green bottles on the wall.";

		string val = valStream.str();

		assert(testMap1.addValue(key,val)==true);
		assert(testMap1.getSize()==(i+1));		

	}
	
	
	

	// test getVal
	for(int i=0;i<STRESS_TEST_SIZE;i++) {
		ostringstream keyStream;
		keyStream << "key:" << i;
		string key = keyStream.str();
		
		ostringstream valStream;
		valStream << "there are " << i << " green bottles on the wall.";
		string val = valStream.str();
		
		
		assert((testMap1.getValue(key)).compare(val)==0);
		
		
	}
	//testMap1.dm(); 
	
	
	

	// this is a test of the copy constructor
	StringMap testMap2(testMap1);
	
	// testMap2 should have exactly same key-value pairs
	// copied over...
	for(int i=0;i<STRESS_TEST_SIZE;i++) {
		ostringstream keyStream;
		keyStream << "key:" << i;
		string key = keyStream.str();
		
		ostringstream valStream;
		valStream << "there are " << i << " green bottles on the wall.";
		string val = valStream.str();
		
		assert((testMap2.getValue(key)).compare(val)==0);
		
	}

	
	
	// this is a test of the assignment operator
	StringMap testMap3;
	testMap3 = testMap2;

	// testMap3 should have exactly same key-value pairs copied over...
	for(int i=0;i<STRESS_TEST_SIZE;i++) {
		ostringstream keyStream;
		keyStream << "key:" << i;
		string key = keyStream.str();
		
		ostringstream valStream;
		valStream << "there are " << i << " green bottles on the wall.";
		string val = valStream.str();
		
		assert((testMap3.getValue(key)).compare(val)==0);
		
	}
	
	//
	// End of Stress Testing
	// 
	
	return 0; 
}