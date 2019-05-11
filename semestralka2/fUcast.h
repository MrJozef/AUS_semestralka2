#pragma once
#include "../structures/heap_monitor.h"
#include "filterDvojParam.h"
#include "uzemnaJednotka.h"

class FUcast: public FilterDvojParam<double, UzemnaJednotka*>
{
};