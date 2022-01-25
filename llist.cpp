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
//  FILE:        llist.cpp
//
//  DESCRIPTION:
//   This file defines the functions declared in llist.h.
//   It is the back end for the bank project.
//
****************************************************************/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "llist.h"

/*****************************************************************
//
//  Constructor name: llist
//  
//  DESCRIPTION:   This constructor is called when
//                 the list of records is created.
//
//  Parameters:    no parameters
//
//  Return values: constructor
//
****************************************************************/

llist::llist()
{
#ifdef DEBUGMODE
    std::cout << std::endl << "----------DEBUG----------" << std::endl;
    std::cout << "Constructor called: llist" << std::endl;
    std::cout << "-------------------------" << std::endl << std::endl;
#endif

    this->start = NULL;
    strcpy(this->filename, "data.txt");
    readfile();
}

/*****************************************************************
//
//  Constructor name: llist
//  
//  DESCRIPTION:   This constructor is called when
//                 the list of records is created with a file name.
//
//  Parameters:    dataFile (char[]) : the file containing records
//
//  Return values: constructor
//
****************************************************************/

llist::llist(char dataFile[])
{
#ifdef DEBUGMODE
    std::cout << std::endl << "----------DEBUG----------" << std::endl;
    std::cout << "Constructor called: llist" << std::endl << std::endl;
    std::cout << "Parameters:" << std::endl;
    std::cout << "char dataFIle[]" << std::endl << std::endl;
    std::cout << "Values:" << std::endl;
    std::cout << "dataFile[]: " << dataFile << std::endl;
    std::cout << "-------------------------" << std::endl << std::endl;
#endif

    std::cout << "file constructor\n";
    this->start = NULL;
    strcpy(this->filename, dataFile);
    readfile();
}

/*****************************************************************
//
//  Constructor name: llist
//  
//  DESCRIPTION:   This is a copy of the first constructor.
//
//  Parameters:    copy (const llist&) : copy of the object
//
//  Return values: constructor
//
****************************************************************/

llist::llist(const llist & copy)
{
#ifdef DEBUGMODE
    std::cout << std::endl << "----------DEBUG----------" << std::endl;
    std::cout << "Copy Constructor called: llist" << std::endl;
    std::cout << "-------------------------" << std::endl << std::endl;
#endif

    this->start = copy.start;
    readfile();
}

/*****************************************************************
//
//  Destructor name: ~llist
//  
//  DESCRIPTION:   This destructor is called before the program closes.
//
//  Parameters:    no parameters
//
//  Return values: constructor
//
****************************************************************/

llist::~llist()
{
#ifdef DEBUGMODE
    std::cout << std::endl << "----------DEBUG----------" << std::endl;
    std::cout << "Destructor called: ~llist" << std::endl;
    std::cout << "-------------------------" << std::endl << std::endl;
#endif
    writefile();
    cleanup();
}

/*****************************************************************
//
//  Function name: ostream& operator<<
//  
//  DESCRIPTION:   This function creates overloads the << operator
//                 and replaces the printAllRecords function call.
//                 It is basically a copy paste of the printAllRecords
//                 function, but everything is stored in the parameter
//                 variable and is printed at once.
//
//  Parameters:    ecPrint (ostream&) : holds everything to be printed
//                 ecList (const llist&) : connection to the llist object
//
//  Return values: none
//
****************************************************************/

std::ostream& operator<<(std::ostream& ecPrint, const llist& ecList)
{
#ifdef DEBUGMODE
    std::cout << std::endl << "----------DEBUG----------" << std::endl;
    std::cout << "Function called: ostream& operator<<" << std::endl << std::endl;
    std::cout << "Parameters:" << std::endl;
    std::cout << "ostream& ecPrint" << std::endl;
    std::cout << "const llist& ecList" << std::endl << std::endl;
    std::cout << "-------------------------" << std::endl << std::endl;
#endif

    struct record *temp;
    int breakLoop;
    temp = ecList.start;
    breakLoop = 0;

    while (breakLoop == 0)
    {
        if (ecList.start == NULL)
        {
            ecPrint << std::endl << "---There are no records---";
            ecPrint << std::endl << std::endl;
            breakLoop = 1;
        }
        else if (temp->next != NULL)
        {
            ecPrint << "-----Record-----" << std::endl;
            ecPrint << temp->accountno << std::endl;
            ecPrint << temp->name << std::endl;
            ecPrint << temp->address << std::endl;
            ecPrint << "----------------" << std::endl << std::endl;

            temp = temp->next;
        }
        // end of list
        else if (temp->next == NULL)
        {
            ecPrint << "-----Record-----" << std::endl;
            ecPrint << temp->accountno << std::endl;
            ecPrint << temp->name << std::endl;
            ecPrint << temp->address << std::endl;
            ecPrint << "----------------" << std::endl << std::endl;

            breakLoop = 1;
        }
    }
    return ecPrint;
}

/*****************************************************************
//
//  Function name: addRecord
//  
//  DESCRIPTION:   This function creates a new record based on the
//                 inputs from user_interface.
//
//  Parameters:    uaccountno (int) : the user inputted account number
//                 uname (char[]) : the user inputted name
//                 uaddress (char[]) : the user inputted address
//
//  Return values: 0 : sucess! the record was added
//                -1 : the record was not able to be added
//
****************************************************************/

int llist::addRecord(int uaccountno, char uname[], char uaddress[])
{
#ifdef DEBUGMODE
    std::cout << std::endl << "----------DEBUG----------" << std::endl;
    std::cout << "Function called: addRecord" << std::endl << std::endl;
    std::cout << "Parameters:" << std::endl;
    std::cout << "int uaccountno" << std::endl;
    std::cout << "char uname[]" << std::endl;
    std::cout << "char uaddress[]" << std::endl << std::endl;
    std::cout << "Values:" << std::endl;
    std::cout << "uaccountno: " << uaccountno << std::endl;
    std::cout << "uname[]: " << uname << std::endl;
    std::cout << "uaddress: " << std::endl << uaddress << std::endl;
    std::cout << "-------------------------" << std::endl << std::endl;
#endif

    struct record * temp;
    struct record * current;
    struct record * newRec;
    int ret, breakLoop, insert;
    ret = 0;
    breakLoop = 0;
    insert = 0;
    temp = start;
    current = start;
    newRec = start;

    if (start == NULL)
    {
        start = new struct record;
        newRec = start;
        newRec->next = NULL;

        newRec->accountno = uaccountno;
        strcpy(newRec->name, uname);
        strcpy(newRec->address, uaddress);
        ret = 0;
    }
    else
    {
        while (breakLoop == 0)
        {
            if (temp != NULL)
            {
                // duplicate
                if (temp->accountno == uaccountno)
                {
                    ret = -1;
                    breakLoop = 1;
                }
                else if (temp->accountno < uaccountno)
                {
                    insert = 1;
                    breakLoop = 1;
                }
                else if (temp->accountno > uaccountno)
                {
                    temp = temp->next;
                }
            }
            // uaccountno is the smallest and is at the end of the list
            else
            {
                insert = 1;
                breakLoop = 1;
            }
        }
    }
    if (insert == 1)
    {
        breakLoop = 0;
        while (breakLoop == 0)
        {
            if (current->next == temp)
            {
                newRec = new struct record;
                newRec->next = temp;
                current->next = newRec;
                newRec->accountno = uaccountno;
                strcpy(newRec->name, uname);
                strcpy(newRec->address, uaddress);
                breakLoop = 1;
            }
            else if (temp == start)
            {
                newRec = new struct record;
                newRec->next = temp;
                start = newRec;
                newRec->accountno = uaccountno;
                strcpy(newRec->name, uname);
                strcpy(newRec->address, uaddress);
                breakLoop = 1;
            }
            else
            {
                current = current->next;
            }
        }
    }
    return ret;
}

/******************************************************************
//
//  Function name: printAllRecords
//  
//  DESCRIPTION:   This function displays all of the saved records.
//
//  Parameters:    no parameters
//
//  Return values: void function
//
****************************************************************/

void llist::printAllRecords()
{
#ifdef DEBUGMODE
    std::cout << std::endl << "----------DEBUG----------" << std::endl;
    std::cout << "Function called: printAllrecords" << std::endl;
    std::cout << "-------------------------" << std::endl << std::endl;
#endif

    struct record *temp;
    int breakLoop;
    temp = start;
    breakLoop = 0;

    while (breakLoop == 0)
    {
        if (start == NULL)
        {
            std::cout << std::endl << "---There are no records---";
            std::cout << std::endl << std::endl;
            breakLoop = 1;
        }
        else if (temp->next != NULL)
        {
            std::cout << "-----Record-----" << std::endl;
            std::cout << temp->accountno << std::endl;
            std::cout << temp->name << std::endl;
            std::cout << temp->address << std::endl;
            std::cout << "----------------" << std::endl << std::endl;

            temp = temp->next;
        }
        // end of list
        else if (temp->next == NULL)
        {
            std::cout << "-----Record-----" << std::endl;
            std::cout << temp->accountno << std::endl;
            std::cout << temp->name << std::endl;
            std::cout << temp->address << std::endl;
            std::cout << "----------------" << std::endl << std::endl;

            breakLoop = 1;
        }
    }
}

/******************************************************************
//
//  Function name: findRecord
//  
//  DESCRIPTION:   This function takes a user's account number and
//                 searches for any records with that number.
//                 
//  Parameters:    uaccountno (int) : the user inputted account number 
//
//  Return values: 0 : success! record was found
//                -1 : no record was found
//
****************************************************************/

int llist::findRecord(int uaccountno)
{
#ifdef DEBUGMODE
    std::cout << std::endl << "----------DEBUG----------" << std::endl;
    std::cout << "Function called: findRecord" << std::endl << std::endl;
    std::cout << "Parameters:" << std::endl;
    std::cout << "int uaccountno" << std::endl << std::endl;
    std::cout << "Values:" << std::endl;
    std::cout << "uaccountno: " << uaccountno << std::endl;
    std::cout << "-------------------------" << std::endl << std::endl;
#endif

    struct record * temp;
    int ret, breakLoop;
    ret = 0;
    breakLoop = 0;
    temp = start;

    // there is no list
    if (start == NULL)
    {
        ret = -1;
    }
    else
    {
        while (breakLoop == 0)
        {
            // the record doesn't exist
            if (temp == NULL)
            {
                ret = -1;
                breakLoop = 1;
            }
            else if (temp->accountno == uaccountno)
            {
                std::cout << std::endl;
                std::cout << "-----Record-----" << std::endl;
                std::cout << temp->accountno << std::endl;
                std::cout << temp->name << std::endl;
                std::cout << temp->address << std::endl;
                std::cout << "----------------" << std::endl << std::endl;

                breakLoop = 1;
                ret = 0;
            }
            else
            {
                temp = temp->next;
            }
        }
    }
    return ret;
}

/******************************************************************
//
//  Function name: deleteRecord
//  
//  DESCRIPTION:   This function takes a user's account number and
//                 deletes the record associated with it.
//
//  Parameters:    uaccountno (int) : the user inputted account number
//
//  Return values: 0 : success! the record was deleted
//                -1 : no record was deleted
//
****************************************************************/

int llist::deleteRecord(int uaccountno)
{
#ifdef DEBUGMODE
    std::cout << std::endl << "----------DEBUG----------" << std::endl;
    std::cout << "Function called: deleteRecord" << std::endl << std::endl;
    std::cout << "Parameters:" << std::endl;
    std::cout << "int uaccountno" << std::endl << std::endl;
    std::cout << "Values:" << std::endl;
    std::cout << "uaccountno: " << uaccountno << std::endl;
    std::cout << "-------------------------" << std::endl << std::endl;
#endif

    struct record * temp;
    struct record * current;
    int ret, breakLoop;
    ret = 0;
    breakLoop = 0;
    temp = start;
    current = start;

    // there is no list
    if (start == NULL)
    {
        ret = -1;
    }
    else
    {
        while (breakLoop == 0)
        {
            // the record doesn't exist
            if (temp == NULL)
            {
                ret = -1;
                breakLoop = 1;
            }
            else if (temp->accountno == uaccountno)
            {
                while (breakLoop == 0)
                {
                    if (current->next == temp)
                    {
                        current->next = temp->next;
                        delete(temp);
                        breakLoop = 1;
                    }
                    else if (temp == start)
                    {
                        start = temp->next;
                        delete(temp);
                        breakLoop = 1;
                    }
                    else
                    {
                        current = current->next;
                    }
                }
                ret = 0;
            }
            else
            {
                temp = temp->next;
            }
        }
    }
    return ret;
}

/*****************************************************************
//
//  Function name: readfile
//
//  DESCRIPTION:   This function reads from a file and adds the records
//                 on the file to the list.
//
//  Parameters:    no parameters
//
//  Return values:  0 : sucess! the file was read and a list was created
//                 -1 : file was not open
//
****************************************************************/

int llist::readfile()
{
#ifdef DEBUGMODE
    std::cout << std::endl << "----------DEBUG----------" << std::endl;
    std::cout << "Function called: readfile" << std::endl;
    std::cout << "-------------------------" << std::endl << std::endl;
#endif

    std::ifstream datafile(filename);

    int faccNum, ret, quit;
    char fname[25];
    char faddress[50];
    char store[50];

    if (datafile.is_open())
    {
        // checks if next character is end of file
        while (datafile.peek() != EOF)
        {
            quit = 0;

            datafile.get(store, 50);
            datafile.clear();
            datafile.ignore();

            datafile >> faccNum;
            datafile.clear();
            datafile.ignore();

            datafile.get(fname, 25);
            datafile.clear();
            datafile.ignore();

            datafile.get(faddress, 50);
            datafile.clear();
            datafile.ignore();
            strcpy(store, faddress);

            while (quit == 0)
            {
                datafile.get(faddress, 50);
                datafile.clear();
                datafile.ignore();

                if (strstr(faddress, "----------------"))
                {
                    quit = 1;
                    datafile.clear();
                    datafile.ignore();
                }
                else
                {
                    strcat(store, "\n");
                    strcat(store, faddress);
                }
            }
            strcpy(faddress, store);

            addRecord(faccNum, fname, faddress);
        }
        datafile.close();
    }
    else
    {
        ret = - 1;
    }
    return ret;
}

/*****************************************************************
//
//  Function name: writefile
//
//  DESCRIPTION:   This function creates a file and prints the
//                 list of records to that file.
//
//  Parameters:    no parameters
//
//  Return values:  0 : sucess! the list of records has been witten
//                      on the file
//                 -1 : file was not open
//
****************************************************************/

int llist::writefile()
{
#ifdef DEBUGMODE
    std::cout << std::endl << "----------DEBUG----------" << std::endl;
    std::cout << "Function called: writefile" << std::endl;
    std::cout << "-------------------------" << std::endl << std::endl;
#endif

    struct record * temp;
    int ret;
    temp = start;
    ret = 0;

    std::ofstream datafile;
    datafile.open(filename);

    if (datafile.is_open())
    {
        while (temp != NULL)
        {
            datafile << "-----Record-----" << std::endl;
            datafile << temp->accountno << std::endl;
            datafile << temp->name << std::endl;
            datafile << temp->address << std::endl;
            datafile << "----------------" << std::endl;

            temp = temp->next;
        }
        datafile.close();
    }
    else
    {
        ret = -1;
    }
    return ret;
}

/******************************************************************
//
//  Function name: cleanup
//  
//  DESCRIPTION:   This function deletes the linked list when
//                 the user chooses to quit and sets start to NULL.
//
//  Parameters:    no parameters
//
//  Return values: void function
//
****************************************************************/

void llist::cleanup()
{
#ifdef DEBUGMODE
    std::cout << std::endl << "----------DEBUG----------" << std::endl;
    std::cout << "Function called: cleanup" << std::endl;
    std::cout << "-------------------------" << std::endl << std::endl;
#endif

    struct record * temp;
    temp = start;

    while (start != NULL)
    {
        temp = temp->next;
        delete(start);
        start = temp;
    }
}
