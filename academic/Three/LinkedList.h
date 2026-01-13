#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

struct Flight
{
    string airLine;
    int flightNum;
    string deptDate;
    struct Flight* next;
};

class LinkedList
{
	private:
		struct Flight* head;
		int size;      //number of Flight objects inside the linked list
    public:
       	LinkedList();
       	~LinkedList();
       	Flight* getHead();
       	int getSize();
       	bool searchFlight(string airLine, int flightNum, string deptDate);
       	bool insertFlight(string airLine, int flightNum, string deptDate);
       	bool deleteFlight(string airLine, int flightNum, string deptDate);
       	void displayList();
};

//Constructor
LinkedList::LinkedList()
{
    
    head = nullptr; //this sets the head as null by default.
    size = 0; //this sets the current size of the linked list as 0 so in this case no Flight objects are in the linked list yet.

}

//Destructor
LinkedList::~LinkedList()
{
    
    Flight* curr = head; //this sets the current pointer to head node.
    

    while(curr != nullptr){
        Flight* deleted_flight = curr; //this puts the current node into a deleted Flight object.
        curr = curr->next; //this sets curr to whatever curr's next is pointing to. 
        delete deleted_flight; //deletes temporary flight object since it has to be deleted. 

    }

    head = nullptr; //this will reset the head back to null as well as size of the linked list back to 0.
    size = 0;

}

Flight* LinkedList::getHead()
{
    
    return head; //this simply returns the head of the linked list.
}

//Return number of Flights inside the Linked list
int LinkedList::getSize()
{
    
    return size; //this will just return the current size of the linked list.
}

//This function does a linear search on the Flight list with the given flight info.
//it returns true if the corresponding Flight is found, otherwise it returns false.

bool LinkedList::searchFlight(string airLine, int flightNum, string deptDate)
{
    
    Flight* curr = head; //this sets the current pointer as head of the linked list.

    while(curr != nullptr){ //this checks to see if the current pointer is not empty. 
        if(curr->airLine == airLine){ //this checks to see if the current's airline pointer is equal to the airline and the same for the flight number and departure date.
            if(curr->flightNum == flightNum){
                if(curr->deptDate == deptDate){
                    
                    return true; //if it shows up its true.
                }

                
            }
        }

        curr = curr->next; //makes current have whatever it's next pointer is pointing at. 

    }

    return false; //if nothing shows up its false. 

}

//Insert the parameter Flight at the head of the linked list.
//return true if it is inserted successfully and false otherwise
bool LinkedList::insertFlight(string airLine, int flightNum, string deptDate)
{
     //if the Flight already exist, return false
     if (searchFlight(airLine, flightNum, deptDate))
     {
         cout << "\n" << airLine << " " << flightNum << " on " << deptDate << " duplicated. NOT added" << endl;
         return false;
     }
     
    
     Flight* insert_flight = new Flight; //this makes a new flight that can be used to add to the front of the linked list.

     insert_flight->airLine = airLine; //this sets up the new insert flight node with its airline, flight number and its departure date. 
     insert_flight->flightNum = flightNum;
     insert_flight->deptDate = deptDate;

     insert_flight->next = head; //this makes insert_flight's next pointer point at the head of the linked list.
     head = insert_flight; //this then sets the head node to be set as the new inserted flight node so it basically inserts it at the front. 

     size++; //this increases the count of the amount of flights in the linked list.
     
     return true;
}

//Delete the Flight with the given info. from the linked list.
//Return true if it is deleted successfully and false otherwise
bool LinkedList::deleteFlight(string airLine, int flightNum, string deptDate)
{
    
    

    if(head == nullptr){ //this just checks to see if head is emtpy.

        return false;
    }

    Flight* trail = head; //this sets up the trailing pointer that follows the current pointer.
    Flight* curr = head->next; //this sets up the current pointer equal to next node in the linked list.

    if(head->airLine == airLine){ //this is used to check if the head has the flight info needed. It checks the flight number and the departure date as well.
        if(head->flightNum == flightNum){
            if(head->deptDate == deptDate){

                Flight* deleted_flight = head; //this node is temporary but it holds the head node that has to be deleted. 

                head = head->next; //this sets the head node to be equal to whatever it's next is pointing to.
                delete deleted_flight; //this deletes the old head node since its not needed.
                size--; //this lowers the current amount of flights in the linked list.
                return true;
            }


        }
    }    
    
    while(curr != nullptr){ //this checks to see if the current pointer is not empty. 
        if(curr->airLine == airLine){ //this is used to check to see if the current pointer has the flight info needed. It checks the flight number and the departure date as well.
            if(curr->flightNum == flightNum){
                if(curr->deptDate == deptDate){
                    trail->next = curr->next; //this removes the current node from the linked list and instead sets it to the trail node's next pointer.
                    delete curr; //this deletes the current node that was holding the flight that was found.
                    size--; //this lowers the current amount of flights in the linked list.
                    return true;
 
                }

            }

        }

        trail = curr; //this moves the trail pointer foward in the linked list.
        curr = curr->next; //this moves the current pointer forward in the linked list.

    }

    return false;
    
}

//This function displays the content of the linked list.
void LinkedList::displayList()
{
    
    Flight* temp = head; //this is the start of the linked list because each new flight entry is places at the front. 

    if(temp == nullptr){ //this checks to see of the temporary node is empty or not. 
        //cout << "No Flights found." << endl;
        return;

    }
    
    while(temp != nullptr){ //this will loop through each flight that is found on the linked list.
        cout << left<< setw(5)  << temp->airLine
             << setw(10) << temp->flightNum
             << setw(12) << temp->deptDate  << "\n";
        
        temp = temp->next; //this will move to the next node in the linked list to display.
    }
    
}