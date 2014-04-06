#include "truck.h"
#include "MPRNG.h"
#include "bottle.h"
#include "nameserver.h"
#include "vending.h"
#include "printer.h"

extern MPRNG RNG;

Truck::Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
unsigned int numVendingMachines, unsigned int maxStockPerFlavour ): prt(prt), nameServer(nameServer),
plant(plant),numVendingMachines(numVendingMachines),maxStockPerFlavour(maxStockPerFlavour){

}

void Truck::main(){
	prt.print(Printer::Truck, Printer::Start);
	while(true){
		// Get coffee from Timmy's
		yield(RNG(1,10));
		
		// Get cargo from plant
		bool isPlantClosed = plant.getShipment(cargo);
		if (isPlantClosed){
			break;	//exit loop when plant is closed
		}
		
		prt.print(Printer::Truck, Printer::PickedUp, (int)(cargo[0]+cargo[1]+cargo[2]+cargo[3]));
		
		// Get a list of vending machines
		VendingMachine** v_list = nameServer.getMachineList();		

		// Fill all the vending machines
		for(unsigned int i=0; i<numVendingMachines; i++){
			prt.print(Printer::Truck, Printer::BeginDelivery, (int)i, (int)(cargo[0]+cargo[1]+cargo[2]+cargo[3]));
			VendingMachine* v = v_list[i];
			
			// Check inventory
			unsigned int* inv = v->inventory();
			
			//For printing purpose
			int unfilled = 0;
			
			// Fill all 4 flavours
			for (unsigned int j=0; j<4; j++){
				//If there is cargo to refill, then proceed
				if(cargo[j]>0){
					unsigned int numberToRefill = maxStockPerFlavour - inv[j];
					if (cargo[j] < numberToRefill){
						//Record unfilled number of bottles
						unfilled += numberToRefill - cargo[j];
						//Not enough cargo to refill to max capacity, so fill what we have
						inv[j] += cargo[j];
						cargo[j] = 0;
					} else {
						//Refill normally
						inv[j] += numberToRefill;
						cargo[j] -= numberToRefill;
					}
				}
			}
			if (unfilled > 0) prt.print(Printer::Truck, Printer::UnsuccessFill, (int)i, unfilled);
			prt.print(Printer::Truck, Printer::EndDelivery, (int)i, (int)(cargo[0]+cargo[1]+cargo[2]+cargo[3]));
			// Restocking is completed
			v->restocked();
		}
	}
	prt.print(Printer::Truck, Printer::Finish);
}