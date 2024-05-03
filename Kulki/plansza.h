#ifndef PLANSZA_H
#define PLANSZA_H
#include <iostream>

#define MAX_ROZMIAR_PLANSZY 10			//rozmiar planszy do podania do tablicy
#define BICIE 5							//ile kulek w jednej linii oznacza bicie
#define IleKulekCoKolejke 3				//ile kulek ma sie pojawiac co kolejke

class Plansza {					//klasa plansza
public:
	Plansza(int rozmiar);			//konstruktor
	void rysuj();					//metoda rysujaca plansze
	int czyKoniecGry();				//metoda sprawdzajaca czy gra moze byc kontynuowana (czy sa wolne pola pozwalajace na ruch)
	int czyJestDroga(int x, int y, int newX, int newY);			//metoda sprawdzajaca czy gracz jest w stanie przemiescic kulke z pola o wsp. x,y na pole newX, newY
	int wykonajBicie();				//metoda realizujaca bicia na planszy
	int* generujKulki(int ileKulek);				//metoda generujaca kolejke kulek do pojawienia sie na planszy, podajemy ile kulek ma zostac dodanych do kolejki
	void losujKulki(int ileKulek, int *kulki);			//metoda rozstawiajaca wylosowane kulki na planszy
	void losujKulkiNaStart(int ileKulek);				//metoda rozstawiajaca kulki na planszy na samym poczatku (bo jest to rozna ilosc, bez kolejki bo gracz jej nie zna przed rozpoczeciem gry)
	void przeniesKulke(int x, int y, int newX, int newY);			//metoda przenoszaca kulke z miejsca x,y na miejsce newX, newY
	int getRozmiar() {				//geter
		return rozmiar;
	}
	void setRozmiar(int size) {			//seter
		rozmiar = size;
	}
private:
	char plansza[MAX_ROZMIAR_PLANSZY][MAX_ROZMIAR_PLANSZY];
	int rozmiar;
};

#endif