#include "watcard.h"

WATCard::WATCard( const WATCard & ) {
}

WATCard WATCard::&operator=( const WATCard & ) {
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

