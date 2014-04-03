#include "watcardoffice.h"

WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers )
: printer( prt ), bank( bank ), numCouriers( numCouriers ) {
	couriers = new Courier[numCouriers];
	for( int i = 0; i < numCouriers; i++ ) {
		couriers[i] = new Courier( bank );
	}
}

FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
	WATCard *newCard = new WATCard();

	return transfer( sid, amount, newCard );
}

FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ) {
	Args args;
	args.id = sid;
	args.amount = amount;
	args.card = card;

	struct Job *curJob = new struct Job( &args );

	jobList.push_back( curJob );

	return curJob->result;
}

Job* WATCardOffice::requestWork() {
	_When( jobList.empty() ) _Accept( transfer ) {
		struct Job *newJob = jobList.front();
		jobList.pop_front();
		return newJob;
	}
}

int Courier::doWithdraw( unsigned int id, unsigned int amount, WATCard* card ) {
	bank.withdraw( id, amount );
	card.deposit( amount );
}

void Courier::main() {
	Job *job = requestWork();
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
