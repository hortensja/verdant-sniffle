#include "KomoraKancera.h"
#include "UniwersKancera.h"
#include <random>
#include <iostream>

std::mt19937 mtJakis;
std::normal_distribution <double> fajnyRozkladPrawdopodobienstwa(0.5, 0.25);
std::uniform_real_distribution <double> mniejFajnyRozkladPrawdopodobienstwa(0, 1);

KomoraKancera::KomoraKancera()
{
	mCisnienie[0] = 0;
	mCisnienie[1] = 0;
	mCisnienie[2] = 0;
	mStan = Puste;
	mJedzonko = 0.66;
	mOzywaj = false;
	mCzasZycia = 0;
}

KomoraKancera::KomoraKancera(Stan stan, double cisnienie)
{
	mCisnienie[0] = cisnienie;
	mCisnienie[1] = cisnienie;
	mCisnienie[2] = cisnienie;
	mStan = stan;
	mJedzonko = 0.66;
	mOzywaj = false;
	mCzasZycia = 0;
}

KomoraKancera::KomoraKancera(int i, int j)
{
	mICzyliWspolrzednaPozioma = i;
	mJCzyliWspolrzednaPionowa = j;

	mCisnienie[0] = 0;
	mCisnienie[1] = 0;
	mCisnienie[2] = 0; 
	
	mStan = Puste;
	mJedzonko = 0.66;
	mOzywaj = false;
	mCzasZycia = 0;
}

KomoraKancera::~KomoraKancera()
{
}

void KomoraKancera::aktualizujKomore(UniwersKancera &uniwers)
{
	double stala = 0.01;
	double kappa = 0.11;
	
	ozywSie();

	mJedzonko = mJedzonko + stala;
	mJedzonko = mJedzonko > 1 ? 1 : mJedzonko;

	mCisnienie[0] = mCisnienie[1];
	mCisnienie[1] = mCisnienie[2];
	
	
	double k1x = kappa * uniwers.liczPochodnaDrugiegoRzeduPoX(mICzyliWspolrzednaPozioma, mJCzyliWspolrzednaPionowa, 2);
	double k2x = kappa * uniwers.liczPochodnaDrugiegoRzeduPoX(mICzyliWspolrzednaPozioma, mJCzyliWspolrzednaPionowa, 1);
	double k4x = kappa * uniwers.liczPochodnaDrugiegoRzeduPoX(mICzyliWspolrzednaPozioma, mJCzyliWspolrzednaPionowa, 0);

	double k1y = kappa * uniwers.liczPochodnaDrugiegoRzeduPoY(mICzyliWspolrzednaPozioma, mJCzyliWspolrzednaPionowa, 0);
	double k2y = kappa * uniwers.liczPochodnaDrugiegoRzeduPoY(mICzyliWspolrzednaPozioma, mJCzyliWspolrzednaPionowa, 1);
	double k4y = kappa * uniwers.liczPochodnaDrugiegoRzeduPoY(mICzyliWspolrzednaPozioma, mJCzyliWspolrzednaPionowa, 2);


	double dkx = (k1x +4 * k2x + k4x) / 6;
	double dky = (k1y +4 * k2y + k4y) / 6;

	double dk = dkx + dky;

	mCisnienie[2] = mCisnienie[1] + dk;

	if (mStan == Zyje) {
		mCzasZycia++;
		mJedzonko -= 1.05*stala;
		if (czySieRozrastaCzyNie()) {
			rozrastajSie(uniwers);
		}
		if (czySiePrzerzucaCzyNie()) {
			przerzucSie(uniwers);
		}
		if (czyUmieraCzyNie(uniwers)) {
			umrzyjSie(uniwers);
		}
	}


}

Stan KomoraKancera::wezStan()
{
	return this->mStan;
}

double KomoraKancera::wezCisnienie(int t)
{
	return mCisnienie[t];
}

int KomoraKancera::wezI()
{
	return mICzyliWspolrzednaPozioma;
}

int KomoraKancera::wezJ()
{
	return mJCzyliWspolrzednaPionowa;
}

void KomoraKancera::ustawI(int i)
{
	mICzyliWspolrzednaPozioma = i;
}

void KomoraKancera::ustawJ(int j)
{
	mJCzyliWspolrzednaPionowa = j;
}

bool KomoraKancera::czySieRozrastaCzyNie()
{
	double randomJakis = fajnyRozkladPrawdopodobienstwa(mtJakis);
	if (mJedzonko*randomJakis * 5 * (-(mCisnienie[2] + 0.30)*(mCisnienie[2] - 0.60)) > 0.66) {

	//if (0.05*(1 - 0.01*mCzasZycia) + 0.2*mJedzonko*mJedzonko*mJedzonko + (-(mCisnienie[2] + 0.30)*(mCisnienie[2] - 0.60)) > 0.5*randomJakis) {
		//std::cout << "Rozrastam sie ";
		return true;
	}
	return false;
}

bool KomoraKancera::czySiePrzerzucaCzyNie()
{
	double randomInny = mniejFajnyRozkladPrawdopodobienstwa(mtJakis);
	if (randomInny <= 0.001) {
		//std::cout << "Przerzucam sie ";
		return true;
	}
	return false;
}

bool KomoraKancera::czyUmieraCzyNie(UniwersKancera &uniwers)
{
	double randomJakis = mniejFajnyRozkladPrawdopodobienstwa(mtJakis);
	double czasZyciaWCzasie = mCzasZycia/100;
	double iloscJedzonkaWZyciu = 1 / (1.1 + 2 * mJedzonko);
	double iloscCisnieniaWEsilonOtoczneiu = mCisnienie[2]*mCisnienie[2];
	double wspolczynnikZapelnienia = uniwers.wezLiczbeZywych() / (rozmiar*rozmiar);


	double wspolczynnikUmarcia = (wspolczynnikZapelnienia + czasZyciaWCzasie + iloscJedzonkaWZyciu + 0.2 * iloscCisnieniaWEsilonOtoczneiu);
	
	//std::cout << wspolczynnikUmarcia << std::endl;

	if (wspolczynnikUmarcia > randomJakis / 2 + 0.4)
		return true;

	return false;
}

void KomoraKancera::przerzucSie(UniwersKancera &uniwers)
{
	double randomJeszczeInniejszy = (mniejFajnyRozkladPrawdopodobienstwa(mtJakis) - 0.5)*0.25*rozmiar;
	double randomJeszczeJeszczeInniejszy = (mniejFajnyRozkladPrawdopodobienstwa(mtJakis) - 0.5)*0.25*rozmiar;
	std::cout << "Przerzucam sie na " << wezI() + randomJeszczeInniejszy << " , " << wezJ() + randomJeszczeJeszczeInniejszy << std::endl;
	ozyw(wezI() + randomJeszczeInniejszy, wezJ() + randomJeszczeJeszczeInniejszy, uniwers);
	
}

void KomoraKancera::rozrastajSie(UniwersKancera & uniwers)
{
	ozyw(wezI() - 1, wezJ(), uniwers);
	ozyw(wezI(), wezJ() - 1, uniwers);
	
	ozyw(wezI() + 1, wezJ(), uniwers);
	ozyw(wezI(), wezJ() + 1, uniwers);

}

void KomoraKancera::umrzyjSie(UniwersKancera & uniwers)
{
	mStan = NieZyje;
	mCzasZycia = 0;
	std::cout << "UNIERAM" << std::endl;
}

void KomoraKancera::ozyw(int i, int j, UniwersKancera & uniwers)
{
	if (i > 0 && i < rozmiar && j < rozmiar && j > 0)
		uniwers.wezKomore(i, j).mOzywaj = true;
}

void KomoraKancera::ozywSie()
{
	if (mOzywaj) {
		if (mStan == Zyje) {
			mCisnienie[2] += 0.1;
		}
		else if (mStan == Puste) {
			mStan = Zyje;
			//std::cout << "Ozywiam\n";
		}
		else if (mStan == NieZyje){
		}
	}
	mOzywaj = false;
}
