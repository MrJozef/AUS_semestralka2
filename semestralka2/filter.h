#pragma once
#include "../structures/heap_monitor.h"
#include "kriterium.h"

using namespace std;

///<summary>Abstraktný predok všetkých filtrov</summary>
template <typename T, typename O>
class Filter
{
public:
	Filter();
	virtual ~Filter();
	///<summary>Táto metóda vráti True/False objektu O, podla zvoleneho kriteria</summary>
	virtual bool ohodnot(O objekt, Kriterium<T, O> kriterium) = 0;
};

template <typename T, typename O>
Filter<T, O>::Filter()
{
}

template <typename T, typename O>
Filter<T, O>::~Filter()
{
}