#include <iostream>
#include <limits>
#include <chrono>
#include <thread>
#include <fstream>
#include "functions.h"
#include "driver_code.h"

using std::cout;
using std::endl;
using std::cin;
using std::string;
using namespace std::chrono;
using namespace std::this_thread;

/***************************************************************************************************************************************/

// Base functions

/**
 * Creates a new node with the given data and nullptr as left and right nodes.
 * 
 * @param iData The data to be stored in the new node.
 * 
 * @return A pointer to the new node.
*/
struct TreeNode* newTreeNode(int iData)
{
    // memory allocation
    struct TreeNode* newNode = (struct TreeNode*) malloc(sizeof(struct TreeNode));

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
void traversePreOrder(struct TreeNode* ptrStartingNode)
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
void insertNode(struct TreeNode** ptrRoot, int iData)
{
    if (*ptrRoot == nullptr)
    {
        // if the tree is empty, the inserted node becomes the root
        (*ptrRoot) = newTreeNode(iData);
    }
    else if (iData < (*ptrRoot)->iData)
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
 * Deletes the entire tree from bottom up to avoid memory leakage.
 * 
 * @param ptrRoot A pointer to the root node of the tree to be deleted.
 * 
 * @return Void.
 */
void deleteTree(struct TreeNode** ptrRoot)
{
    // Base case: If the tree is empty (root is nullptr), return
    if (*ptrRoot == nullptr) return;

    // Delete left and right subtrees
    deleteTree(&(*ptrRoot)->ptrLeft);
    deleteTree(&(*ptrRoot)->ptrRight);

    // Delete the current node
    free(*ptrRoot);

    // Set the pointer to `nullptr`
    *ptrRoot = nullptr;
}

/**
 * Finds the smallest leaf of a tree.
 * 
 * @param ptrRoot A pointer to the root node of the tree.
 * 
 * @return A pointer to the smallest leaf of the tree.
*/
struct TreeNode* getSmallestChild(struct TreeNode* ptrRoot)
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
struct TreeNode* deleteNode(struct TreeNode* ptrRoot, int iData)
{
    // if the tree is empty, return nullptr
    if (ptrRoot == nullptr) return nullptr;

    // if the tree is not empty, traverse it
    else if (iData < ptrRoot->iData) ptrRoot->ptrLeft = deleteNode(ptrRoot->ptrLeft, iData);
    else if (iData > ptrRoot->iData) ptrRoot->ptrRight = deleteNode(ptrRoot->ptrRight, iData);

    // if the node to be deleted is found
    else if (iData == ptrRoot->iData)
    {  
        struct TreeNode* ptrNewRoot = nullptr;

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
            struct TreeNode* ptrSuccessor = getSmallestChild(ptrRoot->ptrRight);
            struct TreeNode* ptrNewRoot = newTreeNode(ptrSuccessor->iData);

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
struct TreeNode* searchNode(struct TreeNode* ptrStartingNode, int iData)
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
int getHeight(struct TreeNode* ptrRoot)
{
    // if the tree is empty, return 0
    if (ptrRoot == nullptr) return 0;

    // if the tree has no children, return 1
    else if (ptrRoot->ptrLeft == nullptr && ptrRoot->ptrRight == nullptr) return 1;

    // if the tree has children, return 1 + the height of the tallest subtree
    else return (1 + std::max(getHeight(ptrRoot->ptrLeft), getHeight(ptrRoot->ptrRight)));
}

/**
 * Gets the height of a node in the tree.
 * 
 * @param ptrRoot A pointer to the root node of the tree.
 * 
 * @return The height of the node.
*/
int getNodeHeight(struct TreeNode* ptrRoot, struct TreeNode* ptrNode)
{
    // if the tree is empty, return 0
    if (ptrRoot == nullptr) return 0;

    // if the node is the root, return 1
    else if (ptrRoot == ptrNode) return 1;

    // if the node is in the left subtree, return 1 + the height of the node in the left subtree
    else if (ptrNode->iData < ptrRoot->iData) return (1 + getNodeHeight(ptrRoot->ptrLeft, ptrNode));

    // if the node is in the right subtree, return 1 + the height of the node in the right subtree
    else return (1 + getNodeHeight(ptrRoot->ptrRight, ptrNode));
}

/**
 * Gets the number of nodes in the tree.
 * 
 * @param ptrRoot A pointer to the root node of the tree.
 * 
 * @return The number of nodes in the tree.
*/
int getNumberOfNodes(struct TreeNode* ptrRoot)
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
bool isPerfect(struct TreeNode* ptrRoot, int iTreeHeight, int iBranchHeight)
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
bool isComplete(struct TreeNode* ptrRoot, int iTreeHeight, int iBranchHeight)
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

/***************************************************************************************************************************************/

// BFS functions

/**
 * Creates a new node for the doubly linked list with the given data and nullptr as prev and next pointers.
 * 
 * @param iData The data to be stored in the new node.
 * 
 * @return A pointer to the new node.
 */
struct ListNode* newListNode(int iData)
{
    // memory allocation
    struct ListNode* newNode = (struct ListNode*) malloc(sizeof(struct ListNode));

    // initialization
    newNode->iData = iData;
    newNode->ptrPrev = nullptr;
    newNode->ptrNext = nullptr;
    
    return newNode;
}

/**
 * Inserts a new node with the given data into the doubly linked list.
 * 
 * @param ptrHead A pointer to the head of the list.
 * @param iData The data to be stored in the new node.
 * 
 * @return A pointer to the head of the updated list.
 */
struct ListNode* insertNode(struct ListNode* ptrHead, int iData)
{
    struct ListNode* newNode = newListNode(iData);

    // if the list is empty, return the ListNode.
    if (ptrHead == nullptr)
    {   
        return newNode;
    }

    // if the node has no Next, add the newNode.
    if (ptrHead->ptrNext == nullptr)
    {   
        newNode->ptrPrev = ptrHead;    
        ptrHead->ptrNext = newNode;
    }
    else
    {   // use recursion, passing the ptrHead->ptrNext as ptrHead.
        ptrHead->ptrNext = insertNode(ptrHead->ptrNext, iData);
    }
     // return the ptrHead of the new list with the new node.
    return ptrHead;
}

/**
 * Prints the contents of the doubly linked list.
 * 
 * @param ptrHead A pointer to the head of the list. 
 * 
 * @return Void.
 */
void printList(struct ListNode* ptrHead)
{
    struct ListNode* ptrCurrent = ptrHead;
    // if the list is empty.    
    if (ptrCurrent == nullptr)
    {
        cout << "Empty List" << endl;
    }
    else
    {
        while (ptrCurrent != nullptr)
        {   
            // traverse the list by printing the nodes.
            cout << ptrCurrent->iData << "\t";
            ptrCurrent = ptrCurrent->ptrNext;
        }        
        
    }
    cout << endl;
}

/**
 * Recursively inserts the nodes of a binary tree at the given level them to the doubly linked list.
 * 
 * @param ptrHead A pointer to the head of the doubly linked list.
 * @param ptrRoot A pointer to the root of the binary tree.
 * @param iLevel The current level of the tree being processed.
 * 
 * @return A pointer to the head of the updated doubly linked list.
 */
struct ListNode* insertCurrentLevel(struct ListNode* ptrHead, struct TreeNode* ptrRoot, int iLevel)
{
    // if the level is empty
    if (ptrRoot == nullptr)
    {
        return ptrHead;    
    }
    // if the level is the first 
    if (iLevel == 1)
    {   
        ptrHead = insertNode(ptrHead, ptrRoot->iData);
    }
    // if level is superior than 1
    else if (iLevel > 1) 
    {   
        ptrHead = insertCurrentLevel(ptrHead, ptrRoot->ptrLeft, iLevel - 1);
        ptrHead = insertCurrentLevel(ptrHead, ptrRoot->ptrRight, iLevel - 1);
    }
    
    // return the ptrHead
    return ptrHead;
}

/**
 * Creates a doubly linked list by inserting the nodes of a binary tree in breadth-first order.
 * 
 * @param ptrRoot A pointer to the root of the binary tree.
 * 
 * @return A pointer to the head of the created doubly linked list.
 */
struct ListNode* insertBFS(struct TreeNode* ptrRoot)
{
    // initialize th head of the list as nullptr.
    struct ListNode* ptrHead = nullptr;
    
    // get the depth of the binary tree.
    int iDepth = getHeight(ptrRoot);
    for (int iLevel = 0; iLevel < iDepth; iLevel++)
    {   
        // insert the nodes of the current level into the list. 
        ptrHead = insertCurrentLevel(ptrHead, ptrRoot, iLevel + 1);
    }

    // return the head of the list.
    return ptrHead;
}

/**
 * Prints the binary tree in breadth-first order.
 * 
 * @param ptrRoot A pointer to the root of the binary tree.
 * 
 * @return Void.
 */
void traverseBFS(struct TreeNode* ptrRoot)
{
    // if the tree is empty.
    if (ptrRoot == nullptr)
    {
        cout << "Empty Tree" << endl;
    }

    // get the depth of the tree.
    int iDepth = getHeight(ptrRoot);
    for (int iLevel = 0; iLevel < iDepth; iLevel++)
    {
        // print the nodes of the current level.
        printCurrentLevel(ptrRoot, iLevel + 1);
        cout << endl;
    }   
}

/**
 * Calculates the length of a doubly linked list.
 * 
 * @param ptrHead A pointer to the head of the doubly linked list.
 * 
 * @return The length of the doubly linked list.
 */
int getLength(struct ListNode* ptrHead)
{
    // initialization.
    struct ListNode* ptrCurrent = ptrHead;
    int iLength = 1;

    // traverse the list until reaching the end.
    while (ptrCurrent->ptrNext != nullptr)
    {
        // tranverse the list count the elements.
        ptrCurrent = ptrCurrent->ptrNext;
        iLength++;
    }

    // return the lenght of the list.
    return iLength;
}

/**
 * Retrieves a node from a linked list by its index.
 * 
 * @param ptrHead A pointer to the head of the linked list.
 * @param iIndex The index of the desired node (starting from 0).
 * 
 * @return A pointer to the node at the specified index.
 */
struct ListNode* getNodeByIndex(struct ListNode* ptrHead, int iIndex)
{
    // inizialization.
    struct ListNode* ptrCurrent = ptrHead;
    
    // go through the list until you find the index
    for (int i = 0; i < iIndex; i++)
    {
        ptrCurrent = ptrCurrent->ptrNext;
    }
    // return the node of the index
    return ptrCurrent;
}

/**
 * Prints the nodes at the specified level of the binary tree.
 * 
 * @param ptrRoot A pointer to the root of the binary tree.
 * @param iLevel The current level of the tree being processed.
 * 
 * @return Void.
 */
void printCurrentLevel(struct TreeNode* ptrRoot, int iLevel)
{
    // if the node is empty return.
    if (ptrRoot == nullptr)
    {
        return;
    }
    // if the node is the first.
    if (iLevel == 1)
    {   
        cout << ptrRoot->iData << "\t";
    }
    // if the level is greater than 1.
    else if (iLevel > 1) 
    {   
        // let's go down to the children, first to the left child, second to the right child. 
        printCurrentLevel(ptrRoot->ptrLeft, iLevel - 1);
        printCurrentLevel(ptrRoot->ptrRight, iLevel - 1);      
    }
}

/**
 * Creates a new node for the queue.
 * 
 * @param ptrTreeNode A pointer to the node of the binary tree.
 * 
 * @return A pointer to the new node.
*/
struct QueueNode* newQueueNode(struct TreeNode* ptrTreeNode)
{
    // Allocate memory for new node
    struct QueueNode* ptrNewNode = (struct QueueNode*) malloc(sizeof(struct QueueNode));

    // Assign data to this node
    ptrNewNode->ptrTreeNode = ptrTreeNode;
    ptrNewNode->ptrNext = nullptr;
    return ptrNewNode;
}

/**
 * Creates a new queue.
 * 
 * @return A pointer to the new queue.
*/
struct Queue* newQueue()
{
    // Allocate memory for new queue
    struct Queue* ptrQueue = (struct Queue*) malloc(sizeof(struct Queue));

    // Assign data to this queue
    ptrQueue->ptrFront = nullptr;
    ptrQueue->ptrRear = nullptr;
    return ptrQueue;
}

/**
 * Adds a node to the end of the queue.
 * 
 * @param ptrQueue A pointer to the queue.
 * 
 * @return Void.
*/
void enQueue(struct Queue* ptrQueue, struct TreeNode* ptrTreeNode)
{
    // Create a new node
    struct QueueNode* ptrNewNode = newQueueNode(ptrTreeNode);

    // If queue is empty, then new node is front and rear both
    if (ptrQueue->ptrRear == nullptr)
    {
        ptrQueue->ptrFront = ptrNewNode;
        ptrQueue->ptrRear = ptrNewNode;
        return;
    }

    // else, add new node at the end of queue and change rear
    ptrQueue->ptrRear->ptrNext = ptrNewNode;
    ptrQueue->ptrRear = ptrNewNode;
}

/**
 * Removes the first node from the queue and returns it.
 * 
 * @param ptrQueue A pointer to the queue.
 * 
 * @return A pointer to the first node in the queue.
*/
struct TreeNode* deQueue(struct Queue* ptrQueue)
{
    // If queue is empty, there is nothing to dequeue
    if (ptrQueue->ptrFront == nullptr)
    {
        return nullptr;
    }

    // Store previous front and move front one node ahead
    struct TreeNode* ptrTreeNode = ptrQueue->ptrFront->ptrTreeNode;
    struct QueueNode* ptrTemp = ptrQueue->ptrFront;

    ptrQueue->ptrFront = ptrQueue->ptrFront->ptrNext;

    // if queue becomes empty, then change rear to nullptr as well
    if (ptrQueue->ptrFront == nullptr)
    {
        ptrQueue->ptrRear = nullptr;
    }

    // Free memory and return the dequeued node
    free(ptrTemp);
    return ptrTreeNode;
}

/**
 * Prints the binary tree in breadth-first order using a queue.
 * 
 * @param ptrRoot A pointer to the root of the binary tree.
 * 
 * @return Void.
*/
void efficientBFS(struct TreeNode* ptrRoot)
{
    // If tree is empty, return
    if (ptrRoot == nullptr)
    {
        cout << "Empty Tree" << endl;
        return;
    }

    // Create an empty queue for level order traversal
    struct Queue* ptrQueue = newQueue();
    enQueue(ptrQueue, ptrRoot);

    int iFrontHeight = getNodeHeight(ptrRoot, ptrQueue->ptrFront->ptrTreeNode);
    int iCurrentHeight = iFrontHeight;

    // Loop until queue is empty
    while (ptrQueue->ptrFront != nullptr)
    {
        // Get and remove front of queue
        struct TreeNode* ptrCurrent = deQueue(ptrQueue);

        // Get height of current node
        iCurrentHeight = getNodeHeight(ptrRoot, ptrCurrent);

        // If the current node's height is greater than the previous' height, we have reached a new level
        if (iCurrentHeight > iFrontHeight)
        {
            cout << endl;
            cout << ptrCurrent->iData << "\t";
            iFrontHeight = iCurrentHeight;
        }
        else
        {
            cout << ptrCurrent->iData << "\t";
        }

        // Enqueue left child
        if (ptrCurrent->ptrLeft != nullptr)
        {
            enQueue(ptrQueue, ptrCurrent->ptrLeft);
        }

        // Enqueue right child
        if (ptrCurrent->ptrRight != nullptr)
        {
            enQueue(ptrQueue, ptrCurrent->ptrRight);
        }
    }
    cout << endl;
}

/***************************************************************************************************************************************/

// Sorting functions

/**
 * Swaps two nodes in a doubly linked list.
 * Assumes nodeA comes before nodeB
 * 
 * @param ptrHead A pointer to the pointer to the head of the linked list.
 * @param ptrNodeA A pointer to the first node to be swapped.
 * @param ptrNodeB A pointer to the second node to be swapped.
 * 
 * @return Void.
 */
void swapNodes(struct ListNode** ptrHead, struct ListNode* ptrNodeA, struct ListNode* ptrNodeB)
{
    // rearrange the nexts of node A, node B, node A prev, and node B prev, we also need to change the prevs of node A, node B, node A next, and node B next.
    // if NodeA is the head.
    if (ptrNodeA == *ptrHead)
    {
        // if ptrNodeA->ptrNext is the NodeB.
        if (ptrNodeA->ptrNext == ptrNodeB)
        {   
            ptrNodeA->ptrNext = ptrNodeB->ptrNext;
            // if NodeB is not the tail.
            if (ptrNodeB->ptrNext != nullptr) ptrNodeB->ptrNext->ptrPrev = ptrNodeA;
            // if NodeB is the tail.
            ptrNodeA->ptrPrev = ptrNodeB;
            ptrNodeB->ptrNext = ptrNodeA;
            ptrNodeB->ptrPrev = nullptr;
            (*ptrHead) = ptrNodeB;
        }
        // if ptrNodeA->ptrNext is not the NodeB.
        else
        {   
            // save the adjacent nodes of NodeB in the news ListNodes.
            struct ListNode* ptrCurrentBPrev = ptrNodeB->ptrPrev;
            struct ListNode* ptrCurrentBNext = ptrNodeB->ptrNext;

            // rearrange nodes.
            ptrNodeB->ptrNext = ptrNodeA->ptrNext;
            ptrNodeB->ptrPrev = nullptr;
            ptrCurrentBPrev->ptrNext = ptrNodeA;
            if (ptrCurrentBNext != nullptr) ptrCurrentBNext->ptrPrev = ptrNodeA;
            ptrNodeA->ptrNext->ptrPrev = ptrNodeB;
            ptrNodeA->ptrNext = ptrCurrentBNext;
            ptrNodeA->ptrPrev = ptrCurrentBPrev;
            (*ptrHead) = ptrNodeB;
        }
    }
    // NodeA is not the head.
    else
    {
        // if ptrNodeA->ptrNext is the NodeB.
        if (ptrNodeA->ptrNext == ptrNodeB)
        {   
            ptrNodeA->ptrNext = ptrNodeB->ptrNext;
            // if NodeB is not the tail. 
            if (ptrNodeB->ptrNext != nullptr) ptrNodeB->ptrNext->ptrPrev = ptrNodeA;
            // if NodeB is the tail.
            ptrNodeB->ptrPrev = ptrNodeA->ptrPrev;
            ptrNodeA->ptrPrev->ptrNext = ptrNodeB;
            ptrNodeB->ptrNext = ptrNodeA;
            ptrNodeA->ptrPrev = ptrNodeB;
        }
        // if ptrNodeA->ptrNext is not the NodeB.
        else
        {
            // save the adjacent nodes of NodeB and Node A in the news ListNodes.
            struct ListNode* ptrCurrentAPrev = ptrNodeA->ptrPrev;
            struct ListNode* ptrCurrentBPrev = ptrNodeB->ptrPrev;

            struct ListNode* ptrCurrentANext = ptrNodeA->ptrNext;
            struct ListNode* ptrCurrentBNext = ptrNodeB->ptrNext;
            
            // rearrange the nodes prevs and nexts.
            ptrNodeA->ptrPrev = ptrNodeB->ptrPrev;
            ptrNodeB->ptrPrev = ptrCurrentAPrev;

            ptrCurrentAPrev->ptrNext = ptrNodeB;
            ptrCurrentBPrev->ptrNext = ptrNodeA;

            ptrNodeA->ptrNext = ptrNodeB->ptrNext;
            ptrNodeB->ptrNext = ptrCurrentANext;

            ptrCurrentANext->ptrPrev = ptrNodeB;
            // if NodeB is the tail.
            if (ptrCurrentBNext != nullptr) ptrCurrentBNext->ptrPrev = ptrNodeA;
        }
    }
}

/**
 * Sorts a doubly linked list using the selection sort algorithm.
 * 
 * @param ptrHead A pointer to the pointer to the head of the linked list.
 * 
 * @return Void.
 */
void selectionSort(struct ListNode** ptrHead)
{
    // initialization.
    struct ListNode* ptrCurrent = *ptrHead;
    int iLength = getLength(*ptrHead);
    
    for (int iIndex = 0; iIndex < iLength; iIndex++)
    {
        // ptrCurrent receive the index node.
        ptrCurrent = getNodeByIndex(*ptrHead, iIndex);
        // initialization, the "min" and "min candidate" being the current.
        struct ListNode* ptrMin = ptrCurrent;
        struct ListNode* ptrCandidate = ptrCurrent;

        // traversing the successor nodes and comparing.
        while (ptrCandidate != nullptr)
        {
            if (ptrMin->iData > ptrCandidate->iData)
            {   
                // if candidate is smaller than min node, update the min node.
                ptrMin = ptrCandidate;
            }
            // just candidate update.
            ptrCandidate = ptrCandidate->ptrNext;
        }
        //if there is a smaller than the current, change the current with the min.
        if (ptrMin != ptrCurrent)
        {
            swapNodes(ptrHead, ptrCurrent, ptrMin);
            
            // Print the list vertically with a 0.5-second delay
            printVertical(*ptrHead);
            sleep_for(milliseconds(200));
            system("clear");
        }
        
        
    }
}

/**
 * Sorts a doubly linked list using the insertion sort algorithm.
 * 
 * @param ptrHead A pointer to the pointer to the head of the linked list.
 * 
 * @return Void.
 */
void insertionSort(struct ListNode** ptrHead)
{
    // initialization.
    struct ListNode* ptrCurrent1 = *ptrHead;
    struct ListNode* ptrCurrent2 = *ptrHead;
    int iLength = getLength(ptrCurrent1);

    // growing loop, ptrCurrent1 is the index Node iOuterLoop. 
    for (int iOuterLoop = 1; iOuterLoop < iLength; iOuterLoop++)
    {
        // loop comparing with the previous ones and changing if there is a smaller one.
        for (int iInnerLoop = iOuterLoop; iInnerLoop > 0; iInnerLoop--)
        {
            ptrCurrent1 = getNodeByIndex(*ptrHead, iInnerLoop);
            ptrCurrent2 = getNodeByIndex(*ptrHead, iInnerLoop - 1);

            if (ptrCurrent1->iData < ptrCurrent2->iData)
            {
                swapNodes(ptrHead, ptrCurrent2, ptrCurrent1);
                
                // Print the list vertically with a 0.5-second delay
                printVertical(*ptrHead);
                sleep_for(milliseconds(200));
                system("clear");
            }
        }
    }
}

/**
 * Sorts a doubly linked list using the shell sort algorithm.
 * 
 * @param ptrHead A pointer to the pointer to the head of the linked list.
 * 
 * @return Void.
 */
void shellSort(struct ListNode** ptrHead)
{
    struct ListNode* ptrCurrent1 = *ptrHead;
    int iLength = getLength(*ptrHead);
    int iGap = 1;

    // Knuth's sequence
    while (iGap < iLength) iGap = 3 * iGap + 1;
    // calculate the initial gap and updates the value of gap.
    for (iGap = (iGap - 1) / 3; iGap > 0; iGap = (iGap - 1) / 3)
    {
        for (int iOuterLoop = iGap; iOuterLoop < iLength; iOuterLoop++)
        {
            for (int iInnerLoop = iOuterLoop; iInnerLoop >= iGap; iInnerLoop -= iGap)
            {
                ptrCurrent1 = getNodeByIndex(*ptrHead, iInnerLoop);
                struct ListNode* ptrCurrent2 = getNodeByIndex(*ptrHead, iInnerLoop - iGap);
                // comparisons between elements with distance gap
                if (ptrCurrent1->iData < ptrCurrent2->iData)
                {
                    swapNodes(ptrHead, ptrCurrent2, ptrCurrent1);
                    
                    // Print the list vertically with a 0.5-second delay
                    printVertical(*ptrHead);
                    sleep_for(milliseconds(200));
                    system("clear");
                }
            }
        }
    }
}

/**
 * Sorts a doubly linked list using the bubble sort algorithm.
 * 
 * @param ptrHead A pointer to the pointer to the head of the linked list.
 * 
 * @return Void.
 */
void bubbleSort(struct ListNode** ptrHead)
{
    struct ListNode* ptrRoot = *ptrHead;
    int iLength = getLength(*ptrHead);
    bool bUnordered = true;
    // loop to decrease where we left off the inner loop.
    for (int iOuterLoop = 0; iOuterLoop < iLength; iOuterLoop++)
    {
        bUnordered = false;
        for (int iInnerLoop = 0; iInnerLoop < iLength - 1 - iOuterLoop; iInnerLoop++)
        {   
            // comparing two by two and switching when necessary
            struct ListNode* ptrTempA = getNodeByIndex(*ptrHead, iInnerLoop);
            struct ListNode* ptrTempB = getNodeByIndex(*ptrHead, iInnerLoop + 1);
            
            if (ptrTempA->iData > ptrTempB->iData)
            {
                swapNodes(ptrHead, ptrTempA, ptrTempB);
                bUnordered = true;
                
                // Print the list vertically with a 0.5-second delay
                printVertical(*ptrHead);
                sleep_for(milliseconds(200));
                system("clear");
            }
            
        }
        // if we do not perform any changes in a loop, we have our ordered list
        if (!bUnordered) break;
    }
}

/**
 * Prints a doubly linked list vertically with strings of 'O' characters representing each node
 * 
 * @param ptrHead A pointer to the pointer to the head of the linked list.
 * 
 * @return Void.
 */
void printVertical(struct ListNode* ptrHead) {
    // If the head is nullptr, do nothing.
    if (ptrHead == nullptr)
    {
        return;
    }
    
    // Iterate over the list printing the payload and the corresponding quantity of "O" characters
    for (struct ListNode* ptrTemp = ptrHead; ptrTemp != nullptr; ptrTemp = ptrTemp->ptrNext)
    {
        cout << ptrTemp->iData << "\t";
        
        for (int i = 0; i < ptrTemp->iData; i++)
        {
            cout << "O";
        }
        cout << endl;
    }
}

/***************************************************************************************************************************************/

// Main loop of the program

/**
 * Runs the main loop of the program
 * 
 * @return Void.
 */
void loop()
{
    // Greeting message
    cout << strSeparator << endl;
    cout << strGreetingMessage << endl;
    
    // Define the sentinel and the execution holder
    int iSentinel = 0;
    bool bExecuting = true;
    
    // Define the tree root (it's only possible to have one tree at a time)
    struct TreeNode* ptrRoot = nullptr;
    
    // Do the loop
    while (bExecuting)
    {
        // Print the menu of options and ask a new input
        printMenu();
        cin >> iSentinel;
        
        // Handle input error
        if (!iSentinel)
        {
            // Display error message
            cout << strErrorMessage << endl;
            cout << endl;
            
            // Clear the error flag and the input buffer
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        
        // Perform operations
        switch (iSentinel)
        {
            case 1: // Quit the program
            {
                // Set `bExecuting` to false to stop the while loop
                bExecuting = false;
                
                cout << endl; break;
            }
            
            case 2: // Build a binary tree from a text file
            {
                // Ask the user to enter the text file name
                string strFileName = askFileName();
                
                /******************************/
                
                // Start the timer
                auto timeStart = high_resolution_clock::now();
                
                // Build the tree
                ptrRoot = buildFromFile(ptrRoot, strFileName);
                
                // Stop the timer and compute the duration
                auto timeStop = high_resolution_clock::now();
                auto timeDuration = duration_cast<milliseconds>(timeStop - timeStart);
                
                /******************************/
                
                // Report the time taken to complete the operation
                cout << "\nTask finnished in: " << timeDuration.count() << " milliseconds." << endl;
                
                break;
            }
            
            case 3: // Build a binary tree from numbers inserted in the terminal.
            {
                /******************************/
                
                // Start the timer
                auto timeStart = high_resolution_clock::now();
                
                // Build the tree
                ptrRoot = buildFromUser(ptrRoot);
                
                // Stop the timer and compute the duration
                auto timeStop = high_resolution_clock::now();
                auto timeDuration = duration_cast<milliseconds>(timeStop - timeStart);
                
                /******************************/
                
                // Report the time taken to complete the operation
                cout << "\nTask finnished in: " << timeDuration.count() << " milliseconds." << endl;
                
                break;
            }
            
            case 4: // Get the height of the tree.
            {
                /******************************/
                
                // Start the timer
                auto timeStart = high_resolution_clock::now();
                
                // Calculate the height
                int iTreeHeight = getHeight(ptrRoot);
                
                // Stop the timer and compute the duration
                auto timeStop = high_resolution_clock::now();
                auto timeDuration = duration_cast<milliseconds>(timeStop - timeStart);
                
                /******************************/
                
                // Print the height
                cout << "The height of the tree is: " << iTreeHeight << endl;
                
                // Report the time taken to complete the operation
                cout << "\nTask finnished in: " << timeDuration.count() << " milliseconds." << endl;
                
                break;
            }
            
            case 5: // Get the size of the tree.
            {
                /******************************/
                
                // Start the timer
                auto timeStart = high_resolution_clock::now();
                
                // Calculate the height
                int iTreeSize = getNumberOfNodes(ptrRoot);
                
                // Stop the timer and compute the duration
                auto timeStop = high_resolution_clock::now();
                auto timeDuration = duration_cast<milliseconds>(timeStop - timeStart);
                
                /******************************/
                
                // Print the height
                cout << "The size of the tree is: " << iTreeSize << endl;
                
                // Report the time taken to complete the operation
                cout << "\nTask finnished in: " << timeDuration.count() << " milliseconds." << endl;
                
                break;
            }
            
            case 6: // Insert an element into the tree.
            {
                // Ask the user to enter the number to be inserted
                int iNumber = askElement();
                
                /******************************/
                
                // Start the timer
                auto timeStart = high_resolution_clock::now();
                
                // Insert the received integer into the tree
                insertNode(&ptrRoot, iNumber);
                
                // Stop the timer and compute the duration
                auto timeStop = high_resolution_clock::now();
                auto timeDuration = duration_cast<milliseconds>(timeStop - timeStart);
                
                /******************************/
                
                // Report the time taken to complete the operation
                cout << "\nTask finnished in: " << timeDuration.count() << " milliseconds." << endl;
                
                break;
            }
            
            case 7: // Remove an element off the tree.
            {
                // Ask the user to enter the number to be removed
                int iNumber = askElement();
                
                /******************************/
                
                // Start the timer
                auto timeStart = high_resolution_clock::now();
                
                // Remove the received integer from the tree
                ptrRoot = deleteNode(ptrRoot, iNumber);
                
                // Stop the timer and compute the duration
                auto timeStop = high_resolution_clock::now();
                auto timeDuration = duration_cast<milliseconds>(timeStop - timeStart);
                
                /******************************/
                
                // Report the time taken to complete the operation
                cout << "\nTask finnished in: " << timeDuration.count() << " milliseconds." << endl;
                
                break;
            }
            
            case 8: // Search the memory address of an element.
            {
                // Ask the user to enter the number to be searched
                int iNumber = askElement();
                
                /******************************/
                
                // Start the timer
                auto timeStart = high_resolution_clock::now();
                
                // Remove the received integer from the tree
                struct TreeNode* ptrSearchedNode = searchNode(ptrRoot, iNumber);
                
                // Stop the timer and compute the duration
                auto timeStop = high_resolution_clock::now();
                auto timeDuration = duration_cast<milliseconds>(timeStop - timeStart);
                
                /******************************/
                
                // Print the memory address of the requested element
                cout << "The memory address of " << iNumber << " is: " << ptrSearchedNode << endl;
                
                // Report the time taken to complete the operation
                cout << "\nTask finnished in: " << timeDuration.count() << " milliseconds." << endl;
                
                break;
            }
            
            case 9: // Ask if the tree is complete.
            {
                // Initialize the boolean to store the answer
                bool bIsComplete = true;
                
                /******************************/
                
                // Start the timer
                auto timeStart = high_resolution_clock::now();
                
                // Check if the tree is complete
                bIsComplete = isComplete(ptrRoot, getHeight(ptrRoot), 1);
                
                // Stop the timer and compute the duration
                auto timeStop = high_resolution_clock::now();
                auto timeDuration = duration_cast<milliseconds>(timeStop - timeStart);
                
                /******************************/
                
                // Print the answer
                if (bIsComplete) cout << "Yes, the tree is complete." << endl;
                else cout << "No, the tree is not complete." << endl;
                
                // Report the time taken to complete the operation
                cout << "\nTask finnished in: " << timeDuration.count() << " milliseconds." << endl;
                
                break;
            }
            
            case 10: // Ask if the tree is perfect.
            {
                // Initialize the boolean to store the answer
                bool bIsPerfect = true;
                
                /******************************/
                
                // Start the timer
                auto timeStart = high_resolution_clock::now();
                
                // Check if the tree is complete
                bIsPerfect = isPerfect(ptrRoot, getHeight(ptrRoot), 1);
                
                // Stop the timer and compute the duration
                auto timeStop = high_resolution_clock::now();
                auto timeDuration = duration_cast<milliseconds>(timeStop - timeStart);
                
                /******************************/
                
                // Print the answer
                if (bIsPerfect) cout << "Yes, the tree is perfect." << endl;
                else cout << "No, the tree is not perfect." << endl;
                
                // Report the time taken to complete the operation
                cout << "\nTask finnished in: " << timeDuration.count() << " milliseconds." << endl;
                
                break;
            }
            
            case 11: // Exhibit the tree using BFS.
            {
                /******************************/
                
                // Start the timer
                auto timeStart = high_resolution_clock::now();
                
                // Print the tree using BFS
                efficientBFS(ptrRoot);
                
                // Stop the timer and compute the duration
                auto timeStop = high_resolution_clock::now();
                auto timeDuration = duration_cast<milliseconds>(timeStop - timeStart);
                
                /******************************/
                
                // Report the time taken to complete the operation
                cout << "\nTask finnished in: " << timeDuration.count() << " milliseconds." << endl;
                
                break;
            }
            
            case 12: // Convert the tree to list and sort via Bubble Sort.
            {
                /******************************/
                
                // Start the timer
                auto timeStart = high_resolution_clock::now();
                
                // Convert the tree to a doubly linked list using BFS
                struct ListNode* ptrList = insertBFS(ptrRoot);
                
                // Sort the tree via Bubble Sort
                bubbleSort(&ptrList);
                
                // Stop the timer and compute the duration
                auto timeStop = high_resolution_clock::now();
                auto timeDuration = duration_cast<milliseconds>(timeStop - timeStart);
                
                /******************************/
                
                // Print the sorted list
                printVertical(ptrList);
                cout << "Sorted list:\n";
                printList(ptrList);
                
                // Report the time taken to complete the operation
                cout << "\nTask finnished in: " << timeDuration.count() << " milliseconds." << endl;
                
                break;
            }
            
            case 13: // Convert the tree to list and sort via Selection Sort.
            {
                /******************************/
                
                // Start the timer
                auto timeStart = high_resolution_clock::now();
                
                // Convert the tree to a doubly linked list using BFS
                struct ListNode* ptrList = insertBFS(ptrRoot);
                
                // Sort the tree via Selection Sort
                selectionSort(&ptrList);
                
                // Stop the timer and compute the duration
                auto timeStop = high_resolution_clock::now();
                auto timeDuration = duration_cast<milliseconds>(timeStop - timeStart);
                
                /******************************/
                
                // Print the sorted list
                printVertical(ptrList);
                cout << "Sorted list:\n";
                printList(ptrList);
                
                // Report the time taken to complete the operation
                cout << "\nTask finnished in: " << timeDuration.count() << " milliseconds." << endl;
                
                break;
            }
            
            case 14: // Convert the tree to list and sort via Insertion Sort.
            {
                /******************************/
                
                // Start the timer
                auto timeStart = high_resolution_clock::now();
                
                // Convert the tree to a doubly linked list using BFS
                struct ListNode* ptrList = insertBFS(ptrRoot);
                
                // Sort the tree via Insertion Sort
                insertionSort(&ptrList);
                
                // Stop the timer and compute the duration
                auto timeStop = high_resolution_clock::now();
                auto timeDuration = duration_cast<milliseconds>(timeStop - timeStart);
                
                /******************************/
                
                // Print the sorted list
                printVertical(ptrList);
                cout << "Sorted list:\n";
                printList(ptrList);
                
                // Report the time taken to complete the operation
                cout << "\nTask finnished in: " << timeDuration.count() << " milliseconds." << endl;
                
                break;
            }
            
            case 15: // Convert the tree to list and sort via Shell Sort.
            {
                /******************************/
                
                // Start the timer
                auto timeStart = high_resolution_clock::now();
                
                // Convert the tree to a doubly linked list using BFS
                struct ListNode* ptrList = insertBFS(ptrRoot);
                
                // Sort the tree via Shell Sort
                shellSort(&ptrList);
                
                // Stop the timer and compute the duration
                auto timeStop = high_resolution_clock::now();
                auto timeDuration = duration_cast<milliseconds>(timeStop - timeStart);
                
                /******************************/
                
                // Print the sorted list
                printVertical(ptrList);
                cout << "Sorted list:\n";
                printList(ptrList);
                
                // Report the time taken to complete the operation
                cout << "\nTask finnished in: " << timeDuration.count() << " milliseconds." << endl;
                
                break;
            }
            
            case 16: // Display tests from driver_code.cpp
            {
                // Display the tests
                test();

                cout << endl;
                break;
            }
            
            default: // Report error if inserted sentinel is not in 1, ..., 16.
            {
                // Display error message
                cout << strErrorMessage << endl;
                cout << endl; break;
            }
        }
    }
    
    // Ending message
    cout << strSeparator << endl;
    cout << strEndingMessage << endl;
    cout << strSeparator << endl;
}

/***************************************************************************************************************************************/

// Auxiliary functions

/**
 * Print the ASCII menu with user options.
 * 
 * @return Void.
 */
void printMenu()
{
    // Start each loop with separator and instructions
    cout << strSeparator << endl;
    cout << strInstruction << endl;
    
    // Iterate from 0 to 16 printing the number and the corresponding option in `strOptions`
    for (int i=0; i<16; i++)
    {
        cout << "[" << i+1 << "]\t" << strOptions[i] << endl;
    }
    
    // End with separator string and ">>>" for the user input
    cout << strSeparator << endl;
    cout << ">>> ";
}

/**
 * Checks if a string contains only numeric characters.
 * 
 * @param &strInput Reference to the input string to check.
 * 
 * @return True if the string contains only numeric characters, False otherwise.
 */
bool isNumeric(const string &strInput)
{
    if (strInput.empty()) return false;
        
    // Check if the first character is a minus sign
    if (strInput[0] == '-')
    {
        // If the string has only a minus sign, it is not numeric
        if (strInput.length() == 1) return false;
        
        // Check the remaining characters if they are numeric
        return strInput.find_first_not_of("0123456789", 1) == std::string::npos;
    }
    
    // Check if all characters are numeric
    return strInput.find_first_not_of("0123456789") == std::string::npos;
}

/**
 * Asks the user for the text file name, with data to build the tree.
 * 
 * @return String with the file name.
 */
string askFileName()
{
    // Initialize the file name string as empty
    string strFileName = "";
    
    // Ask the user to type it
    cout << "Please, insert the name of the text file with \".txt\"" << endl;
    cout << "> "; cin >> strFileName;
    
    return strFileName;
}

/**
 * Ask the user to input an integer in the terminal.
 * 
 * @return Integer given by the user.
 */
int askElement()
{
    // Initialize the string input as empty
    string strInput = "";
    
    // Run an infinite loop
    cout << "Please, enter an integer: " << endl;
    while (true)
    {
        // Ask the integer
        cout << "> "; cin >> strInput;
        
        if (isNumeric(strInput))
        {
            // Convert the `strInput` to int type and return it
            int iNumber = stoi(strInput);
            return iNumber;
        }
        else
        {
            // If the user's input is non-integer, print an error message and keep asking
            cout << "Invalid input! Please enter an integer." << endl;
        }
    }
}

// Functions to build the tree

/**
 * Asks the user for the text file name, with data to build the tree.
 * 
 * @param ptrRoot A pointer to the root of the existing tree.
 * @param strFileName A string containing the name of the text file.
 * 
 * @return A pointer to the root the tree build from the given file.
 */
struct TreeNode* buildFromFile(struct TreeNode* ptrRoot, string strFileName)
{
    // Check if `ptrRoot` is empty. If not, drain it
    if (ptrRoot != nullptr) deleteTree(&ptrRoot);
    
    // Create a string to hold the numbers in the file
    string strLine = "";
    string strDelimiter = " ";
    
    // Iterate over each line to get the data
    ifstream MyReadFile(strFileName);
    
    while (getline(MyReadFile, strLine))
    {
        int iPos = 0;
        string strToken;
        while ((iPos = strLine.find(strDelimiter)) != string::npos)
        {
            strToken = strLine.substr(0, iPos);
            if (isNumeric(strToken)) insertNode(&ptrRoot, stoi(strToken));
            strLine.erase(0, iPos + strDelimiter.length());
        }
        
        if (isNumeric(strLine)) insertNode(&ptrRoot, stoi(strLine));
    }
    cout << endl;
    
    // Close the file
    MyReadFile.close();
    
    // Return the built tree
    return ptrRoot;
}

/**
 * Builds the binary tree from data entered by the user.
 * 
 * @param ptrRoot A pointer to the root of the existing tree.
 * 
 * @return A pointer to the root of the built tree.
 */
struct TreeNode* buildFromUser(struct TreeNode* ptrRoot)
{
    // Check if `ptrRoot` is empty. If not, drain it
    if (ptrRoot != nullptr) deleteTree(&ptrRoot);
    
    // Initialize the string to store user's input
    string strInput = "";
    
    // Run an infinite loop
    cout << "Enter an integer or \"q\" to quit: " << endl;
    while (true)
    {
        cout << "> "; cin >> strInput;
        
        if (strInput == "q")
        {
            // Quit inserting
            break;
        }
        else if (isNumeric(strInput))
        {
            // Convert the `strInput` to int type and insert it into the tree
            int iNumber = stoi(strInput);
            insertNode(&ptrRoot, iNumber);
        }
        else
        {
            // If the user's input is non-integer or not "q", print an error message
            cout << "Invalid input! Please enter an integer or \"q\" to quit." << endl;
        }
    }
    
    // Return the built tree
    return ptrRoot;
}

/***************************************************************************************************************************************/
