#include "bank.h"

//Initialize student accounts
Bank::Bank( unsigned int numStudents )
: numStudents( numStudents ){
	studentAccount = new struct Account[numStudents];
	for( unsigned int i = 0; i < numStudents; i++ ) {
		studentAccount[i].amount = 0;
	}
}

void Bank::deposit( unsigned int id, unsigned int amount ) {
	studentAccount[id].amount += amount;
}

//Wait until the student account have enough money from deposit, then we withdraw
void Bank::withdraw( unsigned int id, unsigned int amount ) {
	while( studentAccount[id].amount < amount ) _Accept( deposit );
	studentAccount[id].amount -= amount;
}

Bank::~Bank(){
	delete [] studentAccount;
}
