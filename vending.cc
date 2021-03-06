#include "vending.h"
#include "nameserver.h"
#include "watcard.h"
#include "printer.h"

VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
unsigned int maxStockPerFlavour ):prt(prt),nameServer(nameServer),id(id),sodaCost(sodaCost),
maxStockPerFlavour(maxStockPerFlavour){
	stock[0] = 0;
	stock[1] = 0;
	stock[2] = 0;
	stock[3] = 0;
	nameServer.VMregister(this);
}

VendingMachine::Status VendingMachine::buy(Flavours flavour, WATCard &card){
	// No stock
	if (stock[flavour] == 0){
		return STOCK;
	// Not enough funds
	} else if (card.getBalance() < sodaCost){
		return FUNDS;
	// Successful buy
	} else {
		stock[flavour] = stock[flavour] - 1;
		prt.print(Printer::Vending, (unsigned int)id, (char)Printer::StudentBought, (int)flavour, stock[flavour]);
		card.withdraw(sodaCost);
		return BUY;
	}
}

unsigned int* VendingMachine::inventory(){
	prt.print(Printer::Vending, (unsigned int)id, (char)Printer::StartReload);
	return stock;
}

void VendingMachine::restocked(){
	prt.print(Printer::Vending, (unsigned int)id, (char)Printer::CompleteReload);
	return;
}

unsigned int VendingMachine::cost(){
	return sodaCost;
}

unsigned int VendingMachine::getId(){
	return id;
}

void VendingMachine::main(){
	prt.print(Printer::Vending, (unsigned int)id, (char)Printer::Start, (int)sodaCost);
	while (true){
		_Accept(buy){
		} or _Accept(inventory){
			// Block here while restocking
			_Accept(restocked);
		} or _Accept(~VendingMachine){
			break;
		}
	}
	prt.print(Printer::Vending, (unsigned int)id, (char)Printer::Finish);
}