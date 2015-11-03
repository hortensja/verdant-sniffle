#pragma once

class UniwersKancera;

enum Stan
{
	Puste = 0,
	Zyje = 1,
	NieZyje = 2
};

class KomoraKancera
{
public:
	KomoraKancera();

	KomoraKancera(Stan stan, double cisnienie);
	KomoraKancera(int i, int j);
	~KomoraKancera();

	KomoraKancera aktualizujKomore(UniwersKancera &uniwers);
	Stan wezStan();
	double wezCisnienie(int t);
	int wezI();
	int wezJ();

	void ustawI(int i);
	void ustawJ(int j);


private:
	Stan mStan;
	double mCisnienie[3];
	double mJedzonko;
	double mParametry;

	int mICzyliWspolrzednaPozioma, mJCzyliWspolrzednaPionowa;
};

