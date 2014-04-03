#pragma once
#include "watcard.h"
#include "bank.h"
#include "printer.h"
#include <queue>

struct FWATCard{};		//TODO: REMOVE THIS AND GET IT TO COMPILE

_Task WATCardOffice {
	struct Args {
		unsigned int id;
		unsigned int amount;
		WATCard *card;
	};

	struct Job {                           // marshalled arguments and return future
		Args args;                         // call arguments (YOU DEFINE "Args")
		FWATCard result;                   // return future
		Job( Args args ) : args( args ) {}
	};

	std::queue<struct Job *> jobList;
	
	_Task Courier {
		Bank& bank;

		int doWithdraw( unsigned int id, unsigned int amount, WATCard* card );
		void main();
		Courier( Bank& b )
		: bank( b ) {}
	};                 // communicates with bank

	Courier *couriers;
	Printer &printer;
	Bank &bank;
	unsigned int numCouriers;

	void main();
public:
	_Event Lost {};                        // uC++ exception type, like "struct"
	WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
	FWATCard create( unsigned int sid, unsigned int amount );
	FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
	Job *requestWork();
};
