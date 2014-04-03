#include "parent.h"
#include "MPRNG.h"
#include "bank.h"

extern MPRNG RNG;

Parent::Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay ) :
printer( prt ), bank( bank ), numStudents( numStudents ), parentalDelay( parentalDelay ) {}

void Parent::main() {
	for( ; ; ) {
		_Accept( ~Parent ) {
			break;
		} _Else {
			unsigned int studentID = RNG( numStudents );
			unsigned int depositAmount = RNG( 1, 3 );
			yield( parentalDelay );
			bank.deposit( studentID, depositAmount );
		}
	}
}
