

Truck::Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
unsigned int numVendingMachines, unsigned int maxStockPerFlavour ): prt(prt), nameServer(nameServer),
plant(plant),numVendingMachines(numVendingMachines),maxStockPerFlavour(maxStockPerFlavour){

}

void Truck::main(){
	
	while(true){
		//getting coffee
		yield(RNG(1,10)); 
		
		//getting cargo
		bool isPlantClosed = plant.getShipment(cargo);
		if (isPlantClosed){
			break;	//exit loop
		}
		
		// CHANGE THE FOLLOWING TO GET MACHINE LIST
		// Fill all the vending machines
		for(unsigned int id=0; id<numVendingMachines; id++){
			VendingMachine* v = nameServer.getMachine(id)		//can I make this assumption that id goes from 0 to max????
			
			// Check inventory
			unsigned int* inv = v->inventory();
			
			// Fill all 4 flavours
			for (unsigned int i=0; i<4; i++){
				//If there is cargo to refill, then proceed
				if(cargo[i]>0){
					unsigned int numberToRefill = maxStockPerFlavour - inv[i];
					if (cargo[i] < numberToRefill){
						//Not enough cargo to refill to max capacity
						inv[i] += cargo[i];
						cargo[i] = 0;
					} else {
						//Refill normally
						inv[i] += numberToRefill;
						cargo[i] -= numberToRefill;
					}
				}
			}
			v->restocked();
		}
		
		//DOES THIS HAVE TO WAIT HERE?
		
	}
}