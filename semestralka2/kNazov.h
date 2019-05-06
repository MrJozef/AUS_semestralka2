#pragma once
#include "../structures/heap_monitor.h"
#include "kriterium.h"
#include "uzemnaJednotka.h"

class KNazov: public Kriterium<string, UzemnaJednotka*>
{
public:
	KNazov();
	~KNazov();

	string ohodnot(UzemnaJednotka* objekt) override;
};

inline KNazov::KNazov()
{
}

inline KNazov::~KNazov()
{
}

inline string KNazov::ohodnot(UzemnaJednotka* objekt)
{
	return objekt->dajNazov();
}