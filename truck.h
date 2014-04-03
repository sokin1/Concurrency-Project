#pragma once

_Monitor Printer;
_Task NameServer;
_Task BottlingPlant;

_Task Truck {
    Printer &prt;
		NameServer &nameServer;
		BottlingPlant &plant;
    unsigned int numVendingMachines;
		unsigned int maxStockPerFlavour;
		void main();
		unsigned int cargo[4];
  public:
    Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
};