#pragma once
#include "../structures/heap_monitor.h"
#include "../structures/list/linked_list.h"
#include "kraj.h"
#include "okres.h"
#include "obec.h"
#include "kNazov.h"
#include "kZapisaniVolici.h"
#include "kUcast.h"
#include "kVydaneObalky.h"
#include "kOdovzdaneObalky.h"
#include "kPlatneHlasy.h"
#include "kPrislusnostObce.h"
#include "fNazov.h"
#include "fZapisaniVolici.h"
#include "fUcast.h"
#include "fPrislusnostObce.h"

class System
{
private:
	//todo docasne struktury
	structures::Array<Kraj*>* kraje_;
	structures::Array<Okres*>* okresy_;
	structures::LinkedList<Obec*>* obce_;

	KNazov* kriteriumNazov_;
	KZapisaniVolici* kriteriumVolici_;
	KVydaneObalky* kriteriumVydaneObalky_;
	KUcast* kriteriumUcast_;
	KOdovzdaneObalky* kriteriumOdovzdaneObalky_;
	KPlatneHlasy* kriteriumPlatneHlasy_;
	KPrislusnostObce* kriteriumPrislusnost_;

	FNazov* filterNazov_;
	FZapisaniVolici* filterVolici_;
	FUcast* filterUcast;
	FPrislusnostObce* filterPrislusnost_;

public:
	///<summary>Konštruktor pre naèítavanie zo súboru</summary>
	System(fstream* inSubor);
	~System();
};