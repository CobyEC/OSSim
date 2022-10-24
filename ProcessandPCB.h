//Coby Cockrell
//10/13/2022 --- 10/15/2022REDO
//This is the header file for the Process class

#ifndef process_H
#define process_H
#ifndef PCB_H
#define PCB_H

using namespace std;


enum ProcStates { New, Ready, Run, Wait, Exit };

class PCB
{
private:
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

	void PrintPCB();            //Function to Print the PCB
};


class process {

private:
	//Tactic: 1 = Calc, 2 = IO, 3 = Fork

	PCB APCB;
	vector<int> OP;
	vector<int> RunCyc;
	vector<int> Min;
	vector<int> Max;

public:

	//Base Constructor
	process();


	//Constructor to setup based on a template
	process(ifstream&);

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
	int PrMemSize();

	//This function increases the PCB size 
	void Inccyc();

	//This function Saves the context of the process to the memory
	void ContextSwitch(ProcStates, int, int, int); 


};
#endif
#endif