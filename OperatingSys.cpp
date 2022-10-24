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

//UserInterface original functionality --load, --RunNumCyc, --Stat, --help, --Templates
int UserInterface(int NumP) {
    int input;
    cout << "\nWelcome to Coby's first UI and OS simulator..... \n";
    cout << "Enter command  (Enter help for more info.): ";
    cin >> input;

    return input;
}



int main()
{

    
    //Now testing the process class
    ifstream TestFile("XMLFile.xml");
    process TestOne = process(TestFile);
    
    TestOne.PrintProcess();

    ifstream TestFile2("XMLFile2.xml");
    process TestTwo = process(TestFile2);
    TestTwo.PrintProcess();


    TestOne.PrintProcess();
   
    TestOne.~process();
    TestTwo.~process();
}




