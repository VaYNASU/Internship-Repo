
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

using namespace std;

//Flight represents a departure flight
struct Flight
{
    string airLine;
    int flightNum;
    string deptDate;        //departure date
    struct Flight* next;
};

//class LinkedList will contains a linked list of flights
class LinkedList
{
    private:
        struct Flight* head;

    public:
   LinkedList();
   ~LinkedList();
   bool searchFlight(string airLine, int flightNum, string deptDate);
   bool addFlight(string airLine, int flightNum, string deptDate);
   int countTotalFlights();
   int countFlightsByAirLine(string airLine);
   int countFlightsByDate(string deptDate);
   bool cancelOneFlight(string airLine, int flightNum, string deptDate);
   bool cancelFlightsByAirLine(string airLine);
   bool cancelFlightsByDate(string deptDate);
   bool delayAFlight(string airLine, int flightNum, string oldDeptDate, string newDeptDate);
   bool changeAFlightAirLine(string oldAirLine, int flightNum, string deptDate, string newAirLine);
   void displayAllFlights();
   void displayFlightsByAirLine(string airLine);
   void displayFlightsByDate(string date);
};

//Constructor to initialize an empty linked list
LinkedList::LinkedList()
{
    head = nullptr;
}

//Destructor
//Before termination, the destructor is called to free the associated memory occupied by the existing linked list.
//It deletes all the nodes including the head and finally prints the number of nodes deleted by it.
//Return value: Prints the number of nodes deleted by it.
LinkedList::~LinkedList()
{
	//Add your own code
    //----
    int flightCount = 0;
    Flight* curr = head;

    while(curr != nullptr){
        Flight* deleted_flight = curr;
        curr = curr->next;
        delete deleted_flight;
        flightCount++;
    }
    

    cout<< "\nThe number of deleted flights is: " << flightCount <<"\n";
}

//A function to find if the parameterized flight is inside the LinkedList or not.
//Return true if it exists and false otherwise.
bool LinkedList::searchFlight(string airLine, int flightNum, string deptDate)
{
	//Add your own code
    //----
    Flight* curr = head;
    
    while(curr != nullptr){
        if(curr->airLine == airLine){
            if(curr->flightNum == flightNum){
                if(curr->deptDate == deptDate){
                    return true;
                }
            }
        }
        curr = curr->next;
    }
    return false;
    
}

string convert_date(string date) { //changes date formatting to YYYYMMDD to make it easier to check departure.
    int month, day, year; //date conversion advice from TA on Discord.
    char character1, character2;
    istringstream iss(date);
    iss >> month >> character1 >> day >> character2 >> year;
    ostringstream oss;
    oss << setw(4) << setfill('0') << year
        << setw(2) << setfill('0') << month
        << setw(2) << setfill('0') << day;
    return oss.str();
}


//Creates a new node and inserts it into the list at the right place.
//It also maintains an alphabetical ordering of flights by the airLine, flight number
//and departure date. i.e. first by airLine, then by flight numbers. i.e. if two flights
//come from the same airline, the flight should be inserted by the increasing order of
//their flight numbers. 
//Return value: true if it is successfully inserted and false in case of failures.

bool LinkedList::addFlight(string airLine, int flightNum, string deptDate)
{
    //Add your own code
    //----
    Flight* add_Flight = new Flight; //sets up node.
    add_Flight->airLine = airLine;
    add_Flight->flightNum = flightNum;
    add_Flight->deptDate = deptDate;
    add_Flight->next = nullptr;
    
    Flight* current = head;
    Flight* trail = nullptr;

    if(head == nullptr){ //checks to see if nothing in linked list.
        head = add_Flight;
        return true;
    }
    
    if(searchFlight(airLine, flightNum, deptDate)){ //if already exists, don't add.
        delete add_Flight;
        return false;
    }

    
    while(current != nullptr){ //where to keep the new flight.
        bool placed = false;

        if(add_Flight->airLine < current->airLine){
            placed = true;
        }else if(add_Flight->airLine == current->airLine){ //checks if same.
            if(add_Flight->flightNum < current->flightNum){ //checks if the new flight's number is smaller compared to the current. 
                placed = true;
            }else if(add_Flight->flightNum == current->flightNum){ //checks to see if the new flight's number is the same as the current.
                if(convert_date(add_Flight->deptDate) < convert_date(current->deptDate)){ // checks to see if the departure date is before the current departure date.
                    placed = true;
                }
            }
        }
        if (placed){ //figured out where the new flight belongs.
            break;
        }

        trail = current;
        current = current->next;

    }

    if(trail == nullptr){ //puts new flight at the front of the linked list.
            add_Flight->next = head; //add_Flight's next is set to the orginal head
            head = add_Flight; //head is now set as the new flight.
    }else{
        add_Flight->next = current; //puts it in the middle. add_Flight's next points to the node that is after it
        trail->next = add_Flight; // trail is set to the new flight. trail's next points to add_Flight
    }

    return true;
    
    
}

//This function counts total number of flights inside the list and return it.
int LinkedList::countTotalFlights()
{
    //Add your own code
    //----
    int total_Flights = 0;
    Flight* curr = head;

    while(curr != nullptr){
        total_Flights++; // this adds to how many flights we find.
        curr = curr->next; //moves to next flight in the linked list.
    }
    return total_Flights;

}

//This function counts total number of flights by the specified airLine and return it.
int LinkedList::countFlightsByAirLine(string airLine)
{
    //Add your own code
    //----
    int total_Flights = 0;
    Flight* curr = head;

    while(curr != nullptr){
        if(curr->airLine == airLine){ //check to see the if its the correct flight.
            total_Flights++;
        }
        curr = curr->next; //moves to the next flight in the linked list.
    }
    return total_Flights;


}

//This function counts total number of flights on the specified date and return it.
int LinkedList::countFlightsByDate(string deptDate)
{
    //Add your own code
    //----
    string date_converted = convert_date(deptDate); //changes date to YYYYMMDD

    int total_Flights = 0;
    Flight* curr = head;

    while(curr != nullptr){
        if(convert_date(curr->deptDate) == date_converted){ //converts the date so its easier to compare then it checks if its the same.
            total_Flights++;
        }
        curr = curr->next; //moves to the next flight in the linked list.
    }
    return total_Flights;


}

//Display all flights in the linked list starting from the head.
void LinkedList::displayAllFlights()
{
    //Add your own code
    //----
    Flight* temp = head;
    while(temp != nullptr){
        cout << left    << setw(5)  << temp->airLine
                    << setw(10) << temp->flightNum
                    << setw(12) << temp->deptDate   << "\n";
    
        temp = temp->next;
    }
	
}

//Display all flights in the list with the specified airLine.
void LinkedList::displayFlightsByAirLine(string airLine)
{
    //Add your own code
    //----
    Flight* temp = head;
    while(temp != nullptr){
        if(temp->airLine == airLine){
            cout << left    << setw(5)  << temp->airLine
                    << setw(10) << temp->flightNum
                    << setw(12) << temp->deptDate   << "\n";
        }
        temp = temp->next;
    }
    
}

//Display all flights with the specified date
void LinkedList::displayFlightsByDate(string date)
{
    //Add your own code
    //----
    Flight* temp = head;
    while(temp != nullptr){
        if(temp->deptDate == date){
            cout << left    << setw(5)  << temp->airLine
                    << setw(10) << temp->flightNum
                    << setw(12) << temp->deptDate   << "\n";
        }
        temp = temp->next;
    }
    

}

//Cancel the specified flight from the list, releases the memory and updates pointers.
//Return true if it is successfully canceled, false otherwise.
bool LinkedList::cancelOneFlight(string airLine, int flightNum, string deptDate)
{
    //Add your own code
    //----
    Flight* curr = head;
    Flight* trail = nullptr;

    if(head == nullptr){ //checks to see if the linked list is empty.
        return false;
    }

    while(curr != nullptr){
        if(curr->airLine == airLine){
            if(curr->flightNum == flightNum){
                if(curr->deptDate == deptDate){
                    if(trail == nullptr){
                        head = curr->next; //removes the head
                    }else{
                        trail->next = curr->next;
                    }

                    delete curr;
                    return true;
                    
                }

                
            }
        }
        trail = curr; //these moves the pointers to the next part of the linked list.
        curr = curr->next;
    }
    return false; 
}

//Cancel all flights from a specific airline, releases the memory and updates pointers.
//Return true if it is successfully canceled, false otherwise.
bool LinkedList::cancelFlightsByAirLine(string airLine)
{
    //Add your own code
    //----
    Flight* curr = head;
    Flight* trail = nullptr;
    
    bool is_deleted = false;
    if(head == nullptr){ //checks to see if the linked list is empty.
        return false;
    }

    while(curr != nullptr){
        if(curr->airLine == airLine){
            Flight* deleted_Flight = curr;
            
            if(trail == nullptr){
                head = curr->next;
                curr = head;
            }else{
                trail->next = curr->next;
                curr = curr->next;
            }
            delete deleted_Flight;
            is_deleted = true;
        }else{
            trail = curr; //these moves the pointers to the next part of the linked list.
            curr = curr->next;
        }
    }

    return is_deleted;
    
    
}

//Removes all flights with the specified date, releases the memory and updates pointers.
//Return true if they are successfully removed, false otherwise. 
bool LinkedList::cancelFlightsByDate(string deptDate)
{
    //Add your own code
    //----
    Flight* curr = head;
    Flight* trail = nullptr;
    
    bool is_deleted = false;
    if(head == nullptr){ //checks to see if the linked list is empty.
        return false;
    }

    while(curr != nullptr){
        if(curr->deptDate == deptDate){
            Flight* deleted_Flight = curr;
            
            if(trail == nullptr){ //this will remove the head if needed.
                head = curr->next;
                curr = head;
            }else{ //removes flight from list.
                trail->next = curr->next;
                curr = curr->next;
            }

            delete deleted_Flight;
            is_deleted = true;
        }else{
            trail = curr; //these moves the pointers to the next part of the linked list.
            curr = curr->next;
        }
    }

    return is_deleted;
}

//Modifies the departure date of the given flight. Return true if it modifies successfully and
//false otherwise.
bool LinkedList::delayAFlight(string airLine, int flightNum, string oldDeptDate, string newDeptDate)
{
    //Add your own code
    //----
    Flight* curr = head;
    Flight* trail = nullptr;

    if(head == nullptr){ //checks to see if the linked list is empty.
        return false;
    }

    while(curr != nullptr){
        if(curr->airLine == airLine){
            if(curr->flightNum == flightNum){
                if(curr->deptDate == oldDeptDate){
                    if(trail == nullptr){
                        head = curr->next;
                    }else{ //removes flight from list.
                        trail->next = curr->next;
                    }
                    
                    string new_Info = curr->airLine;
                    int new_Num = curr->flightNum;
                    delete curr;
                    
                    return addFlight(new_Info, new_Num, newDeptDate);
                }

                
            }
        }
        trail = curr; //these moves the pointers to the next part of the linked list.
        curr = curr->next;
    }
    return false; 
}

//Change a specific flight airline info. if it is found and change its airline successfully, return
//true; otherwise return false. 
bool LinkedList::changeAFlightAirLine(string oldAirLine, int flightNum, string deptDate, string newAirLine)
{
    //Add your own code
    //----
    Flight* curr = head;
    Flight* trail = nullptr;

    if(head == nullptr){ //checks to see if the linked list is empty.
        return false;
    }

    while(curr != nullptr){
        if(curr->airLine == oldAirLine){
            if(curr->flightNum == flightNum){ //these check to see it the correct flight info.
                if(curr->deptDate == deptDate){
                    if(trail == nullptr){
                        head = curr->next;
                    }else{
                        trail->next = curr->next;
                    }
                    
                    string new_depDate = curr->deptDate; //keeps everything but changes the airline.
                    int new_Num = curr->flightNum;
                    delete curr;
                    
                    return addFlight(newAirLine, new_Num, new_depDate); //adds the infor back into the linked list.
                }

                
            }
        }
        trail = curr; //these moves the pointers to the next part of the linked list.
        curr = curr->next;
    }
    return false;
}

#endif