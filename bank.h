#pragma once

_Monitor Bank {
	struct Account {
		unsigned int id;
		unsigned int amount;
	};
	struct Account *studentAccount;
	unsigned int numStudents;
public:
	Bank( unsigned int numStudents );
	void deposit( unsigned int id, unsigned int amount );
	void withdraw( unsigned int id, unsigned int amount );
	~Bank();
};
