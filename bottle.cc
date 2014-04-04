#include "bottle.h"
#include "MPRNG.h"

extern MPRNG RNG;

BottlingPlant::BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour, unsigned int timeBetweenShipments):
prt(prt), nameServer(nameServer), numVendingMachines(numVendingMachines), 
maxShippedPerFlavour(maxShippedPerFlavour), maxStockPerFlavour(maxStockPerFlavour){
	production[0] = production[1] = production[2] = production[3] = 0;
}

bool BottlingPlant::getShipment( unsigned int cargo[] ){
	cargo[0] = production[0];
	cargo[1] = production[1];
	cargo[2] = production[2];
	cargo[3] = production[3];
	return isClosed;
}

void BottlingPlant::main(){
	Truck truck(prt, nameServer, *this, numVendingMachines, maxStockPerFlavour);
	while(true){
		//pretend to be busy producing
		yield(timeBetweenShipments);
		
		//the actual production run
		unsigned int shipped = RNG(0,maxShippedPerFlavour);
		production[0] = shipped;
		shipped = RNG(0,maxShippedPerFlavour);
		production[1] = shipped;
		shipped = RNG(0,maxShippedPerFlavour);
		production[2] = shipped;
		shipped = RNG(0,maxShippedPerFlavour);
		production[3] = shipped;
		
		//wait for truck to pick the items up
		_Accept(getShipment) or
		_Accept(~BottlingPlant){
			//Make one last delivery for truck to terminate
			isClosed = true;
			_Accept(getShipment);
			break;
		}
	}
}