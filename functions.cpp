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
    // memory allocation
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));

    // initialization
    newNode->iData = iData;
    newNode->ptrLeft = nullptr;
    newNode->ptrRight = nullptr;

    return newNode;
};

/**
 * Traverses the tree in pre-order, printing it along the way.
 * 
 * @param ptrStartingNode A pointer to the starting node of the tree.
 * 
 * @return Void.
*/
void traversePreOrder(struct Node* ptrStartingNode)
{
    // if the tree is empty, return
    if (ptrStartingNode == nullptr) return;

    // if the tree is not empty, print current node and traverse its subtrees
    else
    {
        cout << ptrStartingNode->iData << "\t";
        traversePreOrder(ptrStartingNode->ptrLeft);
        traversePreOrder(ptrStartingNode->ptrRight);
    }
}

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
        // if the tree is empty, the inserted node becomes the root
        (*ptrRoot) = newNode(iData);
    }
    else if (iData <= (*ptrRoot)->iData)
    {
        // if the inserted value is less than the root, insert it in the left subtree
        insertNode(&((*ptrRoot)->ptrLeft), iData);
    }
    else
    {
        // if the inserted value is greater than the root, insert it in the right subtree
        insertNode(&((*ptrRoot)->ptrRight), iData);
    }
}

/**
 * Finds the smallest leaf of a tree.
 * 
 * @param ptrRoot A pointer to the root node of the tree.
 * 
 * @return A pointer to the smallest leaf of the tree.
*/
struct Node* getSmallestChild(struct Node* ptrRoot)
{
    // if the tree is empty, return nullptr
    if (ptrRoot == nullptr) return ptrRoot;
    else
    {
        // traverse the left subtree until the smallest leaf is found
        while (ptrRoot->ptrLeft != nullptr) ptrRoot = ptrRoot->ptrLeft;

        return ptrRoot;
    }
}

/**
 * Deletes a node with the given data from the tree.
 * 
 * @param ptrRoot A pointer to the root node of the tree.
 * @param iData The data to be deleted from the tree.
 * 
 * @return A pointer to the root node of the modified tree.
*/
struct Node* deleteNode(struct Node* ptrRoot, int iData)
{
    // if the tree is empty, return nullptr
    if (ptrRoot == nullptr) return nullptr;

    // if the tree is not empty, traverse it
    else if (iData < ptrRoot->iData) ptrRoot->ptrLeft = deleteNode(ptrRoot->ptrLeft, iData);
    else if (iData > ptrRoot->iData) ptrRoot->ptrRight = deleteNode(ptrRoot->ptrRight, iData);

    // if the node to be deleted is found
    else if (iData == ptrRoot->iData)
    {  
        struct Node* ptrNewRoot = nullptr;

        // if the node has no left child, replace it with its right child
        if (ptrRoot->ptrLeft == nullptr)
        {
            ptrNewRoot = ptrRoot->ptrRight;

            free(ptrRoot);
            
            return ptrNewRoot;
        }

        // if the node has no right child, replace it with its left child
        else if (ptrRoot->ptrRight == nullptr)
        {
            ptrNewRoot = ptrRoot->ptrLeft;

            free(ptrRoot);
            
            return ptrNewRoot;
        }

        // if the node has two children, replace it with the smallest child of its right subtree
        else
        {
            // get the smallest child of the right subtree
            struct Node* ptrSuccessor = getSmallestChild(ptrRoot->ptrRight);
            struct Node* ptrNewRoot = newNode(ptrSuccessor->iData);

            // copy the left subtree of the node to be deleted
            ptrNewRoot->ptrLeft = ptrRoot->ptrLeft;

            // copy the right subtree, deleting the child from its original position
            ptrNewRoot->ptrRight = deleteNode(ptrRoot->ptrRight, ptrNewRoot->iData);

            free(ptrRoot);

            return ptrNewRoot;
        }
    }

    return ptrRoot;
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
    // if the tree is empty, return nullptr
    if (ptrStartingNode == nullptr) return nullptr;

    // if the tree is not empty, traverse it, searching along the way
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
    // if the tree is empty, return 0
    if (ptrRoot == nullptr) return 0;

    // if the tree has no children, return 1
    else if (ptrRoot->ptrLeft == nullptr && ptrRoot->ptrRight == nullptr) return 1;

    // if the tree has children, return 1 + the height of the tallest subtree
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
    // if the tree is empty, return 0
    if (ptrRoot == nullptr) return 0;

    // if the tree is not empty, return 1 + the number of nodes in its subtrees
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
    // if the tree is empty, return true
    if (ptrRoot == nullptr) return true;

    // if the tree has no children, return true if the branch height is equal to the tree height
    else if (ptrRoot->ptrLeft == nullptr && ptrRoot->ptrRight == nullptr) return (iTreeHeight == iBranchHeight);

    // if the tree has only one child, return false
    else if (ptrRoot->ptrLeft == nullptr || ptrRoot->ptrRight == nullptr) return false;

    // if the tree has two children, return true if both subtrees are perfect
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
    // if the tree is empty, return true
    if (ptrRoot == nullptr) return true;

    // if the tree has no children, return true if we are on the max depth or one level above it
    else if (ptrRoot->ptrLeft == nullptr && ptrRoot->ptrRight == nullptr) return (iTreeHeight == iBranchHeight || iTreeHeight == iBranchHeight + 1);

    // if the tree has a right child but no left child, return false
    else if (ptrRoot->ptrLeft == nullptr && ptrRoot->ptrRight != nullptr) return false;

    // if the tree has a left child but no right child, check if the left subtree is complete and if we are just above the max depth
    else if (ptrRoot->ptrLeft != nullptr && ptrRoot->ptrRight == nullptr) return (isComplete(ptrRoot->ptrLeft, iTreeHeight, iBranchHeight + 1) && (iTreeHeight == iBranchHeight + 1));

    // if the tree has two children, there are two possibilities:
    // 1. the left subtree is perfect and the right subtree is complete
    // 2. the left subtree is complete and the right subtree is perfect, but is one level shallower than the left subtree
    else return ((isPerfect(ptrRoot->ptrLeft, iTreeHeight, iBranchHeight + 1) && isComplete(ptrRoot->ptrRight, iTreeHeight, iBranchHeight + 1)) ||
                 (isComplete(ptrRoot->ptrLeft, iTreeHeight, iBranchHeight + 1) && isPerfect(ptrRoot->ptrRight, iTreeHeight, iBranchHeight + 2)));
}