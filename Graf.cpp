#include <iostream>
#include <algorithm> 
#include "Graf.h"
using namespace std;

Graf::Graf(int Punkt, int punkt_poczatkowy)
{
	try 
	{
		if (Punkt < 1) 
		{
			throw 101;
		}


		else if (Punkt == 1)
		{
			throw 102;		
		}

		else if (punkt_poczatkowy<Punkt - Punkt || punkt_poczatkowy > Punkt - 1)
		{
			throw 103;
		}
	}
	catch (int kod) 
	{
		if (kod == 101) 
		{ 
			cerr << "Error: Liczba punktow nie moze byc <= 0\n"; 
			system("pause"); 
			exit(101);
		}
		if (kod == 102) 
		{ 
			cerr << "Error: Twoj graf sklada sie tylko z jednego punktu\n"; 
			system("pause"); exit(102);
		}
		if (kod == 103) 
		{ 
			cerr << "Error: Komiwojazera nie ma na grafie. Wybrales zly punkt poczatkowy. Upewnij sie ze znajduje sie on w zakresie od 0 do " << Punkt - 1 << "\n";
			system("pause"); 
			exit(103); 
		}
	}
	this->Punkt = Punkt; 
	this->punkt_poczatkowy = punkt_poczatkowy; 
	this->krawedzie = 0; 
}

void Graf::info_graf()  
{
	cout << "Informacje o grafie:\n\n";
	cout << "Liczba wierzcholkow: " << pobierzPunkt();
	cout << "\nLiczba krawedzi: " << mapa_krawedzi.size()/2 << "\n";
}



void Graf::wyswietl_graf()
{
	map<pair<int, int>, int>::iterator it;
	for (it = mapa_krawedzi.begin(); it != mapa_krawedzi.end(); ++it)
		cout << it->first.first << " polaczony z punktem " << it->first.second << " z waga krawedzi " << it->second << endl;
}


int Graf::czy_krawedz(int Punkt1, int Punkt2) 
{
	map<pair<int, int>, int>::iterator it = mapa_krawedzi.find(make_pair(Punkt1, Punkt2));

	if (it != mapa_krawedzi.end())
		return it->second; 
	return -1;
}