

BottlingPlant::BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour, unsigned int timeBetweenShipments):prt(prt),
nameserver(nameserver), numVendingMachines(numVendingMachines),
maxShippedPerFlavour(maxShippedPerFlavour), maxStockPerFlavour(maxStockPerFlavour){}

bool BottlingPlant::getShipment( unsigned int cargo[] ){
	cargo[0] = production[0];
	cargo[1] = production[1];
	cargo[2] = production[2];
	cargo[3] = production[3];
	return isClosed;	//isClosed needs to be set somehow.....
}

void BottlingPlant::main(){
	Truck t(prt, nameServer, plant, numVendingMachines, maxStockPerFlavour);
	
	while(true){
		//busy producing
		yield(timeBetweenShipments);
	
		//production run
		unsigned int shipped = RNG(0,maxShippedPerFlavour);
		production[0] = shipped;
		shipped = RNG(0,maxShippedPerFlavour);
		production[1] = shipped;
		shipped = RNG(0,maxShippedPerFlavour);
		production[2] = shipped;
		shipped = RNG(0,maxShippedPerFlavour);
		production[3] = shipped;
		
		//wait for truck to pick the items up
		_Accept(getShipment);
		
		// NEEDS TO TERMINATE SOMEHOW............
	}
}