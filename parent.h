#pragma once

_Monitor Printer;
_Monitor Bank;

_Task Parent {
    Printer &printer;
    Bank &bank;
    unsigned int numStudents;
    unsigned int parentalDelay;
    void main();
  public:
    Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay );
};
