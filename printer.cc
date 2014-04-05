#include "printer.h"
#include <iostream>
using namespace std;

Printer::Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers ):
numStudents(numStudents), numVendingMachines(numVendingMachines), numCouriers(numCouriers){
	numOfColumns = 5 + numStudents + numVendingMachines + numCouriers;
	buffer = new PrintBuffer[numOfColumns];
	for( unsigned int i = 0; i < numOfColumns; i++ ) {
		buffer[i].numOfArguments = -1;
		buffer[i].buffered = false;
	}
	cout << "Parent\tWATOff\tNames\tTruck\tPlant\t";
	for( unsigned int i = 0; i < numStudents; i++ ) {
		cout << "Stud" << i << "\t";
	}
	for( unsigned int i = 0; i < numVendingMachines; i++ ) {
		cout << "Mach" << i << "\t";
	}
	for( unsigned int i = 0; i < numCouriers; i++ ) {
		cout << "Cour" << i << "\t";
	}
	cout << endl;
	for( unsigned int i = 0; i < numOfColumns; i++ ) {
		cout << "*******\t";
	}
	cout << endl;
}

// S has 0 or 1 or 2 arguments...
// B has 1 or 2 arguments...
// R has 0 or 1 arguments...
// P has 0 or 1 arguments...

void Printer::flush() {
	for( unsigned int i = 0; i < numOfColumns; i++ ) {
		if( buffer[i].buffered ) {
			switch( buffer[i].numOfArguments ) {
			case 0:
				cout << (char)buffer[i].state;
				break;
			case 1:
				cout << (char)buffer[i].state << buffer[i].value1;
				break;
			case 2:
				cout << (char)buffer[i].state << buffer[i].value1 << "," << buffer[i].value2;
				break;
			default:
				break;
			}
			buffer[i].numOfArguments = -1;
			buffer[i].buffered = false;
		}
		if( i != numOfColumns - 1 ) cout << '\t';
	}
	cout << endl;
}

void Printer::flush_finish( unsigned int id ) {
	for( unsigned int i = 0; i < numOfColumns; i++ ) {
		if( i == id ) {
			cout << (char)Printer::Finish;
		} else {
			cout << "...";
		}
		cout << '\t';
	}
	cout << endl;
}

void Printer::print( Kind kind, char state ){
	if( buffer[kind].buffered ) {
		flush();
	}
	if( state == Printer::Finish ) {
		flush_finish(kind);
		return;
	}
	buffer[kind].state = (Printer::State) state;
	buffer[kind].numOfArguments = 0;
	buffer[kind].buffered = true;
}

void Printer::print( Kind kind, char state, int value1 ){
	if( buffer[kind].buffered ) {
		flush();
	}
	buffer[kind].state = (Printer::State) state;
	buffer[kind].value1 = value1;
	buffer[kind].numOfArguments = 1;
	buffer[kind].buffered = true;
}

void Printer::print( Kind kind, char state, int value1, int value2 ){
	if( buffer[kind].buffered ) {
		flush();
	}
	buffer[kind].state = (Printer::State) state;
	buffer[kind].value1 = value1;
	buffer[kind].value2 = value2;
	buffer[kind].numOfArguments = 2;
	buffer[kind].buffered = true;
}

void Printer::print( Kind kind, unsigned int lid, char state ){
	int offset = kind;
	if (kind == Printer::Vending){
		offset = 5 + numStudents;
	} else if (kind == Printer::Courier){
		offset = 5 + numStudents + numVendingMachines;
	}
	
	if( buffer[offset+lid].buffered ) {
		flush();
	}
	if( state == Printer::Finish ) {
		flush_finish(offset+lid);
		return;
	}

	buffer[offset+lid].state = (Printer::State) state;
	buffer[offset+lid].numOfArguments = 0;
	buffer[offset+lid].buffered = true;
}

void Printer::print( Kind kind, unsigned int lid, char state, int value1 ){
	int offset = kind;
	if (kind == Printer::Vending){
		offset = 5 + numStudents;
	} else if (kind == Printer::Courier){
		offset = 5 + numStudents + numVendingMachines;
	}
	
	if( buffer[offset+lid].buffered ) {
		flush();
	}
	
	buffer[offset+lid].state = (Printer::State) state;
	buffer[offset+lid].value1 = value1;
	buffer[offset+lid].numOfArguments = 1;
	buffer[offset+lid].buffered = true;
}

void Printer::print( Kind kind, unsigned int lid, char state, int value1, int value2 ){
	int offset = kind;
	if (kind == Printer::Vending){
		offset = 5 + numStudents;
	} else if (kind == Printer::Courier){
		offset = 5 + numStudents + numVendingMachines;
	}
	
	if( buffer[offset+lid].buffered ) {
		flush();
	}

	buffer[offset+lid].state = (Printer::State) state;
	buffer[offset+lid].value1 = value1;
	buffer[offset+lid].value2 = value2;
	buffer[offset+lid].numOfArguments = 2;
	buffer[offset+lid].buffered = true;
}

Printer::~Printer(){
	cout << "***********************" << endl;
	delete [] buffer;
}