
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