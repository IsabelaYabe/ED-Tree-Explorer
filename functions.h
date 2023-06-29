#pragma once
using namespace std;

struct Node
{
    int iData;
    struct Node* ptrLeft;
    struct Node* ptrRight;
};

/***************************************************************************************************************************************/

// Useful variables

const string strSeparator = "================================================================================";
const string strOptions[16] = {
    "Quit the program.",
    "Build a binary tree from a text file.",
    "Build a binary tree from numbers inserted in the terminal.",
    "Get the height of the tree.",
    "Get the size of the tree.",
    "Insert an element into the tree.",
    "Remove an element off the tree.",
    "Search the memory address of an element.",
    "Ask if the tree is complete.",
    "Ask if the tree is perfect.",
    "Exhibit the tree using BFS.",
    "Convert the tree to list and sort via Bubble Sort.",
    "Convert the tree to list and sort via Selection Sort.",
    "Convert the tree to list and sort via Insertion Sort.",
    "Convert the tree to list and sort via Shell Sort.",
    "Display tests from driver_code.cpp",
};
const string strErrorMessage = "Invalid entry! Insert an integer between 1 and 16.";
const string strGreetingMessage = "Welcome to Tree Explorer!\nAn interactive ASCII menu to play with binary tree structures.";
const string strEndingMessage = "Thanks for playing Tree Explorer! :)";
const string strInstruction = "To choose an option, enter the corresponding number (without brackets).";

/***************************************************************************************************************************************/

// Basic functions

struct Node* newNode(int);
void traversePreOrder(struct Node*);
void insertNode(struct Node**, int);
void deleteTree(struct Node** ptrRoot);
struct Node* getSmallestChild(struct Node*);
struct Node* deleteNode(struct Node*, int);
struct Node* searchNode(struct Node*, int);
int getHeight(struct Node*);
int getNumberOfNodes(struct Node*);
bool isPerfect(struct Node*, int, int);
bool isComplete(struct Node*, int, int);

/***************************************************************************************************************************************/

// Loop function
void loop();

// Auxiliary functions
void printMenu();
bool isNumeric(const string&);
string askFileName();
int askElement();

// Functions to build the tree
struct Node* buildFromFile(struct Node*, string);
struct Node* buildFromUser(struct Node*);

/***************************************************************************************************************************************/
