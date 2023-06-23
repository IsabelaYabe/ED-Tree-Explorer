#pragma once

struct Node
{
    int iData;
    struct Node* ptrLeft;
    struct Node* ptrRight;
};

struct Node* newNode(int);

void insertNode(struct Node**, int);

struct Node* getSmallestChild(struct Node*);

struct Node* deleteNode(struct Node*, int);

void traversePreOrder(struct Node*);

struct Node* searchNode(struct Node*, int);

int getHeight(struct Node*);

int getNumberOfNodes(struct Node*);

bool isPerfect(struct Node*, int, int);

bool isComplete(struct Node*, int, int);