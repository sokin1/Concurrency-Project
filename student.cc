#include "student.h"

extern MPRNG mprng;

Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id, 
unsigned int maxPurchases ):prt(prt), nameServer(nameServer), cardOffice(cardOffice), 
id(id),maxPurchases(maxPurchases){}

void Student::main(){
	unsigned int numPurchases = mprng( 1, maxPurchases+1 );
	unsigned int flavour = mprng( 4 );
	int i = 0;
	bool reAttempt = false;

	// Create watcard
	FWATCard watcard = cardOffice.create( id, 5 );
	VendingMachine *machine;

	// Purchase sodas
	while( i <= numPurchases ) {
		if( !reAttempt ) {
			yield( mprng( 1, 11 ) );
			machine = nameServer.getMachine( id );
		}
		reAttempt = false;

		try {
			VendingMachine::Status status;
			status = machine->buy( flavour, *watcard() );
			if( status == VendingMachine::BUY ) {
			} else if ( VendingMachine::STOCK ) {
				machine = nameServer.getMachine( id );
				continue;
			} else if ( VendingMachine::FUNDS ) {
				watcard = cardOffice.transfer( id, machine->cost()+5, *watcard() );
				continue;
			}
			i++;
		} catch( WATCardOffice::Lost ) {
			// If card is lost, create new watcard
			watcard = cardOffice.create( id, 5 );
			reAttempt = true;
		}
	}
}
