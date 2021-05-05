#include <iostream>
#include "AlgorytmGenetyczny.h"
#include "zwykla.h"
#include "kierunkowa.h"
#include <chrono>
using namespace std;
namespace ch = std::chrono;
int main()
{
	zwykla a,b,c,d,e,f,g,h,i,j,k,l;
	kierunkowa x, y, z;
	
	// stworzenie grafu z parametrami: liczba punktow oraz punkt poczatkowy
	//graf testowy 1
	//Graf * test_graf = new Graf(5, 0);
	//
	//// dodanie krawedzi punkt a, punkt b, koszt, czy kierunkowy
	//x.dodaj_krawedz(0, 1, 1, test_graf);
	//y.dodaj_krawedz(1, 0, 5, test_graf);	
	//
	//a.dodaj_krawedz(0, 2, 3, test_graf);	
	//b.dodaj_krawedz(0, 3, 4, test_graf);	
	//c.dodaj_krawedz(0, 4, 5, test_graf);
	//d.dodaj_krawedz(1, 2, 1, test_graf);
	//e.dodaj_krawedz(1, 3, 4, test_graf);
	//f.dodaj_krawedz(1, 4, 2, test_graf);
	//g.dodaj_krawedz(2, 3, 4, test_graf);
	//h.dodaj_krawedz(2, 4, 1, test_graf);
	//i.dodaj_krawedz(3, 4, 4, test_graf);
	
	
	////graf testowy 2
	//Graf * test_graf = new Graf(4, 0);

	//a.dodaj_krawedz(0, 1, 2, test_graf);
	//c.dodaj_krawedz(0, 2, 6, test_graf);
	//e.dodaj_krawedz(0, 3, 3, test_graf);
	//g.dodaj_krawedz(1, 3, 7, test_graf);
	//i.dodaj_krawedz(1, 2, 4, test_graf);
	//k.dodaj_krawedz(2, 3, 2, test_graf);

	//
	//
		
	// graf testowy 3
	Graf * test_graf = new Graf(4, 0);

	a.dodaj_krawedz(0, 1, 10, test_graf);
	c.dodaj_krawedz(1, 3, 20, test_graf);
	e.dodaj_krawedz(0, 2, 15, test_graf);
	g.dodaj_krawedz(1, 3, 25, test_graf);
	i.dodaj_krawedz(2, 3, 30, test_graf);
	k.dodaj_krawedz(1, 2, 35, test_graf);
	b.dodaj_krawedz(0, 3, 20, test_graf);

	

	
	test_graf->info_graf();		//wyswietlamy informacje o grafie
	test_graf->wyswietl_graf();	//wyswietlamy "mape" polaczen

	// parametry: graf, wielkosc populacji, liczba generacji oraz wspolczynnik mutacji
	// parametr opcjonalny: czy_pokazac_populacje - dla true i pustego pokazuje, dla false nie pokazuje
	AlgorytmGenetyczny test_algorytm2(test_graf, 10, 100, 5, true);
	
	ch::high_resolution_clock timer; //rozpoczecie odliczania
	auto start = timer.now();

	test_algorytm2.rozpocznij_algorytm(); //uruchamia algorytm genetyczny
		
	auto end = timer.now();
	auto nsecs = ch::duration_cast<ch::milliseconds>(end - start).count();
	cout << "\n\nCzas dla testu 1: " << nsecs << " ms\n";
	
	delete test_graf;
	system("pause");
	return 0;
}