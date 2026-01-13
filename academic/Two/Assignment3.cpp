
#include <iostream>
#include <iomanip>
#include <string>

#include "MaxHeap.h"

using namespace std;

void printMenu();
void heapSort(MaxHeap* oneMaxHeap);

int main()
{
	char input1 = 'Z';
	string airLine;
    int flightNum;
	string deptDate;
	int capacity;   //array capacity

	bool success = false;

	
	int newFlightNum;

    Flight oneFlight;

	// instantiate an empty Heap
	MaxHeap* heap1 = nullptr;
	printMenu();

	do {
		cout << "\nWhat action would you like to perform?" << endl;
		cin.get(input1);
		cin.ignore(20, '\n');	//flush the buffer
		input1 = toupper(input1);

		// matches one of the cases
		switch (input1)
		{
			case 'C':	//create empty Heap with the relevant capacity
				cout << "\nPlease enter the heap capacity: ";
				cin >> capacity;
				cin.ignore(20, '\n');	//flush the buffer

				
				heap1 = new MaxHeap(capacity); //creates a new heap with the capacity from the user.

				break;

			case 'D':	//delete the heap, call the destructor explicitly
				cout << "\nDelete the heap" << endl;
				
				delete heap1; // delets the heap. 

				//re-initialize it with default capacity 4
				
				heap1 = new MaxHeap(4); //reuses heap1 and sets the capacity to 4. 

				break;

			case 'E':	//Extract the maximum node
                if (heap1 == nullptr)
                    cout << "\nEmpty heap, can NOT extract max" << endl;
                else
                {
                    
					cout << "\nBefore extract heap max operation:" << endl;
					heap1->printHeap(); //this prints out the current heap.

					heap1->extractHeapMax(); //this will pull out the root from the heap. 

					cout << "\nAfter extract heap max operation:" << endl;
					heap1->printHeap(); //this prints out the current heap after the root is extracted and after the last element of the heap got heapified.
                }
                break;

			case 'F':	//Find a Flight
				cout << "\nEnter the flight number you want to search: ";
				cin >> flightNum;
				cin.ignore(20, '\n');	//flush the buffer

				
				
				 if (heap1->isFound(flightNum) != -1){ //this checks to see if isFound is not equal to a -1.
					
					cout << "\nFlight with number: " << flightNum << " is found" << endl; //this happens if isFound is anything but a -1, which means that a flight was found.
				 }else{

					cout << "\nFlight with number: " << flightNum <<  " is NOT found" << endl; //this happens if isFound got a -1 which means that a flight was not found. 
				 }

				break;

			case 'I':	//Insert a Flight
				cout << "\nEnter the flight airLine: ";
				cin >> airLine;

				cout << "\nEnter the flight number: ";
				cin >> flightNum;

				cout << "\nEnter the flight departure date: ";
				cin >> deptDate;

                cin.ignore(20, '\n');	//flush the buffer

				
				success = heap1->heapInsert(airLine, flightNum, deptDate); //this basically tells to see if the node actually was inserted after heapInsert runs.

				if (success){ //checks to see if node was inserted

					cout << "\nFlight: " << airLine << " " << flightNum << " on " << deptDate << " is added" << endl; //tell whether or not the flight was added. 
				}else{

					cout << "\nFlight: " << airLine << " " << flightNum << " on " << deptDate << " is NOT added" << endl;
				}


				break;

			case 'K':	//increase the FlightNum
				
				cout << "\nEnter the original flight number which you want to increase: ";
				cin >> flightNum;
				cout << "\nEnter the new flight number: ";
				cin >> newFlightNum;
				cin.ignore(20, '\n');	//flush the buffer

				
				if (heap1->isFound(flightNum) == -1){ //checks to see if the old flight actually exists in the heap.
					
					cout << "\nThe old flight number you try to increase does not exist" << endl;
				}else if(newFlightNum <= flightNum){ //another condition where the new flight number is less or equal than the orginal flight number.

					cout << "\nIncrease flight number error: new number is smaller than current number" << endl;
				}else if (heap1->isFound(newFlightNum) != -1){ //another condition where the flight already is on the heap.
					
					cout << "\nThe new flight number you entered already exist, increase flight number operation failed" << endl;
				}else{

					cout << "\nBefore increase flight number operation:" << endl; 
					heap1->printHeap(); //prints out the current heap that is found. 

					oneFlight = heap1->getFlightArr()[heap1->isFound(flightNum)]; //this makes a new flight which is basically the key to use to increase.
					
					oneFlight.flightNum = newFlightNum; //this sets the new flight to have the new flight number.
					heap1->heapIncreaseFlightNum(heap1->isFound(flightNum), oneFlight); //this increases the old flight number to the new one. 

					cout << "\nFlight with old number: " << flightNum << " is increased to new number: " << newFlightNum << endl;  

					cout << "\nAfter increase flight number operation: " << endl; 
					heap1->printHeap(); //prints out the new heap.
				}

				break;

			case 'M':	//get maximum node
			    
				if (heap1->getSize() == 0){ //checks to see if the heap is empty.

					cout << "\nEmpty heap, can NOT get max node" << endl;
				}else{

					Flight maxFlight = heap1->getHeapMax(); //this will literally get the max node.

					cout << "\nThe maximum heap node is:" << endl; //prints out the max node.
					cout << left;
					cout << setw(5) << maxFlight.airLine
     					 << setw(10) << maxFlight.flightNum
     					 << setw(12) << maxFlight.deptDate  << endl;

				}
				
				break;

			case 'P':	//Print heap contents
			    
				heap1->printHeap();

				break;

			case 'S':	//HeapSort
				cout << "\nHeap sort. Flights will be sorted in increasing order of their numbers" << endl;
				
				heapSort(heap1);

				break;

			case 'Q':	//Quit
				delete heap1;
				break;

			case '?':	//Display Menu
				printMenu();
				break;

			default:
				cout << "\nUnknown action" << endl;
				break;
		} //end of switch
	} while (input1 != 'Q');
	return 0;
}

//***********************************************************************
//Given a max heap, it is sorted in increasing order of flightNum.
void heapSort(MaxHeap* oneMaxHeap)
{
    
	int total_flights = oneMaxHeap->getSize(); //this gets the size of the heap basically the same as getting the total ammount of flights.

	Flight* temp_array = new Flight[total_flights]; //this creates a temporary array to store the sorted flights.

	int sort_index = total_flights - 1; //this is the last node.

	while(sort_index >= 0){ //this is where the heapsort happens. it keeps going till there is nothing left.

		temp_array[sort_index] = oneMaxHeap->getHeapMax(); //this stores the root into the temporary array.
		oneMaxHeap->extractHeapMax(); //gets the root then heapify the new root.
		sort_index--;
	}

	for (int i = 0; i < total_flights; i++){ //prints out the sorted array.
		cout << left;
        cout << setw(5)  << temp_array[i].airLine
             << setw(10) << temp_array[i].flightNum
             << setw(12) << temp_array[i].deptDate << endl;
	}

	delete[] temp_array; //don"t need this anymore after we printed out the sorted flights.

}

//**The function displays the menu to a user**
void printMenu()
{
	cout << "Choice\t\tAction\n";
	cout << "------\t\t------\n";
	cout << "C\t\tCreate a heap\n";
	cout << "D\t\tDelete the heap\n";
	cout << "E\t\tExtract max node\n";
	cout << "F\t\tFind a flight by number\n";
	cout << "I\t\tInsert a flight\n";
	cout << "K\t\tIncrease a flight number\n";
	cout << "M\t\tGet the max node\n";
	cout << "P\t\tPrint the heap\n";
	cout << "S\t\tHeap Sort\n";
	cout << "Q\t\tQuit\n";
	cout << "?\t\tDisplay Help\n\n";
}