#ifndef KIERUNKOWA_H
#define KIERUNKOWA_H
#include "Graf.h"

/**
* Klasa reprezentujaca krawedz kierunkowa. 
*/class kierunkowa : public Graf
{
public:
	kierunkowa() {};	 /**< Konstruktor domyslny */
	
	/** 
	* Metoda dodajaca krawedz do grafu
	*/
	virtual void dodaj_krawedz(int Punkt1, int Punkt2, int koszt, Graf* graf) override; 
};

#endif KIERUNKOWA_H