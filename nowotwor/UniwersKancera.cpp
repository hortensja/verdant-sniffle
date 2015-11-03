#include <fstream>
#include <sstream>
#include "UniwersKancera.h"
#include <iostream>
KomoraKancera UniwersKancera::zerowaKomora = KomoraKancera();

//template <int rozmiar>
UniwersKancera::UniwersKancera()
{
	mSwiat = new KomoraKancera*[rozmiar];
	mNowySwiat = new KomoraKancera*[rozmiar];

	for (size_t i = 0; i < rozmiar; i++){
		mSwiat[i] = new KomoraKancera[rozmiar];
		mNowySwiat[i] = new KomoraKancera[rozmiar];

		for (size_t j = 0; j < rozmiar; j++){
			mSwiat[i][j] = KomoraKancera(i,j);
			mNowySwiat[i][j] = KomoraKancera(i,j);
		}
	}

}


UniwersKancera::~UniwersKancera()
{
}


void UniwersKancera::ustawKomoreUniwersu(int i, int j, KomoraKancera &komora)
{
	if (i < 0 || i >= rozmiar || j < 0 || j >= rozmiar)
		return;
	komora.ustawI(i);
	komora.ustawJ(j);
	mSwiat[i][j] = komora;
}

void UniwersKancera::aktualizujUniwers() {
	//@TOFIX
	for (int i = 0; i < rozmiar; i++) {
		for (int j = 0; j < rozmiar; j++) {
			mNowySwiat[i][j] = mSwiat[i][j].aktualizujKomore(*this);

		}
	}


	KomoraKancera** t = mSwiat;
	mSwiat = mNowySwiat;
	mNowySwiat = t;


}

KomoraKancera &UniwersKancera::wezKomore(int i, int j)
{
	if (i < 0 || i >= rozmiar || j < 0 || j >= rozmiar)
		return zerowaKomora;

	return mSwiat[i][j];
}

void UniwersKancera::zapiszDoPlikaPPM(std::string nazwa, int numer)
{
	std::stringstream ss;
	ss << numer;
	nazwa += ss.str();
	nazwa += ".ppm";
	std::ofstream file(nazwa);
	ss.clear();

	file << "P3" << std::endl;
	file << rozmiar << " " << rozmiar << std::endl;
	file << "255" << std::endl;

	for (size_t i = 0; i < rozmiar; i++)
	{
		for (size_t j = 0; j < rozmiar; j++)
		{

			int greenp = (wezKomore(i, j).wezCisnienie(2) * 10e4);
			greenp = (greenp > 255) ? 255 : greenp;

			if (wezKomore(i, j).wezStan() == Zyje)
			{
				file << "255 0 ";
				file << greenp;
				file << " ";
			}
				
			else if (wezKomore(i, j).wezStan() == NieZyje)
			{
				file << "0 255 ";	
				file << greenp;
				file << " ";
			}
			else
			{
				file << "0 0 ";
				file << greenp;
				file << " ";
			}

		}
		file << std::endl;
	}

	file.close();
}

double UniwersKancera::liczPochodnaDrugiegoRzeduPoX(double I, double J, int t)
{
	int calkowityI = I;
	int calkowityJ = J;
	double rzeczywistyI = I - calkowityI;
	double rzeczywistyJ = J - calkowityJ;
	
	if (rzeczywistyI + rzeczywistyJ < 0.01)
	{
		
		double p1 = wezKomore(calkowityI, calkowityJ).wezCisnienie(t) - wezKomore(calkowityI - 1, calkowityJ).wezCisnienie(t);
		double p2 = wezKomore(calkowityI, calkowityJ).wezCisnienie(t) - wezKomore(calkowityI + 1, calkowityJ).wezCisnienie(t);

		double dp = p1 + p2;
		

		return -dp;
	}
	else
	{

		double d1 = liczPochodnaDrugiegoRzeduPoX(calkowityI, calkowityJ, t);
		double d2 = liczPochodnaDrugiegoRzeduPoX(calkowityI+1, calkowityJ, t);
		double d3 = liczPochodnaDrugiegoRzeduPoX(calkowityI, calkowityJ+1, t);
		double d4 = liczPochodnaDrugiegoRzeduPoX(calkowityI+1, calkowityJ+1, t);
		return (d1*(rzeczywistyI + rzeczywistyJ) + d2*(1 - rzeczywistyI + rzeczywistyJ) + d3*(1 - rzeczywistyJ + rzeczywistyI) + d4*(2 - rzeczywistyI - rzeczywistyJ))/4;
	}
	return 0;

}

double UniwersKancera::liczPochodnaDrugiegoRzeduPoY(double I, double J, int t)
{
	int calkowityI = I;
	int calkowityJ = J;
	double rzeczywistyI = I - calkowityI;
	double rzeczywistyJ = J - calkowityJ;

	if (rzeczywistyI + rzeczywistyJ < 0.01)
	{

		double p1 = wezKomore(calkowityI, calkowityJ).wezCisnienie(t) - wezKomore(calkowityI, calkowityJ - 1).wezCisnienie(t);
		double p2 = wezKomore(calkowityI, calkowityJ).wezCisnienie(t) - wezKomore(calkowityI, calkowityJ + 1).wezCisnienie(t);

		double dp = p1 + p2;


		return -dp;
	}
	else
	{

		double d1 = liczPochodnaDrugiegoRzeduPoY(calkowityI, calkowityJ, t);
		double d2 = liczPochodnaDrugiegoRzeduPoY(calkowityI + 1, calkowityJ, t);
		double d3 = liczPochodnaDrugiegoRzeduPoY(calkowityI, calkowityJ + 1, t);
		double d4 = liczPochodnaDrugiegoRzeduPoY(calkowityI + 1, calkowityJ + 1, t);
		return (d1*(rzeczywistyI + rzeczywistyJ) + d2*(1 - rzeczywistyI + rzeczywistyJ) + d3*(1 - rzeczywistyJ + rzeczywistyI) + d4*(2 - rzeczywistyI - rzeczywistyJ)) / 4;
	}
	return 0;
}


