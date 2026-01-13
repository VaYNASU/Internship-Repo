#include "LinkedList.h"

using namespace std;

class Hash
{
    private:
		LinkedList* hashTable;     //hashTable is a one-dimensional array of LinkedList
		int m;      //m is the slot number of the hash table
	public:
      Hash(int size);
      ~Hash();
      bool hashSearch(string airLine, int flightNum, string deptDate);
      bool hashInsert(string airLine, int flightNum, string deptDate);
      bool hashDelete(string airLine, int flightNum, string deptDate);
      double hashLoadFactor();
      void hashDisplay();
      int hashFunction(string key);
 };


//constructor
Hash::Hash(int size)
{
   
   m = size; //this sets m to the size of the hash table. 
   hashTable = new LinkedList[m]; //this creates a hash table with the LinkedList being used as an array.
}

//Destructor
Hash::~Hash()
{
   
   delete[] hashTable; //this deletes the LinkedList array.
   hashTable = nullptr; //this closes off teh hasTable pointer because its not being used at the moment. 
}

//This function searches for a key inside the hash table and
//return true if it is found and false otherwise
bool Hash::hashSearch(string airLine, int flightNum, string deptDate)
{
   bool found = false;
   
   string hash_key = airLine + to_string(flightNum) + deptDate; //this creates a key for the hash table to use. flight number had to be changed to a string so that it wouldn't cause issues.
   int hash_index = hashFunction(hash_key); //this figures out where to hash the flight based on what the hash funciton outputs. 

   found = hashTable[hash_index].searchFlight(airLine,flightNum,deptDate); //this searches for the flight and the linked list will report back true or false depending on if the flight was found or not.

   if (found == true)
     cout << "\n"       << left
          << setw(5)    << airLine
          << setw(10)   << flightNum << " on "
          << setw(12)   << deptDate
          << " is found inside the hash table" << endl;
   else
      cout << "\n"      << left
           << setw(5)   << airLine
           << setw(10)  << flightNum << " on "
           << setw(12)  << deptDate
           << " is NOT found inside the hash table" << endl;
   
   return found; 
}

//hashInsert inserts a Flight with the relevant info. into the hashTable.
//it returns true if the data is inserted successfully and false otherwise
bool Hash::hashInsert(string airLine, int flightNum, string deptDate)
{
   
   bool inserted_flight = false;

   string hash_key = airLine + to_string(flightNum) + deptDate; //this is similar to search. this creates a key for the hash table to use. flight number had to be changed to a string so that it wouldn't cause issues.
   int hash_index = hashFunction(hash_key); //this figures out where to hash the flight based on what the hash funciton outputs.
   
   inserted_flight = hashTable[hash_index].insertFlight(airLine,flightNum,deptDate); //this tries to insert the flight and the linked list  will report back true or false depending on if the flight was added to the hash table or not.

   return inserted_flight;
}

//hashDelete deletes a Flight with the relevant key from the hashTable.
//it returns true if it is deleted successfully and false otherwise
bool Hash::hashDelete(string airLine, int flightNum, string deptDate)
{
   
   bool flight_deleted = false; 

   string hash_key = airLine + to_string(flightNum) + deptDate; //this creates a key for the hash table to use. flight number had to be changed to a string so that it wouldn't cause issues.
   int hash_index = hashFunction(hash_key); //this figures out where to hash the flight based on what the hash function gives out.

   flight_deleted = hashTable[hash_index].deleteFlight(airLine,flightNum,deptDate); //this tries to deletes the flight and the linked list will report back true or false depending on if the flight was deleted to the hash table or not.
   
   if(flight_deleted == true){ //this checks to see if the flight was actually deleted or not.
      cout << left
           << setw(5)   << airLine
           << setw(10)  << flightNum << " on "
           << setw(12)  << deptDate
           << " is deleted from hash table" << endl;
   }else{ //this happens if the flight was not deleted.
   
      cout << left
           << setw(5)   << airLine
           << setw(10)  << flightNum << " on "
           << setw(12)  << deptDate
           << " is NOT deleted from hash table" << endl;
   }
   
   return flight_deleted;
}

//This function computes your hash table real load factor
//it is the longest linked list size
double Hash::hashLoadFactor()
{
   
   int longest = 0; //this hold the size of the largest linked list in the hash table.

   int index = 0;
   while(index < m){ //this will go through every slot that is on the hash table.
      int current_hash_size = hashTable[index].getSize(); //this gets the total amount of flights that are on a specific linked list.

      if(current_hash_size > longest){ //this checks to see if the newly recieved linked list size is bigger than the currently longest linked list size.
         
         longest = current_hash_size; //this updates the longest linkest list size.
      }

      index++; //this simply increments to the next slot.
   }
   return longest;
}

//This function prints all elements from the hashTable.
void Hash::hashDisplay()
{
   
   int index = 0;
   while(index < m){ //this will go through every slot on the hash table.

      cout << "\nHashTable[" << index << "], size = " << hashTable[index].getSize() << endl; //this prints out the index of each slot and the linked list size.
      hashTable[index].displayList(); //this will show the flights that are stored at a specific linked list at the index.

      index++; //this simply increments to the next slot.
   }
   
}

//This is the hash function you need to design. Given a
//string key, the function should return the slot number

int Hash::hashFunction(string key)
{
   
   unsigned int hash_value = 0; //this stores the hash value.
   unsigned int hash_final; //this holds the final.

   for (char index : key){ //this loops through every single character on the key that is shared to the hash function.
      hash_value = hash_value * 43 + index; //this helps evenly spread out the keys.

   }
   hash_final = hash_value % m; //this makes sure the final hash actually fits on the hash table.
   return hash_final;
}