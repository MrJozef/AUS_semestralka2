#pragma once
#include "../structures/heap_monitor.h"
#include "kriterium.h"
#include "uzemnaJednotka.h"

class KVydaneObalky: public Kriterium<int, UzemnaJednotka*>
{
private:
	Kolo kolo_;

public:
	KVydaneObalky();
	~KVydaneObalky();

	int ohodnot(UzemnaJednotka* objekt) override;
	///<summary>V konštruktore sa nastaví defaultná hodnota attr. kolo_, pomocou tejto metody si mozeme nastavit kolo, ako chceme</summary>
	void set(Kolo kolo);
};

inline KVydaneObalky::KVydaneObalky()
{
	kolo_ = prve;
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

inline void KVydaneObalky::set(Kolo kolo)
{
	kolo_ = kolo;
}
