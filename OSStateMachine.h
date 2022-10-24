//Coby Cockrell
//10/15/2022
//Purpose: This is the header to the state machine class, The state machine will handle processes and depending on the 
//lifecycle, update the states, and incriment a counter.
#include "ProcessandPCB.h"


class OSStateMachine {
private:
    ProcStates CurrState;  //Variable for the current state
    process CurrPr;        //Variable for the current process

public:
    OSStateMachine();  //Base constructor for the Statemachine class

    ~OSStateMachine();  //Base Deconstructor for the Statemachine class

    void setCurSt(ProcStates);  //Function to set the Current state

    void setCurPr(process);  //Function to set the Current process

    int RunSim(process);  //Runs a cycle of the simulation
};