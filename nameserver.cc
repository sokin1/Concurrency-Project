#include "nameserver.h"
#include "vending.h"
#include "printer.h"

NameServer::NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents ):
prt(prt),numVendingMachines(numVendingMachines),numStudents(numStudents){
	studentAssign = new unsigned int [numStudents];
	VendingMachine** temp = new VendingMachine* [numVendingMachines];
	machineList = temp;
	machineCount = 0;
}

NameServer::~NameServer(){
	delete [] studentAssign;
	delete machineList;
}

void NameServer::VMregister( VendingMachine *vendingmachine ){
	prt.print(Printer::NameServer, Printer::RegVendMachine, (int)machineCount);
	machineList[machineCount] = vendingmachine;
	machineCount++;
}

VendingMachine* NameServer::getMachine( unsigned int id ){	//id is the student's id
	prt.print(Printer::NameServer, Printer::NewVendMachine, (int)id, (int)studentAssign[id]);
	unsigned int temp = studentAssign[id];
	studentAssign[id] = (studentAssign[id] + 1) % numVendingMachines;
	return machineList[temp];
}

VendingMachine** NameServer::getMachineList(){
	return machineList;
}

void NameServer::main(){
	
	prt.print(Printer::NameServer, Printer::Start);
	
	//Assign students to vending machines
	for (unsigned int i=0; i<numStudents; i++){
		studentAssign[i] = i % numVendingMachines;
	}
	
	//Let vending machine registering finish first before students can get the location of a machine
	unsigned int count = 0;
	while(count < numVendingMachines){
		_Accept(VMregister);
		count++;
	}
	
	while(true){
		_Accept(~NameServer){
			break;
		} or _Accept(getMachine){
		} or _Accept(getMachineList){
		}
	}
	
	prt.print(Printer::NameServer, Printer::Finish);
}