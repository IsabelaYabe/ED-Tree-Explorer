#pragma once

using namespace std;

struct Node
{
    int iData;
    struct Node* ptrLeft;
    struct Node* ptrRight;
};

// Useful variables
const string strSeparator = "======================================================================";
const string strOptions[16] = {
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
    "Display tests from driver_code.cpp"
};

// Base functions
struct Node* newNode(int);

void traversePreOrder(struct Node*);

void insertNode(struct Node**, int);

struct Node* getSmallestChild(struct Node*);

struct Node* deleteNode(struct Node*, int);

struct Node* searchNode(struct Node*, int);

int getHeight(struct Node*);

int getNumberOfNodes(struct Node*);

bool isPerfect(struct Node*, int, int);

bool isComplete(struct Node*, int, int);

// Loop
void loop();

// Menu functions
void printMenu();

// Case 2
string askFileName();

struct Node* buildFromFile(string);

// Case 3
bool isNumeric(const string&);

struct Node* buildFromUser();