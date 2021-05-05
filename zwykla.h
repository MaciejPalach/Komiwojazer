#ifndef ZWYKLA_H
#define ZWYKLA_H
#include "Graf.h"
/**
* Klasa reprezentujaca krawedz kierunkowa.
*/
class zwykla : public Graf
{
public:
	zwykla() {}; /**< Konstruktor domyslny */
	
	/**
	* Metoda dodajaca krawedz do grafu
	*/
	virtual void dodaj_krawedz(int Punkt1, int Punkt2, int koszt, Graf* graf) override ;
};

#endif