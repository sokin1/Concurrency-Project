#include "watcardoffice.h"
#include "MPRNG.h"
#include "printer.h"

#include <iostream>

// #include <iostream>

extern MPRNG RNG;

WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers )
: printer( prt ), numCouriers( numCouriers ), courierCount(0), terminate( false ) {
	Courier** temp = new Courier* [numCouriers];
	for( unsigned int i = 0; i < numCouriers; i++ ) {
		temp[i] = new Courier( bank, this, i, prt );
	}
	couriers = temp;
}

FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
	printer.print(Printer::WATCardOffice, Printer::CreationRComplete, (int)sid, (int)amount);

	WATCard *newCard = new WATCard();

	curArgs.id = sid;
	curArgs.amount = 5;
	curArgs.card = newCard;

	struct Job *initJob = new struct Job( curArgs );
	jobList.push( initJob );
	waiter.signal();

	return initJob->result;
//	return transfer( sid, amount, newCard );
}

//Transfers money from the bank to the WATCard 
//(by creating a job and let couriers grab that job to do this)
FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ) {
	printer.print(Printer::WATCardOffice, Printer::TransferRComplete, (int)sid, (int)amount);
	
	curArgs.id = sid;
	curArgs.amount = amount;
	curArgs.card = card;

	struct Job *curJob = new struct Job( curArgs );
	jobList.push( curJob );
	waiter.signal();

	int courierNum = courierCount % numCouriers;
	courierCount++;
	printer.print(Printer::Courier, (unsigned int)courierNum, (char)Printer::StartFundTransfer, sid, amount);
//	couriers[courierNum]->transferDone();
	return curJob->result;
}

WATCardOffice::Job* WATCardOffice::requestWork() {
	printer.print(Printer::WATCardOffice, Printer::CourierRComplete);
	if( jobList.empty() ) waiter.wait();
	if( terminate ) {
		return NULL;
	}
	struct Job *newJob = jobList.front();
	jobList.pop();
	return newJob;
}

void WATCardOffice::Courier::doWithdraw( unsigned int id, unsigned int amount, WATCard* card ) {
	bank.withdraw( id, amount );
	card->deposit( amount );
}

void WATCardOffice::Courier::transferDone(){
}

bool WATCardOffice::Courier::getWork() {
	Job *job = office->requestWork();
	if( job == NULL ) return false;
	doWithdraw( job->args.id, job->args.amount, job->args.card );
	if( RNG( 5 ) == 0 ) {		// Watcard is lost - 1 in 6 chances (RNG of 0 to 5)
		job->result.reset();
		job->result.exception( new Lost );
		delete job->args.card;
	} else {
		job->result.reset();
		job->result.delivery( job->args.card );
		printer.print(Printer::Courier, (unsigned int)id, (char)Printer::CompleteFundTransfer,
		job->args.id, job->args.amount);
	}
	delete job;
	return true;
}

void WATCardOffice::Courier::main() {
	printer.print(Printer::Courier, (unsigned int)id, (char)Printer::Start);
	for (;;){
		_Accept(~Courier){
			break;
		} _Else {
			if( !getWork() ) break;
		}
	}
	printer.print(Printer::Courier, (unsigned int)id, (char)Printer::Finish);
}

void WATCardOffice::main() {
	printer.print(Printer::WATCardOffice, Printer::Start);
	for( ; ; ) {
		_Accept(~WATCardOffice){
			terminate = true;
			while( !waiter.empty() ) waiter.signalBlock();
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
	printer.print(Printer::WATCardOffice, Printer::Finish);
}
