#pragma once
#include "../structures/heap_monitor.h"
#include "kriterium.h"
#include "uzemnaJednotka.h"

class KOdovzdaneObalky: public Kriterium<int, UzemnaJednotka*>
{
private:
	Kolo kolo_;			//todo setter

public:
	KOdovzdaneObalky(Kolo kolo);
	~KOdovzdaneObalky();

	int ohodnot(UzemnaJednotka* objekt) override;
};

inline KOdovzdaneObalky::KOdovzdaneObalky(Kolo kolo)
{
	kolo_ = kolo;
}

inline KOdovzdaneObalky::~KOdovzdaneObalky()
{
}

inline int KOdovzdaneObalky::ohodnot(UzemnaJednotka* objekt)
{
	if (kolo_ != obe)
	{
		return objekt->dajOdovzdaneObalky(kolo_);
	}
	return objekt->dajOdovzdaneObalky(prve) + objekt->dajOdovzdaneObalky(druhe);
}