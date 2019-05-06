#include "../structures/heap_monitor.h"
#include "system.h"

#include "kNazov.h"
#include "kZapisaniVolici.h"
#include "kUcast.h"
#include "kVydaneObalky.h"
#include "kOdovzdaneObalky.h"
#include "kPlatneHlasy.h"
#include "kPrislusnostObce.h"


System::System(fstream* inSubor)
{
	int pocetKrajov;
	int pocetOkresov;
	int pocetObci;
	(*inSubor) >> pocetKrajov;
	(*inSubor) >> pocetOkresov;
	(*inSubor) >> pocetObci;

	string staraUzJednotka;
	string novaUzJednotka;
	int cisVysJednotky = -1;

	kraje_ = new structures::Array<Kraj*>(pocetKrajov);
	for (int i = 0; i < pocetKrajov; i++)
	{
		(*inSubor).ignore();
		(*kraje_)[i] = new Kraj(inSubor);
	}

	okresy_ = new structures::Array<Okres*>(pocetOkresov);
	for (int i = 0; i < pocetOkresov; i++)
	{
		inSubor->ignore();
		getline(*inSubor, novaUzJednotka);
		if(staraUzJednotka != novaUzJednotka)
		{
			staraUzJednotka = novaUzJednotka;
			cisVysJednotky++;
		}

		(*okresy_)[i] = new Okres(inSubor, (*kraje_)[cisVysJednotky]);
	}


	staraUzJednotka = "";
	cisVysJednotky = -1;

	obce_ = new structures::LinkedList<Obec*>;
	for (int i = 0; i < pocetObci; i++)
	{
		inSubor->ignore();
		getline(*inSubor, novaUzJednotka);
		if (staraUzJednotka != novaUzJednotka)
		{
			staraUzJednotka = novaUzJednotka;
			cisVysJednotky++;
		}

		obce_->add(new Obec(inSubor, (*okresy_)[cisVysJednotky]));
	}

	KNazov* kriteriumNaNazov = new KNazov();
	cout << kriteriumNaNazov->ohodnot((*obce_)[2]) << endl;
	KZapisaniVolici* kriteriumVolici = new KZapisaniVolici(obe);
	cout << kriteriumVolici->ohodnot((*kraje_)[2]) << endl;
	KUcast* kriteriumUcast = new KUcast(obe);
	cout << kriteriumUcast->ohodnot((*kraje_)[2]) << endl;

	KVydaneObalky* kriteriumVydaneObalky = new KVydaneObalky(obe);
	cout << kriteriumVydaneObalky->ohodnot((*okresy_)[0]) << endl;

	KOdovzdaneObalky* kriteriumOdovzdaneObalky = new KOdovzdaneObalky(obe);
	cout << kriteriumOdovzdaneObalky->ohodnot((*okresy_)[0]) << endl;

	KPlatneHlasy* kriteriumPlatneHlasy = new KPlatneHlasy(obe);
	cout << kriteriumPlatneHlasy->ohodnot((*okresy_)[4]) << endl;
	KPrislusnostObce* kriteriumPrislusnost = new KPrislusnostObce((*kraje_)[7]);
	if (kriteriumPrislusnost->ohodnot((*obce_)[2925]))
		cout << "Patrim" << endl;
}


System::~System()
{
	int pom = kraje_->size();
	for (int i = 0; i < pom; i++)
	{
		delete (*kraje_)[i];
	}
	delete kraje_;

	pom = okresy_->size();
	for (int i = 0; i < pom; i++)
	{
		delete (*okresy_)[i];
	}
	delete okresy_;

	for (Obec* obec : *obce_)
	{
		delete obec;
	}
	delete obce_;

	kraje_ = nullptr;
	okresy_ = nullptr;
	obce_ = nullptr;
}