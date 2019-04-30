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
private:
	///<summary>Met�da, ktor� na��ta objekt zo s�boru, volan� kon�truktorom</summary>
	void fromSubor(fstream* inSubor);
};