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
	int dajZapisVolicov(int kolo);
	int dajVydaneObalky(int kolo);
	double dajUcastVPercent(int kolo);
	int dajOdovzdaneObalky(int kolo);
	int dajPlatneHlasy(int kolo);

	///<summary>Metóda, ktorá vráti pointer na vyššiu územnu jednotku do kt. patrí, napr. Okres vráti pointer na Kraj</summary>
	virtual UzemnaJednotka* dajVyssiuJednotku() = 0;
private:
	///<summary>Metóda, ktorá naèíta objekt zo súboru, volaná konštruktorom</summary>
	void fromSubor(fstream* inSubor);

	///<summary>Overí, èi takéto kolo prebehlo (èíslované od 0) - napr. ak mame 2 kola, tak su povolene hodnoty - 0 a 1</summary>
	bool overKolo(int kolo);
};