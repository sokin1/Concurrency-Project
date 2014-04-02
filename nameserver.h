#pragma once

_Task NameServer {
    Printer &prt;
		unsigned int numVendingMachines;
		unsigned int numStudents;
		void main();
		VendingMachine** machineList;
		unsigned int machineCount;
		unsigned int studentAssign [numStudents];	//for assigning students to vending machines
  public:
    NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents );
    void VMregister( VendingMachine *vendingmachine );
    VendingMachine *getMachine( unsigned int id );
    VendingMachine **getMachineList();
};