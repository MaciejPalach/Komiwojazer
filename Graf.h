#ifndef GRAF_H
#define GRAF_H

#include <vector>
#include <map>
#include <set>
#include <utility> 
#include <time.h> 
#include <stdlib.h> 

/**
* Klasa reprezentujaca graf
*/
class Graf 
{
private:
	int Punkt; /**< Liczba punktow tworzacych graf */
	int krawedzie; /**< Liczba krawedzi znajdujacych sie w grafie */
	int punkt_poczatkowy; /**< Punkt od ktorego komiwojazer zaczyna swoja podroz (punkt startowy)*/
public:
	/**
	*Settery i gettery do pobierania i ustawiania parametrow grafu z zewnatrz klasy
	*/
	int pobierzPunkt() const { return Punkt; };
	void ustawPunkt(int Punkt) { this->Punkt = Punkt; };
	int pobierzkrawedzie() const { return krawedzie; };
	void ustawkrawedzie(int krawedzie) { this->krawedzie = krawedzie; };
	int pobierzpunkt_poczatkowy() const { return punkt_poczatkowy; };
	void ustawpunkt_poczatkowy(int punkt_poczatkowy)  { this->punkt_poczatkowy=punkt_poczatkowy; };
	
	std::map<std::pair<int, int>, int> mapa_krawedzi; // mapa krawedzi
	
	Graf() {}; /**< Konstruktor domyslny */
	
	/**
	* Konstruktor inicjalizujacy skladowe grafu
	*/
	Graf(int Punkt, int punkt_poczatkowy);
	
	/** Metoda wirtualna dodajaca krawedz do grafu
	*
	*/
	virtual void dodaj_krawedz(int Punkt1, int Punkt2, int koszt, Graf* graf) {}; 
	
	/** Metoda wyswietlajaca na ekranie wynikowym wszystkie polaczenia dostepne w grafie razem z kosztem przejscia po nich (mapa polaczen)
	*
	*/
	void wyswietl_graf(); 
	
	/** Metoda wyswietlajaca na ekranie wynikowym podstawowe informacje dotyczace grafu czyli liczbe punktow oraz krawedzi
	*
	*/
	void info_graf(); 
	
	/** Metoda sprawdzajaca czy krawedz z jednego punktu do drugiego istnieje
	*
	*/
	int czy_krawedz(int Punkt1, int Punkt2); 
	
	/** Uzyskanie dostepu do private klasy AlgorytmuGenetycznego
	*
	*/
	friend class AlgorytmGenetyczny; 
	
	~Graf() {}; /**< Destruktor domyslny */
};

#endif