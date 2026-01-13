// Description: Red black tree header file. It defines the Node and the
//              red black tree functionalities.

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <string>

using namespace std;

#ifndef REDBLACKTREE_H_
#define REDBLACKTREE_H_

//Node represents one node of the RBT which is a Flight
struct Node
{
   string airLine;
   int flightNum;
   string deptDate;
   Node *parent;
   Node *leftChild;
   Node *rightChild;
   string color;
};

class RedBlackTree
{
    private:
        Node *root;
    public:
        RedBlackTree();
        ~RedBlackTree();
        Node* getRoot();
        int deleteNode(Node *node);
        void insertNode(Node *node);
        void fixUp(Node *node);

        void preOrderTraversal(Node *node);
        void inorderTraversal(Node *node);
        void postOrderTraversal(Node *node);

        Node* findMinimumNode(Node *node);
        Node* findMaximumNode(Node *node);
        Node* treeSearch(string airLine, int flightNum, string deptDate);
        void leftRotate(Node *node);
        void rightRotate(Node *node);
        Node* findPredecessorNode(Node *node);
        Node* findSuccessorNode(Node *node);

        void treeMinimum();
        void treeMaximum();
        void treePreorder();
        void treeInorder();
        void treePostorder();
        void treePredecessor(string airLine, int flightNum, string deptDate);
        void treeSucessor(string airLine, int flightNum, string deptDate);
        void treeInsert(string airLine, int flightNum, string deptDate);

        void print(Node *node);

        bool equalNodes(string first_airline, string second_airline, int first_flight_number, int second_flight_number, string first_departure, string second_departure); //this is a helper function to see if nodes are equal.
        bool nodeComparision(string first_airline, string second_airline, int first_flight_number, int second_flight_number, string first_departure, string second_departure); //this is a helper function to compare nodes.
};  
#endif
