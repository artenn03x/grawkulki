#ifndef GRACZE_H
#define GRACZE_H
#include <iostream>
#include "plansza.h"
class Gracz {				//klasa Gracz
private:
	char nick[30];	
	int punkty;
	int x, y, x1, y1;
public:
	Gracz() : punkty(0), x(0), y(0), x1(0), y1(0) {			//lista inicjalizatorow konstruktora dla Gracz
		strcpy(nick, "Gracz");
	}
	Gracz(const char* nickname) : punkty(0), x(0), y(0), x1(0), y1(0) {	//lista inicjalizatorow konstruktora dla Gracz
		strcpy(nick, nickname);
	}
	virtual int wykonajRuch(Plansza& plansza, int*losowaneKulki) = 0;	//zlozona metoda polimorficzna realizujaca ruch gracza lub komputera wywolujacy wykonanie sekwencji zachowan na planszy, zwraca wartosc wskazujaca na to czy w poprzednim ruchu zostalo wykonane bicie
	virtual void wypiszDaneGracza() = 0; //metoda polimorficzna wypisujaca dane gracza lub gracza-komputera
	void wczytajRuch();		//metoda wczytujaca z klawiatury ruch gracza
	int dodajPunkty(int punktyDoDodania);	//metoda dodajaca do punkty ilosci zasluzonych punktow
	int getPunkty() const;		//geter Punkty
	char* getNick();	//geter Nick
	int getX();		//geter x (wiersza kulki)
	int getY();		//geter y (kolumny kulki)
	int getX1();		//geter x1 (wiersza gdzie przeniesc kulke)
	int getY1();			//geterx2 (kolumny gdzie przeniesc kulke)
	void setX(int dana);		//seter x
	void setY(int dana);		//seter y
	void setX1(int dana);			//seter x1
	void setY1(int dana);			//seter x2
	void setPunkty(int dana);			//seter punkty (ilosc punktow gracza)
	void setNick(char nickname[15]);		//seter nick (nazwa gracza)
	friend class GraczCzlowiek;				//"zaprzyjaznienie" klasy GraczCzlowiek
	friend class GraczKomputer;				//"zaprzyjaznienie" klasy GraczKomputer
};
class GraczCzlowiek : public Gracz {		//klasa GraczCzlowiek
public:
	GraczCzlowiek() {						//konstruktor
		strcpy(nick, "Czlowiek");
		punkty = 0;
		x = 0;
		y = 0;
		x1 = 0;
		y1 = 0;
	}
	GraczCzlowiek(const char* nickname) {		//konstruktor
		strcpy(nick, nickname);
		punkty = 0;
		x = 0;
		y = 0;
		x1 = 0;
		y1 = 0;
	}
	void wypiszDaneGracza();				//analogicznie jak wyzej
	int getX();
	int getY();
	int getX1();
	int getY1();
	void setX(int dana);
	void setY(int dana);
	void setX1(int dana);
	void setY1(int dana);
	int wykonajRuch(Plansza& plansza, int *losowaneKulki); //analogicznie jak wyzej (metoda polimorficzna)
};
class GraczKomputer : public Gracz { //klasa GraczKomputer
public:
	GraczKomputer() {				//konstruktor
		strcpy(nick, "Komputer");
		punkty = 0;
		x = 0;
		y = 0;
		x1 = 0;
		y1 = 0;
	}
	GraczKomputer(const char* nickname) {					//konstruktor
		strcpy(nick, nickname);
		punkty = 0;
		x = 0;
		y = 0;
		x1 = 0;
		y1 = 0;
	}
	void wypiszDaneGracza();		//analogicznie 
	int getX();
	int getY();
	int getX1();
	int getY1();
	void setX(int dana);
	void setY(int dana);
	void setX1(int dana);
	void setY1(int dana);
	int wykonajRuch(Plansza& plansza, int *losowaneKulki);			//metoda polimorficzna
};
#endif