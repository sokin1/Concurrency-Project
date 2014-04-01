

struct ConfigParms {
    unsigned int sodaCost;                 // MSRP per bottle
    unsigned int numStudents;              // number of students to create
    unsigned int maxPurchases;             // maximum number of bottles a student purchases
    unsigned int numVendingMachines;       // number of vending machines
    unsigned int maxStockPerFlavour;       // maximum number of bottles of each flavour stocked
    unsigned int maxShippedPerFlavour;     // number of bottles of each flavour in a shipment
    unsigned int timeBetweenShipments;     // length of time between shipment pickup
    unsigned int parentalDelay;            // length of time between cash deposits
    unsigned int numCouriers;              // number of couriers in the pool
};

void uMain::main(){
	//Read in the config file
	ConfigParms config;
	processConfigFile("soda.config", config);
	
	//Initialize the whole thing
	Printer printer(config.numStudents, config.numVendingMachines, config.numCouriers);
	Bank bank(config.numStudents);
	Parent parent(printer, bank, config.numStudents, config.parentalDelay);
	WATCardOffice office(printer, bank, config.numCouriers);
	NameServer nameserver(printer, config.numVendingMachines, config.numStudents);
	VendingMachine machine(printer, nameserver, unsigned int id /*some id*/, config.sodaCost, config.maxStockPerFlavour);
	BottlingPlant plant(printer, nameserver, config.numVendingMachines, config.maxShippedPerFlavour, config.maxStockPerFlavour, config.timeBetweenShipments);
	Student student (printer, nameserver, office, unsigned int id /*some id*/, config.maxPurchases);
	
}