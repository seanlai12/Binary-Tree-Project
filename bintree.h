// Lab2
// file bintree.h
// Binary Tree class
// Author:  Sean Lai and Sai Badey
// Date:    April 18, 2014
// Class:   CSS343 - Dr. Carol Zander

#ifndef BINTREE_H
#define BINTREE_H

#include <iostream>
#include "nodedata.h"

using namespace std;

//---------------------------------------------------------------------------
// BinTree class: Contains Binary tree of nodes with a string data
//   Features:
//   -- allows output of the Tree in sideways or inorder
//   -- allows for comparison of two BinTrees
//   -- allows for assignment of BinTrees
//   -- contains a struct for a Node. which has point to data, left and right
//   -- allows insertion of nodes into the tree
//   -- able to retrive a node from the tree
//   -- able to find the depth of a node from the tree
//   -- able to conver the BinTree to Array and vice versa
//   -- able to check if the BinaryTree is an empty tree
//
// Implementation and assumptions:
//   -- data in the nodes must be strings
//   -- duplicates will be ignored when inserting
//   -- conversion of array to BinaryTree will assume the array is size of 100
//   -- array to BinTree will ignore the NULL elements in the array
//   -- depth of root in the tree is 1, and depth of unfound node is 0
//   -- operator<< will print the tree using inorder traversal
//---------------------------------------------------------------------------

class BinTree
{
    
    friend ostream& operator<<(ostream&, const BinTree&); // operator << output
    
public:
    BinTree();                   // the default constructor
    BinTree(const BinTree &);    // copy constructor
    ~BinTree();                  // destructor
    
    BinTree& operator=(const BinTree &); //assigns parameter tree to this tree
    bool operator==(const BinTree &) const; //checks equality of two trees
    bool operator!=(const BinTree &) const; //checks inequality of two trees
        
    bool isEmpty() const; // checks if the BinTree is empty
    void makeEmpty();     // deletes all contents of BinTree

    bool insert(NodeData*); //inserts a node data into Bintree

    //search function that sets pointer to nodedata of search
    bool retrieve(const NodeData&, NodeData*&) const; 
    int getDepth(const NodeData &) const; //returns depth of a nodedata
    
    void displaySideways() const; //displays the tree as if seen sideways
    
    void bstreeToArray(NodeData* []); //converts tree to handed array
    void arrayToBSTree(NodeData* []); //converts array to bintree
    
private:
   //node struct which makes up the tree
    struct Node {
        NodeData* data;
        Node* left;
        Node* right;
    };
    Node* root;
    
    void makeEmptyHelper(Node*& subTree); //helper function which does work
    
    //function which can be called to do inorder operations on whole tree
    void inorderHelper(Node* subTree, void (visit(Node*))) const;
    
    //worker function for equality operators, returns true if the same
    bool compareTrees(const Node* subTree, const Node* other) const;
    //worker function for the assignment operator & copy constructor
    void copyBinTree(Node* subTree, Node*& otherSubTree);
    //worker function for display sideways
    void sideways(Node*, int) const;
    //worker function for <<operator
    void displayHelper(Node* current) const;
    //worker function for bstreeToArray
    int bstreeToArrayHelper(Node* curPtr, NodeData *tempArray[]);
    //worker function for arrayToBSTree
    void arrayToBSTreeHelper(NodeData* tempArray[], Node*&, int low, int high);
};

#endif
