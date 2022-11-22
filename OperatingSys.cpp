//Coby Cockrell
//10/11/2022
//Purpose: This is the main program that I will test all the other operations from.

#include <iostream>
#include <fstream>
#include <vector>
#include "rapidxml.hpp"
#include "ProcessandPCB.h"

using namespace std;
using namespace rapidxml;


xml_document<> doc;
xml_node<>* rt_node = NULL;

int NumProcesses;

//UserInterface original functionality --load, --RunNumCyc, --Stat, --help, --Templates, --display proc 
int UserInterface(int NumP) {
    int input;
    cout << "\nWelcome to Coby's first UI and OS simulator..... \n";
    cout << "Enter command currently  (Enter 5 -(help) for more info.): ";
    cin >> input;

    return input;
}



int main()
{
    //List testing object
    LinkedProcesses list;



    //Now testing the process class
    ifstream TestFile("XMLFile.xml");

    process TestOne(TestFile, nullptr);
    TestOne.PrintProcess();

    ifstream TestFile2("XMLFile2.xml");

    process TestTwo(TestFile2, nullptr);


    TestTwo.PrintProcess();
    TestOne.PrintProcess();

    TestOne.~process();
    TestTwo.~process();

    //Reset both the files back to the beginning
    TestFile.seekg(0, ios::beg);
    TestFile2.seekg(0, ios::beg);

    list.pushProc(TestFile);
    list.setProcID();
    list.pushProc(TestFile2);
    list.setProcID();
    cout << " The length of the list is: " << list.ListLength() << endl;

    list.PrintList();
}



