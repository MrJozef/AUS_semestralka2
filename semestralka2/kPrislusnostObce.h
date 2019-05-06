#pragma once
#include "../structures/heap_monitor.h"
#include "kriterium.h"
#include "uzemnaJednotka.h"
#include "obec.h"

class KPrislusnostObce: public Kriterium<bool, Obec*>
{
private:
	UzemnaJednotka* vyssiCelok_;			//todo setter

public:
	KPrislusnostObce(UzemnaJednotka* vyssiCelok);
	~KPrislusnostObce();

	bool ohodnot(Obec* objekt) override;
};

inline KPrislusnostObce::KPrislusnostObce(UzemnaJednotka* vyssiCelok)
{
	vyssiCelok_ = vyssiCelok;
}

inline KPrislusnostObce::~KPrislusnostObce()
{
}

inline bool KPrislusnostObce::ohodnot(Obec* objekt)
{
	return objekt->dajVyssiuJednotku() == vyssiCelok_ || objekt->dajVyssiuJednotku()->dajVyssiuJednotku() == vyssiCelok_;
}
