#pragma once
#include "../structures/heap_monitor.h"
#include "filter.h"

using namespace std;

template <typename T, typename O>
class FilterJednoParam: public Filter<T, O>
{
private:
	///<summary>Jeden parameter jednoparametroveho filtra, typu bude takeho ako navrat. hodnota kriteria</summary>
	T alfa_;
public:
	FilterJednoParam();
	~FilterJednoParam();

	bool ohodnot(O objekt, Kriterium<T, O>* kriterium) override;
	void set(T alfa);
};

template <typename T, typename O>
FilterJednoParam<T, O>::FilterJednoParam()
{
}

template <typename T, typename O>
FilterJednoParam<T, O>::~FilterJednoParam()
{
}

template <typename T, typename O>
bool FilterJednoParam<T, O>::ohodnot(O objekt, Kriterium<T, O>* kriterium)
{
	return kriterium->ohodnot(objekt) == alfa_;
}

template <typename T, typename O>
void FilterJednoParam<T, O>::set(T alfa)
{
	alfa_ = alfa;
}