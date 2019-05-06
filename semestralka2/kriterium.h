#pragma once
#include "../structures/heap_monitor.h"
#include "const.h"

using namespace std;

///<summary>Abstraktnı predok všetkıch kritérií; O - objekt, ktorı chcem ohodnoti; T - hodnota ohodnotenia</summary>
template <typename T, typename O>			//generika
class Kriterium
{
public:
	Kriterium();
	virtual ~Kriterium();

	///<summary>Táto metóda vráti ohodnotenie objektu O, kt. bude typu T</summary>
	virtual T ohodnot(O objekt) = 0;		//todo ked tak toto upravit ako to ma majkl
};

template <typename T, typename O>
Kriterium<T, O>::Kriterium()
{
}

template <typename T, typename O>
Kriterium<T, O>::~Kriterium()
{
}