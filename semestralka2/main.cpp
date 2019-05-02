#include <iostream>
#include <fstream>
#include "../structures/heap_monitor.h" 
#include "kraj.h"

using namespace std;
//todo pridat system.h/.cpp a asi aj ArrayList/LinkedList
int main()
{
	initHeapMonitor();

	Kraj* jedna;
	Kraj* dva;
	Kraj* tri;

	fstream* subor = new fstream;
	subor->open(CESTA_K_DATAM, ios::in);

	jedna = new Kraj(subor);
	dva = new Kraj(subor);
	tri = new Kraj(subor);

	cout << tri->dajNazov();
	cout << dva->dajNazov();

	subor->close();
	cin.get();

	delete jedna;
	delete dva;
	delete tri;

	delete subor;
	return 0;
}