#pragma once
#include "../structures/heap_monitor.h"
#include "filterJednoParam.h"
#include "obec.h"

using namespace std;

///<summary>alfa v tomto filtri - ak true, obec ma patrit k vyssiemu uzemnemu celku, kt. zadame do kriteria, ak false, obec nema patrit</summary>
class FPrislusnostObce: public FilterJednoParam<bool, Obec*>
{
};