#include "Hash.h"

#include <sstream>

using namespace std;

//This function used to get all info. of a Flight object
void getFlightInfo(string oneLine, string& airLine, int& flightNum, string& deptDate);

int main()
{
   int size = 0;

   //a counter used to count number of valid Flight objects entered
   int counter = 0;

   string airLine, deptDate;
   int flightNum;

   
   string oneLine; //this is used to hold a line of flight info.
   string hash_operation; //this is used to hold the command the user wants to perform.

   cin >> size;
   cin.ignore(20, '\n');

   
   Hash* flight_hash = new Hash(size); //this creates a new hash table.
   

   do {
         
         getline(cin,oneLine); 

         if(oneLine == "InsertionEnd"){ //this checks to see if we reached the end of inserting.
            
            break;
         }

         getFlightInfo(oneLine,airLine,flightNum,deptDate); //this gets all the flight info.

         bool flight_inserted = flight_hash->hashInsert(airLine,flightNum,deptDate); //this will try to insert the flight in to the hash table. 

         if(flight_inserted){ //this checks to see if the flight is inserted it will then increment the counter.
            
            counter++; //this simply increments the counter.
         }



   } while(true);

    cout << "\nHash table size is: " << size;
    cout << "\nTotal Flight objects entered is: " << counter;

   //This do..while loop is used to get the commands until 'End'
   do {
        //get one line command
        getline(cin,oneLine);

        stringstream extract_line(oneLine); //this is used to go through the user's data and uses the comma as a delimiter.
        
        getline(extract_line,hash_operation,','); //this is used to send the command from the user's data so it can be stored in hash_operation to perform an action.

        if(hash_operation == "hashSearch")
        {
            
            int flight_number;
            string airline;
            string departure_date;
            

            getline(extract_line,airline,','); //this grabs the airline from the user's data right before the comma which is the delimter.
            
            extract_line >> flight_number; //this grabs the flight number.
            extract_line.ignore(20,','); //this skips the comma after the flight number.
            
            getline(extract_line,departure_date,','); //this grabs the departure date from the user's data right before the comma which is the delimter.
            
            flight_hash->hashSearch(airline,flight_number,departure_date); //this searches for the flight on the hash table.

        }
        else if(hash_operation == "hashDelete")
        {
    
            int flight_number;
            string airline;
            string departure_date;

            getline(extract_line,airline,','); //this grabs the airline from the user's data right before the comma which is the delimter.
            
            extract_line >> flight_number; //this grabs the flight number.
            extract_line.ignore(20,','); //this skips the comma after the flight number.
            
            getline(extract_line,departure_date,','); //this grabs the departure date from the user's data right before the comma which is the delimter.

            flight_hash->hashSearch(airline,flight_number,departure_date); //this first searches for the flight on the hash table so that it can then be deleted.

            flight_hash->hashDelete(airline,flight_number,departure_date); //this deletes the flight from the hash table. 

        }else if(hash_operation == "hashDisplay"){

            flight_hash->hashDisplay();
        }else if(hash_operation == "hashLoadFactor"){
            
            double ideal_load = (double)counter / size; //this gives the ideal load factor for the hash table. needed to convert counter since counter is an int. 

            double actual_load = flight_hash->hashLoadFactor(); //this gets the actual load factor of the hash table. 

            double performance = actual_load / ideal_load; //this gets the performance ratio as shown how in the instructions. 

            printf("\nThe ideal load factor is: %.2f\n",ideal_load);
            printf("\nMy hash table real load factor is: %.2f\n",actual_load);
            printf("\nMy hash table performance ratio is: %.2f\n",performance);


        }else if(hash_operation == "End"){
            
            break;
        }
    } while(true);

    delete flight_hash; //this cleans up the memory after finished.

   return 0;
}

//***************************************************************************
//From one line, this function extracts the tokens and get one Flight info.
//This function is completed and given here as a study guide for extracting tokens (Given By Professor)
void getFlightInfo(string oneLine, string& airLine, int& flightNum, string& deptDate)
{
    string delimiter = ",";
	int pos = oneLine.find(delimiter);
	string token = oneLine.substr(0,pos);
	airLine = token;
	oneLine.erase(0, pos+delimiter.length());

	pos = oneLine.find(delimiter);
	token = oneLine.substr(0,pos);
	flightNum = stoi(token);
	oneLine.erase(0, pos+delimiter.length());

	pos=oneLine.find(delimiter);
	token = oneLine.substr(0,pos);
	deptDate = token;
	oneLine.erase(0, pos+delimiter.length());
}