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
	Obec* pomSmernik;

	obce_ = new structures::UnsortedSequenceTable<std::string, Obec*>(pocetObci);
	for (int i = 0; i < pocetObci; i++)
	{
		inSubor->ignore();
		getline(*inSubor, novaUzJednotka);
		if (staraUzJednotka != novaUzJednotka)
		{
			staraUzJednotka = novaUzJednotka;
			cisVysJednotky++;
		}

		pomSmernik = new Obec(inSubor, (*okresy_)[cisVysJednotky]);
		obce_->insert(pomSmernik->dajNazov(), pomSmernik);
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
	/*kriteriumVolici_->set(prve);
	filterVolici_->set(400000, 450000);
	if (filterVolici_->ohodnot((*kraje_)[1], kriteriumVolici_))
		cout << "Kraj ma stanovenu ucast volicov!" << endl;

	kriteriumPrislusnost_->set((*okresy_)[0]);
	filterPrislusnost_->set(true);
	if (filterPrislusnost_->ohodnot((*obce_)[1], kriteriumPrislusnost_))
		cout << "patri!" << endl;*/
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

	pom = static_cast<int>(obce_->size());
	for (int i = 0; i < pom; i++)
	{
		delete obce_->getItemAtIndex(i).accessData();
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

void System::filtKraje(string nazovKraja)
{
	int pom = kraje_->size();
	filterNazov_->set(nazovKraja);
	for (int i = 0; i < pom; i++)
	{
		if (filterNazov_->ohodnot((*kraje_)[i], kriteriumNazov_))
		{
			plnyVypis((*kraje_)[i]);
			break;
		}
	}
}//todo doplnit ak nic nenaslo tak - nenasiel sa s danym nazvom..

void System::filtOkresy(string nazovOkresu)
{
	int pom = okresy_->size();
	filterNazov_->set(nazovOkresu);
	for (int i = 0; i < pom; i++)
	{
		if (filterNazov_->ohodnot((*okresy_)[i], kriteriumNazov_))
		{
			plnyVypis((*okresy_)[i]);
			break;
		}
	}
}

void System::filtObce(string nazovObce)
{
	int pom = obce_->size();
	Obec* pomObec;
	filterNazov_->set(nazovObce);
	if (obce_->tryFind(nazovObce, pomObec))
	{
		plnyVypis(pomObec);
	}
}

void System::plnyVypis(UzemnaJednotka* uzJednotka)
{
	cout << kriteriumNazov_->ohodnot(uzJednotka);

	if (uzJednotka->dajVyssiuJednotku() != nullptr)
	{
		cout << "  ->  " << kriteriumNazov_->ohodnot(uzJednotka->dajVyssiuJednotku());

		if (uzJednotka->dajVyssiuJednotku()->dajVyssiuJednotku() != nullptr)
		{
			cout << "  ->  " << kriteriumNazov_->ohodnot(uzJednotka->dajVyssiuJednotku()->dajVyssiuJednotku());
		}
	}

	for (int i = 0; i < POCET_KOL; i++)
	{
		kriteriumVolici_->set(static_cast<Kolo>(i));
		cout << "\n\nKolo: " << (i + 1) << ".\nPocet volicov:  " << kriteriumVolici_->ohodnot(uzJednotka) << endl;
		kriteriumVydaneObalky_->set(static_cast<Kolo>(i));
		cout << "Vydane obalky:  " << kriteriumVydaneObalky_->ohodnot(uzJednotka) << endl;
		kriteriumUcast_->set(static_cast<Kolo>(i));
		cout << "Ucast dosiahla:  " << kriteriumUcast_->ohodnot(uzJednotka) << "%" << endl;
		kriteriumOdovzdaneObalky_->set(static_cast<Kolo>(i));
		cout << "Odovzdane obalky:  " << kriteriumOdovzdaneObalky_->ohodnot(uzJednotka) << endl;
		kriteriumPlatneHlasy_->set(static_cast<Kolo>(i));
		cout << "Platne hlasy:  " << kriteriumPlatneHlasy_->ohodnot(uzJednotka) << endl;
	}
}
