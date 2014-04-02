_Task Parent {
    Printer printer;
    Bank bank;
    unsigned int numStudents;
    unsigned int parentDelay;
    void main();
  public:
    Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay );
};
