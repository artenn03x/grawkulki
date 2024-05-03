#include "gracze.h"
#include "funkcje.h"
#define IleKulekCoKolejke 3			//ilosc dodanych kulek co nastepny ruch
using namespace std;
void Gracz::wczytajRuch() {				//metoda realizujaca wczytanie ruchu gracza 
	cout << "Podaj wiersz kulki do przeniesienia: ";
	czyszczenieBufora();			//czyszczenie bufora
	cin >> x;
	x--;					//aby byla zgodnosc miedzy tabelka, ktora jest narysowana w konsoli oraz tym co chce uzytkownik np. wiersz 1 kolumna 1 bedzie elementem [0][0] tablicy
	cout << "Podaj kolumne kulki do przeniesienia: ";
	czyszczenieBufora();
	cin >> y;
	y--;
	cout << "Podaj wiersz, gdzie przeniesc kulke: ";
	czyszczenieBufora();
	cin >> x1;
	x1--;
	cout << "Podaj kolumne, gdzie przeniesc kulke: ";
	czyszczenieBufora();
	cin >> y1;
	y1--;
}
int Gracz::dodajPunkty(int punktyDoDodania) {			//metoda dodajaca punkty dla gracza
	komunikatODodaniuPunktow(punktyDoDodania);			//komunikat do konsoli o tym ze dodaje punkty
	punkty += punktyDoDodania;
	return punktyDoDodania;
}
int Gracz::getPunkty() const {					//geter
	return punkty;
}
char* Gracz::getNick() {			//geter
	return nick;
}
int Gracz::getX() {			//geter
	return x;
}
int Gracz::getY() {			//geter
	return y;
}
int Gracz::getX1() {		//geter
	return x1;
}
int Gracz::getY1() {		//geter
	return y1;
}
void Gracz::setX(int dana) {		//seter
	x = dana;
}
void Gracz::setY(int dana) {			//seter
	y = dana;
}
void Gracz::setX1(int dana) {				//seter
	x1 = dana;
}
void Gracz::setY1(int dana) {		//seter
	y1 = dana;
}
void Gracz::setPunkty(int dana) {		//seter
	punkty = dana;
}
void Gracz::setNick(char nickname[15]) {			//seter
	strcpy(nick, nickname);
}
void GraczCzlowiek::wypiszDaneGracza() {					//metoda wypisujaca dane gracza bedacego Czlowiekiem, dalej analogicznie...
	cout << "Nazwa gracza: " << nick << endl << "Punkty gracza: " << punkty << endl;
}
int  GraczCzlowiek::getX() {			//analogicznie..
	return x;
}
int  GraczCzlowiek::getY() {
	return y;
}
int  GraczCzlowiek::getX1() {
	return x1;
}
int  GraczCzlowiek::getY1() {
	return y1;
}
void  GraczCzlowiek::setX(int dana) {
	x = dana;
}
void  GraczCzlowiek::setY(int dana) {
	y = dana;
}
void  GraczCzlowiek::setX1(int dana) {
	x1 = dana;
}
void  GraczCzlowiek::setY1(int dana) {
	y1 = dana;
}
int GraczCzlowiek::wykonajRuch(Plansza& plansza, int *losowaneKulki) {		//metoda realizacja ruch dla gracza, potrzebuje informacji na jakiej planszy gracz sie porusza, oraz jakie kulki sa obecnie w kolejce do danego gracza
	do {
		wczytajRuch();					//pobranie ruchu gracza
		if (!plansza.czyJestDroga(x, y, x1, y1)) {			//sprawdzenie czy ruch podany przez gracza byl prawidlowy
			cout << endl << "Zle dane! Sprobuj ponownie" << endl;
		}
	} while (!plansza.czyJestDroga(x, y, x1, y1));			//do momentu az uzytkownik nie poda prawidlowych danych dla ruchu kulki
	plansza.przeniesKulke(x, y, x1, y1);				//przeniesienie kulki, bazujac na tym co chcial gracz
	if (dodajPunkty(plansza.wykonajBicie()) == 0) {			//metoda wykonajBicie() zwraca wartosc rowna tej ile kulek zostalo zbitych, metoda dodajPunkty robi to co w nazwie, a sprawdzenie czy ==0 weryfikuje co robic w przypadku gdy bicie nie nastapilo
		plansza.losujKulki(IleKulekCoKolejke, losowaneKulki);			//metoda losujaca na planszy kulki, po tym jak nic nie zostalo zbite
		dodajPunkty(plansza.wykonajBicie());		//sprawdzenie czy przypadkiem pojawienie sie nowych kulek nie spowodowalo ze czesc z nich zostala zbita
		return 0;	//zwrocenie wartosci ktora potem pozwoli na sprawdzenie czy nalezy losowac nowe kulki czy tez nie (w wypadku jesli bicie nastapilo przez losowanie - kulki sa losowane na nowo i pojawiaja sie pozostale, weryfikowalem to specjalnie na kurniku)
	}
	else {
		return 1;		//zwrocenie wartosci ktora mowi ze nie nalezy znowu losowac kulek bo bylo bicie
	}
}
void GraczKomputer::wypiszDaneGracza() {		//metoda wypisuajca dane dla komputera
	cout << "Nazwa gracza: " << nick << " (Komputer) " << endl << "Punkty gracza: " << punkty << endl;
}
int GraczKomputer::getX() {
	return x;
}
int GraczKomputer::getY() {
	return y;
}
int GraczKomputer::getX1() {
	return x1;
}
int GraczKomputer::getY1() {
	return y1;
}
void GraczKomputer::setX(int dana) {
	x = dana;
}
void GraczKomputer::setY(int dana) {
	y = dana;
}
void GraczKomputer::setX1(int dana) {
	x1 = dana;
}
void GraczKomputer::setY1(int dana) {
	y1 = dana;
}
int GraczKomputer::wykonajRuch(Plansza& plansza, int *losowaneKulki) {		//ruch dla komputera zblizony do ruchu gracza z roznicami
	do {
		x = rand() % plansza.getRozmiar();			//pole ruchu kompuetra i kulka do przeniesienia jest losowa, korzysta z rozmiaru planszy
		y = rand() % plansza.getRozmiar();
		x1 = rand() % plansza.getRozmiar();
		y1 = rand() % plansza.getRozmiar();
	} while (!plansza.czyJestDroga(x, y, x1, y1));		//ale zgodna z zasadami
	plansza.przeniesKulke(x, y, x1, y1);		
	if (dodajPunkty(plansza.wykonajBicie()) == 0) {
		plansza.losujKulki(IleKulekCoKolejke, losowaneKulki);
		dodajPunkty(plansza.wykonajBicie());
		return 0;
	}
	else {
		return 1;
	}
}