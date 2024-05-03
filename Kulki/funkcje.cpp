#include "funkcje.h"
#define RESET   "\033[0m"								//sekwencje ucieczki ASCII pozwalajace na uzycie kolorow w konsoli
#define JASNONIEBIESKI  "\033[94m"
#define CZERWONY     "\033[31m"
#define ROZOWY	"\033[95m"
#define NIEBIESKI    "\033[34m"
#define ZIELONY   "\033[32m"
#define ZOLTY	 "\033[33m"
#define BIALY   "\033[37m"
#define IleKulekNaStart 5							//ilosc kulek losowanych na starcie
#define nazwa "tabela.txt"							//nazwa pliku do ktorego beda wypisywane wyniki graczy
using namespace std;
void czyszczenieBufora() {	//czyszczenie bufora
	cin.clear();
	while (cin.get() != '\n') {
		continue;
	}
}
void Logo() {					//wyswietlenie pokolorowanego LOGO zlozonego z O imitujacych kulki
	cout << "Autor: Piotr Graczyk "<< endl << endl;
	cout << JASNONIEBIESKI << "OO    OO OO     OO OO       OO    OO OOOO" << RESET << endl;
	cout << CZERWONY << "OO   OO  OO     OO OO       OO   OO   OO" << RESET << endl;
	cout << NIEBIESKI << "OO  OO   OO     OO OO       OO  OO    OO" << RESET << endl;
	cout << ZIELONY << "OOOO     OO     OO OO       OOOOO     OO" << RESET << endl;
	cout << ZOLTY << "OO  OO   OO     OO OO       OO  OO    OO" << RESET << endl;
	cout << BIALY << "OO   OO  OO     OO OO       OO   OO   OO" << RESET << endl;
	cout << ROZOWY << "OO    OO  OOOOOOO  OOOOOOOO OO    OO OOOO" << RESET << endl;
	cout << endl;
	cout << endl;
	cout << endl;
}
void komunikatODodaniuPunktow(int punktyDoDodania) {		//tak jak w nazwie funkcji
	if (punktyDoDodania > 0) {									//jak nie ma punktow (nie bylo bicia) to nie wyswietla nic
		cout << endl << "Bicie! Dodaje punkty!" << endl;
	}
}
void podajNick(char* nick) {										//funkcja pozwalajaca na podanie przez uzytkownika nicku
	cout << "Podaj nick (Nick >30 znakow zostanie uciety, nie uzywaj spacji): ";
	cin >> nick;
}
void zapiszDaneDoPliku(const char* nazwaPliku, const char* nick, int punkty) {		//funkcja pozwalajaca zapisac dane do pliku
	FILE* plik = fopen(nazwaPliku, "a");							//tryb append
	if (!plik) {												//kontrola czy sie udalo otworzyc plik
		cout << "Blad podczas otwierania pliku" << endl;
		return;
	}
	fprintf(plik, "Nazwa gracza: %s\t", nick);						//wypisanie do pliku nicku gracza
	fprintf(plik, "Ilosc zdobytych punktow: %d\n", punkty);				//oraz ilosci punktow
	fclose(plik);							
}
void tekstDoWyborow() {												//wypisanie tekstu "Menu" uzytkownika z jego mozliwymi wyborami dalszych akcji
	cout << "Wybierz akcje: " << endl << endl;
	cout << "1. Gra: tylko gracz" << endl;
	cout << "2. Gra: gracz vs gracz		(Kazdy ma swoja plansze)" << endl;
	cout << "3. Gra: gracz vs komputer	(Kazdy ma swoja plansze)" << endl;
	cout << "4. Zobacz aktualne wyniki" << endl;
	cout << "5. Wyjdz" << endl;
	cout << endl;
	cout << "Akcja: ";
}
int wybory() {							//realizacja wpisania wyboru gracza
	int wybor = 0;
	do {
		tekstDoWyborow();						//wypisanie mozliwosci akcji
		cin >> wybor;							
		if (wybor == 1 || wybor == 2 || wybor == 3 || wybor == 4 || wybor == 5) return wybor;		//jak uzytkownik dokonal wyboru to zwroc wybor
		czyszczenieBufora();							//wyczyszczenie bufora przed kolejnym wpisaniem
	} while (true);					//petla az uzytkownik nie dokona wyboru 1,2,3,4 lub 5
	return wybor;
}
void Werdykt(Gracz& gracz1, Gracz& gracz2) {			//sprawdzenie kto wygral (kto ma wiecej punktow ze swojej planszy)
	if (gracz1.getPunkty() > gracz2.getPunkty()) {							//sprawdzenie czy gracz1 wygral uzywajac getera
		cout << "Wygrana gracza: " << gracz1.getNick() << " Ilosc punktow: " << gracz1.getPunkty() << endl;
	}
	else if (gracz2.getPunkty() > gracz1.getPunkty()) {	//sprawdzenie czy gracz2 wygral
		cout << "Wygrana gracza: " << gracz2.getNick() << " Ilosc punktow: " << gracz2.getPunkty() << endl;
	}
	else if (gracz1.getPunkty() == gracz2.getPunkty()) {		//sprawdzenie opcji remisu
		cout << "Remis! Ilosc punktow: " << gracz1.getPunkty() << endl;
	}
}
void graJednegoGracza() {		//realizajca gry dla jednego gracza
	char nick[30];				
	podajNick(nick);					//podanie nicku
	Plansza plansza1(MAX_ROZMIAR_PLANSZY - 1);
	GraczCzlowiek gracz1(nick);
	plansza1.losujKulkiNaStart(IleKulekNaStart);			//wylosowanie na plansze kulek na start (jest to inna ilosc niz co kolejke)
	int czyLosowacNowa = 1;					//sprawdzenie czy losowac nowa kulke, potem sie przydaje aby zapobiec sytuacji gdzie po zbiciu losuja sie nowe kulki
	int* kulki = nullptr;
	while (!plansza1.czyKoniecGry()) {				//dopoki plansza nie jest zapelniona
		gracz1.wypiszDaneGracza();					//wypisz dane gracza
		plansza1.rysuj();						//narysuj plansze
		if (czyLosowacNowa == 1) kulki = plansza1.generujKulki(IleKulekCoKolejke);	//jak nie bylo bicia tzn. zmienna czyLosowacNowa==1 no to kolejne kulki do kolejki
		int czyByloBicie = gracz1.wykonajRuch(plansza1, kulki);	//wykonanie ruchu przez gracza zwraca wartosc czy bylo bicie czy go nie bylo
		if (czyByloBicie != 1) {					//jesli bicie nie nastapilo to zwalniam pamiec, i szykuje sie na losowanie nowych kul
			delete[] kulki;
			czyLosowacNowa = 1;
		}
		else {
			czyLosowacNowa = 0;			//jesli bicie nastapilo to nie generuje nowych kulek do kolejki
		}
	}
	cout << "Koniec gry! Zapisuje dane" << endl;		
	gracz1.wypiszDaneGracza();					
	zapiszDaneDoPliku(nazwa, nick, gracz1.getPunkty());					//zapis danych gracza do pliku
}
void graGraczvsGracz() {					//realizacja gry Gracz vs Gracz 
	char nick[30];
	podajNick(nick);
	char nick2[30];
	podajNick(nick2);
	Plansza plansza1(MAX_ROZMIAR_PLANSZY - 1);
	GraczCzlowiek gracz1(nick);
	Plansza plansza2(MAX_ROZMIAR_PLANSZY - 1);			
	GraczCzlowiek gracz2(nick2);
	plansza1.losujKulkiNaStart(IleKulekNaStart);		//tworzone sa dwie indywidualne plansze
	plansza2.losujKulkiNaStart(IleKulekNaStart);
	int* kulki1 = nullptr;
	int czyLosowacNowa1 = 1;
	int* kulki2 = nullptr;
	int czyLosowacNowa2 = 1;
	while (!plansza1.czyKoniecGry() || !plansza2.czyKoniecGry()) {				//gra sie toczy do momentu gdy obaj gracze pozostana bez ruchu
		gracz1.wypiszDaneGracza();
		plansza1.rysuj();
		if (!plansza1.czyKoniecGry()) {						//jesli gracz juz nie ma mozliwosci ruchu to nie gra

			if (czyLosowacNowa1 == 1) kulki1 = plansza1.generujKulki(IleKulekCoKolejke);
			int czyByloBicie1 = gracz1.wykonajRuch(plansza1, kulki1);
			if (czyByloBicie1 != 1) {
				delete[] kulki1;
				czyLosowacNowa1 = 1;
			}
			else {
				czyLosowacNowa1 = 0;
			}
		}
		gracz2.wypiszDaneGracza();				//wciaz wypisuje dane gracza mimo ze juz moze nie grac (zabieg celowy, aby na biezaco jeden z graczy mogl patrzec na roznice punktow miedzy drugim graczem)
		plansza2.rysuj();
		if (!plansza2.czyKoniecGry()) {						//analogicznie dla drugiego gracza i 2 planszy

			if (czyLosowacNowa2 == 1) kulki2 = plansza2.generujKulki(IleKulekCoKolejke);
			int czyByloBicie2 = gracz2.wykonajRuch(plansza2, kulki2);
			if (czyByloBicie2 != 1) {
				delete[] kulki2;
				czyLosowacNowa2 = 1;
			}
			else {
				czyLosowacNowa2 = 0;
			}
		}
	}
	Werdykt(gracz1, gracz2);					//werdykt kto wygral
	cout << "Koniec gry! Zapisuje dane" << endl;		
	gracz1.wypiszDaneGracza();
	zapiszDaneDoPliku(nazwa, nick, gracz1.getPunkty());
	gracz2.wypiszDaneGracza();
	zapiszDaneDoPliku(nazwa, nick2, gracz2.getPunkty());
}
void graGraczvsKomputer() {						//gra Gracz kontra komputer robiacy losowe ruchy ale zgodne z zasadami tzn. nie moze wykonac niedozwolonego ruchu
	char nick[30];
	podajNick(nick);			// w tym wypadku prosi tylko o nick Gracza bedacego czlowiekiem
	Plansza plansza1(MAX_ROZMIAR_PLANSZY - 1);
	GraczCzlowiek gracz1(nick);
	Plansza plansza2(MAX_ROZMIAR_PLANSZY - 1);
	GraczKomputer gracz2;					//komputer dostaje domyslny nick
	plansza1.losujKulkiNaStart(IleKulekNaStart);
	plansza2.losujKulkiNaStart(IleKulekNaStart);
	int* kulki1 = nullptr;
	int czyLosowacNowa1 = 1;
	int* kulki2 = nullptr;
	int czyLosowacNowa2 = 1;
	while (!plansza1.czyKoniecGry() || !plansza2.czyKoniecGry()) {
		gracz1.wypiszDaneGracza();
		plansza1.rysuj();
		if (!plansza1.czyKoniecGry()) {

			if (czyLosowacNowa1 == 1) kulki1 = plansza1.generujKulki(IleKulekCoKolejke);
			int czyByloBicie1 = gracz1.wykonajRuch(plansza1, kulki1);
			if (czyByloBicie1 != 1) {
				delete[] kulki1;
				czyLosowacNowa1 = 1;
			}
			else {
				czyLosowacNowa1 = 0;
			}
		}
		gracz2.wypiszDaneGracza();
		plansza2.rysuj();
		if (!plansza2.czyKoniecGry()) {
			if (czyLosowacNowa2 == 1) kulki2 = plansza2.generujKulki(IleKulekCoKolejke);
			int czyByloBicie2 = gracz2.wykonajRuch(plansza2, kulki2);
			if (czyByloBicie2 != 1) {
				delete[] kulki2;
				czyLosowacNowa2 = 1;
			}
			else {
				czyLosowacNowa2 = 0;
			}
		}
	}
	Werdykt(gracz1, gracz2);
	cout << "Koniec gry! Zapisuje dane" << endl;
	gracz1.wypiszDaneGracza();
	zapiszDaneDoPliku(nazwa, nick, gracz1.getPunkty());
	gracz2.wypiszDaneGracza();
	zapiszDaneDoPliku(nazwa, gracz2.getNick(), gracz2.getPunkty());
}
void odczytywanieDanych(const char* nazwaPliku) {			//odczyt danych z pliku zawierajacego wyniki
	FILE* plik = fopen(nazwaPliku, "r");			//tryb do odczytu
	if (!plik) {					//jak sie nie udalo otworzyc pliku to wtedy
		cout << endl << "Blad otwierania pliku." << endl << endl;
		return;
	}
	char znak;		
	while ((znak = fgetc(plik)) != EOF) {				//zczytywanie kolejno znakow i wypisywanie ich w oknie konsoli
		cout << znak;
	}
	fclose(plik);				//zamkniecie pliku
}
void Menu() {					//funkcja realizujaca finalne menu gry, realizujace juz de facto gre, w ktorej do momentu az nie podejmie wyboru ktory konczy gre, moze wciaz grac
	int decyzja;
	while (true) {				//petla nieskonczona
		decyzja = wybory();					//pobranie od uzytkownika wyboru
		if (decyzja == 1) {
			graJednegoGracza();					//1 oznacza gre jednego gracza (klasyczna)
		}
		if (decyzja == 2) {
			graGraczvsGracz();			//2 gracz vs gracz
		}
		if (decyzja == 3) {
			graGraczvsKomputer();			//3 gracz vs komputer
		}
		if (decyzja == 4) {
			odczytywanieDanych(nazwa);	//4 odczytuje wyniki graczy z pliku
		}
		if (decyzja == 5) {		//5 oznacza zakonzcenie gry
			exit(0);
		}
	}
}