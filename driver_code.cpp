#include <iostream>
#include <limits>
#include <chrono>
#include "functions.h"

using namespace std;
using namespace std::chrono;

int main()
{
    // Define the sentinel and the execution holder
    int iSentinel = 0;
    bool bExecuting = true;
    
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
            
            default: // Report error if inserted sentinel is <0 or >15.
            {
                cout << "Invalid number! Insert an integer between 0 and 15.\n" << endl;
                break;
            }
        }
    }
    
    // End the program
    cout << "The End!" << endl;
    
    return 0;
}
