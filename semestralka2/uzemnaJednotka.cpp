#include "../structures/heap_monitor.h"
#include "uzemnaJednotka.h"


UzemnaJednotka::UzemnaJednotka(fstream* inSubor)
{
	fromSubor(inSubor);
}

UzemnaJednotka::~UzemnaJednotka()
{
	delete zapisaniVolici_;
	delete vydaneObalky_;
	delete ucastPercent_;
	delete odovzdaneObalky_;
	delete platneHlasy_;
	zapisaniVolici_ = nullptr;
	vydaneObalky_ = nullptr;
	ucastPercent_ = nullptr;
	odovzdaneObalky_ = nullptr;
	platneHlasy_ = nullptr;
}

void UzemnaJednotka::fromSubor(fstream* inSubor)
{
	zapisaniVolici_ = new structures::Array<int>(POCET_KOL);
	vydaneObalky_ = new structures::Array<int>(POCET_KOL);
	ucastPercent_ = new structures::Array<double>(POCET_KOL);
	odovzdaneObalky_ = new structures::Array<int>(POCET_KOL);
	platneHlasy_ = new structures::Array<int>(POCET_KOL);

	getline(*inSubor, nazov_);
	for (int kolo = 0; kolo < POCET_KOL; kolo++)
	{
		*inSubor >> (*zapisaniVolici_)[kolo];
		*inSubor >> (*vydaneObalky_)[kolo];
		*inSubor >> (*ucastPercent_)[kolo];
		*inSubor >> (*odovzdaneObalky_)[kolo];
		*inSubor >> (*platneHlasy_)[kolo];
	}
}

bool UzemnaJednotka::overKolo(int kolo)
{
	return (kolo >= 0 && kolo < POCET_KOL);
}

string UzemnaJednotka::dajNazov()
{
	return nazov_;
}

int UzemnaJednotka::dajZapisVolicov(int kolo)
{
	if (overKolo(kolo))
	{
		return (*zapisaniVolici_)[kolo];
	}
	return -1;
}

int UzemnaJednotka::dajVydaneObalky(int kolo)
{
	if (overKolo(kolo))
	{
		return (*vydaneObalky_)[kolo];
	}
	return -1;
}

double UzemnaJednotka::dajUcastVPercent(int kolo)
{
	if (overKolo(kolo))
	{
		return (*ucastPercent_)[kolo];
	}
	return -1;
}

int UzemnaJednotka::dajOdovzdaneObalky(int kolo)
{
	if (overKolo(kolo))
	{
		return (*odovzdaneObalky_)[kolo];
	}
	return -1;
}

int UzemnaJednotka::dajPlatneHlasy(int kolo)
{
	if (overKolo(kolo))
	{
		return (*platneHlasy_)[kolo];
	}
	return -1;
}
