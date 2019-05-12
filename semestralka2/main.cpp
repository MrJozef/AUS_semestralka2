#include <iostream>
#include <fstream>
#include "../structures/heap_monitor.h" 
#include "system.h"

using namespace std;

void zadavam();
void zadavamEnter();
int nacitajCeleKladneCisMensieRovne(int max, bool sNulou);
int nacitajCeleKladneCislo();
double nacitajKladneDouble();
Kolo nacitajKoloVolieb();

int main()
{
	initHeapMonitor();

	fstream* subor = new fstream;
	subor->open(CESTA_K_DATAM, ios::in);

	System* sys = nullptr;

	if (subor->is_open())
	{
		sys = new System(subor);
		subor->close();

		bool pokracovat = true;
		string pom = "";
		int pocetOd;
		int pocetDo;
		double ucastOd;
		double ucastDo;
		Kolo zvoleneKolo;
		TypUzemnejJednotky typJednotky;

		while (pokracovat)
		{
			system("cls");
			cout << "  ~~  2. semestralna praca - Jozef Kubik  ~~\n\n";
			cout << "  1) Vypisanie informacii o uzemnych jednotkach\n  2) Zoradenie prefiltrovanych uzemnych jednotiek\n";
			cout << "  0) Koniec\n\n" << endl;

			switch (nacitajCeleKladneCisMensieRovne(POCET_POLOZIEK_MENU, true))
			{
			case 1:
				cout << "Uzemne jednotky chcete vyberat podla (filtra):\n  1) Nazvu\n  2) Zapisanych volicov\n  3) Ucasti\n" << endl;

				switch(nacitajCeleKladneCisMensieRovne(POCET_POUZIT_FILTROV, false))
				{
				case 1:
					cout << "Chcete hladat:\n  1) Kraj\n  2) Okres\n  3) Obec\n" << endl;

					switch (nacitajCeleKladneCisMensieRovne(POCET_TYPOV_UZEM_JEDNOTIEK, false))
					{
					case 1:
						cout << "Zadajte nazov kraja:" << endl;
						zadavam();
						cin.ignore();
						getline(std::cin, pom);
						sys->filtKraje(pom);
						break;
					case 2:
						cout << "Zadajte nazov okresu:" << endl;
						zadavam();
						cin.ignore();
						getline(std::cin, pom);
						sys->filtOkresy(pom);
						break;
					case 3:
						cout << "Zadajte nazov obce:" << endl;
						zadavam();
						cin.ignore();
						getline(std::cin, pom);
						sys->filtObce(pom);
						break;
					}
					break;

				case 2:
					cout << "Zadajte interval poctu opravnenych volicov v tvare <OD, DO>\nOD:\n";
					pocetOd = nacitajCeleKladneCislo();
					cout << "\nDO:\n";
					pocetDo = nacitajCeleKladneCislo();

					if (pocetOd <= pocetDo)
					{
						zvoleneKolo = nacitajKoloVolieb();
						sys->filtVolicov(zvoleneKolo, pocetOd, pocetDo);
						cin.ignore();
					}
					else { cout << "Chyba - Nespravne zadany interval!" << endl; }
					break;

				case 3:
					cout << "Zadajte interval ucasti (v %) volicov na volbach v tvare <OD, DO>\nOD (znak % nepiste):\n";
					ucastOd = nacitajKladneDouble();
					cout << "\nDO (znak % nepiste):\n";
					ucastDo = nacitajKladneDouble();

					if (ucastOd <= ucastDo)
					{
						zvoleneKolo = nacitajKoloVolieb();
						sys->filtUcasti(zvoleneKolo, ucastOd, ucastDo);
						cin.ignore();
					}
					else { cout << "Chyba - Nespravne zadany interval!" << endl; }
					break;
				}
				zadavamEnter();
				break;


			case 2:
				cout << "Obce maju patrit ku:\n  1) Kraju\n  2) Okresu" << endl;
				if (nacitajCeleKladneCisMensieRovne(2, false) == 1)
				{
					cout << "Zadajte nazov kraja, ku ktoremu patri obec:" << endl;
					getline(std::cin, pom);
					typJednotky = typ_kraj;
				}
				else
				{
					cout << "Zadajte nazov okresu, ku ktoremu patri obec:" << endl;
					getline(std::cin, pom);
					typJednotky = typ_okres;
				}
				cout << "Zadajte interval ucasti (v %) volicov na volbach v tvare <OD, DO>\nOD (znak % nepiste):\n";
				ucastOd = nacitajKladneDouble();
				cout << "\nDO (znak % nepiste):\n";
				ucastDo = nacitajKladneDouble();

				if (ucastOd <= ucastDo)
				{
					zvoleneKolo = nacitajKoloVolieb();
					sys->zorad(pom, typJednotky, zvoleneKolo, ucastOd, ucastDo);
					cin.ignore();
				}
				else { cout << "Chyba - Nespravne zadany interval!" << endl; }

				break;

			case 0:
			default:
				pokracovat = false;
			}
		}
	}
	else
	{
		cout << "Chyba - Nepodarilo sa otvorit subor s datami!" << endl;
	}

	cout << "\n\nKoniec programu - stlacte <Enter> pre ukoncenie" << endl;
	cin.get();

	delete subor;
	delete sys;		//mozem bez obav deletovat nullptr
	return 0;
}

void zadavam() { cout << ">> "; }

void zadavamEnter() { cout << "Pre pokracovanie stlacte <Enter>\n"; cin.ignore(); zadavam(); }

int nacitajCeleKladneCisMensieRovne(int max, bool sNulou)
{
	int cislo = nacitajCeleKladneCislo();

	while ((cislo > max) || (!sNulou && cislo <= 0))
	{

		cout << "Zadane cislo nie je mensie, rovne " << to_string(max) << " a sucasne vacsie";
		if (sNulou)
		{
			cout << ", rovne 0!" << endl;
		}
		else
		{
			cout << " ako 0!" << endl;
		}

		cislo = nacitajCeleKladneCislo();
	}

	return cislo;
}

int nacitajCeleKladneCislo()
{
	bool zlyVstup = false;
	string pom;
	cout << "Zadajte cele, kladne cislo:" << endl;
	zadavam();
	cin >> pom;

	for (unsigned int i = 0; i < pom.size(); i++)
	{
		if (!(pom[i] >= '0' && pom[i] <= '9'))
		{
			zlyVstup = true;
			break;
		}
	}

	while (zlyVstup)
	{
		cout << "Zly vstup! Zadajte cele, kladne cislo:" << endl;
		zadavam();
		cin >> pom;
		zlyVstup = false;

		for (unsigned int i = 0; i < pom.size(); i++)
		{
			if (!(pom[i] >= '0' && pom[i] <= '9'))
			{
				zlyVstup = true;
				break;
			}
		}
	}

	return stoi(pom);
}

double nacitajKladneDouble()
{
	bool zlyVstup = false;
	string pom;
	cout << "Zadajte desatinne cislo (pouzite des. bodku):" << endl;
	zadavam();
	cin >> pom;

	for (unsigned int i = 0; i < pom.size(); i++)
	{
		if (!((pom[i] >= '0' && pom[i] <= '9') || pom[i] == '.'))
		{
			zlyVstup = true;
			break;
		}
	}

	while (zlyVstup)
	{
		cout << "Zly vstup! Zadajte desatinne cislo (pouzite des. bodku):" << endl;
		zadavam();
		cin >> pom;
		zlyVstup = false;

		for (unsigned int i = 0; i < pom.size(); i++)
		{
			if (!((pom[i] >= '0' && pom[i] <= '9') || pom[i] == '.'))
			{
				zlyVstup = true;
				break;
			}
		}
	}

	return stod(pom);
}

Kolo nacitajKoloVolieb()
{
	cout << "\nZadany interval sa vztahuje na:\n  1) 1. kolo volieb\n  2) 2. kolo volieb" << endl;
	if (nacitajCeleKladneCisMensieRovne(POCET_KOL, false) == 1)
	{
		return prve;
	}
	return druhe;
}