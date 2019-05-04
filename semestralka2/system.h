#pragma once
#include "../structures/heap_monitor.h"
#include "../structures/list/linked_list.h"
#include "kraj.h"
#include "okres.h"
#include "obec.h"


class System
{
private:
	//todo docasne struktury
	structures::Array<Kraj*>* kraje_;
	structures::Array<Okres*>* okresy_;
	structures::LinkedList<Obec*>* obce_;

public:
	///<summary>Konštruktor pre naèítavanie zo súboru</summary>
	System(fstream* inSubor);
	~System();

	void zmenNazvy();
};