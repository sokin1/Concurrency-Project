#include "student.h"

Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id, 
unsigned int maxPurchases ):prt(prt), nameServer(nameServer), cardOffice(cardOffice), 
id(id),maxPurchases(maxPurchases){}

void Student::main(){
	unsigned int numPurchases = mprng( 1, maxPurchases+1 );
	unsigned int flavour = mprng( 4 );
	int i;
	// Create watcard
	FWATCard watcard = cardOffice.create( id, 5 );

	// Purchase sodas
	for( i = 0; i < numPurchases; i++ ) {
		yield( mprng( 1, 11 ) );
		// Look for name server and find vendor.
		try {
		//Buy soda should be done here
		} catch( WATCardOffice::Lost ) {
			// If card is lost, create new watcard
			FWATCard watcard = cardOffice.create( id, 5 );
		}
	}
}
