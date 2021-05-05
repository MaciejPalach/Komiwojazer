#ifndef ALGORYTMGENETYCZNY_H
#define ALGORYTMGENETYCZNY_H

#include <vector>
#include <map>
#include <set>
#include <utility> 
#include <time.h> 
#include <stdlib.h>
#include "Graf.h"
#include "sortowanie.h"

/**
* Klasa reprezentujaca algorytm genetyczny
*/
class AlgorytmGenetyczny
{
private:
	Graf* graf; /**< Wskaznik na graf na ktorym bedzie szukana najkrotsza sciezka */
	std::vector< para > populacja; /**< Kazdy element populacji przechowywany jest jako para: wektor(trasa) i koszt przejscia */ 
	int wielkosc_populacji; /**< Wielkosc populacji */ 
	int rzeczywista_wielkosc_populacji; /**< Rzeczywista wielkosc populacji (taka ktora jest na danym etapie algorytmu) */ 
	int generacje; /**< liczba generacji */ 
	int wspolczynnik_mutacji; /**< Wspolczynnik mutacji */ 
	bool czy_pokazac_populacje; /**< Parametr opcjonalny stanowiacy o tym, czy na ekranie wynikowym wyswietli sie kazdy element populacji */ 
	
	/** Metoda inicjujaca (tworzaca) poczatkowa populacje
	*
	*/
	void poczatkowa_populacja(); 
public:
	
	/** 
	*Settery i gettery do pobierania i ustawiania parametrow algorytmu z zewnatrz klasy
	*/
	int pobierz_wielkosc_populacji() const { return wielkosc_populacji; };
	void ustaw_wielkosc_populacji(int wielkosc_populacji) { this->wielkosc_populacji = wielkosc_populacji; };
	int pobierz_rzeczywista_wielkosc_populacji() const { return rzeczywista_wielkosc_populacji; };
	void ustaw_rzeczywista_wielkosc_populacji(int rzeczywista_wielkosc_populacji) { this->rzeczywista_wielkosc_populacji = rzeczywista_wielkosc_populacji; };
	int pobierz_generacje() const { return generacje; };
	void ustaw_generacje(int generacje) { this->generacje = generacje; };
	int pobierz_wspolczynnik_mutacji() const { return wspolczynnik_mutacji; };
	void ustaw_wspolczynnik_mutacji(int wspolczynnik_mutacji) { this->wspolczynnik_mutacji = wspolczynnik_mutacji; };
	bool pobierz_czy_pokazac_populacje() { return czy_pokazac_populacje; };
	void ustaw_czy_pokazac_populacje(bool czy_pokazac_populacje) { this->czy_pokazac_populacje=czy_pokazac_populacje; };
	

	AlgorytmGenetyczny() {};  /**< Konstruktor domyslny */
	
	/** 
	* Konstruktor inicjalizujacy skladowe algorytmu genetycznego
	*/
	AlgorytmGenetyczny(Graf* graf, int wielkosc_populacji, int generacje, int wspolczynnik_mutacji, bool czy_pokazac_populacje = true); // konstruktor algorytmu genetycznego
	
	/** Metoda wyswietlajaca na ekranie wynikowym populacje
	*  @return Populacja: Elementy skladajace sie ze sciezki i kosztu przejscia po niej
	*/
	void pokaz_populacje(); 
	
	/** Metoda robiaca crossover i mutacje pomiedzy osobnikami populacji
	*  
	*/
	void polaczenie(std::vector<int>& rodzic1, std::vector<int>& rodzic2); 
	
	/** Metoda uzywajaca poszukiwania binarnego do znalezienia najlepszego osobnika populacji (najkrotszej sciezki przejscia po wszystkich punktach)
	*
	*/
	void BinarySearch(std::vector<int>& dziecko, int calkowity_koszt); 
	
	/** Metoda rozpoczynajaca prace algorytmu genetycznego
	* @return Wynik koncowy dzialania programu
	*/
	void rozpocznij_algorytm(); 
	
	/** Metoda sprawdzajaca czy podane do niej rozwiazanie jest poprawne i czy takie juz nie wystepuje w populacji
	* 
	*/
	int poprawne_rozwiazanie(std::vector<int>& rozwiazanie);
	
	/** Metoda zwracajaca najlepsze rozwiazanie
	* 
	*/
	int rozwiazanie(); 
	
	/** Metoda sprawdzajaca czy dany chromosom istnieje
	* 
	*/
	bool czy_chromosom(const std::vector<int> & Punkt); 
};




#endif