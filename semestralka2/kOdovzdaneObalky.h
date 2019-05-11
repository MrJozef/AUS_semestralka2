#pragma once
#include "../structures/heap_monitor.h"
#include "kriterium.h"
#include "uzemnaJednotka.h"

class KOdovzdaneObalky: public Kriterium<int, UzemnaJednotka*>
{
private:
	Kolo kolo_;

public:
	KOdovzdaneObalky();
	~KOdovzdaneObalky();

	int ohodnot(UzemnaJednotka* objekt) override;
	///<summary>V konštruktore sa nastaví defaultná hodnota attr. kolo_, pomocou tejto metody si mozeme nastavit kolo, ako chceme</summary>
	void set(Kolo kolo);
};

inline KOdovzdaneObalky::KOdovzdaneObalky()
{
	kolo_ = prve;
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

inline void KOdovzdaneObalky::set(Kolo kolo)
{
	kolo_ = kolo;
}