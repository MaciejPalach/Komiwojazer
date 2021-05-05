#include <iostream>
#include <algorithm> 
#include "AlgorytmGenetyczny.h"
using namespace std;


AlgorytmGenetyczny::AlgorytmGenetyczny(Graf* graf, int wielkosc_populacji, int generacje, int wspolczynnik_mutacji, bool czy_pokazac_populacje)
{
	try 
	{
		if (wielkosc_populacji < 1) // sprawdzamy czy wielkosc populacji jest wieksza od 1
		{
			throw 201;
		}
		else if (wspolczynnik_mutacji < 0 || wspolczynnik_mutacji > 100) // sprawdzamy czy wspolczynnik mutacji jest wiekszy od zera
		{
			throw 202;
		}
	}
	catch (int kod)
	{
		if (kod == 201)
		{
			cerr<< "Error: wielkosc populacji nie moze byc < 1\n";
			system("pause");
			exit(201);
		}
		if (kod == 202)
		{
			cerr << "Error: wspolczynnik mutacji musi byc o wartosci >= 0 i <= 100\n";
			system("pause");
			exit(202);
		}
	}
	this->graf = graf;
	this->wielkosc_populacji = wielkosc_populacji;
	this->rzeczywista_wielkosc_populacji = 0;
	this->generacje = generacje;
	this->wspolczynnik_mutacji = wspolczynnik_mutacji;
	this->czy_pokazac_populacje = czy_pokazac_populacje;
}



// sprawdzamy czy istnieje poprawne rozwiazanie i zwracamy calkowity koszt przejscia, jezeli nie: return -1
int AlgorytmGenetyczny::poprawne_rozwiazanie(vector<int>& rozwiazanie)
{
	int calkowity_koszt = 0;
	set<int> ustaw_rozwiazanie;

	// sprawdza czy nie powtazaja sie elementy
	for (int i = 0; i < graf->Punkt; i++)
		ustaw_rozwiazanie.insert(rozwiazanie[i]);

	if (ustaw_rozwiazanie.size() != (unsigned)graf->Punkt)
		return -1;

	// sprawdza czy polaczenie jest poprawne
	for (int i = 0; i < graf->Punkt; i++)
	{
		if (i + 1 < graf->Punkt)
		{
			int koszt = graf->czy_krawedz(rozwiazanie[i], rozwiazanie[i + 1]);

			// sprawdza czy istnieje polaczenie
			if (koszt == -1)
				return -1;
			else
				calkowity_koszt += koszt;
		}
		else
		{
			int koszt = graf->czy_krawedz(rozwiazanie[i], rozwiazanie[0]);

			// sprawdza czy istnieje polaczenie
			if (koszt == -1)
				return -1;
			else
				calkowity_koszt += koszt;
			break;
		}
	}
	return calkowity_koszt;
}


bool AlgorytmGenetyczny::czy_chromosom(const vector<int>& v)
{
	// sprawdza czy istnieje populacja
	for (vector<pair<vector<int>, int> >::iterator it = populacja.begin(); it != populacja.end(); ++it)
	{
		const vector<int>& vec = (*it).first; // pobiera wektor
		if (equal(v.begin(), v.end(), vec.begin())) // porownanie wektorow
			return true;
	}
	return false;
}


void AlgorytmGenetyczny::poczatkowa_populacja() // generacja poczatkowej populacji
{
	vector<int> rodzic;

	// wsadzenie poczatkowego punktu na poczatek rodzica (dodanie go do sekwencji)
	rodzic.push_back(graf->punkt_poczatkowy);

	// tworzy rodzica
	for (int i = 0; i < graf->Punkt; i++)
	{
		if (i != graf->punkt_poczatkowy)
			rodzic.push_back(i);
	}

	int calkowity_koszt = poprawne_rozwiazanie(rodzic);

	if (calkowity_koszt != -1) // sprawdza czy rodzic jest poprawny
	{
		populacja.push_back(make_pair(rodzic, calkowity_koszt)); // inserts in the population
		rzeczywista_wielkosc_populacji++; // inkrementacja populacji (rzeczywistej)
	}

	//tworzy randomowe permutacje tyle razy ile mamy miec generajci (generations)
	for (int i = 0; i < generacje; i++)
	{
		// generuje randomowa populacje
		random_shuffle(rodzic.begin() + 1, rodzic.begin() + (rand() % (graf->Punkt - 1) + 1));

		int calkowity_koszt = poprawne_rozwiazanie(rodzic); // sprawdza czy rozwiazanie jest poprawne

		
		//sprawdza czy dana permutacja jest poprawnym rozwiazaniem i czy nie istnieje
		if (calkowity_koszt != -1 && !czy_chromosom(rodzic))
		{
			populacja.push_back(make_pair(rodzic, calkowity_koszt)); // dodanie rozwiazania do populacji
			rzeczywista_wielkosc_populacji++; // inkrementacja rzeczywistej populacji w jednostce
		}
		if (rzeczywista_wielkosc_populacji == wielkosc_populacji) // sprawdza wielkosc populacji
			break;
	}

	// sprawdza wielkosc poczatkowej populacji
	try 
	{
		if (rzeczywista_wielkosc_populacji == 0)
		{
			throw 203;
		}
	}
	catch (int kod)
	{
		if (kod == 203)
		{
			cerr << "\nError: poczatkowa populacja moze byc pusta poniewaz graf nie ma wszystkich polaczen. Graf musi byæ pe³ny (kazdy punkt polaczony z kazdym) \n";
			system("pause");
			exit(203);
		}
	}
		sort(populacja.begin(), populacja.end(), sortowanie());
}


void AlgorytmGenetyczny::pokaz_populacje()  
{
	cout << "\nZnalezione rozwiazania: \n\n";
	for (vector<pair<vector<int>, int> >::iterator it = populacja.begin(); it != populacja.end(); ++it)
	{
		const vector<int>& vec = (*it).first; /**< Pobieramy wektor */

		for (int i = 0; i < graf->Punkt; i++)
			cout << vec[i] << " ";
		cout << graf->punkt_poczatkowy;
		cout << " | Koszt przejazdu: " << (*it).second << "\n\n";
	}
	cout << "\nWielkosc populacji: " << rzeczywista_wielkosc_populacji << endl;
}



void AlgorytmGenetyczny::BinarySearch(vector<int>& dziecko, int calkowity_koszt)
{
	int imin = 0;
	int imax = rzeczywista_wielkosc_populacji - 1;

	while (imax >= imin)
	{
		int imid = imin + (imax - imin) / 2;

		if (calkowity_koszt == populacja[imid].second)
		{
			populacja.insert(populacja.begin() + imid, make_pair(dziecko, calkowity_koszt));
			return;
		}
		else if (calkowity_koszt > populacja[imid].second)
			imin = imid + 1;
		else
			imax = imid - 1;
	}
	populacja.insert(populacja.begin() + imin, make_pair(dziecko, calkowity_koszt));
}


void AlgorytmGenetyczny::polaczenie(vector<int>& rodzic1, vector<int>& rodzic2)
{
	vector<int> dziecko1, dziecko2;

	// mapa genow, sprawdza czy sa juz wybrane
	map<int, int> gen1, gen2;

	for (int i = 0; i < graf->Punkt; i++)
	{
		//poczatkowo geny nie sa uzywane
		gen1[rodzic1[i]] = 0;
		gen2[rodzic2[i]] = 0;
	}

	// generuje randomowe punkty
	int Punkt1 = rand() % (graf->Punkt - 1) + 1;
	int Punkt2 = rand() % (graf->Punkt - Punkt1) + Punkt1;

	// dostosowuje punkty jezeli sa rowne
	if (Punkt1 == Punkt2)
	{
		if (Punkt1 - 1 > 1)
			Punkt1--;
		else if (Punkt2 + 1 < graf->Punkt)
			Punkt2++;
		else
		{
			// jezeli punkty sa rowne wybieramy randomowo
			int point = rand() % 10 + 1;
			if (point <= 5)
				Punkt1--;
			else
				Punkt2++;
		}
	}

	// generuje dzieci
	// dopoki przesylany(uzywany) jest Punkt1, dziecko1 dostaje geny od rodzic1
	// a dziecko2 dosteje geny od rodzic2
	for (int i = 0; i < Punkt1; i++)
	{
		// dodaje geny
		dziecko1.push_back(rodzic1[i]);
		dziecko2.push_back(rodzic2[i]);
		// oznacza geny
		gen1[rodzic1[i]] = 1;
		gen2[rodzic2[i]] = 1;
	}

	// oznacza pozostale geny
	for (int i = Punkt2 + 1; i < graf->Punkt; i++)
	{
		gen1[rodzic1[i]] = 1;
		gen2[rodzic2[i]] = 1;
	}

	// tu podciag jest odwrocany
	// dziecko1 dostaje geny od rodzic2 a
	// dziecko2 dostaje geny od rodzic1
	for (int i = Punkt2; i >= Punkt1; i--)
	{
		if (gen1[rodzic2[i]] == 0) // jesli gen nie jest uzywany
		{
			dziecko1.push_back(rodzic2[i]);
			gen1[rodzic2[i]] = 1; // oznacza gen	
		}
		else
		{
			// jezeli gen jest juz uzywany, wybiera gen ktory nie jest
			for (map<int, int>::iterator it = gen1.begin(); it != gen1.end(); ++it)
			{
				if (it->second == 0) // sprawdza czy nie jest uzywany
				{
					dziecko1.push_back(it->first);
					gen1[it->first] = 1; // oznacza jako uzywany
					break; // wyjscie z petli
				}
			}
		}

		if (gen2[rodzic1[i]] == 0) // jezeli gen nie jest uzywany
		{
			dziecko2.push_back(rodzic1[i]);
			gen2[rodzic1[i]] = 1; //oznacza gen
		}
		else
		{
			// jezeli gen jest juz uzywany, wybiera gen ktory nie jest
			for (map<int, int>::iterator it = gen2.begin(); it != gen2.end(); ++it)
			{
				if (it->second == 0) // sprawdza czy nie jest uzywany
				{
					dziecko2.push_back(it->first);
					gen2[it->first] = 1; //oznacza jako uzywany
					break; // wyjscie z petli
				}
			}
		}
	}

	// pozostale geny: dziecko1 dostaje geny od rodzic11
	// a dziecko2 dostaje geny od rodzic2
	for (int i = Punkt2 + 1; i < graf->Punkt; i++)
	{
		dziecko1.push_back(rodzic1[i]);
		dziecko2.push_back(rodzic2[i]);
	}

	// mutacja
	int mutacja = rand() % 100 + 1; // randomowy numer z przedzialu [1,100]
	if (mutacja <= wspolczynnik_mutacji) // sprawdza czy losowy numer jest <= wspolczynnikowi mutacji
	{
		// tworzy mutacje: zmiana dwoch genow

		int index_gen1, index_gen2;
		index_gen1 = rand() % (graf->Punkt - 1) + 1;
		index_gen2 = rand() % (graf->Punkt - 1) + 1;

		// tworzenie dla dziecko1
		int pom = dziecko1[index_gen1];
		dziecko1[index_gen1] = dziecko1[index_gen2];
		dziecko1[index_gen2] = pom;

		// tworzenie dla dziecko2
		pom = dziecko2[index_gen1];
		dziecko2[index_gen1] = dziecko2[index_gen2];
		dziecko2[index_gen2] = pom;
	}

	int calkowity_koszt_dziecko1 = poprawne_rozwiazanie(dziecko1);
	int calkowity_koszt_dziecko2 = poprawne_rozwiazanie(dziecko2);

	// sprawdza czy jest to poprawne rozwiazanie i czy nie istnieje juz takie
	if (calkowity_koszt_dziecko1 != -1 && !czy_chromosom(dziecko1))
	{
		// dodaje dziecko do populacji
		BinarySearch(dziecko1, calkowity_koszt_dziecko1); // uzywa wyszukiwania binarnego do wstawienia
		rzeczywista_wielkosc_populacji++; // populacja krolestwa zwieksza sie
	}

	// sprawdzenie dla dziecko2
	if (calkowity_koszt_dziecko2 != -1 && !czy_chromosom(dziecko2))
	{
		// dodanie dziecka do populacji
		BinarySearch(dziecko2, calkowity_koszt_dziecko2); // uzywa wyszukiwania binarnego do wstawienia
		rzeczywista_wielkosc_populacji++; // populacja krolestwa zwieksza sie
	}
}


// uruchamia algorytm genetyczny
void AlgorytmGenetyczny::rozpocznij_algorytm()
{
	poczatkowa_populacja(); // pobiera poczatkowa populacje

	if (rzeczywista_wielkosc_populacji == 0)
		return;

	for (int i = 0; i < generacje; i++)
	{
		int  poprzednia_wielkosc_populacji = rzeczywista_wielkosc_populacji;

		//wybiera dwoch rodzicow (jesli istnieja) ktorzy beda uczestniczyli
		//w procesie produkcji nastepnych pokolen 
		if (rzeczywista_wielkosc_populacji >= 2)
		{
			if (rzeczywista_wielkosc_populacji == 2)
			{
				// laczenie rodzicow
				polaczenie(populacja[0].first, populacja[1].first);
			}
			else
			{
				// jezeli populacja jest > 2

				int rodzic1, rodzic2;

				do
				{
					// wybieramy dwoch randomowych rodzicow
					rodzic1 = rand() % rzeczywista_wielkosc_populacji;
					rodzic2 = rand() % rzeczywista_wielkosc_populacji;
				} while (rodzic1 == rodzic2);

				// laczenie rodzicow
				polaczenie(populacja[rodzic1].first, populacja[rodzic2].first);
			}

			// sprawdzenie czy populacja wzrosla
			int roznica = rzeczywista_wielkosc_populacji - poprzednia_wielkosc_populacji;

			if (roznica == 2)
			{
				if (rzeczywista_wielkosc_populacji > wielkosc_populacji)
				{
					// usuwa dwoje najgorszych rodzicow
					populacja.pop_back();
					populacja.pop_back();

					// zmniejsza liczbe rzeczywistej populacji
					rzeczywista_wielkosc_populacji -= 2;
				}
			}
			else if (roznica == 1)
			{
				if (rzeczywista_wielkosc_populacji > wielkosc_populacji)
				{
					populacja.pop_back(); // usuwa najgorszego rodzica
					rzeczywista_wielkosc_populacji--; // zmniejsza liczbe rzeczywistej populacji
				}
			}
		}
		else // jezeli populacja sklada sie tylko z jednego rodzica
		{
			// laczenie rodzicow (2 tych samych)
			polaczenie(populacja[0].first, populacja[0].first);

			if (rzeczywista_wielkosc_populacji > wielkosc_populacji)
			{
				populacja.pop_back(); // usuwa najgorszego rodzica
				rzeczywista_wielkosc_populacji--; // zmniejsza liczbe rzeczywistej populacji
			}
		}
	}

	if (czy_pokazac_populacje == true)
		pokaz_populacje(); // pokazuje populacje

	cout << "\nNajlepsze rozwiazanie: ";
	const vector<int>& vec = populacja[0].first;
	for (int i = 0; i < graf->Punkt; i++)
		cout << vec[i] << " ";
	cout << graf->punkt_poczatkowy;
	cout << " | Koszt przejazdu: " << populacja[0].second;
}


int AlgorytmGenetyczny::rozwiazanie()
{
	if (rzeczywista_wielkosc_populacji > 0)
		return populacja[0].second;
	return -1;
}