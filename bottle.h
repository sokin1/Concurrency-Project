#pragma once
#include "truck.h"

_Monitor Printer;
_Task NameServer;
_Monitor MPRNG;

_Task BottlingPlant {
    Printer &prt;
		NameServer &nameServer;
		unsigned int numVendingMachines;
		unsigned int maxShippedPerFlavour;
		unsigned int maxStockPerFlavour;
    unsigned int timeBetweenShipments;
		void main();
		unsigned int production[4];
		bool isClosed;
  public:
    BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments );
    bool getShipment( unsigned int cargo[] );
};