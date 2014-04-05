#include "watcard.h"

WATCard::WATCard( const WATCard & ) {
}

WATCard& WATCard::operator=( const WATCard& w) {
	currentBalance = w.currentBalance;
	//TODO: check how to assign FWATCard properly
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

