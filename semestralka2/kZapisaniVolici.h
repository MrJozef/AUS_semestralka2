#pragma once
#include "../structures/heap_monitor.h"
#include "kriterium.h"
#include "uzemnaJednotka.h"

class KZapisaniVolici: public Kriterium<int, UzemnaJednotka*>
{
private:
	Kolo kolo_;

public:
	KZapisaniVolici();
	~KZapisaniVolici();

	int ohodnot(UzemnaJednotka* objekt) override;
	void set(Kolo kolo);
};

inline KZapisaniVolici::KZapisaniVolici()
{
	kolo_ = prve;
}


inline KZapisaniVolici::~KZapisaniVolici()
{
}

inline int KZapisaniVolici::ohodnot(UzemnaJednotka* objekt)
{
	return objekt->dajZapisVolicov(kolo_);
}

inline void KZapisaniVolici::set(Kolo kolo)
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