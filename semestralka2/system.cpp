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
	filterPrislusnost_->set(true);
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
}

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
	Obec* pomObec;
	filterNazov_->set(nazovObce);
	if (obce_->tryFind(nazovObce, pomObec))
	{
		plnyVypis(pomObec);
	}
}

void System::filtVolicov(Kolo kolo, int pocetVolOd, int pocetVolDo)
{
	kriteriumVolici_->set(kolo);
	filterVolici_->set(pocetVolOd, pocetVolDo);

	int pom = kraje_->size();
	for (int i = 0; i < pom; i++)
	{
		if (filterVolici_->ohodnot((*kraje_)[i], kriteriumVolici_))
		{
			plnyVypis((*kraje_)[i]);
		}
	}

	pom = okresy_->size();
	for (int i = 0; i < pom; i++)
	{
		if (filterVolici_->ohodnot((*okresy_)[i], kriteriumVolici_))
		{
			plnyVypis((*okresy_)[i]);
		}
	}

	pom = obce_->size();
	for (int i = 0; i < pom; i++)
	{
		if (filterVolici_->ohodnot((*obce_).getItemAtIndex(i).accessData(), kriteriumVolici_))
		{
			plnyVypis((*obce_).getItemAtIndex(i).accessData());
		}
	}
}

void System::filtUcasti(Kolo kolo, double percentOd, double percentDo)
{
	kriteriumUcast_->set(kolo);
	filterUcast_->set(percentOd, percentDo);

	int pom = kraje_->size();
	for (int i = 0; i < pom; i++)
	{
		if (filterUcast_->ohodnot((*kraje_)[i], kriteriumUcast_))
		{
			plnyVypis((*kraje_)[i]);
		}
	}

	pom = okresy_->size();
	for (int i = 0; i < pom; i++)
	{
		if (filterUcast_->ohodnot((*okresy_)[i], kriteriumUcast_))
		{
			plnyVypis((*okresy_)[i]);
		}
	}

	pom = obce_->size();
	for (int i = 0; i < pom; i++)
	{
		if (filterUcast_->ohodnot((*obce_).getItemAtIndex(i).accessData(), kriteriumUcast_))
		{
			plnyVypis((*obce_).getItemAtIndex(i).accessData());
		}
	}
}

void System::zorad(string nazovUzJednotky, TypUzemnejJednotky typ, Kolo kolo, double percentOd, double percentDo)
{
	auto* tabulkaNaTriedenie = new structures::UnsortedSequenceTable<std::string, Obec*>();
	UzemnaJednotka* pointerNaJednotku = nullptr;
	if(typ == typ_kraj)
	{
		int pom = kraje_->size();
		for (int i = 0; i < pom; i++)
		{
			if (kriteriumNazov_->ohodnot((*kraje_)[i]) == nazovUzJednotky)
			{
				pointerNaJednotku = (*kraje_)[i];
				break;
			}
		}
	}
	else
	{
		int pom = okresy_->size();
		for (int i = 0; i < pom; i++)
		{
			if (kriteriumNazov_->ohodnot((*okresy_)[i]) == nazovUzJednotky)
			{
				pointerNaJednotku = (*okresy_)[i];
				break;
			}
		}
	}

	//pretriedujeme podla toho ci patria k danej vyssej jednotke
	if (pointerNaJednotku != nullptr)
	{
		kriteriumPrislusnost_->set(pointerNaJednotku);
		kriteriumUcast_->set(kolo);
		filterUcast_->set(percentOd, percentDo);

		int pom = obce_->size();
		for (int i = 0; i < pom; i++)
		{
			//ak obec patri k zadanemu vyssieme uz. celku a sucasne ma ucast od - do
			if (filterPrislusnost_->ohodnot((*obce_).getItemAtIndex(i).accessData(), kriteriumPrislusnost_) && filterUcast_->ohodnot((*obce_).getItemAtIndex(i).accessData(), kriteriumUcast_))
			{
				tabulkaNaTriedenie->insert((*obce_).getItemAtIndex(i).accessData()->dajNazov(), (*obce_).getItemAtIndex(i).accessData());
			}
		}

		//sortovanie
		structures::ShellSort<string, Obec*> ShellSort;
		ShellSort.sort(*tabulkaNaTriedenie);

		//vypis
		pom = tabulkaNaTriedenie->size();
		for (int i = 0; i < pom; i++)
		{
			ciastocnyVypis(tabulkaNaTriedenie->getItemAtIndex(i).accessData(), typ, kolo);
		}
		cout << "\n\n  ----------\n\n\n";

		pom--;
		for (int i = pom; i >= 0; i--)
		{
			ciastocnyVypis(tabulkaNaTriedenie->getItemAtIndex(i).accessData(), typ, kolo);
		}
	}
	else
	{
		cout << "Chyba - Zadana uzemna jednotka nebola najdena!" << endl;
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
	cout << "----------\n\n";
}

void System::ciastocnyVypis(UzemnaJednotka* uzJednotka, TypUzemnejJednotky typ, Kolo kolo)
{
	kriteriumUcast_->set(kolo);
	cout << kriteriumNazov_->ohodnot(uzJednotka);
	cout << "  ->  " << kriteriumNazov_->ohodnot(uzJednotka->dajVyssiuJednotku());
	if (typ == typ_kraj)
	{
		cout << "  ->  " << kriteriumNazov_->ohodnot(uzJednotka->dajVyssiuJednotku()->dajVyssiuJednotku());
	}
	cout << "  -  ucast: " << kriteriumUcast_->ohodnot(uzJednotka);
	cout << endl;
}
