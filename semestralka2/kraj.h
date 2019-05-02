#pragma once
#include "../structures/heap_monitor.h"
#include "uzemnaJednotka.h"

class Kraj: public UzemnaJednotka
{
public:
	///<summary>Konštruktor pre naèítavanie zo súboru</summary>
	Kraj(fstream* inSubor);
	~Kraj();

	///<summary>Metóda, ktorá vráti pointer na vyššiu územnú jednotku do kt. patrí, Kraj vracia nullptr</summary>
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
