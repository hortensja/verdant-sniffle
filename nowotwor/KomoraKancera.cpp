#include "KomoraKancera.h"
#include "UniwersKancera.h"

KomoraKancera::KomoraKancera()
{
	mCisnienie[0] = 0;
	mCisnienie[1] = 0;
	mCisnienie[2] = 0;
	mStan = Puste;
	mJedzonko = 1;
}

KomoraKancera::KomoraKancera(Stan stan, double cisnienie)
{
	mCisnienie[0] = cisnienie;
	mCisnienie[1] = cisnienie;
	mCisnienie[2] = cisnienie;
	mStan = stan;
	mJedzonko = 1;
}

KomoraKancera::KomoraKancera(int i, int j)
{
	mICzyliWspolrzednaPozioma = i;
	mJCzyliWspolrzednaPionowa = j;

	mCisnienie[0] = 0;
	mCisnienie[1] = 0;
	mCisnienie[2] = 0; 
	
	mStan = Puste;
	mJedzonko = 1;
}

KomoraKancera::~KomoraKancera()
{
}

KomoraKancera KomoraKancera::aktualizujKomore(UniwersKancera &uniwers)
{
	double stala = 0.01;
	double kappa = 0.11;
	
	KomoraKancera temp;
		temp.mStan = mStan;
		temp.mJedzonko = mJedzonko + stala;
		temp.mCisnienie[0] = mCisnienie[1];
		temp.mCisnienie[1] = mCisnienie[2];
		temp.mICzyliWspolrzednaPozioma = mICzyliWspolrzednaPozioma;
		temp.mJCzyliWspolrzednaPionowa = mJCzyliWspolrzednaPionowa;


	temp.mJedzonko = temp.mJedzonko > 1 ? 1 : temp.mJedzonko;
	
	double k1x = kappa * uniwers.liczPochodnaDrugiegoRzeduPoX(mICzyliWspolrzednaPozioma, mJCzyliWspolrzednaPionowa, 2);
	double k2x = kappa * uniwers.liczPochodnaDrugiegoRzeduPoX(mICzyliWspolrzednaPozioma, mJCzyliWspolrzednaPionowa, 1);
	double k4x = kappa * uniwers.liczPochodnaDrugiegoRzeduPoX(mICzyliWspolrzednaPozioma, mJCzyliWspolrzednaPionowa, 0);

	double k1y = kappa * uniwers.liczPochodnaDrugiegoRzeduPoY(mICzyliWspolrzednaPozioma, mJCzyliWspolrzednaPionowa, 0);
	double k2y = kappa * uniwers.liczPochodnaDrugiegoRzeduPoY(mICzyliWspolrzednaPozioma, mJCzyliWspolrzednaPionowa, 1);
	double k4y = kappa * uniwers.liczPochodnaDrugiegoRzeduPoY(mICzyliWspolrzednaPozioma, mJCzyliWspolrzednaPionowa, 2);


	double dkx = (k1x +4 * k2x + k4x) / 6;
	double dky = (k1y +4 * k2y + k4y) / 6;

	double dk = dkx + dky;

	
	temp.mCisnienie[2] = mCisnienie[2] + dk;


	if (this->mStan == NieZyje) {
		temp.mStan = NieZyje;
	}
	if (uniwers.wezKomore(wezI() - 1, wezJ()).mStan == Zyje && uniwers.wezKomore(wezI() + 1, wezJ()).mStan == Zyje && uniwers.wezKomore(wezI(), wezJ() - 1).mStan == Zyje && uniwers.wezKomore(wezI(), wezJ() + 1).mStan == Zyje) {
		temp.mStan = NieZyje;
		temp.mCisnienie[2] = 0.0;
	}
	if (this->mStan==Puste && (uniwers.wezKomore(wezI() - 1, wezJ()).mStan == Zyje || uniwers.wezKomore(wezI() + 1, wezJ()).mStan == Zyje || uniwers.wezKomore(wezI(), wezJ() - 1).mStan == Zyje || uniwers.wezKomore(wezI(), wezJ() + 1).mStan == Zyje)) {
		temp.mStan = Zyje;
		temp.mCisnienie[2] = 0.3;
	}
	return temp;
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
