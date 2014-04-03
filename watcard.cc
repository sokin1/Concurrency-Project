#include "watcard.h"

WATCard::WATCard( const WATCard & ) {
}

WATCard& WATCard::operator=( const WATCard& w) {
	//TODO: check how to do this properly
	currentBalance = w.currentBalance;
	// FWATCard = w.FWATCard;
	return *this;
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

