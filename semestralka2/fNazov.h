#pragma once
#include "../structures/heap_monitor.h"
#include "filterJednoParam.h"
#include "uzemnaJednotka.h"

using namespace std;

class FNazov: public FilterJednoParam<string, UzemnaJednotka*>
{
};