#pragma once
#include <uFuture.h>
#include "watcard.h"
#include "bank.h"
#include "printer.h"
#include <queue>

typedef Future_ISM<WATCard *> FWATCard; // future watcard pointer

_Task Courier;

_Task WATCardOffice {
	
	struct Args {
		unsigned int id;
		unsigned int amount;
		WATCard *card;
	};

	struct Job {                       	 // marshalled arguments and return future
		Args args;                         // call arguments (YOU DEFINE "Args")
		FWATCard result;                   // return future
		Job( Args args ) : args( args ) {}
	};

	struct Args curArgs;
	std::queue<struct Job *> jobList;
	
	_Task Courier {
		Bank& bank;
		WATCardOffice *office;
		unsigned int id;
		Printer& printer;
		void doWithdraw( unsigned int id, unsigned int amount, WATCard* card );
		void main();
	public:
		void transferDone();
		Courier( Bank& b, WATCardOffice *office, unsigned int id, Printer &prt )
		: bank( b ), office( office ), id(id), printer(prt) {}
	};                 // communicates with bank

	Courier **couriers;
	Printer &printer;
	unsigned int numCouriers;
	unsigned int courierCount;
	void main();
public:
	_Event Lost {};                        // uC++ exception type, like "struct"
	WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
	FWATCard create( unsigned int sid, unsigned int amount );
	FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
	Job *requestWork();
};
