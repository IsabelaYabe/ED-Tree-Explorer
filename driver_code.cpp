#include <iostream>
#include "functions.h"

using std::cout;
using std::endl;
using std::cin;

int main()
{
    struct Node* ptrRoot = newNode(10);
    insertNode(&ptrRoot, 15);
    traversePreOrder(ptrRoot);

    return 0;
}