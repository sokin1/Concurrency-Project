#include "watcardoffice.h"

WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers )
: printer( prt ), numCouriers( numCouriers ) {
	WATCardOffice::Courier *newCouriers[numCouriers];
//	couriers = new WATCardOffice::Courier[numCouriers];
	for( int i = 0; i < numCouriers; i++ ) {
		newCouriers[i] = new WATCardOffice::Courier( bank, this );
	}

	couriers = newCouriers[0];
}

FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
	WATCard *newCard = new WATCard();

	return transfer( sid, amount, newCard );
}

FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ) {
	curArgs.id = sid;
	curArgs.amount = amount;
	curArgs.card = card;

	struct Job *curJob = new struct Job( curArgs );

	jobList.push( curJob );

	return curJob->result;
}

WATCardOffice::Job* WATCardOffice::requestWork() {
	_When( jobList.empty() ) _Accept( transfer ) {
		struct Job *newJob = jobList.front();
		jobList.pop();
		return newJob;
	}
}

void WATCardOffice::Courier::doWithdraw( unsigned int id, unsigned int amount, WATCard* card ) {
	bank.withdraw( id, amount );
	card->deposit( amount );
}

void WATCardOffice::Courier::main() {
	Job *job = office->requestWork();

	doWithdraw( job->args.id, job->args.amount, job->args.card );

	job->result.reset();
	job->result.delivery( job->args.card );
}

void WATCardOffice::main() {
	for( ; ; ) {
		_Accept( create ) {
		} or _Accept( transfer ) {
		} or _Accept( requestWork ) {
		}
	}
}
