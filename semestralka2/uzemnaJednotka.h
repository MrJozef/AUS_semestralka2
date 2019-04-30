#pragma once
#include "../structures/array/array.h"
#include "../structures/heap_monitor.h"
#include "const.h"

using namespace std;

class UzemnaJednotka
{
private:
	string nazov_;
	structures::Array<int>* zapisaniVolici_;
	structures::Array<int>* vydaneObalky_;
	structures::Array<double>* ucastPercent_;
	structures::Array<int>* odovzdaneObalky_;
	structures::Array<int>* platneHlasy_;

public:
	///<summary>Konštruktor pre naèítavanie zo súboru</summary>
	UzemnaJednotka(fstream* inSubor);
	~UzemnaJednotka();

	string dajNazov();
private:
	///<summary>Metóda, ktorá naèíta objekt zo súboru, volaná konštruktorom</summary>
	void fromSubor(fstream* inSubor);
};