#include <iostream>
#include "functions.h"
#include "driver_code.h"

using namespace std;

void test()
{   
    //Let's create a doubly linked list
    struct NodeList* head;
    head = nullptr;
    //Print empty list
    cout << "============================================================" << endl;
    cout << "Print empty: " << endl;
    printList(head);
    //Inserting nodes
    head = insertNodeList(head, 3);
    head = insertNodeList(head, 6);
    head = insertNodeList(head, 9);
    head = insertNodeList(head, 12);
    head = insertNodeList(head, 15);
    head = insertNodeList(head, 18);
    head = insertNodeList(head, 21);
    head = insertNodeList(head, 24);
    head = insertNodeList(head, 27);
    head = insertNodeList(head, 30);
    head = insertNodeList(head, 33);
    head = insertNodeList(head, 36);
    //Print
    cout << "============================================================" << endl;
    cout << "Print list: " << endl;
    printList(head);
    cout << "============================================================" << endl;
    //Let start by creating a tree
    struct Node* root;
    root = nullptr;
    //Print empty tree
    cout << "============================================================" << endl;
    cout << "Print empty tree: " << endl;
    printBFS(root);
    //Inserting nodes
    root = insertNode(root, 666);
    root = insertNode(root, 21);
    root = insertNode(root, 1024);
    root = insertNode(root, 8);
    root = insertNode(root, 571);
    root = insertNode(root, 923);
    root = insertNode(root, 1729);
    root = insertNode(root, 6);
    root = insertNode(root, 12);
    root = insertNode(root, 57);
    root = insertNode(root, 729);
    root = insertNode(root, 1111);
    root = insertNode(root, 1618);
    root = insertNode(root, 1964);
    root = insertNode(root, 232);
    root = insertNode(root, 496);
    root = insertNode(root, 503);
    root = insertNode(root, 801);
    root = insertNode(root, 1228);
    root = insertNode(root, 31);
    root = insertNode(root, 105);
    //Print BFS tree
    cout << "============================================================" << endl;
    cout << "Print BFS tree: " << endl;
    printBFS(root);
    cout << endl;
    cout << "============================================================" << endl;
    cout << "Depth of tree: " << endl;
    int iDepth = depth(root);
    cout << iDepth << endl;
    //Print levels
    cout << "============================================================" << endl;
    cout << "===PRINT LEVELS===" << endl;
    for(int i = 1; i <= iDepth; i++)
    {
        cout << "Print level " << i << ": " << endl;
        printCurrentLevel(root, i);
        cout << endl;
        cout << "=====:D-:D-:D-:D-:D-:D-:D=====";
        cout << endl;
    }
    //List levels
    cout << "============================================================" << endl;
    cout << "===LIST and PRINT LEVELS===" << endl;
    for(int i = 1; i <= iDepth; i++)
    {
        struct NodeList* level;
        level = nullptr;
        cout << "List ande print: " << i << ": " << endl;
        level = listCurrentLevel(level, root, i);
        printList(level);
        cout << endl;
        cout << "=====:D-:D-:D-:D-:D-:D-:D=====";
        cout << endl;
    }
    cout << "============================================================" << endl;
    cout << "Print list traversing the tree by BFS: " << endl;
    struct NodeList* traverseTreeList;
    traverseTreeList = traverseBFS(root);
    printList(traverseTreeList);
    cout << "============================================================" << endl;
    cout << "Get length of the list: " << endl;
    cout << "List: " << endl;
    printList(head);
    int lengthList;
    cout << "Length: " << endl;
    lengthList = getLength(head);
    cout << lengthList << endl;
    cout << "============================================================" << endl;
    cout << "Get node by index: " << endl;
    cout << "List: " << endl;
    printList(head);
    struct NodeList* node;
    cout << "Get the 3th element in the list ((starting from 0)): " << endl;
    struct NodeList* iNode;
    iNode = getNodeByIndex(head, 2);
    cout << iNode->iPayload << endl;
    cout << "============================================================" << endl;
    cout << "Swap nodes 2nd and 4th node: " << endl;
    cout << "List before swap nodes: " << endl;
    printList(head);
    cout << "List after swap nodes: " << endl;
    swapNodes(&head, head->ptrNext, head->ptrNext->ptrNext->ptrNext);
    printList(head);
    
    cout << "============================================================" << endl;
    cout << "Sort double linked list by selection sort: " << endl;
    cout << "List before sort: " << endl;
    printList(traverseTreeList);
    cout << "List after sort: " << endl;    
    selectionSort(&traverseTreeList);
    printList(traverseTreeList);
    
    cout << "============================================================" << endl;
    cout << "Sort double linked list by insertionSort: " << endl;
    struct NodeList* traverseTreeList2;
    traverseTreeList2 = traverseBFS(root);
    cout << "List before sort: " << endl;
    printList(traverseTreeList2);
    cout << "List after sort: " << endl; 
    insertionSort(&traverseTreeList2);
    printList(traverseTreeList2);
    
    cout << "============================================================" << endl;
    cout << "Sort double linked list by shellSort: " << endl;
    struct NodeList* traverseTreeList3;
    traverseTreeList3 = traverseBFS(root);
    cout << "List before sort: " << endl;
    printList(traverseTreeList3);
    cout << "List after sort: " << endl; 
    shellSort(&traverseTreeList3);
    printList(traverseTreeList3);
    
    cout << "============================================================" << endl;
    cout << "Sort double linked list by bubbleSort: " << endl;
    struct NodeList* traverseTreeList4;
    traverseTreeList4 = traverseBFS(root);
    cout << "List before sort: " << endl;
    printList(traverseTreeList4);
    cout << "List after sort: " << endl; 
    bubbleSort(&traverseTreeList4);
    printList(traverseTreeList4);
    
}