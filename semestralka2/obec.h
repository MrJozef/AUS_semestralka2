#pragma once
#include "../structures/heap_monitor.h"
#include "uzemnaJednotka.h"
#include "okres.h"

class Obec: public UzemnaJednotka
{
private:
	Okres* okres_;

public:
	///<summary>Kon�truktor pre na��tavanie zo s�boru</summary>
	Obec(fstream* inSubor, Okres* vyssiaJednotka);
	~Obec();

	///<summary>Met�da, ktor� vr�ti pointer na vy��iu �zemn� jednotku do kt. patr�, napr. Obec vr�ti pointer na Okres</summary>
	UzemnaJednotka* dajVyssiuJednotku() override;
};

inline Obec::Obec(fstream* inSubor, Okres* vyssiaJednotka)
	: UzemnaJednotka(inSubor)
{
	okres_ = vyssiaJednotka;
}

inline Obec::~Obec()
{
}

inline UzemnaJednotka* Obec::dajVyssiuJednotku()
{
	return okres_;
}
