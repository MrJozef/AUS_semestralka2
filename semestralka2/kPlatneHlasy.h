#pragma once
#include "../structures/heap_monitor.h"
#include "kriterium.h"
#include "uzemnaJednotka.h"

class KPlatneHlasy: public Kriterium<int, UzemnaJednotka*>
{
private:
	Kolo kolo_;
public:
	KPlatneHlasy();
	~KPlatneHlasy();

	int ohodnot(UzemnaJednotka* objekt) override;
	void set(Kolo kolo);
};

inline KPlatneHlasy::KPlatneHlasy()
{
	kolo_ = prve;
}

inline KPlatneHlasy::~KPlatneHlasy()
{
}

inline int KPlatneHlasy::ohodnot(UzemnaJednotka* objekt)
{
	return objekt->dajPlatneHlasy(kolo_);
}

inline void KPlatneHlasy::set(Kolo kolo)
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