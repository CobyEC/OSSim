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

//UserInterface original functionality --load, --RunNumCyc, --Stat, --help, --Templates, --display proc recieves the input and verifies the option
int UserInterface() {
    string input;
    while (1) {
        cout << "\nWelcome to Coby's first UI and OS simulator..... \n";
        cout << "Enter command currently  (Enter (help) for more info.): \n--";
        cin >> input;

        if (input == ("load") || ("RunNumCyc") || ("stat") || ("help") || ("templates") || ("display proc")) {
            return 0;
        }
        else if (input == "RunNumCyc") {
            return 1;
        }
        else if (input == "stat") {
            return 2;
        }
        else if (input == "help") {
            return 3;
        }

        else if (input == "templates") {
            return 4;
        }
        else if (input == "display proc") {
            return 5;
        }
        else {
            cout << "Error, command did not match any of the possible matches\n";
        }
    }
}


//void SpawnMultiProcesses(LinkedProcesses List, string TempNum, int num)  This function iterates and spawns the required number of processes based on a template
void SpawnMultiProcesses(LinkedProcesses LIST, string TempNum, int num) {
    ifstream InTemplate(TempNum);
    
    for (int i = 0; i < num; i++) {
        LIST.pushProc(InTemplate);
        LIST.setProcID();
        InTemplate.seekg(0, ios::beg);
        cout << "i" << endl;
    }
    cout << "Processes created Successfully\n";
}



int main()
{
    //List testing object
    LinkedProcesses list;
    vector <string> TemplateList;


    //Now testing the process class
    ifstream TestFile("XMLFile.xml");

    process TestOne(TestFile, nullptr);
    TestOne.PrintProcess();

    ifstream TestFile2("XMLFile2.xml");

    process TestTwo(TestFile2, nullptr);
    
    //Adding my two templates to the vector
    TemplateList.push_back("XMLFile.xml");
    TemplateList.push_back("XMLFile2.xml");

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

    while (true) {
        switch (UserInterface()) {
            //Load
        case 0:
            int NumProc;
            int TempSel;
            cout << "Loading new Processes please enter the template and the number of selected processes to be created.\n";
            //Printing all my Templates
            for (int i = 0; i < TemplateList.size(); i++) {
                cout << "Number: " << i << "   File: " << TemplateList[i] << endl;
            }
            cout << "Template Number: ";
            cin >> TempSel;

            //Error checking the input for the template 
            while (TempSel < 0 || TempSel > TemplateList.size()) {
                cout << "Error, Index not correct, please choose again...\n";
                cin >> TempSel;
            }

            //Now asking the input for the number of processes to be created
            cout << "\n Please Enter the number of processes to be created : ";
            cin >> NumProc;

            //Error checking the input for the number of processes
            while (NumProc < 0) {
                cout << "Error, Index not correct, please choose again...\n";
                cin >> NumProc;
            }
            //using the function to spawn multiple processes to the list
            SpawnMultiProcesses(list, TemplateList[TempSel], NumProc);

            break;
            //RunNumCyc
        case 1:

            break;
            //stat
        case 2:

            break;
            //help
        case 3:

            break;
            //templates
        case 4:

            break;
            //display proc
        case 5:

            break;
        }
    }
}



