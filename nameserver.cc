#include "nameserver.h"

NameServer::NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents ):
prt(prt),numVendingMachines(numVendingMachines),numStudents(numStudents){}

void NameServer::VMregister( VendingMachine *vendingmachine ){
	machineList[machineCount] = vendingmachine;
	machineCount++;
}

VendingMachine* NameServer::getMachine( unsigned int id ){
	for (unsigned int i=0; i<numVendingMachines; i++){
		if(machineList[i]->getId() == id){
			return machineList[i];
		}
	}
	// Something is wrong, return NULL
	return NULL;
}

VendingMachine** NameServer::getMachineList(){
	return machineList;
}

void main(){
	_Accept(getMachine){
		//TODO: Assign students to machines here
	} or _Accept(getMachineList){
	
	} or _Accept(VMregister){
	
	}
}