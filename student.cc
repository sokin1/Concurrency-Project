#include "student.h"
#include "watcard.h"
#include "vending.h"
#include "nameserver.h"
#include "watcardoffice.h"
#include "MPRNG.h"

extern MPRNG RNG;

Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id, 
unsigned int maxPurchases ):prt(prt), nameServer(nameServer), cardOffice(cardOffice), 
id(id),maxPurchases(maxPurchases){}

void Student::main(){
	unsigned int numPurchases = RNG( 1, maxPurchases+1 );
	unsigned int flavour = RNG( 4 );
	bool reAttempt = false;

	// Create watcard
	WATCard::FWATCard watcard = cardOffice.create( id, 5 );
	VendingMachine *machine;

	// Purchase sodas
	while( numPurchases != 0 ) {
		if( !reAttempt ) {
			yield( RNG( 1, 11 ) );
			machine = nameServer.getMachine( id );
		}
		reAttempt = false;

		try {
			VendingMachine::Status status;
			status = machine->buy( (VendingMachine::Flavours) flavour, *watcard() );
			if( status == VendingMachine::BUY ) {
				numPurchases--;
			} else if ( VendingMachine::STOCK ) {
			} else if ( VendingMachine::FUNDS ) {
				watcard = cardOffice.transfer( id, machine->cost()+5, watcard() );
			}
		} catch( WATCardOffice::Lost ) {
			// If card is lost, create new watcard
			watcard = cardOffice.create( id, 5 );
			reAttempt = true;
		}
	}
}
