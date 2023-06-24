#include <iostream>
#include "function.h"

using namespace std;
/////////////////////////////////////////////////////////////////////////////////////
//Definindo estruturas:
struct NodeList
{
    int iPayload;            // Payload data stored in the node
    struct NodeList* ptrPrev;  // Pointer to the previous node in the list
    struct NodeList* ptrNext;  // Pointer to the next node in the list
};

struct Node
{
    int iPayload;            // Payload data stored in the node
    struct Node* ptrLeft;     // Pointer to the left child node
    struct Node* ptrRight;    // Pointer to the right child node
};


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
struct NodeList* listTree(struct Node* root)
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
///////////////////////////////////////////////////////////////////////////////////////////////
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
    int iDepth = depth(root);
    for (int i = 1; i <= iDepth; i++)
    {
        printCurrentLevel(root, i);
    }
} 

int main()
{
    struct Node* root;
    root = nullptr;
    root = insertNode(root, 42);
    root = insertNode(root, 7);
    root = insertNode(root, 666);
    root = insertNode(root, 1);
    root = insertNode(root, 13);
    root = insertNode(root, 5);
    root = insertNode(root, 59);
    root = insertNode(root, 2023);
    root = insertNode(root, 27);
    
    struct NodeList* head;
    head = nullptr;
    head = insertNodeList(head, 1);
    head = insertNodeList(head, 2);
    head = insertNodeList(head, 3);
    head = insertNodeList(head, 5);
    head = insertNodeList(head, 6);
    head = insertNodeList(head, 7);
    
    //printList(head);    
    //printCurrentLevel(root, 3);
    //cout << endl;
    cout << "Iniciando teste" << endl;
    struct NodeList* headTeste;
    headTeste = nullptr;
    headTeste = listTree(root);
    printList(headTeste);
    cout << "Testado" << endl;
    //printBFS(root);    
    return 0;
}

