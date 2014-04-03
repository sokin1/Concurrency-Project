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
	
	//Read in the config file
	ConfigParms config;
	processConfigFile("soda.config", config);
	
	//Initialize the entire thing
	Printer printer(config.numStudents, config.numVendingMachines, config.numCouriers);
	Bank bank(config.numStudents);
	Parent parent(printer, bank, config.numStudents, config.parentalDelay);
	WATCardOffice office(printer, bank, config.numCouriers);
	NameServer nameserver(printer, config.numVendingMachines, config.numStudents);
	for (unsigned int id=0; id<config.numVendingMachines; id++){
		VendingMachine machine(printer, nameserver, id, config.sodaCost, config.maxStockPerFlavour);
	}
	BottlingPlant plant(printer, nameserver, config.numVendingMachines, config.maxShippedPerFlavour, config.maxStockPerFlavour, config.timeBetweenShipments);
	for (unsigned int id=0; id<config.numStudents; id++){
		Student student (printer, nameserver, office, id, config.maxPurchases);
	}
}