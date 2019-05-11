#include "../structures/heap_monitor.h"
#include "system.h"


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


	//pripravenie vsetkych kriterii a filtrov

	kriteriumNazov_ = new KNazov();
	kriteriumVolici_ = new KZapisaniVolici();
	kriteriumVydaneObalky_ = new KVydaneObalky();
	kriteriumUcast_ = new KUcast();
	kriteriumOdovzdaneObalky_ = new KOdovzdaneObalky();
	kriteriumPlatneHlasy_ = new KPlatneHlasy();
	kriteriumPrislusnost_ = new KPrislusnostObce();

	filterNazov_ = new FNazov();
	filterVolici_ = new FZapisaniVolici();
	filterUcast_ = new FUcast();
	filterPrislusnost_ = new FPrislusnostObce();

	//todo zmazat tieto skusky
	kriteriumVolici_->set(prve);
	filterVolici_->set(400000, 450000);
	if (filterVolici_->ohodnot((*kraje_)[1], kriteriumVolici_))
		cout << "Kraj ma stanovenu ucast volicov!" << endl;

	kriteriumPrislusnost_->set((*okresy_)[0]);
	filterPrislusnost_->set(true);
	if (filterPrislusnost_->ohodnot((*obce_)[1], kriteriumPrislusnost_))
		cout << "patri!" << endl;
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


	//delete kriterii a filtrov
	delete kriteriumNazov_;
	delete kriteriumVolici_;
	delete kriteriumVydaneObalky_;
	delete kriteriumUcast_;
	delete kriteriumOdovzdaneObalky_;
	delete kriteriumPlatneHlasy_;
	delete kriteriumPrislusnost_;
	kriteriumNazov_ = nullptr;
	kriteriumVolici_ = nullptr;
	kriteriumVydaneObalky_ = nullptr;
	kriteriumUcast_ = nullptr;
	kriteriumOdovzdaneObalky_ = nullptr;
	kriteriumPlatneHlasy_ = nullptr;
	kriteriumPrislusnost_ = nullptr;

	delete filterNazov_;
	delete filterVolici_;
	delete filterUcast_;
	delete filterPrislusnost_;
	filterNazov_ = nullptr;
	filterVolici_ = nullptr;
	filterUcast_ = nullptr;
	filterPrislusnost_ = nullptr;
}