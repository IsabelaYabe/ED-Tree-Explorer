#include <iostream>
#include <fstream>
#include "functions.h"

using namespace std;


struct Node* newNode(int iData) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->iData = iData;
    newNode->ptrLeft = nullptr;
    newNode->ptrRight = nullptr;
    return newNode;
}
void traversePreOrder(struct Node* ptrStartingNode) {
    if (ptrStartingNode == nullptr) return;
    else {
        cout << ptrStartingNode->iData << " ";
        traversePreOrder(ptrStartingNode->ptrLeft);
        traversePreOrder(ptrStartingNode->ptrRight);
    }
}
void insertNode(struct Node** ptrRoot, int iData) {
    if (*ptrRoot == nullptr) (*ptrRoot) = newNode(iData);
    else if (iData <= (*ptrRoot)->iData) insertNode(&((*ptrRoot)->ptrLeft), iData);
    else insertNode(&((*ptrRoot)->ptrRight), iData);
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
    for (int i=0; i<15; i++)
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
    string strNumber = "";
    
    // Iterate over each line to get the data
    ifstream MyReadFile(strFileName);
    while (getline(MyReadFile, strNumber))
    {
        // Conver the `strNumber` to int type and insert it into the tree
        int iNumber = stoi(strNumber);
        insertNode(&ptrRoot, iNumber);
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
