#pragma once
#include "sort.h"
#include "../unsorted_sequence_table.h"
#include "../../../semestralka2/kZapisaniVolici.h"
#include "../../../semestralka2/kUcast.h"

namespace structures
{

	/// <summary> Triedenie Shell sort. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class ShellSort : public Sort<K, T>
	{
	public:
		/// <summary> Utriedi tabulku triedenim Shell sort. </summary>
		/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
		void sort(UnsortedSequenceTable<K, T>& table) override;
		void sortPodla(KZapisaniVolici* kriterium, UnsortedSequenceTable<K, T>& table);
		void sortPodla(KUcast* kriterium, UnsortedSequenceTable<K, T>& table);
		void shell(UnsortedSequenceTable<K, T>& table, int krok);
		void shell(KZapisaniVolici* kriterium, UnsortedSequenceTable<K, T>& table, int krok);
		void shellPodlaUcasti(KUcast* kriterium, UnsortedSequenceTable<K, T>& table, int krok);
	};

	template <typename K, typename T>
	inline void ShellSort<K, T>::sort(UnsortedSequenceTable<K, T>& table)
	{
		shell(table, static_cast<int>(table.size() / 2.2));
	}

	template <typename K, typename T>
	void ShellSort<K, T>::sortPodla(KZapisaniVolici* kriterium, UnsortedSequenceTable<K, T>& table)
	{
		shell(kriterium, table, static_cast<int>(table.size() / 2.2));
	}

	template <typename K, typename T>
	void ShellSort<K, T>::sortPodla(KUcast* kriterium, UnsortedSequenceTable<K, T>& table)
	{
		shellPodlaUcasti(kriterium, table, static_cast<int>(table.size() / 2.2));
	}

	template <typename K, typename T>
	void ShellSort<K, T>::shell(UnsortedSequenceTable<K, T>& table, int krok)
	{
		int pocPrvkov = table.size();
		int skok = krok;

		for (int delta = 0; delta < skok; delta++)
		{
			for (int i = delta; i < pocPrvkov; i += skok)
			{
				int j = i;
				while ((j - skok >= delta) && (table.getItemAtIndex(j).getKey() < table.getItemAtIndex(j - skok).getKey()))
				{
					table.swap(j, j - skok);
					j -= skok;
				}
			}
		}

		//if skok == 1 uz v tomto shell, tak koniec
		if (skok == 2)
		{
			shell(table, 1);
		}
		if (skok >= 3)
		{
			shell(table, static_cast<int>(skok / 2.2));
		}
	}

	template <typename K, typename T>
	void ShellSort<K, T>::shell(KZapisaniVolici* kriterium, UnsortedSequenceTable<K, T>& table, int krok)
	{
		int pocPrvkov = table.size();
		int skok = krok;

		for (int delta = 0; delta < skok; delta++)
		{
			for (int i = delta; i < pocPrvkov; i += skok)
			{
				int j = i;
				while ((j - skok >= delta) && (kriterium->ohodnot(table.getItemAtIndex(j).accessData()) < kriterium->ohodnot(table.getItemAtIndex(j - skok).accessData())))
				{
					table.swap(j, j - skok);
					j -= skok;
				}
			}
		}

		if (skok == 2)
		{
			shell(kriterium, table, 1);
		}
		if (skok >= 3)
		{
			shell(kriterium, table, static_cast<int>(skok / 2.2));
		}
	}

	template <typename K, typename T>
	void ShellSort<K, T>::shellPodlaUcasti(KUcast* kriterium, UnsortedSequenceTable<K, T>& table, int krok)
	{
		int pocPrvkov = table.size();
		int skok = krok;

		for (int delta = 0; delta < skok; delta++)
		{
			for (int i = delta; i < pocPrvkov; i += skok)
			{
				int j = i;
				while ((j - skok >= delta) && (kriterium->ohodnot(table.getItemAtIndex(j).accessData()) < kriterium->ohodnot(table.getItemAtIndex(j - skok).accessData())))
				{
					table.swap(j, j - skok);
					j -= skok;
				}
			}
		}

		if (skok == 2)
		{
			shellPodlaUcasti(kriterium, table, 1);
		}
		if (skok >= 3)
		{
			shellPodlaUcasti(kriterium, table, static_cast<int>(skok / 2.2));
		}
	}
}
