#pragma once
#include "../structures/array/array.h"
#include "../structures/heap_monitor.h"
#include "const.h"

using namespace std;

class UzemnaJednotka
{
private:
	
	structures::Array<int>* zapisaniVolici_;
	structures::Array<int>* vydaneObalky_;
	structures::Array<double>* ucastPercent_;
	structures::Array<int>* odovzdaneObalky_;
	structures::Array<int>* platneHlasy_;

public:
	string nazov_;	//todo toto private!
	void toSubor(fstream* outSubor);

	///<summary>Konštruktor pre naèítavanie zo súboru</summary>
	UzemnaJednotka(fstream* inSubor);
	~UzemnaJednotka();

	string dajNazov();
	///<summary>Metóda, ktorá vráti pointer na vyššiu územnu jednotku do kt. patrí, napr. Okres vráti pointer na Kraj</summary>
	virtual UzemnaJednotka* dajVyssiuJednotku() = 0;
private:
	///<summary>Metóda, ktorá naèíta objekt zo súboru, volaná konštruktorom</summary>
	void fromSubor(fstream* inSubor);

};