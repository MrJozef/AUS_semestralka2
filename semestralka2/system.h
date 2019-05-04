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
	///<summary>Kon�truktor pre na��tavanie zo s�boru</summary>
	System(fstream* inSubor);
	~System();

	void zmenNazvy();
};