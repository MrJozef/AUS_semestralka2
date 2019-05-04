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