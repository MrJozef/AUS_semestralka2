#pragma once
#include "../structures/heap_monitor.h"
#include "../structures/list/linked_list.h"
#include "../structures/table/unsorted_sequence_table.h"
#include "../structures/table/sorting/shell_sort.h"
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
	structures::Array<Kraj*>* kraje_;
	structures::Array<Okres*>* okresy_;
	structures::UnsortedSequenceTable<std::string, Obec*>* obce_;

	KNazov* kriteriumNazov_;
	KZapisaniVolici* kriteriumVolici_;
	KVydaneObalky* kriteriumVydaneObalky_;
	KUcast* kriteriumUcast_;
	KOdovzdaneObalky* kriteriumOdovzdaneObalky_;
	KPlatneHlasy* kriteriumPlatneHlasy_;
	KPrislusnostObce* kriteriumPrislusnost_;

	FNazov* filterNazov_;
	FZapisaniVolici* filterVolici_;
	FUcast* filterUcast_;
	FPrislusnostObce* filterPrislusnost_;

public:
	///<summary>Konštruktor pre naèítavanie zo súboru</summary>
	System(fstream* inSubor);
	~System();

	///<summary>Funkcionalita 3 - filter podla nazvu pre kraje</summary>
	void filtKraje(string nazovKraja);
	///<summary>Funkcionalita 3 - filter podla nazvu pre kraje</summary>
	void filtOkresy(string nazovOkresu);
	///<summary>Funkcionalita 3 - filter podla nazvu pre kraje</summary>
	void filtObce(string nazovObce);
	///<summary>Funkcionalita 3 - filter podla poctu volicov, kt. volili vo zvolenom kole</summary>
	void filtVolicov(Kolo kolo, int pocetVolOd, int pocetVolDo);
	///<summary>Funkcionalita 3 - filter podla ucasti, kt. bola vo zvolenom kole</summary>
	void filtUcasti(Kolo kolo, double percentOd, double percentDo);
	///<summary>Zastresujuca metoda pre funkcionalitu c. 4</summary>
	void zorad(string nazovUzJednotky, TypUzemnejJednotky typ, Kolo kolo, double percentOd, double percentDo);

	///<summary>Vypise vsetky informacie o uzemnej jednotke, tak ako to vyzaduje funkcionalita 3</summary>
	void plnyVypis(UzemnaJednotka* uzJednotka);
	///<summary>Vypise ciastkove informacie o uzemnej jednotke, tak ako to vyzaduje funkcionalita 4</summary>
	void ciastocnyVypis(UzemnaJednotka* uzJednotka, TypUzemnejJednotky typ, Kolo kolo);
	
};