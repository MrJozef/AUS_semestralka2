#pragma once
#include "../structures/heap_monitor.h"
#include "kriterium.h"
#include "uzemnaJednotka.h"

class KZapisaniVolici: public Kriterium<int, UzemnaJednotka*>
{
private:
	Kolo kolo_;		//todo setter doplnit?

public:
	///<summary>Konštruktor oèakáva kolo</summary>
	KZapisaniVolici(Kolo kolo);
	~KZapisaniVolici();

	int ohodnot(UzemnaJednotka* objekt) override;
};

inline KZapisaniVolici::KZapisaniVolici(Kolo kolo)
{
	if (kolo == prve || kolo == druhe)
	{
		kolo_ = kolo;
	}
	else
	{
		std::cout << "Chyba - Toto kriterium nepodporuje moznost 'obe'!\nBolo pouzite defaulte nastavenie - prve kolo\n";
		kolo_ = prve;
	}
}


inline KZapisaniVolici::~KZapisaniVolici()
{
}

inline int KZapisaniVolici::ohodnot(UzemnaJednotka* objekt)
{
	return objekt->dajZapisVolicov(kolo_);
}