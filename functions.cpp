#include <iostream>
#include "functions.h"

using std::cout;
using std::endl;
using std::cin;

/**
 * Creates a new node with the given data and nullptr as left and right nodes.
 * 
 * @param iData The data to be stored in the new node.
 * 
 * @return A pointer to the new node.
*/
struct Node* newNode(int iData)
{

    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));

    newNode->iData = iData;
    newNode->ptrLeft = nullptr;
    newNode->ptrRight = nullptr;

    return newNode;
};

/**
 * Inserts a new node with the given data into the tree.
 * 
 * @param ptrRoot A pointer to the root node of the tree.
 * @param iData The data to be stored in the new node.
 * 
 * @return Void.
*/
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

/**
 * Traverses the tree in pre-order, printing it along the way.
 * 
 * @param ptrStartingNode A pointer to the starting node of the tree.
 * 
 * @return Void.
*/
void traversePreOrder(struct Node* ptrStartingNode)
{
    if (ptrStartingNode != nullptr)
    {
        cout << " " << ptrStartingNode->iData;
        traversePreOrder(ptrStartingNode->ptrLeft);
        traversePreOrder(ptrStartingNode->ptrRight);
    }
}

/**
 * Searches the tree for a node with the given data.
 * 
 * @param ptrStartingNode A pointer from which to start the search.
 * @param iData The data to be searched for.
 * 
 * @return A pointer to the first node with the given data, or nullptr if not found.
*/
struct Node* searchNode(struct Node* ptrStartingNode, int iData)
{
    if (ptrStartingNode == nullptr) return nullptr;
    else if (iData == ptrStartingNode->iData) return ptrStartingNode;
    else if (iData < ptrStartingNode->iData) return searchNode(ptrStartingNode->ptrLeft, iData);
    else return searchNode(ptrStartingNode->ptrRight, iData);
}

/**
 * Gets the height of the tree.
 * 
 * @param ptrRoot A pointer to the root node of the tree.
 * 
 * @return The height of the tree.
*/
int getHeight(struct Node* ptrRoot)
{
    if (ptrRoot == nullptr) return 0;
    else if (ptrRoot->ptrLeft == nullptr && ptrRoot->ptrRight == nullptr) return 1;
    else return (1 + std::max(getHeight(ptrRoot->ptrLeft), getHeight(ptrRoot->ptrRight)));
}

/**
 * Gets the number of nodes in the tree.
 * 
 * @param ptrRoot A pointer to the root node of the tree.
 * 
 * @return The number of nodes in the tree.
*/
int getNumberOfNodes(struct Node* ptrRoot)
{
    if (ptrRoot == nullptr) return 0;
    else return (1 + getNumberOfNodes(ptrRoot->ptrLeft) + getNumberOfNodes(ptrRoot->ptrRight));
}

/**
 * Checks if the tree is perfect.
 * 
 * @param ptrRoot A pointer to the root node of the tree.
 * @param iTreeHeight The height of the tree.
 * @param iBranchHeight The height of the current branch.
 * 
 * @return True if the tree is perfect, false otherwise.
*/
bool isPerfect(struct Node* ptrRoot, int iTreeHeight, int iBranchHeight)
{
    if (ptrRoot == nullptr) return true;
    else if (ptrRoot->ptrLeft == nullptr && ptrRoot->ptrRight == nullptr) return (iTreeHeight == iBranchHeight);
    else if (ptrRoot->ptrLeft == nullptr || ptrRoot->ptrRight == nullptr) return false;
    else return (isPerfect(ptrRoot->ptrLeft, iTreeHeight, iBranchHeight + 1) && isPerfect(ptrRoot->ptrRight, iTreeHeight, iBranchHeight + 1));
}

/**
 * Checks if the tree is complete.
 * 
 * @param ptrRoot A pointer to the root node of the tree.
 * @param iTreeHeight The height of the tree.
 * @param iBranchHeight The height of the current branch.
 * 
 * @return True if the tree is complete, false otherwise.
*/
bool isComplete(struct Node* ptrRoot, int iTreeHeight, int iBranchHeight)
{
    if (ptrRoot == nullptr) return true;
    else if (ptrRoot->ptrLeft == nullptr && ptrRoot->ptrRight == nullptr) return (iTreeHeight == iBranchHeight);
    else if (ptrRoot->ptrLeft == nullptr && ptrRoot->ptrRight != nullptr) return false;
    else if (ptrRoot->ptrLeft != nullptr && ptrRoot->ptrRight == nullptr) return isComplete(ptrRoot->ptrLeft, iTreeHeight, iBranchHeight + 1);
    else return (isComplete(ptrRoot->ptrLeft, iTreeHeight, iBranchHeight + 1) && isComplete(ptrRoot->ptrRight, iTreeHeight, iBranchHeight + 1));
}