#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "../structures/heap_monitor.h"

const std::string CESTA_K_DATAM = "../data/spracovane_data.txt";

const int POCET_POLOZIEK_MENU = 2;
const int POCET_POUZIT_FILTROV = 3;
const int POCET_KOL = 2;
const int POCET_TYPOV_UZEM_JEDNOTIEK = 3;

enum Kolo
{
	prve,
	druhe,
	obe
};

enum TypUzemnejJednotky
{
	typ_kraj,
	typ_okres,
	typ_obec
};