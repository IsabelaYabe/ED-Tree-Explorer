#include <iostream>
#include "functions.h"

using std::cout;
using std::endl;
using std::cin;

struct Node* newNode(int iData)
{
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));

    newNode->iData = iData;
    newNode->ptrLeft = nullptr;
    newNode->ptrRight = nullptr;

    return newNode;
};

void insertNode(struct Node** ptrRoot, int iData)
{
    if (*ptrRoot == nullptr)
    {
        (*ptrRoot) = newNode(iData);
    }
    else if (iData <= (*ptrRoot)->iData)
    {
        insertNode(&((*ptrRoot)->ptrLeft), iData);
    }
    else
    {
        insertNode(&((*ptrRoot)->ptrRight), iData);
    }
}

void traversePreOrder(struct Node* ptrStartingNode)
{
    if (ptrStartingNode != nullptr)
    {
        cout << " " << ptrStartingNode->iData;
        traversePreOrder(ptrStartingNode->ptrLeft);
        traversePreOrder(ptrStartingNode->ptrRight);
    }
}