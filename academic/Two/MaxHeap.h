
#include <iostream>
#include <iomanip>
#include <string>


using namespace std;


struct Flight
{
    string airLine;
    int flightNum;
    string deptDate;
};

//class MaxHeap represents a max heap that contains Flight objects. The underline data structure
//is a one dimensional array of Flight.
class MaxHeap
{
    private:
    struct Flight* flightArr;	//an array of Flight
    int capacity, size;

	public:
    MaxHeap(int capacity);
    ~MaxHeap();

	Flight* getFlightArr();
	int getSize();
	int getCapacity();
	int isFound(int aFlightNum);
	bool heapIncreaseFlightNum(int index, Flight oneFlightWithNewFlightNum);
	bool heapInsert(string airLine, int flightNum, string deptDate);
	void heapify(int index);
	Flight getHeapMax();
	void extractHeapMax();
	int leftChild(int parentIndex);
	int rightChild(int parentIndex);
	int parent(int childIndex);
	void printHeap();
};

//Constructor to dynamically allocate memory for a heap with the specified capacity
MaxHeap::MaxHeap(int capacity)
{
 	
    size = 0; //makes sure the heap is empty.
    this->capacity = capacity; //this saves the passed value of capacity in the constructor to the capacity that is part of the array class.
    flightArr = new Flight[capacity]; //this creates a new array based on the capacity given.
}

//Destructor
//Before termination, the destructor is called to free the associated memory occupied by the heap.
//and prints the number of nodes deleted by it.
MaxHeap::~MaxHeap()
{
 	
    int numOfFlights = size; //stores the total number of flights so that it can read out at the end how many it deleted.

    delete[] flightArr; //resets the array.

    flightArr = nullptr; //this closes the pointer.

    size = 0; //resets the size of the heap.
    capacity = 4; //sets the capacity of array to 4.
    
    
    
	cout << "The number of deleted flights is: " << numOfFlights << endl;
}



bool MaxHeap::heapInsert(string airLine, int flightNum, string deptDate)
{
	//if the flight already exist, return false
	if (isFound(flightNum) != -1) //this checks to see if a flight is found. if isFound comes back with -1 then its not found.
	{
		cout << "\nDuplicated flight. Not added" << endl;
		return false;
	}
	
    int double_capacity;

    if (size == capacity){ //this checks to see is the heap size is the same size as the array capacity.
        double_capacity = capacity*2;

        Flight* double_capacity_array = new Flight[double_capacity];

        for (int copy_index = 0; copy_index < size; copy_index++){ //this will move all the flights from the original array into the double capacity array.
            
            double_capacity_array[copy_index] = flightArr[copy_index]; //this is where the copy happens. basically the new array gets everything the original had.

        }

        delete[] flightArr; //cleans up flightArr since we already put its elments into the new array. 
        flightArr = double_capacity_array; //flightArr will now use the new array that has double its capacity. 
 
        capacity = double_capacity; //this updates the heap's object variable capacity but only if it doubles.

        cout << "\nReach the capacity limit, double the capacity now." << endl;
        cout << "The new capacity now is " << capacity << endl;

    }

    Flight dummy_flight; //this created the dummy flight.
        
    dummy_flight.flightNum = -100; 
    dummy_flight.airLine = airLine; 
    dummy_flight.deptDate = deptDate;

    flightArr[size] = dummy_flight; //this is temporary location for for the increase_flight because it helps maintain the heap.

    size = size + 1; //this increases the heap size.

    Flight increase_flight; //this is created so it can be used to increase dummy_flight.

    increase_flight.flightNum = flightNum;
    increase_flight.airLine = airLine;
    increase_flight.deptDate = deptDate;

    heapIncreaseFlightNum(size - 1, increase_flight); //this is called so that we can increase dummy_flight's flightNum in the heap and size - 1 is the index for dummy_flight.
    

    return true;

    
}

Flight MaxHeap::getHeapMax(){
    
    return flightArr[0]; //this literally returns the root. 
}

void MaxHeap::extractHeapMax(){
    
    flightArr[0] = flightArr[size - 1]; //this replaces the root of the heap with the last node of the heap.

    size = size - 1; //this reduces the size of the heap because the root is gone.

    heapify(0); //this calls heapify so that this can make sure the new root is in its correct position in the heap.


}

void MaxHeap::printHeap()
{
	
    int i = 0; //keeps track of the increments in the while loop. This is also the index for flightArr.

    if (size == 0){ //this checks to see if the heap is empty.
        cout << "\nEmpty heap, no elements" << endl;
        return; //this will only return if the heap is empty.
    }
    
	cout << "\nHeap capacity = " << getCapacity() << endl;
	cout << "\nHeap size = " << getSize() << "\n" << endl;

    
    while(i < size){ //this will print out every flight data. 
        cout << left;
        cout << setw(5)  << flightArr[i].airLine
             << setw(10) << flightArr[i].flightNum
             << setw(12) << flightArr[i].deptDate << endl;
        i++; //just increments i.
    }
    
}

int MaxHeap::getSize(){
    return size; //simply returns the size of the heap.
}
int MaxHeap::getCapacity(){
    return capacity; //returns the capacity of the array.
}

Flight* MaxHeap::getFlightArr(){
    return flightArr; //returns the array;
}

int MaxHeap::parent(int childIndex){ //this sets up the parent node.
    int index = (childIndex - 1) / 2;   //need to do childIndex - 1 because we are using 0th index. the pseudo code uses 1 index. 
    
    
    return index;
}

int MaxHeap::leftChild(int parentIndex){ //this sets up the left child node of the parent.
    return 2*parentIndex + 1; //need to do plus 1 since code uses 0th index.
}

int MaxHeap::rightChild(int parentIndex){ //this sets up the right child node of the parent.
    return 2*parentIndex + 2; //need to do plus 2 since the code uses 0th index
}

int MaxHeap::isFound(int aFlightNum){
    int flight_index = 0;

    while(flight_index < size){
        if (flightArr[flight_index].flightNum == aFlightNum){ //checks to see flightNum is found in the array.
            return flight_index; //returns the index where the flight number is found. 
            
        }
        flight_index++; //increments the flight_index to continue the search.
    }
    return -1; //the flight wasn't found.
}




void MaxHeap::heapify(int index){
    
    int left = leftChild(index);
    int right = rightChild(index);

    int largest_num = index;
    
    if (left < size){ //its in 0th index instead of 1 index it also checks to see if the left child is bigger.
        if (flightArr[left].flightNum > flightArr[index].flightNum){
            largest_num = left; //if its bigger then the largest is the left child.
        }else{
            largest_num = index;
        }
        
        
    }

    if (right < size){ //its in 0th index instead of 1 index it also checks to see if the right child is bigger.
        if (flightArr[right].flightNum > flightArr[largest_num].flightNum){
            largest_num = right; //if its bigger than the largest is the right child.
        }
        
         
    }
    

    if (largest_num != index){
        Flight temp_swap = flightArr[index];

        flightArr[index] = flightArr[largest_num]; //this exchanges flightArr[index] with flightArr[largest_num];
        flightArr[largest_num] = temp_swap;

        heapify(largest_num); //does a recursive call to heapify again but this time it passes largest_num.
    }
}    

bool MaxHeap::heapIncreaseFlightNum(int index, Flight oneFlightWithNewFlightNum){
    if (oneFlightWithNewFlightNum.flightNum < flightArr[index].flightNum){ //checks to see if a new flight number can even be used.
        cout << "\nIncrease flight number error: new number is smaller than current number" << endl;

        return false; //this happens when heap doesn't increase flight number.
    }

    flightArr[index].flightNum = oneFlightWithNewFlightNum.flightNum; //this updates the flight number.

    while(index > 0){ //code uses 0th index so we use 0 instead of the 1 index like in psuedo code.
        if (flightArr[parent(index)].flightNum < flightArr[index].flightNum){
            Flight temp_swap = flightArr[index];

            flightArr[index] = flightArr[parent(index)]; //this exchanges flightArr[index] with flightArr[parent(index)].
            flightArr[parent(index)] = temp_swap;
            
            index = parent(index); //this bubbles up.
        }else{
            break; //this gets out of the loop when the heap structure is done.
        }
    }

    return true; //this happens when the heap does increase flight number.

}
