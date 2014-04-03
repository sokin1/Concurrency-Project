#pragma once

_Monitor Printer;
_Task NameServer;
class WATCard;

_Task VendingMachine {
    Printer &prt;
		NameServer &nameServer;
		unsigned int id; 
		unsigned int sodaCost;
    unsigned int maxStockPerFlavour;
		void main();
		unsigned int stock[4];
		uCondition lock;
  public:
    enum Flavours { F1, F2, F3, F4 };      // 4 flavours of soda (YOU DEFINE)
    enum Status { BUY, STOCK, FUNDS };     // purchase status: successful buy, out of stock, insufficient funds
    VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maxStockPerFlavour );
    Status buy( Flavours flavour, WATCard &card );
    unsigned int *inventory();
    void restocked();
    _Nomutex unsigned int cost();
    _Nomutex unsigned int getId();
};