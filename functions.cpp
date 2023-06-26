#include <iostream>
#include <limits>
#include <chrono>
#include <fstream>
#include "functions.h"
#include "driver_code.h"

using namespace std;
using namespace std::chrono;

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
