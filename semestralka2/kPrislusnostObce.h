#pragma once
#include "../structures/heap_monitor.h"
#include "kriterium.h"
#include "uzemnaJednotka.h"
#include "obec.h"

class KPrislusnostObce: public Kriterium<bool, Obec*>
{
private:
	UzemnaJednotka* vyssiCelok_;

public:
	KPrislusnostObce();
	~KPrislusnostObce();

	bool ohodnot(Obec* objekt) override;
	void set(UzemnaJednotka* vyssiCelok);
};

inline KPrislusnostObce::KPrislusnostObce()
{
	vyssiCelok_ = nullptr;
}

inline KPrislusnostObce::~KPrislusnostObce()
{
}

inline bool KPrislusnostObce::ohodnot(Obec* objekt)
{
	return objekt->dajVyssiuJednotku() == vyssiCelok_ || objekt->dajVyssiuJednotku()->dajVyssiuJednotku() == vyssiCelok_;
}

inline void KPrislusnostObce::set(UzemnaJednotka* vyssiCelok)
{
	vyssiCelok_ = vyssiCelok;
}