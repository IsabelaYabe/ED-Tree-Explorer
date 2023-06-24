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

struct NodeList* listTree(struct Node*);

struct Node* newNode(int iData);

struct Node* insertNode(struct Node*, int);

int depth(struct Node*);

void printCurrentLevel(struct Node*, int);

void printBFS(struct Node*);