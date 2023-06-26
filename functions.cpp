#include <iostream>
#include <limits>
#include <chrono>
#include <fstream>
#include "functions.h"
#include "driver_code.h"

using std::cout;
using std::endl;
using std::cin;
using std::string;
using namespace std::chrono;

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

// Main loop of the program
/**
 * ...
 * 
 * @return Void.
 */
void loop()
{
    // Define the sentinel and the execution holder
    int iSentinel = 0;
    bool bExecuting = true;
    
    // Define the pointer to the root of the tree
    struct Node* ptrRoot = nullptr;
    
    // Main loop of the program
    while (bExecuting)
    {
        // Print the menu of options and ask a new input
        printMenu();
        cin >> iSentinel;
        
        // Handle input error
        if (!iSentinel)
        {
            cout << "Invalid entry! Please, insert only a number.\n" << endl;
            cin.clear();  // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear the input buffer
            continue;
        }
        
        // Perform actions
        switch (iSentinel)
        {
            case 1: // Quit the program
            {
                cout << "Quitting\n" << endl;
                cout << strSeparator << "\n" << endl;
                bExecuting = false;
                break;
            }
            
            case 2: // Build a binary tree from a text file
            {
                // Ask the user to enter the text file name
                string strFileName = askFileName();
                
                // Start the timer
                auto timeStart = high_resolution_clock::now();
                
                // Build the tree
                struct Node* ptrRoot = buildFromFile(strFileName);
                
                // Stop the timer and compute the duration
                auto timeStop = high_resolution_clock::now();
                auto timeDuration = duration_cast<milliseconds>(timeStop - timeStart);
                
                // Report the time taken to complete the operation
                cout << "Task finnished in: " << timeDuration.count() << " milliseconds." << endl;
                
                traversePreOrder(ptrRoot);
                
                break;
            }
            
            case 3: // Build a binary tree from data entered by the user
            {
                // Start the timer
                auto timeStart = high_resolution_clock::now();
                
                // Build the tree
                struct Node* ptrRoot = buildFromUser();
                
                // Stop the timer and compute the duration
                auto timeStop = high_resolution_clock::now();
                auto timeDuration = duration_cast<milliseconds>(timeStop - timeStart);
                
                // Report the time taken to complete the operation
                cout << "Task finnished in: " << timeDuration.count() << " milliseconds." << endl;
                
                traversePreOrder(ptrRoot);
                
                break;
            }
            
            case 4:
            {
                cout << "Executing 4\n" << endl;
                break;
            }
            
            case 5:
            {
                cout << "Executing 5\n" << endl;
                break;
            }
            
            case 6:
            {
                cout << "Executing 6\n" << endl;
                break;
            }
            
            case 7:
            {
                cout << "Executing 7\n" << endl;
                break;
            }
            
            case 8:
            {
                cout << "Executing 8\n" << endl;
                break;
            }
            
            case 9:
            {
                cout << "Executing 9\n" << endl;
                break;
            }
            
            case 10:
            {
                cout << "Executing 10\n" << endl;
                break;
            }
            
            case 11:
            {
                cout << "Executing 11\n" << endl;
                break;
            }
            
            case 12:
            {
                cout << "Executing 12\n" << endl;
                break;
            }
            
            case 13:
            {
                cout << "Executing 13\n" << endl;
                break;
            }
            
            case 14:
            {
                cout << "Executing 14\n" << endl;
                break;
            }
            
            case 15:
            {
                cout << "Executing 15\n" << endl;
                break;
            }
            
            case 16:
            {
                cout << "chamando a função int test()" << endl;
                int a = test();
                if (!a) cout << "Tudo certo" << endl;
                else cout << "ops." << endl;
                break;
            }
            
            default: // Report error if inserted sentinel is <1 or >16.
            {
                cout << "Invalid number! Insert an integer between 1 and 16.\n" << endl;
                break;
            }
        }
    }
    
    // End the program
    cout << "Test function" << endl;
}


// Menu functions

/**
 * Print the menu ASCII with user options.
 * 
 * @return Void.
 */
void printMenu()
{
    // Start with separator string
    cout << "\n" << strSeparator << endl;
    cout << "Dictionary of commands. Enter the number without brackets." << endl;
    
    // Iterate from 0 to 15 printing the number and the corresponding option in `strOptions`
    for (int i=0; i<16; i++)
    {
        cout << "[" << i+1 << "]\t" << strOptions[i] << endl;
    }
    
    // End with separator string and ">>>" for the user input
    cout << strSeparator << endl;
    cout << ">>> ";
}


// Case 2

/**
 * Ask the user for the text file name, with data to build the tree.
 * 
 * @return Void.
 */
string askFileName()
{
    // Initialize the file name string as empty
    string strFileName = "";
    
    // Ask the user to type it
    cout << "Please, insert the name of the text file with \".txt\"" << endl;
    cout << ">>> ";
    cin >> strFileName;
    
    return strFileName;
}

/**
 * Ask the user for the text file name, with data to build the tree.
 * 
 * @param strFileName A string containing the name of the text file.
 * 
 * @return A pointer to the root the tree build from the given file.
 */
struct Node* buildFromFile(string strFileName)
{
    // Initialize the tree with `nullptr`
    struct Node* ptrRoot = nullptr;
    
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


// Case 3

/**
 * Check if a string contains only numeric characters.
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
 * Build the binary tree from data entered by the user.
 * 
 * @return A pointer to the root of the built tree.
 */
struct Node* buildFromUser()
{
    // Initialize the tree with `nullptr`
    struct Node* ptrRoot = nullptr;
    
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
            // Conver the `strInput` to int type and insert it into the tree
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