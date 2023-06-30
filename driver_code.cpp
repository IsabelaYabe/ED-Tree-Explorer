#include <iostream>
#include "functions.h"
#include "driver_code.h"

using std::cout;
using std::endl;
using std::cin;

void test()
{
    cout << "========== Testing newNode() ==========" << endl;
    
    struct TreeNode* ptrRoot = newTreeNode(10);

    cout << "ptrRoot->iData: " << ptrRoot->iData << endl;
    cout << "ptrRoot->ptrLeft: " << (ptrRoot->ptrLeft == nullptr) << endl;
    cout << "ptrRoot->ptrRight: " << (ptrRoot->ptrRight == nullptr) << endl;
    
    cout << "Size of ptrRoot: " << sizeof(ptrRoot) << endl;
    cout << "Size of *ptrRoot: " << sizeof(*ptrRoot) << endl;
    
    cout << "TreeNode's payload size: " << sizeof(ptrRoot->iData) << endl;
    cout << "TreeNode's left pointer size: " << sizeof(ptrRoot->ptrLeft) << endl;
    cout << "TreeNode's right pointer size: " << sizeof(ptrRoot->ptrRight) << endl;
    
    cout << "TreeNode Location: " << ptrRoot << endl;
    cout << "TreeNode's payload Location: " << &(ptrRoot->iData) << endl;
    cout << "TreeNode's left pointer Location: " << &(ptrRoot->ptrLeft) << endl;
    cout << "TreeNode's right pointer Location: " << &(ptrRoot->ptrRight) << endl;
    
    ptrdiff_t diff = (char *)&(ptrRoot->ptrLeft) - (char *)&(ptrRoot->iData) - sizeof(ptrRoot->iData);
    cout << "There is a padding of " << diff << " bytes between the payload and the left pointer." << endl;

    cout << "\n========== Testing traversePreOrder() ==========" << endl;
    
    traversePreOrder(ptrRoot);
    cout << endl;

    ptrRoot->ptrLeft = newTreeNode(5);
    traversePreOrder(ptrRoot);
    cout << endl;

    ptrRoot->ptrRight = newTreeNode(15);
    traversePreOrder(ptrRoot);
    cout << endl;

    ptrRoot->ptrLeft->ptrRight = newTreeNode(7);
    traversePreOrder(ptrRoot);
    cout << endl;

    cout << "\n========== Testing insertNode() ==========" << endl;
    
    insertNode(&ptrRoot, 3);
    insertNode(&ptrRoot, 2);
    insertNode(&ptrRoot, 4);
    insertNode(&ptrRoot, 9);
    insertNode(&ptrRoot, 6);
    insertNode(&ptrRoot, 12);
    insertNode(&ptrRoot, 13);
    insertNode(&ptrRoot, 11);
    insertNode(&ptrRoot, 18);
    insertNode(&ptrRoot, 16);
    insertNode(&ptrRoot, 20);

    traversePreOrder(ptrRoot);
    cout << endl;

    cout << "\nChecking if each node is what they should be:" << endl;
    cout << (ptrRoot->iData == 10) << endl;
    cout << (ptrRoot->ptrLeft->iData == 5) << endl;
    cout << (ptrRoot->ptrRight->iData == 15) << endl;
    cout << (ptrRoot->ptrLeft->ptrLeft->iData == 3) << endl;
    cout << (ptrRoot->ptrLeft->ptrLeft->ptrLeft->iData == 2) << endl;
    cout << (ptrRoot->ptrLeft->ptrLeft->ptrRight->iData == 4) << endl;
    cout << (ptrRoot->ptrLeft->ptrRight->iData == 7) << endl;
    cout << (ptrRoot->ptrLeft->ptrRight->ptrLeft->iData == 6) << endl;
    cout << (ptrRoot->ptrLeft->ptrRight->ptrRight->iData == 9) << endl;
    cout << (ptrRoot->ptrRight->ptrLeft->iData == 12) << endl;
    cout << (ptrRoot->ptrRight->ptrLeft->ptrRight->iData == 13) << endl;
    cout << (ptrRoot->ptrRight->ptrLeft->ptrLeft->iData == 11) << endl;
    cout << (ptrRoot->ptrRight->ptrRight->iData == 18) << endl;
    cout << (ptrRoot->ptrRight->ptrRight->ptrLeft->iData == 16) << endl;
    cout << (ptrRoot->ptrRight->ptrRight->ptrRight->iData == 20) << endl;
    
    cout << "\n========== Testing deleteTree() ==========" << endl;
    
    cout << "Current tree:" << endl;
    traversePreOrder(ptrRoot);
    cout << endl;
    
    cout << "\nDeleting the whole tree..." << endl;
    deleteTree(&ptrRoot);
    
    cout << "\nNow the tree is empty and `ptrRoot` is `nullptr`.\nTraverse preOrder:" << endl;
    traversePreOrder(ptrRoot);
    cout << endl;
    
    cout << "\nRebuilding tree..." << endl;
    insertNode(&ptrRoot, 10);
    insertNode(&ptrRoot, 5);
    insertNode(&ptrRoot, 15);
    insertNode(&ptrRoot, 7);
    insertNode(&ptrRoot, 3);
    insertNode(&ptrRoot, 2);
    insertNode(&ptrRoot, 4);
    insertNode(&ptrRoot, 9);
    insertNode(&ptrRoot, 6);
    insertNode(&ptrRoot, 12);
    insertNode(&ptrRoot, 13);
    insertNode(&ptrRoot, 11);
    insertNode(&ptrRoot, 18);
    insertNode(&ptrRoot, 16);
    insertNode(&ptrRoot, 20);
    
    traversePreOrder(ptrRoot);
    cout << endl;
    
    cout << "\n========== Testing getSmallestChild() ==========" << endl;
    
    struct TreeNode* ptrSmallest = getSmallestChild(ptrRoot);
    cout << "Smallest child of ptrRoot: " << ptrSmallest->iData << endl;

    ptrSmallest = getSmallestChild(ptrRoot->ptrLeft);
    cout << "Smallest child of ptrRoot->ptrLeft: " << ptrSmallest->iData << endl;

    ptrSmallest = getSmallestChild(ptrRoot->ptrRight);
    cout << "Smallest child of ptrRoot->ptrRight: " << ptrSmallest->iData << endl;

    ptrSmallest = getSmallestChild(ptrRoot->ptrLeft->ptrLeft->ptrRight);
    cout << "Smallest child of ptrRoot->ptrLeft->ptrLeft->ptrRight: " << ptrSmallest->iData << endl;

    cout << "\n========== Testing deleteNode() ==========" << endl;

    ptrRoot = deleteNode(ptrRoot, 10);
    traversePreOrder(ptrRoot);
    cout << endl;

    ptrRoot = deleteNode(ptrRoot, 5);
    traversePreOrder(ptrRoot);
    cout << endl;

    ptrRoot = deleteNode(ptrRoot, 20);
    traversePreOrder(ptrRoot);
    cout << endl;

    ptrRoot = deleteNode(ptrRoot, 12);
    traversePreOrder(ptrRoot);
    cout << endl;

    cout << "\n========== Testing searchNode() ==========" << endl;

    cout << "Does searching for 10 return nullptr? " << (searchNode(ptrRoot, 10) == nullptr) << endl;
    cout << "Does searching for 5 return nullptr? " << (searchNode(ptrRoot, 5) == nullptr) << endl;

    cout << "\nDoes searching for 3 return nullptr? " << (searchNode(ptrRoot, 3) == nullptr) << endl;
    cout << "What is the address of the node with 3? " << searchNode(ptrRoot, 3) << endl;

    cout << "\nDoes searching for 16 return nullptr? " << (searchNode(ptrRoot, 16) == nullptr) << endl;
    cout << "What is the address of the node with 16? " << searchNode(ptrRoot, 16) << endl;
    
    cout << "\n========== Testing getHeight() ==========" << endl;

    cout << "Height of ptrRoot: " << getHeight(ptrRoot) << endl;
    cout << "Height of ptrRoot->ptrLeft: " << getHeight(ptrRoot->ptrLeft) << endl;
    cout << "Height of ptrRoot->ptrRight: " << getHeight(ptrRoot->ptrRight) << endl;
    cout << "Height of ptrRoot->ptrLeft->ptrLeft: " << getHeight(ptrRoot->ptrLeft->ptrLeft) << endl;
    cout << "Height of ptrRoot->ptrLeft->ptrLeft->ptrLeft: " << getHeight(ptrRoot->ptrLeft->ptrLeft->ptrLeft) << endl;
    cout << "Height of ptrRoot->ptrLeft->ptrLeft->ptrLeft->ptrLeft: " << getHeight(ptrRoot->ptrLeft->ptrLeft->ptrLeft->ptrLeft) << endl;

    cout << "\n========== Testing getNumberOfNodes() ==========" << endl;

    cout << "Number of nodes in ptrRoot: " << getNumberOfNodes(ptrRoot) << endl;

    cout << "\nInserting 10, 5, 15, 3 into ptrRoot..." << endl;

    insertNode(&ptrRoot, 10);
    insertNode(&ptrRoot, 5);
    insertNode(&ptrRoot, 15);
    insertNode(&ptrRoot, 3);

    cout << "Number of nodes in ptrRoot: " << getNumberOfNodes(ptrRoot) << endl;

    cout << "\nDeleting 10 from ptrRoot..." << endl;

    ptrRoot = deleteNode(ptrRoot, 10);

    cout << "Number of nodes in ptrRoot: " << getNumberOfNodes(ptrRoot) << endl;

    cout << "\n========== Testing isPerfect() ==========" << endl;

    cout << "Restarting tree..." << endl;

    ptrRoot = nullptr;
    ptrRoot = newTreeNode(10);
    insertNode(&ptrRoot, 5);
    insertNode(&ptrRoot, 15);
    insertNode(&ptrRoot, 3);
    insertNode(&ptrRoot, 7);
    insertNode(&ptrRoot, 12);
    insertNode(&ptrRoot, 18);

    traversePreOrder(ptrRoot);
    cout << endl;

    cout << "Is ptrRoot perfect? " << isPerfect(ptrRoot, getHeight(ptrRoot), 1) << endl;

    cout << "\nInserting 2, 4, 6, 9, 11, 13, 16, 20 into ptrRoot..." << endl;

    insertNode(&ptrRoot, 2);
    insertNode(&ptrRoot, 4);
    insertNode(&ptrRoot, 6);
    insertNode(&ptrRoot, 9);
    insertNode(&ptrRoot, 11);
    insertNode(&ptrRoot, 13);
    insertNode(&ptrRoot, 16);
    insertNode(&ptrRoot, 20);

    cout << "Is ptrRoot perfect? " << isPerfect(ptrRoot, getHeight(ptrRoot), 1) << endl;

    cout << "\nDeleting 20 from ptrRoot..." << endl;

    ptrRoot = deleteNode(ptrRoot, 20);

    cout << "Is ptrRoot perfect? " << isPerfect(ptrRoot, getHeight(ptrRoot), 1) << endl;


    cout << "\n========== Testing isComplete() ==========" << endl;

    cout << "Is ptrRoot complete? " << isComplete(ptrRoot, getHeight(ptrRoot), 1) << endl;

    cout << "\nDeleting 16 from ptrRoot..." << endl;

    ptrRoot = deleteNode(ptrRoot, 16);

    cout << "Is ptrRoot complete? " << isComplete(ptrRoot, getHeight(ptrRoot), 1) << endl;

    cout << "\nDeleting 13, 11, 9, 6, 4, 2 from ptrRoot..." << endl;

    ptrRoot = deleteNode(ptrRoot, 13);
    ptrRoot = deleteNode(ptrRoot, 11);
    ptrRoot = deleteNode(ptrRoot, 9);
    ptrRoot = deleteNode(ptrRoot, 6);
    ptrRoot = deleteNode(ptrRoot, 4);
    ptrRoot = deleteNode(ptrRoot, 2);

    cout << "Is ptrRoot complete? " << isComplete(ptrRoot, getHeight(ptrRoot), 1) << endl;

    cout << "\nDeleting 7 from ptrRoot..." << endl;

    ptrRoot = deleteNode(ptrRoot, 7);

    cout << "Is ptrRoot complete? " << isComplete(ptrRoot, getHeight(ptrRoot), 1) << endl;

    cout << "\nDeleting 18, 12 from ptrRoot..." << endl;

    ptrRoot = deleteNode(ptrRoot, 18);
    ptrRoot = deleteNode(ptrRoot, 12);

    cout << "Is ptrRoot complete? " << isComplete(ptrRoot, getHeight(ptrRoot), 1) << endl;
    
    /******************************/
    
    cout << "\n========== Testing isNumeric() ==========" << endl;
    
    // Define some strings to test
    string arrstrExampleStrings[5] = {"1234", "foo", "   ", "-10", "-98th"};
    
    for (int i=0; i<5; i++)
    {
        cout << "Is \"" << arrstrExampleStrings[i] << "\" numeric?\t";
        cout << isNumeric(arrstrExampleStrings[i]) << endl;
    }
    
    cout << "\n========== Testing askFileName() ==========" << endl;
    
    cout << "This is just a test of `askFileName` function." << endl;
    string strSampleFile = askFileName();
    cout << "You typed: " << strSampleFile << endl;
    
    
    cout << "\n========== Testing askElement() ==========" << endl;
    
    cout << "This is just a test of `askElement` function." << endl;
    int iSampleInteger = askElement();
    cout << "You typed: " << iSampleInteger << endl;

    cout << "\n========== Testing printList() ==========" << endl;
    //Let's create a doubly linked list
    struct ListNode* ptrHead;
    ptrHead = nullptr;

    //Print empty list
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
    cout << "Adding elements 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36 with insertNode()" << endl;
    cout << "Print list: " << endl;
    printList(ptrHead);
    cout << "\n========== Testing traverseBFS() ==========" << endl;
    
    //Let start by creating a tree
    ptrRoot = nullptr;
    
    //Print empty tree
    cout << "Print empty tree: " << endl;
    traverseBFS(ptrRoot);
    
    //Inserting nodes
    insertNode(&ptrRoot, 666);
    insertNode(&ptrRoot, 21);
    insertNode(&ptrRoot, 1024);
    insertNode(&ptrRoot, 8);
    insertNode(&ptrRoot, 571);
    insertNode(&ptrRoot, 923);
    insertNode(&ptrRoot, 1729);
    insertNode(&ptrRoot, 6);
    insertNode(&ptrRoot, 12);
    insertNode(&ptrRoot, 57);
    insertNode(&ptrRoot, 729);
    insertNode(&ptrRoot, 1111);
    insertNode(&ptrRoot, 1618);
    insertNode(&ptrRoot, 1964);
    insertNode(&ptrRoot, 232);
    insertNode(&ptrRoot, 496);
    insertNode(&ptrRoot, 503);
    insertNode(&ptrRoot, 801);
    insertNode(&ptrRoot, 1228);
    insertNode(&ptrRoot, 31);
    insertNode(&ptrRoot, 105);
    
    //Print BFS tree
    cout << "Adding elements 666, 21, 1024, 8, 571, 923, 1729, 6, 12, 57, 729, 1111, 1618, 1964, 232, 496, 503, 801, 1228, 31, 105 with insertNode()" << endl;
    cout << "Print BFS tree: " << endl;
    traverseBFS(ptrRoot);
    cout << endl;

    cout << "\n========== Testing efficientBFS() ==========" << endl;

    cout << "Restarting tree..." << endl;
    ptrRoot = nullptr;

    cout << "Printing empty tree: " << endl;
    efficientBFS(ptrRoot);

    cout << "Adding elements 5, 3, 15, 2, 4, 7, 18" << endl;
    insertNode(&ptrRoot, 5);
    insertNode(&ptrRoot, 3);
    insertNode(&ptrRoot, 15);
    insertNode(&ptrRoot, 2);
    insertNode(&ptrRoot, 4);
    insertNode(&ptrRoot, 7);
    insertNode(&ptrRoot, 18);

    cout << "Printing tree: " << endl;
    efficientBFS(ptrRoot);

    cout << "Deleting 3" << endl;
    ptrRoot = deleteNode(ptrRoot, 3);
    efficientBFS(ptrRoot);

    cout << "Deleting 7, 4" << endl;
    ptrRoot = deleteNode(ptrRoot, 7);
    ptrRoot = deleteNode(ptrRoot, 4);
    efficientBFS(ptrRoot);

    cout << "Deleting 5" << endl;
    ptrRoot = deleteNode(ptrRoot, 5);
    efficientBFS(ptrRoot);

    cout << "\n========== Testing getHeight() ==========" << endl;
    cout << "Depth of tree: " << endl;
    int iDepth = getHeight(ptrRoot);
    cout << iDepth << endl;
    
    //Print levels
    cout << "\n========== Printing levels ==========" << endl;
    for(int iLevel = 0; iLevel < iDepth; iLevel++)
    {
        cout << "\nPrint level " << iLevel + 1 << " :" << endl;
        printCurrentLevel(ptrRoot, iLevel + 1);
        cout << endl;
    }
    
    //Insert levels
    cout << "\n========== Testing insertCurrentLevel() ==========" << endl;
    cout << "Insert in a  empty list and print the levels===" << endl;
    for(int iLevel = 0; iLevel < iDepth; iLevel++)
    {
        struct ListNode* ptrCurrentLevel;
        ptrCurrentLevel = nullptr;
        cout << "Insert and print level " << iLevel + 1 << ": " << endl;
        ptrCurrentLevel = insertCurrentLevel(ptrCurrentLevel, ptrRoot, iLevel + 1);
        printList(ptrCurrentLevel);
        cout << endl;
    }
    cout << "\n========== Testing insertBFS() ==========" << endl;
    cout << "Create list in BFS order and print it: " << endl;
    struct ListNode* ptrList;
    ptrList = insertBFS(ptrRoot);
    printList(ptrList);
    
    cout << "\n========== Testing getLength() ==========" << endl;
    cout << "List to analyze: " << endl;
    printList(ptrHead);
    int iListLength;
    cout << "Length of the list: " << endl;
    iListLength = getLength(ptrHead);
    cout << iListLength << endl;
    
    cout << "\n========== Testing getNodeByIndex() ==========" << endl;
    cout << "List to analyze: " << endl;
    printList(ptrHead);
    struct ListNode* ptrNode;
    cout << "Get the 3rd element in the list (starting from 0): " << endl;
    ptrNode = getNodeByIndex(ptrHead, 2);
    cout << ptrNode->iData << endl;
    
    cout << "\n========== Testing swapNodes() ==========" << endl;
    cout << "Swap nodes 2nd and 4th node: " << endl;
    cout << "List before swap nodes: " << endl;
    printList(ptrHead);
    cout << "List after swap nodes: " << endl;
    swapNodes(&ptrHead, ptrHead->ptrNext, ptrHead->ptrNext->ptrNext->ptrNext);
    printList(ptrHead);

    cout << "\n========== Testing selectionSort() ==========" << endl;
    cout << "Sort double linked list by selection sort: " << endl;
    cout << "List before sort: " << endl;
    printList(ptrList);
    cout << "List after sort: " << endl;    
    selectionSort(&ptrList);
    printList(ptrList);
    
    cout << "\n========== Testing insertionSort() ==========" << endl;
    cout << "Sort double linked list by insertionSort: " << endl;
    struct ListNode* ptrList2;
    ptrList2 = insertBFS(ptrRoot);
    cout << "List before sort: " << endl;
    printList(ptrList2);
    cout << "List after sort: " << endl; 
    insertionSort(&ptrList2);
    printList(ptrList2);
    
    cout << "\n========== Testing shellSort() ==========" << endl;
    cout << "Sort double linked list by shellSort: " << endl;
    struct ListNode* ptrList3;
    ptrList3 = insertBFS(ptrRoot);
    cout << "List before sort: " << endl;
    printList(ptrList3);
    cout << "List after sort: " << endl; 
    shellSort(&ptrList3);
    printList(ptrList3);
    
    cout << "\n========== Testing bubbleSort() ==========" << endl;
    cout << "Sort double linked list by bubbleSort: " << endl;
    struct ListNode* ptrList4;
    ptrList4 = insertBFS(ptrRoot);
    cout << "List before sort: " << endl;
    printList(ptrList4);
    cout << "List after sort: " << endl; 
    bubbleSort(&ptrList4);
    printList(ptrList4);
    
}