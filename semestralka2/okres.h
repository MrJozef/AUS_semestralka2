#pragma once
#include "../structures/heap_monitor.h"
#include "uzemnaJednotka.h"
#include "kraj.h"

class Okres: public UzemnaJednotka
{
private:
	Kraj* kraj_;

public:
	///<summary>Konštruktor pre naèítavanie zo súboru</summary>
	Okres(fstream* inSubor, Kraj* vyssiaJednotka);
	~Okres();

	///<summary>Metóda, ktorá vráti pointer na vyššiu územnú jednotku do kt. patrí, napr. Okres vráti pointer na Kraj</summary>
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
