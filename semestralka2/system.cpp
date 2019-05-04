#include "../structures/heap_monitor.h"
#include "system.h"
#include <iostream>


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


void System::zmenNazvy()		//todo delete
{
	structures::LinkedList<Obec*>* rovnakeObce = new structures::LinkedList<Obec*>();

	/*for (int i = 0;i<8;i++)
	{
		std::cout << (*kraje_)[i]->dajNazov() << endl;
	}

	for (int i = 0; i < 79; i++)
	{
		std::cout << (*okresy_)[i]->dajNazov() << endl;
	}

	for (Obec* obec : *obce_)
	{
		std::cout << obec->dajNazov() << endl;
	}*/

	string pom;
	for (Obec* obec : *obce_)
	{
		pom = obec->dajNazov();

		for (Obec* ob : *obce_)
		{
			if (pom == ob->dajNazov() && (obec != ob))
			{
				rovnakeObce->add(obec);
				break;
			}
		}
	}

	for (Obec* obec : *rovnakeObce)
	{
		obec->zmenNazov();
		std::cout << obec->dajNazov() << endl;
	}

	fstream* subor = new fstream;
	subor->open("../data/spracovane_data.txt", ios::out);

	*subor << 8 << endl;
	*subor << 79 << endl;
	*subor << 2926 << endl;

	for (int i = 0; i < 8; i++)
	{
		(*kraje_)[i]->toSubor(subor);
	}

	for (int i = 0; i < 79; i++)
	{
		*subor << (*(*okresy_)[i]->dajVyssiuJednotku()).dajNazov() << endl;
		(*okresy_)[i]->toSubor(subor);
	}

	for (Obec* obec : *obce_)
	{
		*subor << obec->dajVyssiuJednotku()->dajNazov() << endl;
		obec->toSubor(subor);
	}

	subor->close();
}