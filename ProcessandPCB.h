//Coby Cockrell
//10/13/2022 --- 10/15/2022REDO
//This is the header file for the Process class

#ifndef process_H
#define process_H
#ifndef PCB_H
#define PCB_H

#include <fstream>
#include <vector>
using namespace std;


enum ProcStates { New, Ready, Run, Wait, Exit };

class PCB
{
private:
	float ProcessID = 0.0;   //This is my process ID, uniqe to each process
	ProcStates state; // This is my state variable for the process
	int Op;           //This keeps track of the operation in the vector we're in
	int cyclesIn;          //This keeps track of the number of cycles into the process Op, this will be reset upon an operation switch
	int Memsize;           //This is the memory size of the process

public:
	PCB();         //Base constructor

	PCB(int);      //Constructor with input memory size

	~PCB();        //Base deconstructor

	ProcStates getState();       //Function to get the state

	int getCycIn();             //Function to get the cycles in

	int getMem();               //Function to get the Memory usage

	int getOp();                //Function to get the OperationNumber

	void setOp(int);             //Function to set the OperationNumber

	void setCycIn(int);          //Function to set the Cycle count

	void setState(ProcStates);  //Function to set the State

	void IncCyc();               //Function to increase the Cycle count

	void setMem(int);           //Function to set the Memory size

	void setID(float);          //Function to set the PCB ID

	float getID();              //Function to get the PCB ID

	void PrintPCB();            //Function to Print the PCB
};


class process {

private:
	//Tactic: 1 = Calc, 2 = IO, 3 = Fork

	PCB APCB;    //My PCB object for the process
	vector<int> OP;     //Vector of operations to perform
	vector<int> RunCyc;  //the actual cycles assigned to run
	vector<int> Min;      //The Minimum cycles needed for the process
	vector<int> Max;      //The Maximum cycles needed for the process

	process *NEXTProcess;

public:

	//Base Constructor
	process();


	//Constructor to setup based on a template
	process(ifstream&, process *);

	//Base Deconstructor
	~process();

	//This process prints the operation and respective cycles corresponding to this
	void PrintProcess();

	//This function returns the OP vector index
	int getOPVec(int);

	//This function returns the RunCyc count
	int getRCyc(int);

	//This function returns the PCB State
	ProcStates getPCBState();

	//This function sets the PCB State
	void setPCBState(ProcStates);

	//This function returns the PCB Operation number it is on
	int getPCBOp();

	//This function sets the PCB Op number
	void IncPCBOp();

	//This function returns the PCB Cycles it is on
	int getPCBCyclesIn();

	//This function is the random number generator with input low and high 
	int RandNum(int, int);

	//This function prints out the poeration type given an integer
	void PrintOp(int Op);

	//This function gets the memory size of the Process in it's operation vector 
	int getMemSize();

	//This function increases the PCB size 
	void Inccyc();

	//This function Saves the context of the process to the memory
	void ContextSwitch(ProcStates, int, int, int);

	//This function get the next process in the list
	process *getNEXTProc();

	//This function simply adds the next process node to the NEXT pointer
	void setNEXTProc(process*);

	//This function sets the PCB ID
	void setPCBID(float);

	//This function gets the PCB ID
	float getPCBID();

	//This function translates the state variable into text
	void CurrStatePrint();

	//This function prints the PCB using it's class function
	void PrintProcPCB();


};

class LinkedProcesses {
private:
	process* HEAD;
public:
	//base constructor for the linkes processes
	LinkedProcesses();

	//base deconstructor
	~LinkedProcesses();

	//This function will add a process to the head of the list NOTE:This is required we use the XML input format
	void pushProc(ifstream &);

	//This function removes a node from the list
	void popProc();

	//This function returns the number of processes in the list
	int ListLength();

	//This function assigns a process a unique ID, but checking if ID is already asigned, once a process is assigned an ID it transitions from the New into the ready state
	void setProcID();

	//This function returns the process from it's ID if it exists
	void FindProc(float);

	//This function Prints all the processes and their respective information (ID/ State/ CycIn/ MemSize)
	void PrintList();

};
#endif
#endif
