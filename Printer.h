#ifndef PRINTER_H
#define PRINTER_H

_Monitor Printer {
	std::vector<char> ch; //state buffer
	std::vector<int> num1; //number buffer
	std::vector<int> num2;
	unsigned int total;
	unsigned int student;
	unsigned int machine;
	unsigned int courier;
	void flush() {
		for (unsigned int i = 0; i < ch.size(); i++) {
			if (ch[i]) {
				if (ch[i]=='.') cout <<"...";
				else cout <<ch[i]; //print characters as is; vector modified before calling flush
			}
			if (num1[i]!=-1) {
				cout <<":" <<num1[i]; //if number exists print
				num1[i] = -1;
			}
			if (num2[i]!=-1) {
				cout <<":" <<num2[i] <<"\t";
				num2[i] = -1;
			}
			else
				cout <<"\t";

		}
		ch.clear(); //reset ch
		cout <<endl;
		ch.resize(total);
	}
  public:
    enum Kind { Parent, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier };
    Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers );
    void print( Kind kind, char state );
    void print( Kind kind, char state, int value1 );
    void print( Kind kind, char state, int value1, int value2 );
    void print( Kind kind, unsigned int lid, char state );
    void print( Kind kind, unsigned int lid, char state, int value1 );
    void print( Kind kind, unsigned int lid, char state, int value1, int value2 );
};

#endif // PRINTER_H
