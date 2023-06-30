#include <iostream>
#include "functions.h"

using std::cout;
using std::cin;
using std::endl;

/**
 * Creates a new node for the doubly linked list with the given data and nullptr as prev and next pointers.
 * 
 * @param iData The data to be stored in the new node.
 * 
 * @return A pointer to the new node.
 */
struct ListNode* newListNode(int iData)
{
    struct ListNode* newNode = (struct ListNode*) malloc(sizeof(struct ListNode));
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
    
    if (ptrHead == nullptr)
    {
        return newNode;
    }
    
    if (ptrHead->ptrNext == nullptr)
    {
        newNode->ptrPrev = ptrHead;    
        ptrHead->ptrNext = newNode;
    }
    else
    {
        ptrHead->ptrNext = insertNode(ptrHead->ptrNext, iData);
    }
    
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
    if (ptrCurrent == nullptr)
    {
        cout << "Empty List" << endl;
    }
    else
    {
        while (ptrCurrent != nullptr)
        {
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
    if (ptrRoot == nullptr)
    {
        return ptrHead;    
    }
    if (iLevel == 1)
    {
        ptrHead = insertNode(ptrHead, ptrRoot->iData);
    }
    else if (iLevel > 1) 
    {
        ptrHead = insertCurrentLevel(ptrHead, ptrRoot->ptrLeft, iLevel - 1);
        ptrHead = insertCurrentLevel(ptrHead, ptrRoot->ptrRight, iLevel - 1);
    }
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
    struct ListNode* ptrHead = nullptr;

    int iDepth = getHeight(ptrRoot);
    for (int iLevel = 0; iLevel < iDepth; iLevel++)
    {
        ptrHead = insertCurrentLevel(ptrHead, ptrRoot, iLevel + 1);
    }
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
    if (ptrRoot == nullptr)
    {
        cout << "Empty Tree" << endl;
    }
    int iDepth = getHeight(ptrRoot);
    for (int iLevel = 0; iLevel < iDepth; iLevel++)
    {
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
    struct ListNode* ptrCurrent = ptrHead;
    int iLength = 1;

    while (ptrCurrent->ptrNext != nullptr)
    {
        ptrCurrent = ptrCurrent->ptrNext;
        iLength++;
    }

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
    struct ListNode* ptrCurrent = ptrHead;
    
    for (int i = 0; i < iIndex; i++)
    {
        ptrCurrent = ptrCurrent->ptrNext;
    }

    return ptrCurrent;
}

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
    if (ptrNodeA == *ptrHead)
    {
        if (ptrNodeA->ptrNext == ptrNodeB)
        {
            ptrNodeA->ptrNext = ptrNodeB->ptrNext;
            if (ptrNodeB->ptrNext != nullptr) ptrNodeB->ptrNext->ptrPrev = ptrNodeA;
            ptrNodeA->ptrPrev = ptrNodeB;
            ptrNodeB->ptrNext = ptrNodeA;
            ptrNodeB->ptrPrev = nullptr;

            (*ptrHead) = ptrNodeB;
        }
        else
        {
            struct ListNode* ptrCurrentBPrev = ptrNodeB->ptrPrev;
            struct ListNode* ptrCurrentBNext = ptrNodeB->ptrNext;

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
    else
    {
        if (ptrNodeA->ptrNext == ptrNodeB)
        {
            ptrNodeA->ptrNext = ptrNodeB->ptrNext;
            if (ptrNodeB->ptrNext != nullptr) ptrNodeB->ptrNext->ptrPrev = ptrNodeA;
            ptrNodeB->ptrPrev = ptrNodeA->ptrPrev;
            ptrNodeA->ptrPrev->ptrNext = ptrNodeB;
            ptrNodeB->ptrNext = ptrNodeA;
            ptrNodeA->ptrPrev = ptrNodeB;
        }
        else
        {
            struct ListNode* ptrCurrentAPrev = ptrNodeA->ptrPrev;
            struct ListNode* ptrCurrentBPrev = ptrNodeB->ptrPrev;

            struct ListNode* ptrCurrentANext = ptrNodeA->ptrNext;
            struct ListNode* ptrCurrentBNext = ptrNodeB->ptrNext;

            ptrNodeA->ptrPrev = ptrNodeB->ptrPrev;
            ptrNodeB->ptrPrev = ptrCurrentAPrev;

            ptrCurrentAPrev->ptrNext = ptrNodeB;
            ptrCurrentBPrev->ptrNext = ptrNodeA;

            ptrNodeA->ptrNext = ptrNodeB->ptrNext;
            ptrNodeB->ptrNext = ptrCurrentANext;

            ptrCurrentANext->ptrPrev = ptrNodeB;
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
    struct ListNode* ptrCurrent = *ptrHead;
    int iLength = getLength(*ptrHead);
    
    for (int iIndex = 0; iIndex < iLength; iIndex++)
    {
        ptrCurrent = getNodeByIndex(*ptrHead, iIndex);
        struct ListNode* ptrMin = ptrCurrent;
        struct ListNode* ptrCandidate = ptrCurrent;

        while (ptrCandidate != nullptr)
        {
            if (ptrMin->iData > ptrCandidate->iData)
            {
                ptrMin = ptrCandidate;
            }

            ptrCandidate = ptrCandidate->ptrNext;
        }

        if (ptrMin != ptrCurrent)
        {
            swapNodes(ptrHead, ptrCurrent, ptrMin);
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
    struct ListNode* ptrCurrent1 = *ptrHead;
    struct ListNode* ptrCurrent2 = *ptrHead;
    int iLength = getLength(ptrCurrent1);

    for (int iOuterLoop = 1; iOuterLoop < iLength; iOuterLoop++)
    {
        for (int iInnerLoop = iOuterLoop; iInnerLoop > 0; iInnerLoop--)
        {
            ptrCurrent1 = getNodeByIndex(*ptrHead, iInnerLoop);
            ptrCurrent2 = getNodeByIndex(*ptrHead, iInnerLoop - 1);

            if (ptrCurrent1->iData < ptrCurrent2->iData)
            {
                swapNodes(ptrHead, ptrCurrent2, ptrCurrent1);
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

    while (iGap < iLength) iGap = 3 * iGap + 1;

    for (iGap = (iGap - 1) / 3; iGap > 0; iGap = (iGap - 1) / 3)
    {
        for (int iOuterLoop = iGap; iOuterLoop < iLength; iOuterLoop++)
        {
            for (int iInnerLoop = iOuterLoop; iInnerLoop >= iGap; iInnerLoop -= iGap)
            {
                ptrCurrent1 = getNodeByIndex(*ptrHead, iInnerLoop);
                struct ListNode* ptrCurrent2 = getNodeByIndex(*ptrHead, iInnerLoop - iGap);

                if (ptrCurrent1->iData < ptrCurrent2->iData)
                {
                    swapNodes(ptrHead, ptrCurrent2, ptrCurrent1);
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
    
    for (int iOuterLoop = 0; iOuterLoop < iLength; iOuterLoop++)
    {
        bUnordered = false;
        for (int iInnerLoop = 0; iInnerLoop < iLength - 1 - iOuterLoop; iInnerLoop++)
        {
            struct ListNode* ptrTempA = getNodeByIndex(*ptrHead, iInnerLoop);
            struct ListNode* ptrTempB = getNodeByIndex(*ptrHead, iInnerLoop + 1);
        
            
            if (ptrTempA->iData > ptrTempB->iData)
            {
                swapNodes(ptrHead, ptrTempA, ptrTempB);
                bUnordered = true;
            }
            
        }
        if (!bUnordered) break;
    }

}

/**
 * Creates a new node for the binary tree with the given data and nullptr as left and right child nodes.
 * 
 * @param iData The data to be stored in the new node.
 * 
 * @return A pointer to the new node.
 */
struct TreeNode* newTreeNode(int iData)
{
    struct TreeNode* newNode = (struct TreeNode*) malloc(sizeof(struct TreeNode));    
    newNode->iData = iData;
    newNode->ptrLeft = nullptr;
    newNode->ptrRight = nullptr;
    
    return newNode;
}

/**
 * Inserts a new node with the given data into the binary tree.
 * 
 * @param ptrNode A pointer to the current node in the tree.
 * @param iData The data to be stored in the new node.
 * 
 * @return A pointer to the modified node.
 */
struct TreeNode* insertNode(struct TreeNode* ptrNode, int iData)
{
    if (ptrNode == nullptr)
    {
        return newTreeNode(iData);
    }
    
    if (iData < ptrNode->iData)
    {
        ptrNode->ptrLeft = insertNode(ptrNode->ptrLeft, iData);
    }
    else
    {
        ptrNode->ptrRight = insertNode(ptrNode->ptrRight, iData);
    }
    return ptrNode;
}

/**
 * Calculates the depth of the binary tree.
 * 
 * @param ptrRoot A pointer to the root of the binary tree.
 * 
 * @return The depth of the binary tree.
 */
int getHeight(struct TreeNode* ptrRoot)
{
    if (ptrRoot == nullptr)
    {
        return 0;
    }

    int leftDepth = getHeight(ptrRoot->ptrLeft);
    int rightDepth = getHeight(ptrRoot->ptrRight);

    if (leftDepth > rightDepth) 
    {
        return (leftDepth + 1);
    }
    else 
    {
        return (rightDepth + 1);
    }
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
    if (ptrRoot == nullptr)
    {
        return;
    }
    if (iLevel == 1)
    {
        cout << ptrRoot->iData << "\t";
    }
    else if (iLevel > 1) 
    {
        printCurrentLevel(ptrRoot->ptrLeft, iLevel - 1);
        printCurrentLevel(ptrRoot->ptrRight, iLevel - 1);      
    }
}