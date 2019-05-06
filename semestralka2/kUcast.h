#pragma once
#include "../structures/heap_monitor.h"
#include "kriterium.h"
#include "uzemnaJednotka.h"

class KUcast: public Kriterium<double, UzemnaJednotka*>
{
private:
	Kolo kolo_;		//todo setter?

public:
	KUcast(Kolo kolo);
	~KUcast();

	double ohodnot(UzemnaJednotka* objekt) override;
};

inline KUcast::KUcast(Kolo kolo)
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

inline KUcast::~KUcast()
{
}

inline double KUcast::ohodnot(UzemnaJednotka* objekt)
{
	return objekt->dajUcastVPercent(kolo_);
}