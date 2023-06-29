#include <iostream>
#include "functions.h"

using namespace std;

//Chamando funções:
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
/////////////////////////////////////////////////////////////////////////////////////
/**
 * Creates a new node for the doubly linked list with the given data and nullptr as prev and next pointers.
 * 
 * @param iData The data to be stored in the new node.
 * 
 * @return A pointer to the new node.
 */
struct NodeList* newNodeList(int iData)
{
    struct NodeList* newNode = (struct NodeList*)malloc(sizeof(struct NodeList));
    newNode->iPayload = iData;
    newNode->ptrPrev = nullptr;
    newNode->ptrNext = nullptr;
    
    return newNode;
}

/**
 * Inserts a new node with the given data into the doubly linked list.
 * 
 * @param head A pointer to the head of the list.
 * @param iData The data to be stored in the new node.
 * 
 * @return A pointer to the head of the updated list.
 */
struct NodeList* insertNodeList(struct NodeList* head, int iData)
{
    struct NodeList* newNode = newNodeList(iData);
    
    if(head == nullptr)
    {
        return newNode;
    }
    
    if(head->ptrNext == nullptr)
    {
        newNode->ptrPrev = head;    
        head->ptrNext = newNode;
    }
    else
    {
        head->ptrNext = insertNodeList(head->ptrNext, iData);
    }
    
    return head;
}

/**
 * Prints the contents of the doubly linked list.
 * 
 * @param head A pointer to the head of the list.
 */
void printList(struct NodeList* head)
{
    struct NodeList* current = head;
    if(current == nullptr)
    {
        cout << "Lista vazia" << endl;
    }
    else
    {
        while(current != nullptr)
        {
            cout << current->iPayload << " ";
            current = current->ptrNext;
        }        
        
    }
    cout << endl;
}

/**
 * Recursively lists the nodes of a binary tree at the given level and adds them to the doubly linked list.
 * 
 * @param head A pointer to the head of the doubly linked list.
 * @param root A pointer to the root of the binary tree.
 * @param iLevel The current level of the tree being processed.
 * 
 * @return A pointer to the head of the updated doubly linked list.
 */
struct NodeList* listCurrentLevel(struct NodeList* head, struct Node* root, int iLevel)
{
    if (root == nullptr)
    {
        return head;    
    }
    if (iLevel == 1)
    {
        head = insertNodeList(head, root->iPayload);
    }
    else if (iLevel > 1) 
    {
        head = listCurrentLevel(head, root->ptrLeft, iLevel - 1);
        head = listCurrentLevel(head, root->ptrRight, iLevel - 1);
    }
    return head;
}

/**
 * Creates a doubly linked list by listing the nodes of a binary tree in breadth-first order.
 * 
 * @param root A pointer to the root of the binary tree.
 * 
 * @return A pointer to the head of the created doubly linked list.
 */
struct NodeList* traverseBFS(struct Node* root)
{
    struct NodeList* head;
    head = nullptr;
    int iDepth = depth(root);
    for (int i = 1; i <= iDepth; i++)
    {
        head = listCurrentLevel(head, root, i);
    }
    return head;
}
/**
 * Calculates the length of a linked list.
 * 
 * @param ptrHead A pointer to the head of the linked list.
 * @return The length of the linked list.
 */
int getLength(struct NodeList* ptrHead)
{
    struct NodeList* ptrCurrent = ptrHead;
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
 * @return A pointer to the node at the specified index.
 */
struct NodeList* getNodeByIndex(struct NodeList* ptrHead, int iIndex)
{
    struct NodeList* ptrCurrent = ptrHead;
    
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
 * @return void
 */
void swapNodes(struct NodeList** ptrHead, struct NodeList* ptrNodeA, struct NodeList* ptrNodeB)
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
            struct NodeList* ptrCurrentBPrev = ptrNodeB->ptrPrev;
            struct NodeList* ptrCurrentBNext = ptrNodeB->ptrNext;

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
            struct NodeList* ptrCurrentAPrev = ptrNodeA->ptrPrev;
            struct NodeList* ptrCurrentBPrev = ptrNodeB->ptrPrev;

            struct NodeList* ptrCurrentANext = ptrNodeA->ptrNext;
            struct NodeList* ptrCurrentBNext = ptrNodeB->ptrNext;

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
 * @return void
 */
void selectionSort(struct NodeList** ptrHead)
{
    struct NodeList* ptrCurrent = *ptrHead;
    int iLength = getLength(*ptrHead);
    
    for (int i = 0; i < iLength; i++)
    {
        ptrCurrent = getNodeByIndex(*ptrHead, i);
        struct NodeList* min = ptrCurrent;
        struct NodeList* r = ptrCurrent;

        while (r != nullptr)
        {
            if (min->iPayload > r->iPayload)
            {
                min = r;
            }

            r = r->ptrNext;
        }

        if (min != ptrCurrent)
        {
            swapNodes(ptrHead, ptrCurrent, min);
        }
    }
}

/**
 * Sorts a doubly linked list using the insertion sort algorithm.
 * 
 * @param ptrHead A pointer to the pointer to the head of the linked list.
 * @return void
 */
void insertionSort(struct NodeList** ptrHead)
{
    struct NodeList* ptrCurrent1 = *ptrHead;
    struct NodeList* ptrCurrent2 = *ptrHead;
    int iLength = getLength(ptrCurrent1);

    for (int i = 1; i < iLength; i++)
    {
        for (int j = i; j > 0; j--)
        {
            ptrCurrent1 = getNodeByIndex(*ptrHead, j);
            ptrCurrent2 = getNodeByIndex(*ptrHead, j - 1);

            if (ptrCurrent1->iPayload < ptrCurrent2->iPayload)
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
 * @return void
 */
void shellSort(struct NodeList** ptrHead)
{
    struct NodeList* ptrCurrent = *ptrHead;
    int iLength = getLength(*ptrHead);
    int iGap = 1;

    while (iGap < iLength) iGap = 3 * iGap + 1;

    for (iGap = (iGap - 1) / 3; iGap > 0; iGap = (iGap - 1) / 3)
    {
        for (int i = iGap; i < iLength; i++)
        {
            for (int j = i; j >= iGap; j -= iGap)
            {
                ptrCurrent = getNodeByIndex(*ptrHead, j);
                struct NodeList* ptrCurrent2 = getNodeByIndex(*ptrHead, j - iGap);

                if (ptrCurrent->iPayload < ptrCurrent2->iPayload)
                {
                    swapNodes(ptrHead, ptrCurrent2, ptrCurrent);
                }
            }
        }
    }
}

/**
 * Sorts a doubly linked list using the bubble sort algorithm.
 * 
 * @param ptrHead A pointer to the pointer to the head of the linked list.
 * @return void
 */
void bubbleSort(struct NodeList** ptrHead)
{
    struct NodeList* ptrRoot = *ptrHead;
    int iLength = getLength(*ptrHead);
    bool bUnordered = true;
    
    for (int iOuterLoop = 0; iOuterLoop < iLength; iOuterLoop++)
    {
        bUnordered = false;
        for (int iInnerLoop = 0; iInnerLoop < iLength - 1 - iOuterLoop; iInnerLoop++)
        {
            struct NodeList* ptrTempA = getNodeByIndex(*ptrHead, iInnerLoop);
            struct NodeList* ptrTempB = getNodeByIndex(*ptrHead, iInnerLoop + 1);
        
            
            if (ptrTempA->iPayload > ptrTempB->iPayload)
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
struct Node* newNode(int iData)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));    
    newNode->iPayload = iData;
    newNode->ptrLeft = nullptr;
    newNode->ptrRight = nullptr;
    
    return newNode;
}

/**
 * Inserts a new node with the given data into the binary tree.
 * 
 * @param node A pointer to the current node in the tree.
 * @param iData The data to be stored in the new node.
 * 
 * @return A pointer to the modified node.
 */
struct Node* insertNode(struct Node* node, int iData)
{
    if(node == nullptr)
    {
        return newNode(iData);
    }
    
    if(iData < node->iPayload)
    {
        node->ptrLeft = insertNode(node->ptrLeft, iData);
    }
    else
    {
        node->ptrRight = insertNode(node->ptrRight, iData);
    }
    return node;
}

/**
 * Calculates the depth of the binary tree.
 * 
 * @param root A pointer to the root of the binary tree.
 * 
 * @return The depth of the binary tree.
 */
int depth(struct Node* root)
{
    if (root == nullptr)
        return 0;
    else {
        int leftDepth = depth(root->ptrLeft);
        int rightDepth = depth(root->ptrRight);
 
        // First, we go down and sum up as we go up.
        // We descend to the deepest node.
        if (leftDepth > rightDepth) {
            return (leftDepth + 1);
        }
        else {
            return (rightDepth + 1);
        }
    }
}

/**
 * Prints the nodes at the specified level of the binary tree.
 * 
 * @param root A pointer to the root of the binary tree.
 * @param iLevel The current level of the tree being processed.
 */
void printCurrentLevel(struct Node* root, int iLevel)
{
    if (root == nullptr)
    {
        return;
    }
    if (iLevel == 1)
    {
        cout << root->iPayload << " ";
    }
    else if (iLevel > 1) 
    {
        printCurrentLevel(root->ptrLeft, iLevel - 1);
        printCurrentLevel(root->ptrRight, iLevel - 1);
    }
}

/**
 * Prints the binary tree in breadth-first order.
 * 
 * @param root A pointer to the root of the binary tree.
 */
void printBFS(struct Node* root)
{
    if(root == nullptr)
    {
        cout << "Árvore vazia" << endl;
    }
    int iDepth = depth(root);
    for (int i = 1; i <= iDepth; i++)
    {
        printCurrentLevel(root, i);
    }
} 


