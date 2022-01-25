/*****************************************************************
//
//  NAME:        Justin Jandoc
//  
//  HOMEWORK:    Project 2
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        November 27, 2021
//
//  FILE:        record.h
//
//  DESCRIPTION:
//   This is the record header file used to define the structure.
//
****************************************************************/

#ifndef RECORD_H
#define RECORD_H

struct record
{
    int accountno;
    char name[25];
    char address[50];
    struct record* next;
};

#endif
