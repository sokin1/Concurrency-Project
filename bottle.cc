#include "bottle.h"
#include "MPRNG.h"
#include "printer.h"

// #include <iostream>

extern MPRNG RNG;

BottlingPlant::BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour, unsigned int timeBetweenShipments):
prt(prt), nameServer(nameServer), numVendingMachines(numVendingMachines), 
maxShippedPerFlavour(maxShippedPerFlavour), maxStockPerFlavour(maxStockPerFlavour),
timeBetweenShipments(timeBetweenShipments){
	production[0] = 0;
	production[1] = 0;
	production[2] = 0;
	production[3] = 0;
	isClosed = false;
}

bool BottlingPlant::getShipment( unsigned int cargo[] ){
	prt.print(Printer::BottlingPlant, Printer::PickedUp);
	cargo[0] = production[0];
	cargo[1] = production[1];
	cargo[2] = production[2];
	cargo[3] = production[3];
	return isClosed;
}

void BottlingPlant::main(){
	prt.print(Printer::BottlingPlant, Printer::Start);
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
		
		int total = production[0] + production[1] + production[2] + production[3];
		prt.print(Printer::BottlingPlant, Printer::GenSoda, total);
		
		_Accept(~BottlingPlant){
			//Make one last delivery for truck to terminate
			isClosed = true;
			_Accept(getShipment);
			break;
		} or _Accept(getShipment){
		}
	}
	prt.print(Printer::BottlingPlant, Printer::Finish);
}