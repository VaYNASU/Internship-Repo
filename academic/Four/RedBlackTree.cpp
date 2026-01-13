// Description: Red black tree implementation. 

#include "RedBlackTree.h"


using namespace std;

//*******************************************************************
//constructor
RedBlackTree::RedBlackTree()
{
	//----
    root = nullptr; //this just creates a empty Red Black tree by essentialy setting the root as null since there is nothing in there.
}

//*******************************************************************
//destructor
RedBlackTree::~RedBlackTree()
{
	//----
	//----
    int nodeNum = deleteNode(root); //this collects the amount of nodes that are deleted because deleteNode function returns the cound after its done. 
	cout << "The number of deleted nodes: " << nodeNum << endl;
}

//Read the assignment description carefully and finish all functions definition here
//----
//----

Node* RedBlackTree::getRoot(){

    return root; //this simply returns the root node. 
}

int RedBlackTree::deleteNode(Node *node){

    Node* deleted_node = node; //this creates a node that is used for deleting a node on the tree.
    int node_count; //this keeps track of the nodes that are deleted on the tree.

    if(deleted_node == nullptr){ //this only happens when there is literally nothing in the tree.
        
        return 0; 
    }

    node_count = 1 + deleteNode(deleted_node->rightChild) + deleteNode(deleted_node->leftChild); //this basically keeps track of the amount of nodes that are deleted in each subtree.
    //the 1 is also there so that count also includes the current node.

    delete deleted_node; //this cleans up the memory.
    return node_count; //this returns the amount of nodes that are deleted from both the right subtree, left subtree as well as the current node. 
}

Node* RedBlackTree::findMinimumNode(Node *node){
    Node* min_node = node;

    if(min_node == nullptr){ //this runs if node is empty then it will jsut return empty. This is also the base case.
        return nullptr;
    }

    if(min_node->leftChild == nullptr){ //this checks to see if the left child doesn't have anymore left child. Left subtree typically contains the smallest node.

        return min_node; //this just returns the last node that had a left child.
    }


    return findMinimumNode(min_node->leftChild); //this just calls the method again because there is a left child still on the subtree.

}



Node* RedBlackTree::findMaximumNode(Node *node){

    Node* max_node = node;

    if(max_node == nullptr){ //if node is empty then it will jsut return empty. This is also the base case.
        return nullptr;
    }

    if(max_node->rightChild == nullptr){ //this checks to see if the right child doesn't have anymore right child. Right subtree typically contains the largest node.

        return max_node; //this just returns the last node that had a right child.
    }

    
    return findMaximumNode(max_node->rightChild); //this just calls the method again because there is a right child still on the subtree.

}

Node* RedBlackTree::findPredecessorNode(Node *node){
    
    Node* current_node = node; //this stores node.
    Node* parent_node; //this is used to hold the parent node when checking to see if its a predecessor or not.
    Node* predecessor_node; //this holds the largest node on the tree. 

    if(current_node == nullptr){

        cout << "Its Predecessor does NOT exist" << endl;
        return nullptr;
    }

    if(current_node->leftChild != nullptr){ //this checks to see if the current node left child is not empty.
        
        predecessor_node = findMaximumNode(current_node->leftChild); //this will return the largest node on the tree by searching on the left side.
        
        cout << "Its Predecessor is: " << endl;
        print(predecessor_node);

        return predecessor_node; //this returns the pointer that is pointing at the predecessor. 
    }
    
    parent_node = current_node->parent; //this sets parent node as current node's parent.

    
    
    while(parent_node != nullptr && current_node == parent_node->leftChild){ //this check to see if the parent node is the predecesor or not and checks if node is parent's left child.
        
        current_node = parent_node; //this sets current node to its parent node.
        parent_node = parent_node->parent; //this sets parent node to its parent.
        
    }

    if(parent_node == nullptr){ //this checks to see if the parent node even exists or not.

        cout << "Its Predecessor does NOT exist" << endl;
        return nullptr;
    }
    
    
    cout << "Its Predecessor is: " << endl;
    print(parent_node);
    return parent_node; //this returns the predecesor if its the parent node.
    
}



Node* RedBlackTree::findSuccessorNode(Node *node){
    
    Node* current_node = node; //this stores node.
    Node* parent_node; //this is used to hold the parent node when checking to see if its a successor or not.
    Node* successor_node; //this holds the smallest node on the tree. 

    if(current_node == nullptr){

        cout << "Its Successor does NOT exist" << endl;
        return nullptr;
    }

    if(current_node->rightChild != nullptr){ //this checks to see if the current node right child is not empty.
        
        successor_node = findMinimumNode(current_node->rightChild); //this will return the smallest node on the tree by searching on the right side.
        
        cout << "Its Successor is: " << endl;
        print(successor_node);

        return successor_node; //this returns the pointer that is pointing at the successor. 
    }
    
    parent_node = current_node->parent; //this sets parent node as current node's parent.

    
    
    while(parent_node != nullptr && current_node == parent_node->rightChild){ //this check to see if the parent node is the successor or not also checks if node is parent's right child.
        
        current_node = parent_node; //this sets current node to its parent node.
        parent_node = parent_node->parent; //this sets parent node to its parent.
        
    }

    if(parent_node == nullptr){ //this checks to see if the parent node even exists or not.

        cout << "Its Successor does NOT exist" << endl;
        return nullptr;
    }
    
    cout << "Its Successor is: " << endl;
    print(parent_node);
    return parent_node; //this returns the successor if its the parent node.
    

}


void RedBlackTree::preOrderTraversal(Node *node){

    Node* pre_travel = node;

    if(pre_travel != nullptr){ //this first prints the node itself then it travels through the left child and the right child. 

        print(pre_travel);
        preOrderTraversal(pre_travel->leftChild);
        preOrderTraversal(pre_travel->rightChild);
    }
}


void RedBlackTree::inorderTraversal(Node *node){

    Node* inorder_travel = node;

    if(inorder_travel != nullptr){ //this first travels through the left child then, prints the node, then travels the right side.

        inorderTraversal(inorder_travel->leftChild);
        print(inorder_travel);
        inorderTraversal(inorder_travel->rightChild);
    }
}


void RedBlackTree::postOrderTraversal(Node *node){

    Node* post_travel = node;

    if(post_travel != nullptr){ //this first travels the left child, then the right child, then it prints the node.

        postOrderTraversal(post_travel->leftChild);
        postOrderTraversal(post_travel->rightChild);
        print(post_travel);
    }
}


void RedBlackTree::leftRotate(Node *node){

    Node* current_node = node->rightChild; //this will hold the right child of the node. y = x.right
    node->rightChild = current_node->leftChild; //this sets the current node left tree to node's right subtree.


    if(current_node->leftChild != nullptr){

        current_node->leftChild->parent = node; //this will set the parent pointer of the subtree that got moved.
    }

    current_node->parent = node->parent; //this connects current_node's parent to the new root of the subtree.

    if(node->parent == nullptr){ //this checks to see if the node that was passes was the root and if it was the current node becomes the root.

        root = current_node;
        
    }else if(node == node->parent->leftChild){ 

        node->parent->leftChild = current_node; //this will connect current node to the grandparent node on the left. 
    }else{ 

        node->parent->rightChild = current_node; //this will connect current node to the gradnparent node on the right.
    }

    current_node->leftChild = node; //this will set the node on to the left side of the current node.

    node->parent = current_node; //this sets the parent to current node. 


}



void RedBlackTree::rightRotate(Node *node){ //this is pretty much the same thing as left rotate but everything is just flipped.

    Node* current_node = node->leftChild; //this will hold the left child of the node. y = x.left
    node->leftChild = current_node->rightChild; //this sets the current node right tree to node's left subtree.


    if(current_node->rightChild != nullptr){

        current_node->rightChild->parent = node; //this will set the parent pointer of the subtree that got moved.
    }

    current_node->parent = node->parent; //this connects current_node's parent to the new root of the subtree.

    if(node->parent == nullptr){ //this checks to see if the node that was passes was the root and if it was the current node becomes the root.

        root = current_node;
        
    }else if(node == node->parent->rightChild){ 

        node->parent->rightChild = current_node; //this will connect current node to the grandparent node on the right. 
    }else{ 

        node->parent->leftChild = current_node; //this will connect current node to the gradnparent node on the left.
    }

    current_node->rightChild = node; //this will set the node on to the right side of the current node.

    node->parent = current_node; //this sets the parent to current node. 
    
}



void RedBlackTree::fixUp(Node *node){


    while(node != root && node->parent != nullptr && node->parent->color == "RED"){ //this checks to see if the parent is colored red and is not null and if node is not the root. 
        
        Node* parent_node = node->parent; //this is the node's parent and it also also kinda makes it easier to work with the pointers cause it got confusing. 
        Node* g_parent_node = parent_node->parent; //this is the node's grand parent.

        if(g_parent_node == nullptr){ //this checks to see if the parent is the root and if it is then the grand parent doesn't exist.

            break;
        }

        if(parent_node == g_parent_node->leftChild){

            Node* uncle_node = g_parent_node->rightChild; //this is the node's uncle.

            if(uncle_node != nullptr && uncle_node->color == "RED"){  //this checks to see if uncle is red and not a dummy node and this is also part of case 1.
                 
                parent_node->color = "BLACK"; //these are the color changes.
                uncle_node->color = "BLACK";
                g_parent_node->color = "RED";
                node = g_parent_node; //this moves node up the tree. 
            }else{

                if(node == parent_node->rightChild){ //this checks to see if the node is a right child and if it is it will rotate to the left its also case 2.
                    
                    node = parent_node;
                    leftRotate(node);
                    parent_node = node->parent; //this fixes up the parent node.
                }

                parent_node->color = "BLACK"; //this will rotate the grand parent node after it changes its color to red and after the parent node changes to black its also case 3.
                g_parent_node->color = "RED"; 
                rightRotate(g_parent_node);

                
            }


        }else{ //this will happen if the parent is a right child and essentially mirrors case 1, case 2 and case 3.

            Node* uncle_node_mirrored = g_parent_node->leftChild; //this is the node's uncle when the parent node is the right child.

            if(uncle_node_mirrored != nullptr && uncle_node_mirrored->color == "RED"){ //this checks to see if uncle is red and not a dummy node and this is case 1 mirrored.
                   
                parent_node->color = "BLACK"; //these are the color changes.
                uncle_node_mirrored->color = "BLACK";
                g_parent_node->color = "RED";
                node = g_parent_node; //this moves node up the tree. 
            }else{

                if(node == parent_node->leftChild){ //this checks to see if the node is a left child and if it is it will rotate to the right and this is case 2 mirrored.
                    
                    node = parent_node;
                    rightRotate(node);
                    parent_node = node->parent; //this wil fix the parent node after the rotation is finished.
                     
                }

                parent_node->color = "BLACK"; //this will rotate the grand parent node after it changes its color to red and after the parent node changes to black this is case 3 mirrored.
                g_parent_node->color = "RED"; 
                leftRotate(g_parent_node);
                

            }


        }


    } 

    root->color = "BLACK"; //this makes the root's color to black since its literally part of the rules for an RBT.
}


void RedBlackTree::treeInsert(string airLine, int flightNum, string deptDate){



    Node* node_insert = new Node();

    node_insert->color = "RED"; //this sets the node to red because every new node in the RBT has to be red.

    node_insert->airLine = airLine; //this just sets up all the parts of the node. 
    node_insert->flightNum = flightNum;
    node_insert->deptDate = deptDate;

    insertNode(node_insert); //this inserts the new node and it also brings along the airline, the flight number and the departure date.
    fixUp(node_insert); //this makes sure the RBT is not messed up when the new node is added.


}


Node* RedBlackTree::treeSearch(string airLine, int flightNum, string deptDate){

    Node* current_node = root; //this is where the search starts from which is the root.

    //string key_search = airLine + to_string(flightNum) + deptDate; //this is the key that contains airline, flight number and the departure date that is being searched for and also converted flightNum.
    //string current_node_key;

    while(current_node != nullptr){ //this checsk to see if the current node we are searching through is empty or not.
        
        //current_node_key = current_node->airLine + to_string(current_node->flightNum) + current_node->deptDate; //this sets up the key for the current node being searched. 
        bool current_node_equal = equalNodes(airLine, current_node->airLine, flightNum, current_node->flightNum, deptDate, current_node->deptDate); //this calls a helper function to see if equal.

        if(current_node_equal){ //this works if the current node is the same as what is being searched for.

            cout << left;
            cout << setw(5) << airLine
                 << setw(10) << flightNum << " on "
                 << setw(12) << deptDate << " is found" << endl;
            
            return current_node;
        }

        bool nodes_compared = nodeComparision(airLine, current_node->airLine, flightNum, current_node->flightNum, deptDate, current_node->deptDate); //this calls a helper function to compare.

        if(nodes_compared){ //this checks to see if the node that is being searched is smaller than the node that is being looked at currently.

            current_node = current_node->leftChild; //this goes to the left side if its smaller
        }else{
            
            current_node = current_node->rightChild; //this goes to the right side if its bigger.
        }


    } //this runs if the flight is not found in the tree.

    cout << left;
    cout << setw(5) << airLine
         << setw(10) << flightNum << " on "
         << setw(12) << deptDate << " is NOT found" << endl;
    
    return nullptr;
    
}

void RedBlackTree::treePreorder(){

    preOrderTraversal(root); //this return the pre order traversal returns.
}

void RedBlackTree::treePostorder(){

    postOrderTraversal(root); //this returns the post order traversal returns.
}

void RedBlackTree::treeInorder(){

    inorderTraversal(root); //this returns the in order traversal
}



void RedBlackTree::treeMinimum(){

    if(root == nullptr){ //this checks to see if the tree is empty or not.

        cout << "Tree is empty" << endl;
        return;
    }

    cout << "The MINIMUM is: " << endl;
    print(findMinimumNode(root)); //this prints out the min node info since findMinimumNode return a pointer and print method passes a pointer.


}

void RedBlackTree::treeMaximum(){

    if(root == nullptr){ //this checks to see if the tree is empty or not.

        cout << "Tree is empty" << endl;
        return;
    }

    cout << "The MAXIMUM is: " << endl;
    print(findMaximumNode(root)); //this prints out the max node info since findMaximumNode return a pointer and print method passes a pointer.


}


void RedBlackTree::treePredecessor(string airLine, int flightNum, string deptDate){

    Node* predecessor_flight = treeSearch(airLine,flightNum,deptDate); //this searches the tree and sees if it can find the flight that is needed and return it with printing as well.

    if(predecessor_flight == nullptr){ //this checks to see if flight is on the tree or not.

        cout << "Its Predecessor does NOT exist" << endl;
    }else{

        findPredecessorNode(predecessor_flight); //this prints out the info that comes from tree search. 
    }
}


void RedBlackTree::treeSucessor(string airLine, int flightNum, string deptDate){
    
    Node* sucessor_flight = treeSearch(airLine,flightNum,deptDate); //this searches the tree and sees if it can find the flight that is needed and return it with printing as well.

    if(sucessor_flight == nullptr){ //this checks to see if flight is on the tree or not.

        cout << "Its Successor does NOT exist" << endl;
    }else{

        findSuccessorNode(sucessor_flight); //this prints out the info that comes from tree search. 
    }

}



bool RedBlackTree::equalNodes(string first_airline, string second_airline, int first_flight_number, int second_flight_number, string first_departure, string second_departure){

    if(first_airline == second_airline){//this checks to see if the two flights that are being checked are equal to each each other.
        if(first_flight_number == second_flight_number){//this checks to see if the flight numbers are equal to each other.
            if(first_departure == second_departure){ //this then checks if the departure dates are equal or not. 

                return true; //this happens if they are all equal.
            }
        }
    }

    return false; //this hapens if they are not equal.
}

bool RedBlackTree::nodeComparision(string first_airline, string second_airline, int first_flight_number, int second_flight_number, string first_departure, string second_departure){

    if(first_airline != second_airline){ //this compares the airlines and which one comes first and if they are the same check the flight number.
        if(first_airline < second_airline){

            return true;
        }else{

            return false;
        }

    }

    string string_first_flight = to_string(first_flight_number); //this converts the first flight number into a string so it can be checked alphabetcily and was suggested by the TA.
    string string_second_flight = to_string(second_flight_number); //this converts the second flight number into a string so it can be checked alphabeticily and was suggested by the TA.

    if(string_first_flight != string_second_flight){ //this compares the flight numbers and which one comes first and if they are the same check the departure date.

        if(string_first_flight < string_second_flight){

            return true;
        }else{

            return false;
        }
    }

    if(first_departure < second_departure){ //this comapares which date come first.

        return true;
    }else{
        
        return false;
    }

    return false; //this runs if everthing else doesn't work.
}

//****************************************************************
//This is the general BST insertion operation.
//It does not care about the color of the newly added node. (Required by the professor)
void RedBlackTree::insertNode(Node *node)
{
    //----
    //----
    Node* current_node = root; //this is the current node that starts from the root and where the new node will start when being placed in to the tree.
    Node* parent_node = nullptr; //this is the parent node. 

    //string new_node_key = node->airLine + to_string(node->flightNum) + node->deptDate; //this basically put all the flight info into a singel string so that it can be used to compare.
    //string current_node_key;
    //string parent_node_key;
    
    while(current_node != nullptr){
        
        parent_node = current_node; //this sets the parent node to the current node and it starts off as the root in the beginning. 
        
        bool equal_nodes = equalNodes(node->airLine, current_node->airLine, node->flightNum, current_node->flightNum, node->deptDate, current_node->deptDate); //this calls a helper function for comparision
        
        if (equal_nodes) //this checks for duplicate nodes. 
        {
            cout << "Duplicated node. NOT added" << endl;
            delete node; //this frees up memory.
            return;

        }

        bool nodes_compared = nodeComparision(node->airLine, current_node->airLine, node->flightNum, current_node->flightNum, node->deptDate, current_node->deptDate); //this calls a helper function for comparision

        if(nodes_compared){ //this check the left subtree by seeing if the new node is smaller than the node that is being checked currently.

            current_node = current_node->leftChild;
        }else{ //this goes through the right subtree.

            current_node = current_node->rightChild;
        }

    }

    node->parent = parent_node; //this connects the new inserted node to its parent.
    node->rightChild = nullptr; //this resets the right child cause a node was inserted.
    node->leftChild = nullptr; //this resets the left child cause a node as inserted.

    //parent_node_key = parent_node->airLine + to_string(parent_node->flightNum) + parent_node->deptDate; //this creates a string for the parent node so that it can be compared to the new node.
    
    

    if(parent_node == nullptr){ //this checks to see if the tree was empty or not and if it was it sets the root as the new inserted node.

        root = node;
    }else{
        bool parent_compared = nodeComparision(node->airLine, parent_node->airLine, node->flightNum, parent_node->flightNum, node->deptDate, parent_node->deptDate); //this calls a helper function for comparision

        if(parent_compared){ //this connects the children to their parent by checkingto see if the node smaller than the parent node. 

            parent_node->leftChild = node;
        }else{

            parent_node->rightChild = node;
        }
    }
    
}

//******************************************************************
//Given a 'node', this function prints the node information on screen
void RedBlackTree::print(Node *node)
{
      cout << left;
      cout << setw(5)  << node->airLine
           << setw(10) << node->flightNum
           << setw(12) << node->deptDate;
      cout << right << setw(7) << node->color << endl;
}
