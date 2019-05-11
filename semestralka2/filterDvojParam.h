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

	bool ohodnot(O objekt, Kriterium<T, O> kriterium) override;
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
bool FilterDvojParam<T, O>::ohodnot(O objekt, Kriterium<T, O> kriterium)
{
	T vysledok = kriterium.ohodnot(objekt);
	return (vysledok <= beta_) && (vysledok >= alfa_);
}

template <typename T, typename O>
void FilterDvojParam<T, O>::set(T alfa, T beta)
{
	alfa_ = alfa;
	beta_ = beta;
}
