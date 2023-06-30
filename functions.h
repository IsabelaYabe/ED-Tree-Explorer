#pragma once

using namespace std;

// This is a tree's Node
struct TreeNode
{
  int iData;
  struct TreeNode *ptrLeft;
  struct TreeNode *ptrRight;
};

// This is a list's Node
struct ListNode
{
  int iData;
  struct ListNode *ptrPrev;
  struct ListNode *ptrNext;
};

// This is a queue's Node
struct QueueNode
{
  struct TreeNode* ptrTreeNode;
  struct QueueNode* ptrNext;
};

// This is a queue
struct Queue
{
  struct QueueNode* ptrFront;
  struct QueueNode* ptrRear;
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

struct TreeNode* newTreeNode(int);
struct ListNode* newListNode(int);
struct QueueNode* newQueueNode(struct TreeNode*);

struct Queue* newQueue();
void enQueue(struct Queue*, struct TreeNode*);
struct TreeNode* deQueue(struct Queue*);

void traversePreOrder(struct TreeNode*);
void traverseBFS(struct TreeNode*);
void efficientBFS(struct TreeNode*);

void printList(struct ListNode*);
void printCurrentLevel(struct TreeNode*, int);
struct ListNode* insertCurrentLevel(struct ListNode*, struct TreeNode*, int);
struct ListNode* insertBFS(struct TreeNode*);

void swapNodes(struct ListNode**, struct ListNode*, struct ListNode*);
struct ListNode* getNodeByIndex(struct ListNode*, int);

void insertNode(struct TreeNode**, int);
struct ListNode* insertNode(struct ListNode*, int);

void deleteTree(struct TreeNode** ptrRoot);
struct TreeNode* getSmallestChild(struct TreeNode*);
struct TreeNode* deleteNode(struct TreeNode*, int);
struct TreeNode* searchNode(struct TreeNode*, int);

int getHeight(struct TreeNode*);
int getNodeHeight(struct TreeNode*, struct TreeNode*);
int getNumberOfNodes(struct TreeNode*);
int getLength(struct ListNode*);

bool isPerfect(struct TreeNode*, int, int);
bool isComplete(struct TreeNode*, int, int);

void selectionSort(struct ListNode**);
void insertionSort(struct ListNode**);
void shellSort(struct ListNode**);
void bubbleSort(struct ListNode**);

/***************************************************************************************************************************************/

// Loop function
void loop();

// Auxiliary functions
void printMenu();
bool isNumeric(const string&);
string askFileName();
int askElement();

// Functions to build the tree
struct TreeNode* buildFromFile(struct TreeNode*, string);
struct TreeNode* buildFromUser(struct TreeNode*);

/***************************************************************************************************************************************/