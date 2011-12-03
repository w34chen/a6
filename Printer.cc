#include "Printer.h"

Printer::Printer(unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers ) {
	//print the initial:
	//Parent  WATOff Names...
	//******* ******* ...
	total = 5+numStudents+numVendingMachines+numCouriers;
	student = numStudents;
	machine = numVendingMachines;
	courier = numCouriers;

	//and size the ch and num vectors with initialization values
	cout <<setw(6) <<"Parent" <<"WATOff" <<"Names" <<"Truck" <<"Plant";
	for (unsigned int i = 0; i < numStudents; i++)
		cout <<setw(6) <<"Stud:" <<i;
	for (unsigned int i = 0; i < numVendingMachines; i++)
		cout <<setw(6) <<"Mach:" <<i;
	for (unsigned int i = 0; i < numVendingMachines; i++)
		cout <<setw(6) <<"Cour:" <<i;
	cout <<endl;

	for (unsigned int i = 0; i < total; i++)
		cout <<"******* ";
	cout <<endl;

	ch.resize(total);
	num1.resize(total);
	num2.resize(total);
}

void Printer::print(Kind kind, char state ) {
	flush();
	//occupy ch and num with new values
	ch[(int)kind] = state;
}

//function only called when printing F. V # are printed through numBLock
void Printer::print(Kind kind, char state, int value1 ) {
	if (ch[(int)kind] != state)
		flush();

	//occupy ch and num with new values
	ch[(int)kind] = state;
	num1[(int)kind] = value1;
}

void Printer::print(Kind kind, char state, int value1, int value2) {
	//only flush if there is a change in state
	if (ch[(int)kind] != state)
		flush();
	ch[(int)kind] = state;
	num1[(int)kind] =value1;
	num2[(int)kind] =value2;
}

void Printer::print(Kind kind, unsigned int lid, char state) {
	unsigned int index;
	//only flush if there is a change in state
	if (kind == Student)
		index = (int)Student+lid;
	else if (kind == Vending)
		index = (int)Student+student+lid; //index is after all students
	else if (kind == Courier)
		index = (int)Student+student+machine+lid; //index is after all students and vending machines
	if (ch[index] != state)
		flush();
	ch[(int)kind] = state;
}

void Printer::print(Kind kind, unsigned int lid, char state, int value1 ) {
	unsigned int index;
	//only flush if there is a change in state
	if (kind == Student)
		index = (int)Student+lid;
	else if (kind == Vending)
		index = (int)Student+student+lid; //index is after all students
	else if (kind == Courier)
		index = (int)Student+student+machine+lid; //index is after all students and vending machines
	if (ch[index] != state)
		flush();
	ch[index] = state;
	num1[index] = value1;
}

void Printer::print(Kind kind, unsigned int lid, char state, int value1, int value2 ) {
	unsigned int index;
	//only flush if there is a change in state
	if (kind == Student)
		index = (int)Student+lid;
	else if (kind == Vending)
		index = (int)Student+student+lid; //index is after all students
	else if (kind == Courier)
		index = (int)Student+student+machine+lid; //index is after all students and vending machines
	if (ch[index] != state)
		flush();
	ch[(int)kind] = state;
	num1[index] = value1;
	num2[index] = value2;
}
