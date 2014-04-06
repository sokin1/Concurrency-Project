#include "parent.h"
#include "MPRNG.h"
#include "bank.h"
#include "printer.h"

// #include <iostream>

extern MPRNG RNG;

Parent::Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay ) :
printer( prt ), bank( bank ), numStudents( numStudents ), parentalDelay( parentalDelay ) {}

void Parent::main() {
	printer.print(Printer::Parent, Printer::Start);
	for(;;) {
		_Accept( ~Parent ) {
			break;
		} _Else {
			unsigned int studentID = RNG(numStudents - 1);
			unsigned int depositAmount = RNG( 1, 3 );
			yield( parentalDelay );
			printer.print(Printer::Parent, Printer::Deposit, (int)studentID, (int)depositAmount);
			bank.deposit( studentID, depositAmount );
		}
	}
	printer.print(Printer::Parent, Printer::Finish);
}
