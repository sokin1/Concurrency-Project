#pragma once

_Monitor Printer { /* or _Cormonitor */
	unsigned int numStudents;
	unsigned int numVendingMachines;
	unsigned int numCouriers;
	
	// Does not work for some reason
	// enum State_Parent {Start='S', Deposit='D', Finish='F'};
	// enum State_WATCard {Start='S', CourierRComplete='W', CreationRComplete='C', TransferRComplete='T', Finish='F'};
	// enum State_NameServer {Start='S', RegVendMachine='R', NewVendMachine='N', Finish='F'};
	// enum State_Truck {Start='S', PickedUp='P', BeginDelivery='d', UnsuccessFill='U', EndDelivery='D', Finish='F'};
	// enum State_BottlingPlant {Start='S', GenSoda='G', PickedUp='P', Finish='F'};
	// enum State_Student {Start='S', SelectVendMachine='V', Bought='B', WATCardLost='L', Finish='F'};
	// enum State_VendingMachine {Start='S', StartReload='r', CompleteReload='R', StudentBought='B', Finish='F'};
	// enum State_Courier {Start='S', StartFundTransfer='t', CompleteFundTransfer='T', Finish='F'};
	
	void flush();
	void flush_finish( unsigned int id );
	unsigned int numOfColumns;
	
public:
	enum Kind { Parent, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier };
	enum State {Start='S', Deposit='D', Finish='F', CourierRComplete='W', CreationRComplete='C', TransferRComplete='T',
		RegVendMachine='R', NewVendMachine='N', PickedUp='P', BeginDelivery='d', UnsuccessFill='U', EndDelivery='D',
		GenSoda='G', SelectVendMachine='V', Bought='B', WATCardLost='L', StartReload='r', CompleteReload='R',
		StudentBought='B', StartFundTransfer='t', CompleteFundTransfer='T'};
	Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers );
	void print( Kind kind, char state );
	void print( Kind kind, char state, int value1 );
	void print( Kind kind, char state, int value1, int value2 );
	void print( Kind kind, unsigned int lid, char state );
	void print( Kind kind, unsigned int lid, char state, int value1 );
	void print( Kind kind, unsigned int lid, char state, int value1, int value2 );
	~Printer();
	
private:
	struct PrintBuffer {
		Printer::Kind kind;
		bool buffered;
		Printer::State state;
		int value1;
		int value2;
		int numOfArguments;
	};
	PrintBuffer *buffer;
};