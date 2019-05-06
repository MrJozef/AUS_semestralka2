#pragma once
#include "../structures/heap_monitor.h"
#include "const.h"

using namespace std;

///<summary>Abstraktn� predok v�etk�ch krit�ri�; O - objekt, ktor� chcem ohodnoti�; T - hodnota ohodnotenia</summary>
template <typename T, typename O>			//generika
class Kriterium
{
public:
	Kriterium();
	virtual ~Kriterium();

	///<summary>T�to met�da vr�ti ohodnotenie objektu O, kt. bude typu T</summary>
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