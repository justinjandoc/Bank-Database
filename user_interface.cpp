/*****************************************************************
//
//  NAME:        Justin Jandoc
//
//  HOMEWORK:    Project2
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        November 27, 2021
//
//  FILE:        user_interface.cpp
//
//  DESCRIPTION:
//   This file displays a menu of choices for the user to pick.
//   One the user picks an option, the program asks for the
//   required information (name, account number, and address).
//   The program then calls functions within llist.cpp.
//   When debugmode is turned on, the file prints out which functions
//   are being called, the parameters, and the values of the functions.
//
****************************************************************/

#include <iostream>
#include <iomanip>
#include <string.h>

#include "llist.h"


void getaddress(char[], int);

/*****************************************************************
//
//  Function name: main
//
//  DESCRIPTION:   This function prints a menu and redirects
//                 the user based on their input.
//
//  Parameters:    argc (int) : The number of elements in argv
//                 argv (char*[]) : An array of arguments passed
//                                  to the program.
//
//  Return values:  0 : sucess!
//
****************************************************************/

int main(int argc, char* argv[])
{
#ifdef DEBUGMODE
    std::cout << std::endl << "----------DEBUG MODE ENABLED----------" << std::endl <<std::endl;
#endif

    llist mylist;

    int accNum, add, printall, find, del, quit;
    char name[25];
    char address[50];
    char input[50];

    std::cout << "Hello, welcome to the bank." << std::endl << std::endl;

    do
    {
        accNum = 0;
        add = 0;
        printall = 0;
        find = 0;
        del = 0;
        quit = 0;

        // instructions
        std::cout << "Please choose from the list of options shown below." << std::endl;
        std::cout << "add:      Creates a new record for the database." << std::endl;
        std::cout << "printall: Displays all of the records within the database." << std::endl;
        std::cout << "find:     Displays records with certain account numbers." << std::endl;
        std::cout << "delete:   Deletes a record based on account number." << std::endl;
        std::cout << "quit:     Exits the program." << std::endl << std::endl;

        // user input
        std::cout << "Please type in your selected option: ";
        std::cin.get(input, 50);
        std::cin.clear();
        std::cin.ignore();

        std::cout << std::endl;

        // checks input
        if (strncmp(input, "add", strlen(input)) == 0)
        {
            add++;
        }
        else if (strncmp(input, "printall", strlen(input)) == 0)
        {
            printall++;
        }
        else if (strncmp(input, "find", strlen(input)) == 0)
        {
            find++;
        }
        else if (strncmp(input, "delete", strlen(input)) == 0)
        {
            del++;
        }
        else if (strncmp(input, "quit", strlen(input)) == 0)
        {
            quit++;
        }

        // checks which option is picked
        // add
        if (add > 0)
        {
            std::cout << "Please enter your name: ";
            std::cin.get(name, 25);
            std::cin.clear();
            std::cin.ignore();

            std::cout << "Please enter an account number: ";
            std::cin >> accNum;

            while (accNum <= 0 || std::cin.fail())
            {
                std::cout << "I'm sorry, your input is invalid. Please try again." << std::endl;
                std::cout << "Please enter an account number: ";
                std::cin.clear();
                std::cin.ignore(50, '\n');
                std::cin >> accNum;
            }
            std::cin.clear();
            std::cin.ignore();

            getaddress(address, accNum);

            if (mylist.addRecord(accNum, name, address) == 0)
            {
                std::cout << std::endl;
                std::cout << "---The record was added---" << std::endl;
            }
            else
            {
                std::cout << std::endl;
                std::cout << "---The record was not added---" << std::endl;
            }

            std::cout << std::endl << "You will now be redirected back to the menu.";
            std::cout << std::endl << std::endl;
        }
        // printall
        else if (printall > 0)
        {
            // mylist.printAllRecords();

            // overloading << extra credit
            std::cout << mylist;

            std::cout << std::endl << "You will now be redirected back to the menu.";
            std::cout << std::endl << std::endl;
        }
        // find
        else if (find > 0)
        {
            std::cout << "Please enter an account number: ";
            std::cin >> accNum;

            while (accNum <= 0 || std::cin.fail())
            {
                std::cout << "I'm sorry, your input is invalid. Please try again." << std::endl;

                std::cout << "Please enter an account number: ";
                std::cin.clear();
                std::cin.ignore(50, '\n');
                std::cin >> accNum;
            }
            std::cin.clear();
            std::cin.ignore();

            if (mylist.findRecord(accNum) == -1)
            {
                std::cout << std::endl;
                std::cout << "---No records were found---" << std::endl;
            }

            std::cout << std::endl << "You will now be redirected back to the menu.";
            std::cout << std::endl << std::endl;
        }
        // delete
        else if (del > 0)
        {
            std::cout << "Please enter an account number: ";
            std::cin >> accNum;

            while (accNum <= 0 || std::cin.fail())
            {
                std::cout << "I'm sorry, your input is invalid. Please try again." << std::endl;

                std::cout << "Please enter an account number: ";
                std::cin.clear();
                std::cin.ignore(50, '\n');
                std::cin >> accNum;
            }
            std::cin.clear();
            std::cin.ignore();

            if (mylist.deleteRecord(accNum) == 0)
            {
                std::cout << std::endl;
                std::cout << "---The record was deleted---" << std::endl;
            }
            else
            {
                std::cout << std::endl;
                std::cout << "---No records were deleted---" << std::endl;
            }

            std::cout << std::endl << "You will now be redirected back to the menu.";
            std::cout << std::endl << std::endl;
        }
        // quit
        else if (quit > 0)
        {
            std::cout << "The program will now close, thank you for your time.";
            std::cout << std::endl << std::endl;
        }
        // invalid
        else
        {
            std::cout << "I'm sorry, your input is invalid. Please try again.";
            std::cout << std::endl << std::endl;
        }
    }
    while (quit == 0);

    return 0;
}

/*****************************************************************
//
//  Function name: getaddress
//  
//  DESCRIPTION:   Gets the address for addRecord function.
//                 
//  Parameters:    address (char[]) : the address inputted by the user
//                 space (int) : the amount of free space
//
//  Return values: void function
//
****************************************************************/

void getaddress(char address[], int space)
{
#ifdef DEBUGMODE
    std::cout << std::endl << "----------DEBUG----------" << std::endl;
    std::cout << "Function called: getaddress" << std::endl << std::endl;
    std::cout << "Parameters:" << std::endl;
    std::cout << "char address[]" << std::endl;
    std::cout << "int space" << std::endl << std::endl;
    std::cout << "Values:" << std::endl;
    std::cout << "address[]: " << address << std::endl;
    std::cout << "space: " << space << std::endl;
    std::cout << std::endl << "-------------------------" << std::endl << std::endl;
#endif

    char store[50];

    int quit, size;
    quit = 0;
    space = 0;

    // debug mode stuff

    std::cout << "Please enter your address (enter '!!!' when you are finished):" << std::endl;
    std::cin.get(address, 50);
    std::cin.clear();
    std::cin.ignore();

    strcpy(store, address);

    while (quit == 0)
    {
        std::cin.get(address, 50);
        std::cin.clear();
        std::cin.ignore();

        // if the user doesnt quit, the new inputs get added on
        if (strstr(address, "!!!") && strlen(address) == 3)
        {
            quit++;
        }
        else
        {
            space = 50 - strlen(store) - 1;
            size = strlen(address);
            if (space < size)
            {
                strcat(store, "\n");
                strncat(store, address, space);
                std::cout << std::endl;
                std::cout << "I am sorry, your address was cut off as it is too long." << std::endl;
                quit++;
            }
            else
            {
                strcat(store, "\n");
                strcat(store, address);
            }
        }
    }
    strcpy(address, store);
}
