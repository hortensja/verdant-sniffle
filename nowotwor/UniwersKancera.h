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
	void zapiszDoPlikaTXT(std::string nzawa);
	double liczPochodnaDrugiegoRzeduPoX(double I, double J, int t);
	double liczPochodnaDrugiegoRzeduPoY(double I, double J, int t);

	double wezLiczbeZywych();

private:
	KomoraKancera **mSwiat;
	KomoraKancera **mNowySwiat;
	static KomoraKancera zerowaKomora;

	int mLiczbaZywych;
	int mLiczbaMartwych;

};

