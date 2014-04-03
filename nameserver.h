#pragma once

_Task VendingMachine;
_Monitor Printer;

_Task NameServer {
    Printer &prt;
		unsigned int numVendingMachines;
		unsigned int numStudents;
		void main();
		VendingMachine** machineList;
		unsigned int machineCount;
		// unsigned int* studentAssign [numStudents];	//for assigning students to vending machines TODO: get this working
  public:
    NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents );
    void VMregister( VendingMachine *vendingmachine );
    VendingMachine *getMachine( unsigned int id );
    VendingMachine **getMachineList();
};