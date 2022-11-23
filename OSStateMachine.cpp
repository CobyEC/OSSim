//Coby Cockrell
//10/20/2022
//Purpose: This file is the implimentation of the OSS state machine THIS IS A RESET BUILD, PREVVIOUS STRUCTURAL DEFINITIONS LED TO IMPOSSIBLE IMPLIMENTATION

#include "OSStateMachine.h"

using namespace std;

//OSSStateMachine()   This function is the Base constructor for the simulator
OSStateMachine::OSStateMachine() {

}

//~OSStateMachine()   This function is the Base deconstructor for the simulator
OSStateMachine::~OSStateMachine() {

}

//void setCurSt(ProcStates)  This function sets the current state
void OSStateMachine::setCurSt(ProcStates st) {
	this->CurrState = st;
}

//void setCurPr(process)  This function sets the current process
void OSStateMachine::setCurPr(process pr) {
	this->CurrPr = pr;
}

//int RunSim(process)   This function is the single cycle simulation of an input process 
int OSStateMachine::RunSim(process proc) {
	this->setCurPr(proc);   //setting the current process from input
	this->setCurSt(proc.getPCBState());    //setting the current state from my function inside my process accessing the PCB

	//first if in the new state, change to the ready state in this cycle
	if (this->CurrState = New) {
		this->CurrState = Ready;
		this->CurrPr.ContextSwitch(this->CurrState, 0, 0, 0);
	}
	//second if in the ready state, change to the run state in this cycle
	else if (this->CurrState = Ready) {
		this->CurrState = Run;
		this->CurrPr.ContextSwitch(this->CurrState, this->CurrPr.getPCBOp(), this->CurrPr.getPCBCyclesIn(), this->CurrPr.getMemSize());
	}
	//third if, in this process, it is on the "CPU", and I test the different processes respective ends 
	// 
	//THIS IS THE MAIN ISSUE: If i need processes to update new and ready outside the statemachine, do I initialize this elsewhere?
	//Idea was to test if at the end which was the next operation and then assign the next state, but in doing so in my previous code, I would run out of data and have to move some to the heap.

	else if (this->CurrState = Run) {
		//This if statement tests if the process has reached the end of it's cycle count 
		if (proc.getPCBCyclesIn() >= proc.getRCyc(proc.getPCBOp())) {
			//If so, incriment the Operation, change the state, reset the value in the PCB for Cycles
			//this->CurrPr.ContextSwitch(this->)

		}
	}
	else if (this->CurrState = Wait) {

	}
	else if (this->CurrState = Exit) {

	}
	return 0;
}
