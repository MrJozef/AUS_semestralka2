#pragma once
#include "../structures/heap_monitor.h"
#include "kriterium.h"
#include "uzemnaJednotka.h"

class KVydaneObalky: public Kriterium<int, UzemnaJednotka*>
{
private:
	Kolo kolo_;		//todo setter

public:
	KVydaneObalky(Kolo kolo);
	~KVydaneObalky();

	int ohodnot(UzemnaJednotka* objekt) override;
};

inline KVydaneObalky::KVydaneObalky(Kolo kolo)
{
	kolo_ = kolo;
}

inline KVydaneObalky::~KVydaneObalky()
{
}

inline int KVydaneObalky::ohodnot(UzemnaJednotka* objekt)
{
	if (kolo_ != obe)
	{
		return objekt->dajVydaneObalky(kolo_);
	}
	return objekt->dajVydaneObalky(prve) + objekt->dajVydaneObalky(druhe);
}
