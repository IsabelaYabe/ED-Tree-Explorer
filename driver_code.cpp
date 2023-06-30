#include <iostream>
#include "functions.h"
#include "driver_code.h"

using namespace std;

void test()
{   
    //Let's create a doubly linked list
    struct ListNode* ptrHead;
    ptrHead = nullptr;

    //Print empty list
    cout << "============================================================" << endl;
    cout << "Print empty: " << endl;
    printList(ptrHead);
    
    //Inserting nodes
    ptrHead = insertNode(ptrHead, 3);
    ptrHead = insertNode(ptrHead, 6);
    ptrHead = insertNode(ptrHead, 9);
    ptrHead = insertNode(ptrHead, 12);
    ptrHead = insertNode(ptrHead, 15);
    ptrHead = insertNode(ptrHead, 18);
    ptrHead = insertNode(ptrHead, 21);
    ptrHead = insertNode(ptrHead, 24);
    ptrHead = insertNode(ptrHead, 27);
    ptrHead = insertNode(ptrHead, 30);
    ptrHead = insertNode(ptrHead, 33);
    ptrHead = insertNode(ptrHead, 36);
    
    //Print
    cout << "============================================================" << endl;
    cout << "Print list: " << endl;
    printList(ptrHead);
    cout << "============================================================" << endl;
    
    //Let start by creating a tree
    struct TreeNode* ptrRoot;
    ptrRoot = nullptr;
    
    //Print empty tree
    cout << "============================================================" << endl;
    cout << "Print empty tree: " << endl;
    traverseBFS(ptrRoot);
    
    //Inserting nodes
    ptrRoot = insertNode(ptrRoot, 666);
    ptrRoot = insertNode(ptrRoot, 21);
    ptrRoot = insertNode(ptrRoot, 1024);
    ptrRoot = insertNode(ptrRoot, 8);
    ptrRoot = insertNode(ptrRoot, 571);
    ptrRoot = insertNode(ptrRoot, 923);
    ptrRoot = insertNode(ptrRoot, 1729);
    ptrRoot = insertNode(ptrRoot, 6);
    ptrRoot = insertNode(ptrRoot, 12);
    ptrRoot = insertNode(ptrRoot, 57);
    ptrRoot = insertNode(ptrRoot, 729);
    ptrRoot = insertNode(ptrRoot, 1111);
    ptrRoot = insertNode(ptrRoot, 1618);
    ptrRoot = insertNode(ptrRoot, 1964);
    ptrRoot = insertNode(ptrRoot, 232);
    ptrRoot = insertNode(ptrRoot, 496);
    ptrRoot = insertNode(ptrRoot, 503);
    ptrRoot = insertNode(ptrRoot, 801);
    ptrRoot = insertNode(ptrRoot, 1228);
    ptrRoot = insertNode(ptrRoot, 31);
    ptrRoot = insertNode(ptrRoot, 105);
    
    //Print BFS tree
    cout << "============================================================" << endl;
    cout << "Print BFS tree: " << endl;
    traverseBFS(ptrRoot);
    cout << endl;
    cout << "============================================================" << endl;
    cout << "Depth of tree: " << endl;
    int iDepth = getHeight(ptrRoot);
    cout << iDepth << endl;
    
    //Print levels
    cout << "============================================================" << endl;
    cout << "===PRINT LEVELS===" << endl;
    for(int iLevel = 0; iLevel < iDepth; iLevel++)
    {
        cout << "Print level " << iLevel + 1 << ": " << endl;
        printCurrentLevel(ptrRoot, iLevel + 1);
        cout << endl;
        cout << "=====:D-:D-:D-:D-:D-:D-:D=====";
        cout << endl;
    }
    
    //Insert levels
    cout << "============================================================" << endl;
    cout << "===INSERT and PRINT LEVELS===" << endl;
    for(int iLevel = 0; iLevel < iDepth; iLevel++)
    {
        struct ListNode* ptrCurrentLevel;
        ptrCurrentLevel = nullptr;
        cout << "List and print: " << iLevel + 1 << ": " << endl;
        ptrCurrentLevel = insertCurrentLevel(ptrCurrentLevel, ptrRoot, iLevel + 1);
        printList(ptrCurrentLevel);
        cout << endl;
        cout << "=====:D-:D-:D-:D-:D-:D-:D=====";
        cout << endl;
    }
    cout << "============================================================" << endl;
    cout << "Create list in BFS order and print it: " << endl;
    struct ListNode* ptrList;
    ptrList = insertBFS(ptrRoot);
    printList(ptrList);
    
    cout << "============================================================" << endl;
    cout << "Get length of the list: " << endl;
    cout << "List: " << endl;
    printList(ptrHead);
    int iListLength;
    cout << "Length: " << endl;
    iListLength = getLength(ptrHead);
    cout << iListLength << endl;
    
    cout << "============================================================" << endl;
    cout << "Get node by index: " << endl;
    cout << "List: " << endl;
    printList(ptrHead);
    struct ListNode* ptrNode;
    cout << "Get the 3rd element in the list (starting from 0): " << endl;
    ptrNode = getNodeByIndex(ptrHead, 2);
    cout << ptrNode->iData << endl;
    
    cout << "============================================================" << endl;
    cout << "Swap nodes 2nd and 4th node: " << endl;
    cout << "List before swap nodes: " << endl;
    printList(ptrHead);
    cout << "List after swap nodes: " << endl;
    swapNodes(&ptrHead, ptrHead->ptrNext, ptrHead->ptrNext->ptrNext->ptrNext);
    printList(ptrHead);

    cout << "============================================================" << endl;
    cout << "Sort double linked list by selection sort: " << endl;
    cout << "List before sort: " << endl;
    printList(ptrList);
    cout << "List after sort: " << endl;    
    selectionSort(&ptrList);
    printList(ptrList);
    
    cout << "============================================================" << endl;
    cout << "Sort double linked list by insertionSort: " << endl;
    struct ListNode* ptrList2;
    ptrList2 = insertBFS(ptrRoot);
    cout << "List before sort: " << endl;
    printList(ptrList2);
    cout << "List after sort: " << endl; 
    insertionSort(&ptrList2);
    printList(ptrList2);
    
    cout << "============================================================" << endl;
    cout << "Sort double linked list by shellSort: " << endl;
    struct ListNode* ptrList3;
    ptrList3 = insertBFS(ptrRoot);
    cout << "List before sort: " << endl;
    printList(ptrList3);
    cout << "List after sort: " << endl; 
    shellSort(&ptrList3);
    printList(ptrList3);
    
    cout << "============================================================" << endl;
    cout << "Sort double linked list by bubbleSort: " << endl;
    struct ListNode* ptrList4;
    ptrList4 = insertBFS(ptrRoot);
    cout << "List before sort: " << endl;
    printList(ptrList4);
    cout << "List after sort: " << endl; 
    bubbleSort(&ptrList4);
    printList(ptrList4);
    
}