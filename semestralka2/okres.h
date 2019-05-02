#pragma once
#include "../structures/heap_monitor.h"
#include "uzemnaJednotka.h"
#include "kraj.h"

class Okres: public UzemnaJednotka
{
private:
	Kraj* kraj_;

public:
	///<summary>Kon�truktor pre na��tavanie zo s�boru</summary>
	Okres(fstream* inSubor, Kraj* vyssiaJednotka);
	~Okres();

	///<summary>Met�da, ktor� vr�ti pointer na vy��iu �zemn� jednotku do kt. patr�, napr. Okres vr�ti pointer na Kraj</summary>
	UzemnaJednotka* dajVyssiuJednotku() override;
};

inline Okres::Okres(fstream* inSubor, Kraj* vyssiaJednotka)
	: UzemnaJednotka(inSubor)
{
	kraj_ = vyssiaJednotka;
}

inline Okres::~Okres()
{
}

inline UzemnaJednotka* Okres::dajVyssiuJednotku()
{
	return kraj_;
}
