//bardzo swietnisty ;rgoram v. 0000.(9)

#include <iostream>
#include <chrono>
#include <random>

#include "KomoraKancera.h"
#include "UniwersKancera.h"


std::mt19937 mt2;
std::normal_distribution <double> fajnyRozkladPrawdopodobienstwa2(5, 2);
std::uniform_int_distribution <int> mniejFajnyRozkladPrawdopodobienstwa2(0, rozmiar);


int main() {

	UniwersKancera uniwers;
	std::cout << sizeof(UniwersKancera) << std::endl;
	auto timeBefAll = std::chrono::high_resolution_clock::now();
	auto timeAfterAll = std::chrono::high_resolution_clock::now();
	KomoraKancera kkk(Zyje, 0.3);

	double ileKomorekPoczatkowych = fajnyRozkladPrawdopodobienstwa2(mt2);
	
	for (int i = 0; i < ileKomorekPoczatkowych; i++) {

		uniwers.ustawKomoreUniwersu(mniejFajnyRozkladPrawdopodobienstwa2(mt2), mniejFajnyRozkladPrawdopodobienstwa2(mt2), kkk);
	}

	//uniwers.ustawKomoreUniwersu(100, 100, kkk);
	//uniwers.ustawKomoreUniwersu(73, 10, kkk);
	//uniwers.ustawKomoreUniwersu(18, 122, kkk);
	//uniwers.ustawKomoreUniwersu(67, 145, kkk);
	//uniwers.ustawKomoreUniwersu(160, 8, kkk);
	//uniwers.ustawKomoreUniwersu(111, 189, kkk);
	////while (1) 0;
	system("del yoloyolo.txt");
	for (size_t i = 0; i < 100; i++)
	{
		auto timeBefOne = std::chrono::high_resolution_clock::now();



		uniwers.aktualizujUniwers();
		if(i%10==0)
			uniwers.zapiszDoPlikaPPM("yoloyolo", i);
		uniwers.zapiszDoPlikaTXT("yoloyolo.txt");



		auto timeAfterOne = std::chrono::high_resolution_clock::now();
		std::cout << "Time for one: " << (timeAfterOne - timeBefOne).count()/10e8 << std::endl;
		
	}
	timeAfterAll = std::chrono::high_resolution_clock::now();
	std::cout << "Time for all: " << (timeAfterAll - timeBefAll).count()/10e8 << std::endl;
	

	system("pause");
	return 0;
}