#include "student.h"
#include "watcard.h"
#include "vending.h"
#include "nameserver.h"
#include "watcardoffice.h"
#include "printer.h"
#include "MPRNG.h"

#include <iostream>

extern MPRNG RNG;

Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id, 
unsigned int maxPurchases ):prt(prt), nameServer(nameServer), cardOffice(cardOffice), 
id(id),maxPurchases(maxPurchases){}

void Student::main(){

	unsigned int numPurchases = RNG( 1, maxPurchases+1 );
	unsigned int flavour = RNG( 4 );
	
	prt.print(Printer::Student, (unsigned int)id, (char)Printer::Start, (int)flavour, (int)numPurchases);
	
	bool reAttempt = false;

	// Create watcard
	WATCard::FWATCard watcard = cardOffice.create( id, 5 );
	VendingMachine *machine;

	// Purchase sodas
	while( numPurchases != 0 ) {
		if( !reAttempt ) {
			yield( RNG( 1, 11 ) );
			machine = nameServer.getMachine( id );
			prt.print(Printer::Student, (unsigned int)id, (char)Printer::SelectVendMachine, (int)machine->getId());
		}
		reAttempt = false;

		try {
			VendingMachine::Status status;
			status = machine->buy( (VendingMachine::Flavours) flavour, *watcard() );
			if( status == VendingMachine::BUY ) {
				prt.print(Printer::Student, (unsigned int)id, (char)Printer::Bought, (int)watcard()->getBalance());
				numPurchases--;
			} else if ( status == VendingMachine::STOCK ) {
			} else if ( status == VendingMachine::FUNDS ) {
				watcard = cardOffice.transfer( id, machine->cost()+5, watcard() );
			}
		} catch( WATCardOffice::Lost ) {
			// If card is lost, create new watcard
			prt.print(Printer::Student, (unsigned int)id, (char)Printer::WATCardLost);
			watcard = cardOffice.create( id, 5 );
			reAttempt = true;
		}
	}
	
	prt.print(Printer::Student, (unsigned int)id, (char)Printer::Finish);
}
