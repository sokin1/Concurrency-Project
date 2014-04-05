#include "watcardoffice.h"
#include "MPRNG.h"

#include <iostream>

extern MPRNG RNG;

WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers )
: printer( prt ), numCouriers( numCouriers ) {
	Courier** temp = new Courier* [numCouriers];
	for( unsigned int i = 0; i < numCouriers; i++ ) {
		temp[i] = new Courier( bank, this );
	}
	couriers = temp;
}

FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
	WATCard *newCard = new WATCard();
	return transfer( sid, amount, newCard );
}

//Transfers money from the bank to the WATCard 
//(by creating a job and let couriers grab that job to do this)
FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ) {
	curArgs.id = sid;
	curArgs.amount = amount;
	curArgs.card = card;

	struct Job *curJob = new struct Job( curArgs );
	jobList.push( curJob );
	couriers[RNG(0,numCouriers-1)]->transferDone();	//get a random courier to start the job
	return curJob->result;
}

WATCardOffice::Job* WATCardOffice::requestWork() {
	struct Job *newJob = jobList.front();
	jobList.pop();
	return newJob;
}

void WATCardOffice::Courier::doWithdraw( unsigned int id, unsigned int amount, WATCard* card ) {
	bank.withdraw( id, amount );
	card->deposit( amount );
}

void WATCardOffice::Courier::transferDone(){}

void WATCardOffice::Courier::main() {
	for (;;){
		_Accept(~Courier){
			break;
		} or _Accept(transferDone){
			Job *job = office->requestWork();
			doWithdraw( job->args.id, job->args.amount, job->args.card );
			if( RNG( 5 ) == 0 ) {		// Watcard is lost - 1 in 6 chances (RNG of 0 to 5)
				job->result.reset();
				job->result.exception( new Lost );
				delete job->args.card;
			} else {
				job->result.reset();
				job->result.delivery( job->args.card );
			}
			//TODO: keep this?
			delete job;
		}
	}
}

void WATCardOffice::main() {
	for( ; ; ) {
		_Accept(~WATCardOffice){
			for( unsigned int i = 0; i < numCouriers; i++ ) {
				delete couriers[i];
			}
			delete couriers;
			break;
		} or _Accept( create ) {
		} or _Accept( transfer ) {
		} or _Accept( requestWork ) {
		}
	}
}
