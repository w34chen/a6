#include "Printer.h"

#include <iostream>
#include <iomanip>

using namespace std;

Printer::Printer(unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers ) {
	//print the initial:
	//Parent  WATOff Names...
	//******* ******* ...
	total = 5+numStudents+numVendingMachines+numCouriers;
	student = numStudents;
	machine = numVendingMachines;
	courier = numCouriers;

	ch.resize(total);
	num1.resize(total);
	num2.resize(total);

	//and size the ch and num vectors with initialization values
	cout  <<"Parent\t";
	cout  <<"WATOff\t";
	cout  <<"Names\t";
	cout  <<"Truck\t";
	cout  <<"Plant\t";
	for (unsigned int i = 0; i < numStudents; i++)
		cout  <<"Stud:" <<i <<"\t";
	for (unsigned int i = 0; i < numVendingMachines; i++)
		cout  <<"Mach:" <<i <<"\t";
	for (unsigned int i = 0; i < numCouriers; i++)
		cout  <<"Cour:" <<i <<"\t";
	cout <<endl;

	for (unsigned int i = 0; i < total; i++) {
		cout <<"******* ";
		num1[i] = -1;
		num2[i] = -1;
	}
	cout <<endl;
}

void Printer::print(Kind kind, char state ) {
	if (ch[(int)kind] && ch[(int)kind] != state)
		flush();

	if (state=='F') {
		for (unsigned int i = 0; i < ch.size(); i++) {
			ch[i] = '.';
		}
		ch[(int)kind] = state;
		flush();
	} else
		ch[(int)kind] = state;

}

//function only called when printing F. V # are printed through numBLock
void Printer::print(Kind kind, char state, int value1 ) {
	if (ch[(int)kind] && ch[(int)kind] != state)
		flush();

	//occupy ch and num with new values
	ch[(int)kind] = state;
	num1[(int)kind] = value1;
}

void Printer::print(Kind kind, char state, int value1, int value2) {
	//only flush if there is a change in state
	if (ch[(int)kind] && ch[(int)kind] != state)
		flush();
	ch[(int)kind] = state;
	num1[(int)kind] =value1;
	num2[(int)kind] =value2;
}

void Printer::print(Kind kind, unsigned int lid, char state) {
	cout <<"print " <<kind <<" lid " <<lid <<" state " <<state <<endl;
	unsigned int index;
	//only flush if there is a change in state
	if (kind == Student)
		index = (int)Student+lid;
	else if (kind == Vending)
		index = (int)Student+student+lid; //index is after all students
	else if (kind == Courier)
		index = (int)Student+student+machine+lid; //index is after all students and vending machines

	if (ch[index] && ch[index] != state)
		flush();

	if (state=='F') {
		for (unsigned int i = 0; i < ch.size(); i++) {
			ch[i] = '.';
		}
		ch[index] = state;
		flush();
	} else
		ch[index] = state;
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
	if (ch[index] && ch[index] != state)
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
	if (ch[index] && ch[index] != state)
		flush();
	ch[index] = state;
	num1[index] = value1;
	num2[index] = value2;
}
