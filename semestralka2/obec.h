#pragma once
#include "../structures/heap_monitor.h"
#include "uzemnaJednotka.h"
#include "okres.h"

class Obec: public UzemnaJednotka
{
private:
	Okres* okres_;

public:
	///<summary>Konštruktor pre naèítavanie zo súboru</summary>
	Obec(fstream* inSubor, Okres* vyssiaJednotka);
	~Obec();

	///<summary>Metóda, ktorá vráti pointer na vyššiu územnú jednotku do kt. patrí, napr. Obec vráti pointer na Okres</summary>
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
