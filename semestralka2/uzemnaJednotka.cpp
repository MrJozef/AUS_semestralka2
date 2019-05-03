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

	inSubor->ignore();
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


string UzemnaJednotka::dajNazov()
{
	return nazov_;
}