#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "../structures/heap_monitor.h"

const std::string CESTA_K_DATAM = "../data/spracovane_data.txt";

const int POCET_POLOZIEK_MENU = 2;
const int POCET_POUZIT_FILTROV = 3;
const int POCET_KOL = 2;

enum Kolo
{
	prve,
	druhe,
	obe
};