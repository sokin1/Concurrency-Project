#include "watcard.h"

// This is for preventing copy - Do not need to implement
WATCard::WATCard( const WATCard & ) {
}

// This is for preventing copy - Do not need to implement
WATCard& WATCard::operator=( const WATCard& w) {
}

WATCard::WATCard()
: currentBalance( 0 ) {}

void WATCard::deposit( unsigned int amount ) {
	currentBalance += amount;
}

void WATCard::withdraw( unsigned int amount ) {
	currentBalance -= amount;
}

unsigned int WATCard::getBalance() {
	return currentBalance;
}

