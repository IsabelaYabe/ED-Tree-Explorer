#pragma once

struct NodeList
{
  int iPayload;
  struct NodeList *ptrPrev;
  struct NodeList *ptrNext;
};

struct Node
{
  int iPayload;
  struct Node *ptrLeft;
  struct Node *ptrRight;
};

struct NodeList* newNodeList(int);

struct NodeList* insertNodeList(struct NodeList*, int);

void printList(struct NodeList*);

struct NodeList* listCurrentLevel(struct NodeList*, struct Node*, int);

struct NodeList* traverseBFS(struct Node*);

int getLength(struct NodeList*);

struct NodeList* getNodeByIndex(struct NodeList*, int);

void swapNodes(struct Node**, struct Node*, struct Node*);

void selectionSort(struct NodeList**);

void insertionSort(struct NodeList**);

void shellSort(struct NodeList**);

void bubbleSort(struct NodeList**);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Node* newNode(int);

struct Node* insertNode(struct Node*, int);

int depth(struct Node*);

void printCurrentLevel(struct Node*, int);

void printBFS(struct Node*);