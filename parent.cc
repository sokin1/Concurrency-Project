#include "parent.h"

Parent::Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay ) :
	printer( prt ), bank( bank ), numStudents( numStudents ), parentalDelay( parentalDelay ) {}

void Parent::main() {
    for( ; ; ) {
	_Accept( ~Parent ) {
	    break;
	} _Else {
	    unsigned int studentID = mprng( numStudents );
    	    unsigned int depositAmount = mprng( 1, 3 );
    	    yield( parentDelay );
	    bank.deposit( studentID, depositAmount );
	}
    }
}
