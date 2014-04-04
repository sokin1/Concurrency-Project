#include <iostream>
#include "bank.h"
#include "bottle.h"
#include "config.h"
#include "MPRNG.h"
#include "nameserver.h"
#include "parent.h"
#include "student.h"
#include "truck.h"
#include "vending.h"
#include "watcard.h"
#include "watcardoffice.h"
#include "printer.h"
using namespace std;

MPRNG RNG;

void uMain::main(){
	
	//Read in the seed
	//...
	RNG.seed(getpid());
	
	//Read in the config file
	ConfigParms config;
	processConfigFile("soda.config", config);
	
	VendingMachine* v_list[config.numVendingMachines];
	Student* s_list[config.numStudents];
	
	//Initialize the entire thing (order according to assignment)
	Printer printer(config.numStudents, config.numVendingMachines, config.numCouriers);
	Bank bank(config.numStudents);
	Parent parent(printer, bank, config.numStudents, config.parentalDelay);
	WATCardOffice office(printer, bank, config.numCouriers);
	NameServer nameserver(printer, config.numVendingMachines, config.numStudents);
	for (unsigned int id=0; id<config.numVendingMachines; id++){
		VendingMachine* v = new VendingMachine (printer, nameserver, id, config.sodaCost, config.maxStockPerFlavour);
		v_list[id] = v;
	}
	BottlingPlant plant(printer, nameserver, config.numVendingMachines, config.maxShippedPerFlavour, config.maxStockPerFlavour, config.timeBetweenShipments);
	for (unsigned int id=0; id<config.numStudents; id++){
		Student* s = new Student (printer, nameserver, office, id, config.maxPurchases);
		s_list[id] = s;
	}
	
	//Stop students and vending machines
	for (unsigned int id=0; id<config.numStudents; id++){
		delete s_list[id];
	}
	for (unsigned int id=0; id<config.numVendingMachines; id++){
		delete v_list[id];
	}
	
}