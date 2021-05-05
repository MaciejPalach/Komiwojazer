#ifndef SORTOWANIE_H
#define SORTOWANIE_H
#include <utility> //para
#include <vector>

typedef std::pair<std::vector<int>, int> para;  /**< zdefiniowanie nowej zmiennej o nazwie para, zawierajacej pare: wektor(sciezke) oraz koszt przejscia po niej */

/**
* Klasa reprezentujaca sortowanie 
*/
class sortowanie 
{
public:
	
	/**
	* Metoda zwracajaca posortowane dane pod wzgledem kosztu przejscia przez wszystkie punkty od najkrotszej do najdluzszej
	*/
	bool operator()(const para& trasa1, const para& trasa2)
	{
		return trasa1.second < trasa2.second;
	}
};

#endif