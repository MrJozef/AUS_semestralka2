#pragma once
#include "../structures/heap_monitor.h"
#include "filter.h"

using namespace std;

template <typename T, typename O>
class FilterDvojParam: public Filter<T, O>
{
private:
	T alfa_;
	T beta_;

public:
	FilterDvojParam();
	~FilterDvojParam();

	bool ohodnot(O objekt, Kriterium<T, O>* kriterium) override;
	///<summary>alfa je mensia nanajvys rovna bete</summary>
	void set(T alfa, T beta);
};

template <typename T, typename O>
FilterDvojParam<T, O>::FilterDvojParam()
{
}

template <typename T, typename O>
FilterDvojParam<T, O>::~FilterDvojParam()
{
}

template <typename T, typename O>
bool FilterDvojParam<T, O>::ohodnot(O objekt, Kriterium<T, O>* kriterium)
{
	T vysledok = kriterium->ohodnot(objekt);
	return (vysledok >= alfa_ && vysledok <= beta_);
}

template <typename T, typename O>
void FilterDvojParam<T, O>::set(T alfa, T beta)
{
	if (alfa <= beta)
	{
		alfa_ = alfa;
		beta_ = beta;
	}
	else
	{
		std::cout << "Chyba - Zle zadane parametre filtra (alfa > beta)!\nNic sa nenastavilo!\n";
	}
}
