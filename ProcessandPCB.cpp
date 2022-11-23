//Coby Cockrell
//10/16/2022 ---10/19/2022REDO
//Purpose: This is the implimentation of the ProcessandPCB.h file, In this file I outline the constructors, the printing file, and basic components of the process

#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include "ProcessandPCB.h"
#include "rapidxml.hpp"

using namespace std;
using namespace rapidxml;


//process(), this is the default constructor for the class
process::process() {

    //Creating buffers and loading one calculate operation with min of 0 and max of 2


    //Now calling each member and saving the converted string 
    this->OP.push_back(1);
    this->Min.push_back(0);
    this->RunCyc.push_back(1);
    this->Max.push_back(2);
    this->NEXTProcess = nullptr;


}

//Process esentially takes the fileXML name, then according to the format, inputs the corresponding operations, and cycles
//updated to also take the next node as a parameter
// How OP is defined 1 = Calc, 2 = IO, 3 = Fork
//Assigning temporaries to compare in XML input
process::process(ifstream& File, process* next = nullptr) {

    this->NEXTProcess = next;
    xml_document<> doc;
    xml_node<>* rtnode = NULL;
    string OPCaltemp = "CALCULATE";

    string OPIOtemp = "I/O";

    string OPFORKtemp = "FORK";
    //Temp for my input 
    string Tstring;


    vector<char> buffer((istreambuf_iterator<char>(File)), istreambuf_iterator<char>());
    buffer.push_back('\0');

    // Parse buffer
    doc.parse<0>(&buffer[0]);

    // Find out the root node
    rtnode = doc.first_node("TemplateData");

    // Iterate over the op nodes in for loop
    for (xml_node<>* op_nodes = rtnode->first_node("Operation"); op_nodes; op_nodes = op_nodes->next_sibling())
    {
        //cout << "In the class loop\n OP type: " << op_nodes->first_attribute("Op_type")->value() << endl;
        //Place the Operation data inside the node using this refrence to the vector

     //   cout << OPCaltemp << "..." << endl;
     //   cout << op_nodes->first_attribute("Op_type")->value() << "..." << endl;
        Tstring = op_nodes->first_attribute("Op_type")->value();
        if (Tstring == OPCaltemp) {

            this->OP.push_back(1);
        }
        else if (Tstring == OPIOtemp) {
            this->OP.push_back(2);
        }
        else if (Tstring == OPIOtemp) {
            this->OP.push_back(3);
        }
        else {
            cout << "Warning Template Type: " << op_nodes->first_attribute("Op_type")->value() << "  NOT READABLE (Please use CALCULATE, I/O, and FORK)\n";
            this->OP.push_back(0);
        }
        //   coub t << "VECTOR:  " << this->OP[0] << endl;

           //Iterate through the min and max of the node print out data for demo
        for (xml_node<>* op_mincyc = op_nodes->first_node("min"); op_mincyc; op_mincyc = op_mincyc->next_sibling())
        {
            this->Min.push_back(atoi(op_mincyc->value()));
            op_mincyc = op_mincyc->next_sibling();
            this->Max.push_back(atoi(op_mincyc->value()));

        }

    }
    //cout << "\n  " << this->OP.size() << endl;
    //Now looping and assigning each operation a random number of cycles
    for (int i = 0; i < this->OP.size(); i++) {

        //Using the RandNum function to assign the operation withe the corresponding randon number between Min and Max 
        this->RunCyc.push_back(RandNum(this->Min[i], this->Max[i]));
    }

    //Finding the size of the process getMemSize(), then creating the Control Block PCB()
    this->APCB = PCB(this->getMemSize());

}

//~process is the deconstructor for the class
process::~process() {
    cout << "Ending process X\n";
}


//PrintProcess goes through each vector and prints out the corresponding data in a loop
void process::PrintProcess() {
    int i = 0;
    //Declaring temporaries to copy the contents of the process
    //vector<char*> tempOP = this->OP;
    //vector<char*> tempMIN = this->Min;
    //vector<char*> tempMAX = this->Max;
    // 
    //Print the PCB
    this->APCB.PrintPCB();
    cout << "\n----------------------    File Contents:    ----------------------\n";
    cout << "OpType        Min          Max        Assigned\n";

    //Looping until I reach the end of the process
    while (i < this->OP.size()) {
        PrintOp(this->OP[i]);
        cout << "             " << this->Min[i] << "            " << this->Max[i] << "            " << this->RunCyc[i] << endl;
        i++;
    }
    cout << "----------------------    End Of File    ----------------------\n\n";
    //clearing the temporaries
    //tempOP.clear();
    //tempMIN.clear();
    //tempMAX.clear();
}

//RandNum(int l, int h) 
//This function takes in low and high integers, and outputs a rendom integer in between them
int process::RandNum(int l, int h) {
    int Cycles;
    //cout << " LOW: " << l << "   HIGH: " << h << "  RAND: " << rand() << endl;
    Cycles = (l + (rand() % (h - l))); //random is set with the low as addition and modulo on the high
    return Cycles;
}

//PrintOp(int Op)
//This function prints the operation based on an input integer, it useses a simple if statement to compare int's
void process::PrintOp(int Op) {
    if (Op == 0) {
        cout << "Null OP";
    }
    else if (Op == 1) {
        cout << "CALC";
    }
    else if (Op == 2) {
        cout << "I/O";
    }
    else if (Op == 3) {
        cout << "FORK";
    }
    else {
        cout << "IDK WHAT HAPPENED...";
    }
}

//int getMemSize()   FFunction gets Memory by multiplying the length of the operation vector by the int corresponding designation
int process::getMemSize() {
    //cout << "MEMSIZE: " << this->OP.size() << endl;
    //cout << "INT size: " << sizeof(int) << endl;;
    int Stemp = this->OP.size() * sizeof(int);

    return Stemp;
}





//PCB() Base Constructor
PCB::PCB() {
    this->state = New;
    this->cyclesIn = 0;
    this->Memsize = 0;
    this->Op = 0;
}
//PCB() Base constructor, sets the PCB to first state, and sets the cycle run to 0, It also updates the total memory size of the process input as m
PCB::PCB(int m) {
    //Set the state to New, the cycles to zero, and get the memory size passed from the process
    this->state = New;
    this->cyclesIn = 0;
    this->Op = 0;
    this->Memsize = m;

}

//~PCB() Base Deconstructor
PCB::~PCB() {
    cout << "Ending PCB X \n";
}

//ProcStates getState()  This function simply returns the value of the PCB state for the process
ProcStates PCB::getState() {
    ProcStates tempst = this->state;
    return tempst;
}

//int getCycIn()   This function returns the value of the Cycles into the process
int PCB::getCycIn() {
    int tempcyc = this->cyclesIn;
    return tempcyc;
}

//int getMem()   This function returns the value of the memory size for the process
int PCB::getMem() {
    int tempMem = this->Memsize;
    return Memsize;
}

//void setState()  This function sets the state in the PCB
void PCB::setState(ProcStates st) {
    this->state = st;
}

//int getCycIn()   This function returns the value of the Cycles into the process
void PCB::setCycIn(int c) {
    this->cyclesIn = c;
}
//void IncCyc()    This functioon increases the cycle count
void PCB::IncCyc() {
    this->cyclesIn++;
}

//void setMem(int Mem)  This function checks the input memory size to make sure it is valid, and then stores the Memory size
void PCB::setMem(int Mem) {
    if (Mem < 0) {
        cout << "Error, PCB setMem()  got a negative input memory size!\n";
    }
    else {
        this->Memsize = Mem;
    }
}

//int getOp()   TThis function returns the operation number that the process in on
int PCB::getOp() {
    int Otemp = this->Op;
    return Otemp;
}

//void setOp(int o)  This function sets the Operation number the process is on in the template
void PCB::setOp(int o) {
    this->Op = o;
}

//void PrintPCB()   This function prints out the PCB class
void PCB::PrintPCB() {
    cout << "---------------------- PCB ----------------------\n";
    cout << "|| \n";
    cout << "|| Process State      :" << this->getState() << "    (0-4)  {New, Ready, Run, Wait, Exit} respectfully.\n";
    cout << "|| Operation #On      :" << this->getOp() << endl;
    cout << "|| Cycles In Operation:" << this->getCycIn() << endl;
    cout << "|| Memory Size        :" << this->getMem() << " Bytes\n\n";
}

//void setID(int id), this function sets the PCB ID according to the input id
void PCB::setID(float id) {
    this->ProcessID = id;
}

//float getID(), this function returns the Process's unique ID in the PCB
float PCB::getID() {
    return this->ProcessID;
}










//void ContextSwitch(ProcStates,  int, int, int )   This function is the "ContextSwitch" which assigns the PCB status of the process
void process::ContextSwitch(ProcStates St, int op, int cyc, int mem) {
    //Using the respectful set functions for each PCB member
    this->APCB.setState(St);
    this->APCB.setOp(op);
    this->APCB.setCycIn(cyc);
    this->APCB.setMem(mem);
}

//ProcStates getPCBState()   This function returns the process's respectful PCB using it's method
ProcStates process::getPCBState() {
    return this->APCB.getState();
}

//void setPCBState()   This function sets the state given the ProcStates type input
void process::setPCBState(ProcStates PSt) {
    this->APCB.setState(PSt);
}

//int getPCBOp()   This function returns the process's respectful operation number is in on
int process::getPCBOp() {
    return this->APCB.getOp();
}

//int getPCBCyclesIn()   This function returns the process's respectful cycle coount
int process::getPCBCyclesIn() {
    return this->APCB.getCycIn();
}

//int getOPVec(int)  This function returns the indexed OP vector operation number type
int process::getOPVec(int i) {
    return this->OP[i];
}

//int getRCyc(int)  This function returns the indexed Cycle time for the Operation it is on
int process::getRCyc(int i) {
    return this->RunCyc[i];
}

//void Inccyc()   This function increases the PCB cycle count through it's class function
void process::Inccyc() {
    this->APCB.IncCyc();
}

//void IncPCBOp()   This function increases the PCB Operation count
void process::IncPCBOp() {
    this->APCB.setOp((this->getPCBOp() + 1));
}


//process getNEXTProc()   This function simply returns the pointer to the next process using this->
process* process::getNEXTProc() {
    return this->NEXTProcess;
}

//process setNEXTProc()    This function sets the next node of the process using this->
void process::setNEXTProc(process* NEXT) {
    this->NEXTProcess = NEXT;
}

//void setPCBID(float id) this function takes in the id and further uses the setID function in the PCB class
void process::setPCBID(float id) {
    this->APCB.setID(id);
}

//float getPCBID()   this function returns the id by using the PCB's function of it's class
float process::getPCBID() {
    return this->APCB.getID();
}

//void CurrStatePrint()   this function gets the current state from the PCB, and then prints the corresponding text
void process::CurrStatePrint() {
    ProcStates temp = this->getPCBState();
    if (temp == New) {
        cout << "New";
    }
    else if (temp == Ready) {
        cout << "Ready";
    }
    else if (temp == Run) {
        cout << "Run";
    }
    else if (temp == Wait) {
        cout << "Wait";
    }
    else if (temp == Exit) {
        cout << "Exit";
    }
    else {
        cout << "Mmmmm... Doesn't have a state.";
    }
}

//void PrintProcPCB()   this function uses the processes PCB function declared in the PCB class
void process::PrintProcPCB() {
    this->APCB.PrintPCB();
}









//void LinkedProcesses()  Base constructor assugning the head  to nullptr
LinkedProcesses::LinkedProcesses() {
    this->HEAD = nullptr;
}

//void ~LinkedProcesses()  Base deconstructor, loops and pops until the end of the list
LinkedProcesses::~LinkedProcesses() {
    while (this->HEAD != nullptr) {
        popProc();
    }
}

//void pushProc(ifstream& )  This function uses the input XML ifstream file, and according constructor in the process clas
void LinkedProcesses::pushProc(ifstream& inFile) {
    this->HEAD = new process(inFile, this->HEAD);
}


//void popProc()  This function deletes an item if there are items in the list, it then assigns a temp to transfer the head and current next to
void LinkedProcesses::popProc() {
    process* temp;
    if (this->HEAD == nullptr) {
        cout << "THE LIST IS EMPTY!/n";
    }
    else {
        temp = this->HEAD;
        this->HEAD = this->HEAD->getNEXTProc();
        delete temp;
    }

}

//int ListLength()   This function iterates through the list and then returns the length through the iterator
int LinkedProcesses::ListLength() {
    int tempLen = 0;
    for (process* currPr = this->HEAD; currPr != nullptr; currPr = currPr->getNEXTProc()) {
        tempLen++;
    }
    return tempLen;
}

//void setProcID()   This function sets the Process's ID in the PCB block, first checking if there is a value, then 
void LinkedProcesses::setProcID() {

    //My temporaries to assign the random ID, as well as the low and high for the number
    float randtemp1;
    float low = 5.0;
    float high = 10000.0;

    //Temp for the while loop
    bool IDExists;


    //Checking if ID exists
    if (this->HEAD->getPCBID() != 0.0) {
        cout << "\nERROR: while trying to set the new process's ID... ID already found!!!\n";
        return;
    }
    else {
        //loop until ID is proven to be unique
        do {
            randtemp1 = (low + ((float(rand()) / high) * (high - low))); //random is set a simple manipulation of my previous randum number generation
            IDExists = false;

            //this loop iterates and checks if any ID exists
            for (process* currPr = this->HEAD; currPr != nullptr; currPr = currPr->getNEXTProc()) {
                if (currPr->getPCBID() == randtemp1) {
                    cout << "PCBID :: " << currPr->getPCBID() << endl;
                    IDExists = true;
                }
            }
        } while (IDExists);

        //Now that the ID is unique I can assign it to the process
        this->HEAD->setPCBID(randtemp1);
        //I assign the process to the ready state once it's creating and ID has now been complete
        this->HEAD->setPCBState(Ready);
        cout << "ID created for process : " << randtemp1 << endl;
    }
}


//void FindProc(float id)   this function find the process with the specific id if it exists, I iterate similiar to the assignment of the id
void LinkedProcesses::FindProc(float id) {

    bool IDFound = false;
    for (process *currPr = this->HEAD; currPr != nullptr; currPr = currPr->getNEXTProc()) {
        //If found, I print the Process ID, the PCB information, and the Process itself
        if (currPr->getPCBID() == id) {
            cout << "PCBID :: " << currPr->getPCBID() << "Found! \n";
            //set boolean value to true to I won't print the not found info at the end
            IDFound = true;
            cout << "Process Information:\n";
            cout << "-----------------------------------------------------------\n";
            cout << "ID: " << currPr->getPCBID() << "        ";
            currPr->PrintProcPCB();
            currPr->PrintProcess();
            cout << "-----------------------------------------------------------\n";
            break;
        }
    }

    if (!IDFound) {
        cout << "ERROR in finding the process, could not locate the id: " << id << endl;
    }
}

//void PrintList()   this function loops and prints all the processes critical information (ID/ State/ CycIn / Memsize)
void LinkedProcesses::PrintList() {
    int CurrentProcessNum = 1;
    if (this->ListLength() == 1) {
        cout << "\n-----------------PROCESS'S CONTAINED-----------------\n";
        cout << "Process " << CurrentProcessNum << endl;
        cout << "ID: " << this->HEAD->getPCBID() << "||  State: ";
        this->HEAD->CurrStatePrint();
        cout << "||  Cycles in state: " << this->HEAD->getPCBCyclesIn() << "||  Memory Size: " << this->HEAD->getMemSize() << endl;
        cout << "\n------------------------------------------------------\n";
    }
    else {
        cout << "\n-----------------PROCESS'S CONTAINED-----------------\n";
        for (process* currPr = this->HEAD; currPr != nullptr; currPr = currPr->getNEXTProc()) {
            cout << "Process " << CurrentProcessNum << endl;
            cout << "ID: " << currPr->getPCBID() << "||  State: ";
            this->HEAD->CurrStatePrint();
            cout << "||  Cycles in state: " << currPr->getPCBCyclesIn() << "||  Memory Size: " << currPr->getMemSize() << endl;
            CurrentProcessNum++;
        }
        cout << "\n------------------------------------------------------\n";

    }
}






