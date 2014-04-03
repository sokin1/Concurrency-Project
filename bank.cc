#include "bank.h"

Bank::Bank( unsigned int numStudents )
: numStudents( numStudents ), amount( 0 ) {
	studentAccount = new struct Account[numStudents];
	for( unsigned int i = 0; i < numStudents; i++ ) {
		studentAccount[i].amount = 0;
	}
}

void Bank::deposit( unsigned int id, unsigned int amount ) {
	studentAccount[id].amount += amount;
}

void Bank::withdraw( unsigned int id, unsigned int amount ) {
	while( studentAccount[id].amount < amount ) _Accept( deposit );
	studentAccount[id].amount -= amount;
}
