#pragma once
#include "../structures/heap_monitor.h"
#include "kriterium.h"
#include "uzemnaJednotka.h"

class KPlatneHlasy: public Kriterium<int, UzemnaJednotka*>
{
private:
	Kolo kolo_;			//todo
public:
	KPlatneHlasy(Kolo kolo);
	~KPlatneHlasy();

	int ohodnot(UzemnaJednotka* objekt) override;
};

inline KPlatneHlasy::KPlatneHlasy(Kolo kolo)
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

inline KPlatneHlasy::~KPlatneHlasy()
{
}

inline int KPlatneHlasy::ohodnot(UzemnaJednotka* objekt)
{
	return objekt->dajPlatneHlasy(kolo_);
}
