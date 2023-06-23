#include <iostream>
#include "functions.h"

using std::cout;
using std::endl;
using std::cin;

int main()
{
    struct Node* ptrRoot = newNode(10);

    insertNode(&ptrRoot, 5);
    insertNode(&ptrRoot, 3);
    insertNode(&ptrRoot, 2);
    traversePreOrder(ptrRoot);

    cout << endl;

    cout << searchNode(ptrRoot, 5) << endl;
    cout << searchNode(ptrRoot, 15) << endl;
    cout << searchNode(ptrRoot, 10) << endl;

    cout << ptrRoot->ptrLeft << endl;
    cout << ptrRoot->ptrRight << endl;
    cout << ptrRoot << endl;

    cout << getHeight(ptrRoot) << endl;
    cout << isPerfect(ptrRoot, getHeight(ptrRoot), 1) << endl;
    cout << isComplete(ptrRoot, getHeight(ptrRoot), 1) << endl;

    return 0;
}