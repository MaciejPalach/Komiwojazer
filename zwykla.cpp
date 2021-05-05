#include "zwykla.h"
#include <iostream>

using namespace std;
void zwykla::dodaj_krawedz(int Punkt1, int Punkt2, int koszt, Graf* graf) 
{
	int pom = graf->pobierzPunkt();
	try
	{
		if (koszt < 1)
		{
			throw 104;
		}
		else
		{
			if ((Punkt1 < pom - pom || Punkt1 > pom - 1) || (Punkt2 < pom - pom || Punkt2 >pom - 1))
			{
				throw 105;
			}
			else
			{
				graf->mapa_krawedzi[make_pair(Punkt1, Punkt2)] = koszt; 
				graf->mapa_krawedzi[make_pair(Punkt2, Punkt1)] = koszt;
			}
		}
	}
	catch (int kod)
	{
			if (kod == 104)
			{
				cerr << "Error: koszt przejscia po krawedzi nie moze byc < 1\n";
				system("pause");
				exit(104);
			}
			if (kod == 105)
			{
				cout << "Error: krawedz przejscia z punktu " << Punkt1 << " do punktu " << Punkt2 << " nie zostala utworzona poniewaz jeden z punktow (lub oba) nie istnieje ";
				cout << "Punkty powinny byc z zakresu od 0 do " << pom - 1 << "\n\n";
			}

	}
}
