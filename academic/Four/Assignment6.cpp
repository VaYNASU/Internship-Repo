// Description: this is the main program that reads input from keyboard,
// it then execute various red-black tree operations which is given in the input.

#include "RedBlackTree.h"

using namespace std;

//This function used to get the info. of a Flight object
void getFlightInfo(string oneLine, string& airLine, int& flightNum, string& deptDate);

int main()
{

   string airLine;
   int flightNum;
   string deptDate;
   string command, oneLine, token;
   string delimiter = ",";

   int pos = 0;

   //Create a RedBlackTree object here, use it throughout the program
   //----
   //----
   RedBlackTree RB_tree; //this creates the Red Black tree


   do
   {
      getline(cin, oneLine);
      pos = oneLine.find(delimiter);
      token = oneLine.substr(0, pos);
      command = token;
      oneLine.erase(0, pos + delimiter.length());

      if(command.compare("quit")==0)
      {
         cout << "\nCommand: quit" << endl;
         //call the relevant function on the red black tree
         //----
         break;
      }
      else if(command.compare("tree_preorder")==0)
      {
         cout << "\nCommand: tree_preorder" << endl;

         //call the relevant function on the red black tree
         //----
         RB_tree.treePreorder(); //this just prints out all the nodes in the tree in pre order traversal.
      }
      else if(command.compare("tree_inorder")==0)
      {
         cout << "\nCommand: tree_inorder" << endl;

         //call the relevant function on the red black tree
         //----
         RB_tree.treeInorder(); //this just prints out the nodes in the tree with in order traversal.
      }
      else if(command.compare("tree_postorder")==0)
      {
         cout << "\nCommand: tree_postorder" << endl;

         //call the relevant function on the red black tree
         //----
         RB_tree.treePostorder(); //this just prints out the nodes in post order traversal.
      }
      else if(command.compare("tree_minimum")==0)
      {
         cout << "\nCommand: tree_minimum" << endl;

         //call the relevant function on the red black tree
         //----
         RB_tree.treeMinimum(); //this simply prints out the smallest node.
      }
      else if(command.compare("tree_maximum")==0)
      {
         cout << "\nCommand: tree_maximum" << endl;

         //call the relevant function on the red black tree
         //----
         RB_tree.treeMaximum(); //this simply prints out the largest node.
      }
      else if(command.compare("tree_predecessor")==0)
      {
         //call the relevant function to get the Flight info. first
         //----
         getFlightInfo(oneLine,airLine,flightNum,deptDate);
         cout << "\nCommand: tree_predecessor" << endl;

         //call the relevant function on the red black tree
         //----
         RB_tree.treePredecessor(airLine,flightNum,deptDate);

      }
      else if(command.compare("tree_successor")==0)
      {
         //call the relevant function to get the Flight info. first
         //----
         getFlightInfo(oneLine,airLine,flightNum,deptDate);
         cout << "\nCommand: tree_successor" << endl;

         //call the relevant function on the red black tree
         //----
         RB_tree.treeSucessor(airLine,flightNum,deptDate);
      }
      else if(command.compare("tree_search")==0)
      {
         //call the relevant function to get the Flight info. first
         //----
         getFlightInfo(oneLine,airLine,flightNum,deptDate);
         cout << "\nCommand: tree_search" << endl;

         //call the relevant function on the red black tree
         //----
         RB_tree.treeSearch(airLine,flightNum,deptDate);
      }
      else if(command.compare("tree_insert")==0)
      {
         //call the relevant function to get the Flight info. first
         //----
         getFlightInfo(oneLine,airLine,flightNum,deptDate);
         cout << "\nCommand: tree_insert" << endl;
         cout << left;
         cout << setw(5)  << airLine
              << setw(10) << flightNum
              << setw(12) << deptDate   << endl;

        //call the relevant function to insert the Flight inside the RBT
        //----
         RB_tree.treeInsert(airLine,flightNum,deptDate);


      }
   } while(true);  //continue until 'quit'
   return 0;
}

//************************************************************************************
//This function from one line, extracts the airLine, flightNum and deptDate of a Flight
void getFlightInfo(string oneLine, string& airLine, int& flightNum, string& deptDate) ////this is essentially similar to what is being done above to extract the flight info from the input.
{
   //Design your own code here
   //----
   int comma_position = 0; //this is where the commma is located in the input.
   string delimiter = ",";

   comma_position = oneLine.find(delimiter); //this is where the comma is located after the airline name.
   airLine = oneLine.substr(0,comma_position); //this is where the airline name will be pulled from.
   oneLine.erase(0,comma_position + delimiter.length()); //this gets rid of the airline name so that rest of the input can be used to extract the rest of the info so that it wont interfere.

   comma_position = oneLine.find(delimiter); //this is where the comma is located after the flight number.
   string string_flightNum = oneLine.substr(0,comma_position); //this is where flightn num will pulled from.
   flightNum = stoi(string_flightNum); //this is where the flight number that was given in the input as a string is converted into an integer so it can be used.
   oneLine.erase(0,comma_position + delimiter.length()); //this gets rid of flight number from the input so that it won't intefere with getting the departure date.
   
   deptDate = oneLine; //this sets the departure date to whatever is left in oneLine. 


}
