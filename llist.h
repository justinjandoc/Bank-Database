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
//  FILE:        llist.h
//
//  DESCRIPTION:
//   This is the llist header file used to declare the functions
//   addRecord, printAllRecords, findRecord, deleteRecord, readfile,
//   writefile, and cleanup functions.
//
****************************************************************/

#include <iostream>

#ifndef LLIST_H
#define LLIST_H
#include "record.h"

class llist
{
private:
    record *    start;
    char        filename[16];
    int         readfile();
    int         writefile();
    void        cleanup();

public:
    llist();
    llist(char[]);
    ~llist();
    int addRecord(int, char [],char []);
    int findRecord(int);
    void printAllRecords();
    int deleteRecord(int);

    llist(const llist & copy);
    llist& operator = (const llist&);
    friend std::ostream & operator << (std::ostream&, const llist&);
};

#endif
