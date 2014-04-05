#include <iostream>
#include <sstream>
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

//Usage Error Message
void usage( char *argv[] ) {
    cerr << "Usage: " << argv[0] << 
	 " [ config-file [ random-seed (> 0) ] ]" << endl;
    exit( EXIT_FAILURE );				// TERMINATE
}

//Converts C string to integer
bool convert( int &val, char *buffer ) {		// convert C string to integer
   stringstream ss( buffer );						// connect stream and buffer
   ss >> dec >> val;									// convert integer from buffer
   return ! ss.fail() &&							// conversion successful ?
	// characters after conversion all blank ?
	string( buffer ).find_first_not_of( " ", ss.tellg() ) == string::npos;
}

void uMain::main(){
	
	//default input values
	char* configFileName = (char*)"soda.config";	//File Name
	int seed = getpid();													//Seed
	ConfigParms config;
	
	switch ( argc ) {		// check command line arguments for correct input
		case 3:
			if(!convert(seed, argv[2])) usage(argv);
			if(seed <= 0) usage(argv);
		case 2:
			//Read in the config file
			configFileName = argv[1];
			processConfigFile(configFileName, config);
		case 1:
			//Set seed
			RNG.seed(seed);
			break;
		default:					// incorrect number of options
			usage( argv );
	}
	
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