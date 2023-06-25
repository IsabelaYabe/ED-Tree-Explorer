#include <iostream>
using namespace std;

struct Node
{
    int iData;
    struct Node* ptrLeft;
    struct Node* ptrRight;
};

struct Node* newNode(int);
void insertNode(struct Node**, int);


// Useful variables

const string strSeparator = "======================================================================";
const string strOptions[15] = {
    "Quit the program.",
    "Build a binary tree from a text file.",
    "Build a binary tree from data inserted by the user.",
    "Get the height of the tree.",
    "Get the size of the tree.",
    "Insert an element into the tree.",
    "Remove an element off the tree.",
    "Search the memory address of an element.",
    "Ask if whether the tree is complete.",
    "Ask if whether the tree is perfect.",
    "Exhibit the tree using BFS.",
    "Convert the tree to list and sort via Bubble Sort.",
    "Convert the tree to list and sort via Selection Sort.",
    "Convert the tree to list and sort via Insertion Sort.",
    "Convert the tree to list and sort via Shell Sort.",
};

// Menu functions
void printMenu();

// Case 2
string askFileName();
struct Node* buildFromFile(string);

// Case 3
bool isNumeric(const string&);
struct Node* buildFromUser();