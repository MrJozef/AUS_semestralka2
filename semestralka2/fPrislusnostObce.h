#pragma once
#include "../structures/heap_monitor.h"
#include "filterJednoParam.h"
#include "obec.h"

using namespace std;

class FPrislusnostObce: public FilterJednoParam<bool, Obec*>
{
};