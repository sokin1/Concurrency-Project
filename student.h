#pragma once

_Monitor Printer;
_Task NameServer;
_Task WATCardOffice;

_Task Student {
	Printer &prt;
	NameServer &nameServer;
	WATCardOffice &cardOffice;
	unsigned int id;
	unsigned int maxPurchases;
	void main();
public:
	Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
	unsigned int maxPurchases );
};