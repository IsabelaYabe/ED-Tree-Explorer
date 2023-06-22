#pragma once

struct Node
{
    int iData;
    struct Node* ptrLeft;
    struct Node* ptrRight;
};

struct Node* newNode(int);

void insertNode(struct Node**, int);

void traversePreOrder(struct Node*);