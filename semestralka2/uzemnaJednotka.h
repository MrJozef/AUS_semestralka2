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
	///<summary>Kon�truktor pre na��tavanie zo s�boru</summary>
	UzemnaJednotka(fstream* inSubor);
	~UzemnaJednotka();

	string dajNazov();
	int dajZapisVolicov(int kolo);
	int dajVydaneObalky(int kolo);
	double dajUcastVPercent(int kolo);
	int dajOdovzdaneObalky(int kolo);
	int dajPlatneHlasy(int kolo);

	///<summary>Met�da, ktor� vr�ti pointer na vy��iu �zemnu jednotku do kt. patr�, napr. Okres vr�ti pointer na Kraj</summary>
	virtual UzemnaJednotka* dajVyssiuJednotku() = 0;
private:
	///<summary>Met�da, ktor� na��ta objekt zo s�boru, volan� kon�truktorom</summary>
	void fromSubor(fstream* inSubor);

	///<summary>Over�, �i tak�to kolo prebehlo (��slovan� od 0) - napr. ak mame 2 kola, tak su povolene hodnoty - 0 a 1</summary>
	bool overKolo(int kolo);
};