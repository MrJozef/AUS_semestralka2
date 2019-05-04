#include <iostream>
#include <fstream>
#include "../structures/heap_monitor.h" 
#include "system.h"

using namespace std;

int main()
{
	initHeapMonitor();

	fstream* subor = new fstream;
	subor->open(CESTA_K_DATAM, ios::in);

	System* sys = nullptr;

	if (subor->is_open())
	{
		sys = new System(subor);
		cout << "Data boli uspesne nacitane!" << endl;
		sys->zmenNazvy();

		subor->close();
	}
	else
	{
		cout << "Chyba - Nepodarilo sa otvorit subor s datami!" << endl;
	}

	
	delete subor;
	delete sys;		//mozem bez obav deletovat nullptr

	cin.get();
	return 0;
}