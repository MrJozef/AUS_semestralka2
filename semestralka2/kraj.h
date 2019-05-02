#pragma once
#include "../structures/heap_monitor.h"
#include "uzemnaJednotka.h"

class Kraj: public UzemnaJednotka
{
public:
	///<summary>Kon�truktor pre na��tavanie zo s�boru</summary>
	Kraj(fstream* inSubor);
	~Kraj();

	///<summary>Met�da, ktor� vr�ti pointer na vy��iu �zemn� jednotku do kt. patr�, Kraj vracia nullptr</summary>
	UzemnaJednotka* dajVyssiuJednotku() override;
};

inline Kraj::Kraj(fstream* inSubor)
	: UzemnaJednotka(inSubor)
{
	//kraj nema ziadne attr navyse oproti triede UzemnaJednotka
}

inline Kraj::~Kraj()
{
}

inline UzemnaJednotka* Kraj::dajVyssiuJednotku()
{
	return nullptr;
}
