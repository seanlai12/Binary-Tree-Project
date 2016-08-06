// Lab2
// file bintree.cpp
// Binary Tree class
// Author:  Sean Lai and Sai Badey
// Date:    April 18, 2014
// Class:   CSS343 - Dr. Carol Zander

#include "bintree.h"

using namespace std;

const int maxElements = 100;

//---------------------------------------------------------------------------
// Bintree
// default constructor
// creates an empty BinTree with NULL root
BinTree::BinTree()
{
    root = NULL;
}

//---------------------------------------------------------------------------
// BinTree
// copy constructor
// Set a BinTree that is equal to target BinTree
BinTree::BinTree(const BinTree &other)
{
    copyBinTree(other.root, this->root);
}

//----------------------------------------------------------------------------
// operator=
// overloaded =: current BinTree = parameter BinTree
BinTree& BinTree::operator=(const BinTree& other)
{
    if (this != &other)
    {
        makeEmpty(); // Clears the current tree
        copyBinTree(other.root, this->root);
    }
    return *this;
}

// ---------------------------------------------------------------------------
// copyBinTree
// Parameter is the subTree to be copied to and target otherSubTree
// Uses a preorder traversal and copies all the nodes in the other tree
// to the tree in the first parameter recursively
void BinTree::copyBinTree(Node* subTree, Node*& otherSubTree)
{
    if (subTree != NULL)
    {
        otherSubTree = new Node;
        NodeData* temp = new NodeData(*subTree->data);
        otherSubTree->data = temp;
        copyBinTree(subTree->left, otherSubTree->left);
        copyBinTree(subTree->right, otherSubTree->right);
    }
    else
    {
        otherSubTree = NULL;
    }
}


//---------------------------------------------------------------------------
// BinTree
// Destructor
// Frees allocated memory
BinTree::~BinTree()
{
    makeEmpty();
}

// ---------------------------------------------------------------------------
// makeEmpty
// Deletes all the nodes in the BinTree and sets root to NULL
void BinTree::makeEmpty()
{
    if(!isEmpty())
    {
        makeEmptyHelper(root);
        root = NULL;
    }
}

// ---------------------------------------------------------------------------
// makeEmptyHelper
// Parameter is the subtree to be made empty
// Helper method that uses recursive postorder traveral to delete all the
// nodes in the tree recursively.
void BinTree::makeEmptyHelper(Node*& subTree)
{
    if(subTree != NULL)
    {
        makeEmptyHelper(subTree->left);
        makeEmptyHelper(subTree->right);
        
        delete subTree->data;
        subTree->data = NULL;
        delete subTree;
        subTree = NULL;
    }
}

//---------------------------------------------------------------------------
// insert
// Parameter is a the data to be inserted to the BinTree
// It will insert a node to the BinTree to the correct position
// returns true if inserted correctly, 
// false if not inserted or out of memory
// also will not insert duplicates.
bool BinTree::insert(NodeData* dataptr)
{
    //insert alphabetical order

    Node* ptr = new Node;
    if (ptr == NULL)
    {
        return false;
    }            // out of memory
    ptr->data = dataptr;
    ptr->left = ptr->right = NULL;
    if (isEmpty())
    {
        root = ptr;
    }
    else
    {
        Node* current = root;
        bool inserted = false;
        
        // if item is less than current item, insert in left subtree,
        // otherwise insert in right subtree
        while (!inserted)
        {
            if (*ptr->data < *current->data)
            {
                if (current->left == NULL)
                {              // insert left
                    current->left = ptr;
                    inserted = true;
                }
                else
                {
                    current = current->left;               // one step left
                }
            }
            else if (*ptr->data > *current->data)
            {
                if (current->right == NULL)
                {             // insert right
                    current->right = ptr;
                    inserted = true;
                }
                else
                    current = current->right;              // one step right
            }
            else
            {
                delete ptr;
                ptr = NULL;
                return false;
            }
        }
    }
    return true;
}

//---------------------------------------------------------------------------
// retrieve
// The function determines whether a nodedata exists in the tree
// Parameter is nodedata to search for and a pointer to a nodedata
// if found, returns true and assigns the leash to the nodedata found
// else, returns false
bool BinTree::retrieve(const NodeData& target, NodeData*& leash) const
{
    if (isEmpty()) //if tree is empty, nodedata will not exist there
    {
        return false;
    }
    else
    {
        Node* current = root;
        bool found = false;
        
        while (!found) //loops until found or doesn't exist in tree
        {
            if (target < *current->data)
            {
                if (current->left == NULL) //nothing to left
                {
                    return false;
                }
                else
                    current = current->left; //step left
            }
            else if (target > *current->data)
            {
                if (current->right == NULL) //nothing to right
                {         
                    return false;
                }
                else
                    current = current->right; //step right
            }
            else
            {
                found = true;
                leash = current->data; //setting leash for later access
            }
        }
        return true;
    }
}

//---------------------------------------------------------------------------
// getDepth
// Parameter is a the data to be checked for depth
// Will return the depth of the node in the tree
// Root of the node is 1, and if not found, returns 0.
int BinTree::getDepth(const NodeData& data) const
{
    int depth = 1; //start at 1
    bool found = false;
    Node *current = root;
    
    if (isEmpty()) // Empty tree will return 0
    {
        return 0;
    }
    
    //steps left or right (while incrementing depth) until found
    while (current != NULL && !found)
    {
        
        if (data < *current->data)
        {
            current = current->left;
            depth++;
        }
        else if (data > *current->data)
        {
            current = current->right;
            depth++;
        }
        else
        {
            found = true;
        }
    }

    if (!found) // If not found, returns 0
    {
        depth = 0;
    }

    
    return depth;
}

//---------------------------------------------------------------------------
// isEmpty
// Returns true if the tree has no nodes, otherwise false
bool BinTree::isEmpty() const
{
    return root == NULL;
}

//---------------------------------------------------------------------------
// inorderHelper
// Parameter is the subtree and the function to be called
// Will recursively use inorder traversal and runs the function at visit.
void BinTree::inorderHelper(Node* subTree, void (visit(Node*))) const
{
    if(subTree != NULL)
    {
        if(subTree->left != NULL) //left recursive call
        {
            inorderHelper(subTree->left, visit);
        }
        
        (*visit)(subTree); //inorder method call
        
        if(subTree->right != NULL) //right recursive call
        {
            inorderHelper(subTree->right, visit);
        }
    }
}

//----------------------------------------------------------------------------
// operator==
// overloaded ==: True if current == other. False if not.
bool BinTree::operator==(const BinTree& other) const
{
    return compareTrees(this->root, other.root);
}

//----------------------------------------------------------------------------
// operator!=
// overloaded !=: True if current != other. False if not.
bool BinTree::operator!=(const BinTree& other) const
{
    return !(*this == other);
}

//---------------------------------------------------------------------------
// compareTrees
// Parameter is the subtree to be checked with the second subtree
// It will check if the two subtrees are equal.
// returns false if any tree reaches the end and not equal.
bool BinTree::compareTrees( const Node* subTree, const Node* other) const
{
   //ensures both subtrees are not null & the data is the same
    if ((subTree != NULL && other!= NULL) && (*subTree->data == *other->data))
    {
        return true;
    }
   //recursively runs function on left subtrees and right subtrees
    return ((subTree->data == other->data) &&
            compareTrees((subTree->left),other->left) &&
            compareTrees((subTree->right), other->right));
}

//---------------------------------------------------------------------------
// displaySideways
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
void BinTree::displaySideways() const {
    sideways(root, 0);
}

//---------------------------------------------------------------------------
// sideways
// Helper method to displaySideways.
// Uses a inorder traversal to print the node data recursively.
void BinTree::sideways(Node* current, int level) const {
    if (current != NULL)
    {
        level++;
        sideways(current->right, level);
        
        // indent for readability, 4 spaces per depth level
        for(int i = level; i >= 0; i--) {
            cout << "    ";
        }
        
        cout << *current->data << endl;        // display information of object
        sideways(current->left, level);
    }
}

//----------------------------------------------------------------------------
// operator<<
// Parameter is the ostream output and the subtree to be printed
// Prints the subtree in inorder on one line.
ostream& operator<<(ostream& output, const BinTree& tree)
{
    tree.displayHelper(tree.root);
    output << endl;
    return output;
}

//----------------------------------------------------------------------------
// displayHelper
// Helper method for operator<<.
// It will use inorder traversal to display the content of the tree
// recursively.
void BinTree::displayHelper(Node *current) const
{
    if (current != NULL)
    {
        displayHelper(current->left);
        cout << *current->data << " ";
        displayHelper(current->right);
    }
}

//----------------------------------------------------------------------------
// bstreeToArray
// This method is called to turn this binary tree into an array
// Parameter is the array into which the tree's data will go
// calls the helper function and empties out this tree afterwards
void BinTree::bstreeToArray(NodeData* tempArray[])
{
    bstreeToArrayHelper(root, tempArray);
    makeEmpty();
}

//----------------------------------------------------------------------------
// bstreeToArrayHelper
// This method is called to turn this binary tree into an array
// Parameters are the array into which the tree's data will go
// and node pointer to current node
// This function calls itself recursively and assigns node data to positions
// in the array. The positions are calculated and returned to itself.
int BinTree::bstreeToArrayHelper(Node* current, NodeData *tempArray[])
{
	if (current == NULL)
    {
		return 0; //base case
    }
   
   //recursively calls function to travel to left most of tree
   //assigns open array position to int
	int leftPosition = bstreeToArrayHelper(current->left, tempArray);

   //assigns data to array position
    *(tempArray + leftPosition) = current->data;
    current->data = NULL;
   
 //recursively calls function on right pointers so whole tree is traversed
	int rightPosition = bstreeToArrayHelper(current->right,
                                            tempArray + leftPosition + 1);
                                            
   //updates position for left and right ints
	return (leftPosition + rightPosition + 1);
}

//----------------------------------------------------------------------------
// arrayToBSTree
// This method is called to turn an array into a binary tree
// Parameter is the array from which data is pulled
// calculates the length of the array (max size 100) and calls helper function
void BinTree::arrayToBSTree(NodeData* tempArray[])
{
    makeEmpty();
    int maxIndex = 0;
    
    for(int i = 0; i < maxElements; i++) //Counts # of array indexes being used
    {
        if (tempArray[i] != NULL)
        {
            maxIndex++;
        }
    }
    arrayToBSTreeHelper(tempArray, root, 0, maxIndex-1);
}

//----------------------------------------------------------------------------
// arrayToBSTreeHelper
// This method is called to turn an array into a bsTree
// Parameters are the array from which the tree's data comes from,
// node pointer to current node, and the indices of the array
// This function calls itself recursively and assigns node data to tree
// First new mid index is calculated, then data is assigned from this index
// Then, the function recursively calls left and right
void BinTree::arrayToBSTreeHelper(NodeData* tempArray[],
                                  Node*& current,
                                  int lowIndex, int highIndex)
{
   //base case
    if (lowIndex > highIndex)
    {
        current = NULL;
    }
    else
    {
    //mid index is always updated
        int midIndex = (lowIndex + highIndex) / 2;
        
        current = new Node;
        current->data = tempArray[midIndex];
        
        //recursive calls to left & right
        arrayToBSTreeHelper(tempArray, current->left, lowIndex, midIndex-1);
        arrayToBSTreeHelper(tempArray, current->right, midIndex+1, highIndex);
    }
}
