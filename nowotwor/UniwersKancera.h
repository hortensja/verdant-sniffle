#pragma once

#include<string>

#include "KomoraKancera.h"
const int rozmiar = 200;

//template<int rozmiar>
class UniwersKancera
{
public:
	UniwersKancera();
	~UniwersKancera();

	void ustawKomoreUniwersu(int i, int j, KomoraKancera &komora);
	void aktualizujUniwers();
	KomoraKancera &wezKomore(int i, int j);
	void zapiszDoPlikaPPM(std::string nazwa, int numer);
	double liczPochodnaDrugiegoRzeduPoX(double I, double J, int t);
	double liczPochodnaDrugiegoRzeduPoY(double I, double J, int t);


private:
	KomoraKancera **mSwiat;
	KomoraKancera **mNowySwiat;
	static KomoraKancera zerowaKomora;

};

