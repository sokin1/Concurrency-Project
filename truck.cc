#include "truck.h"
#include "MPRNG.h"
#include "bottle.h"
#include "nameserver.h"
#include "vending.h"

extern MPRNG RNG;

Truck::Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
unsigned int numVendingMachines, unsigned int maxStockPerFlavour ): prt(prt), nameServer(nameServer),
plant(plant),numVendingMachines(numVendingMachines),maxStockPerFlavour(maxStockPerFlavour){

}

void Truck::main(){
	
	while(true){
		// Get coffee from Timmy's
		yield(RNG(1,10)); 
		
		// Get cargo from plant
		bool isPlantClosed = plant.getShipment(cargo);
		if (isPlantClosed){
			break;	//exit loop
		}
		
		// Get a list of vending machines
		VendingMachine** v_list = nameServer.getMachineList();		

		// Fill all the vending machines
		for(unsigned int i=0; i<numVendingMachines; i++){
			VendingMachine* v = v_list[i];
			
			// Check inventory
			unsigned int* inv = v->inventory();
			
			// Fill all 4 flavours
			for (unsigned int i=0; i<4; i++){
				//If there is cargo to refill, then proceed
				if(cargo[i]>0){
					unsigned int numberToRefill = maxStockPerFlavour - inv[i];
					if (cargo[i] < numberToRefill){
						//Not enough cargo to refill to max capacity, so fill what we have
						inv[i] += cargo[i];
						cargo[i] = 0;
					} else {
						//Refill normally
						inv[i] += numberToRefill;
						cargo[i] -= numberToRefill;
					}
				}
			}
			// Restocking is completed
			v->restocked();
		}
		
		//TODO: DOES THIS HAVE TO WAIT HERE? prob not...
		
	}
}