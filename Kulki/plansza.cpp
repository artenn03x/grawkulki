#include "plansza.h"
#include "kolorki.h"
#define ILEKOLOROW 7					//ile kolorow kulek wystepuje
#define IleKulekCoKolejke 3				//ile kulek ma sie pojawiac co kolejke
#define RESET   "\033[0m"				//sekwencje ucieczki ASCII
#define JASNONIEBIESKI  "\033[94m"
#define CZERWONY     "\033[31m"
#define ROZOWY	"\033[95m"
#define NIEBIESKI    "\033[34m"
#define ZIELONY   "\033[32m"
#define ZOLTY	 "\033[33m"
#define BIALY   "\033[37m"
using namespace std;
Plansza::Plansza(int rozmiar) : rozmiar(rozmiar) {	//konstruktor ustalajacy pola planszy na '-' czyli w znaczeniu gry na puste
	memset(plansza, '-', sizeof(plansza));
}
void Plansza::rysuj() {
	cout << "    ";	//4 spacje odstepu na poczatku (pod tym bedzie numeracja wierszy)
	for (int k = 0; k < rozmiar; k++) { // numerowanie kolumn
		cout << k + 1 << "   ";			//co trzy spacje cyfra 
	}
	cout << endl;
	cout << "  ";
	for (int k = 0; k < rozmiar; k++) {		//kreski oddzielajace pierwszy wiersz
		cout << "----";
	}
	cout << "-" << endl;
	for (int i = 0; i < rozmiar; i++) {				//realizacja kolejnych wierszy (numerowanie)		
		cout << i + 1 << " |";
		for (int j = 0; j < rozmiar; j++) {
			cout << " ";
			Kolorki(plansza, i, j);			//wypisanie zawartosci pola z planszy, razem z kolorem korzystajac z funkcji Kolorki
			cout << " |";
		}

		cout << endl;

		cout << "  ";
		for (int k = 0; k < rozmiar; k++) {	//kolejne kreski oddzielajace od siebie wiersze
			cout << "----";
		}
		cout << "-" << endl;
	}
}
int Plansza::czyKoniecGry() {			//metoda pozwalajaca na sprawdzenie czy gra sie skonczyla
	for (int i = 0; i < rozmiar; i++) {
		for (int j = 0; j < rozmiar; j++) {
			if (plansza[i][j] == '-') {		//jesli jest chociaz jedno pole puste
				return 0;					//zwroc ze gra sie nie skonczyla (0)
			}
		}
	}
	return 1;			//zwroc ze gra sie skonczyla (1)
}
int Plansza::czyJestDroga(int x, int y, int newX, int newY) {			//metoda sprawdzajaca czy istnieje droga z punktu x,y do newX, newY (algorytm DFS - Depth-First Search) 
	if (plansza[x][y] == '-' || plansza[newX][newY] != '-' || x > rozmiar || x < 0 || y > rozmiar || y < 0 || x == newX && y == newY) { //sprawdzenie podstawowej poprawnosci danych, w ktorych przemieszczenie nie ma sensu
		return 0;
	}
	int sprawdzone[MAX_ROZMIAR_PLANSZY][MAX_ROZMIAR_PLANSZY];		//tablica o rozmiarze takim jak plansza
	memset(sprawdzone, 0, sizeof(sprawdzone));						//wszystkie wartosci ustalone na 0 jako "niesprawdzone"
	int dx[] = { -1, 1, 0, 0 };										//sprawdzenie kierunkow przestawienia poziomego na planszy tzn. w lewo w prawo lub w miejscu
	int dy[] = { 0, 0, -1, 1 };										//sprawdzenie kierunkow przestawienia pionowego na planszy tzn. w miejscu w dol lub w gore 
	sprawdzone[x][y] = 1;											//zaczynamy z punktu [x][y] bedacego punktem kulki, oznaczamy ze zostal "sprawdzony"
	while (sprawdzone[newX][newY] == 0) {					//do momentu az punkt docelowy nie zostanie sprawdzony
		int znaleziono = 0;									//czy znaleziono droge
		for (int i = 0; i < rozmiar; i++) {						
			for (int j = 0; j < rozmiar; j++) {
				if (sprawdzone[i][j]) {									//jesli punkt ktory sprawdzam jest 1 to:
					for (int k = 0; k < 4; k++) {
						int nx = i + dx[k];								//sprawdzam cztery mozliwe kierunki
						int ny = j + dy[k];								//lewo prawo lub gora lub dol
						if (nx >= 0 && nx < rozmiar && ny >= 0 && ny < rozmiar && !sprawdzone[nx][ny] && plansza[nx][ny] == '-') {	//kontrola poprawnosci (m.in. czy dookola znajduje sie przeszkoda)
							sprawdzone[nx][ny] = 1;						//ustalam ze nowe pole zostalo sprawdzone jako potencjalny kierunek
							if (nx == newX && ny == newY) {					//sprawdzam czy moze nie dotarlem do punktu docelowego
								return 1;										
							}
							znaleziono = 1;								//czy istnieje dalsza droga		
						}
					}
				}
			}
		}
		if (!znaleziono) {							//jak nie ma dalszej drogi - przerwij
			break;
		}
	}
	return 0;						
}
void Plansza::przeniesKulke(int x, int y, int newX, int newY) {				//przeniesienie kulki
	plansza[newX][newY] = plansza[x][y];					//nowe pole staje sie kulka
	plansza[x][y] = '-';									//stare pole staje sie puste
}
int Plansza::wykonajBicie() {					//metoda realizujaca bicia
	int bicia[MAX_ROZMIAR_PLANSZY][MAX_ROZMIAR_PLANSZY];			//tablica przechowujaca dane ktore pola sa do zbicia
	memset(bicia, 0, sizeof(bicia));					//wszystkie ustalam na 0 tzn. nie sa do zbicia
	//sprawdzam poziomo
	for (int i = 0; i < rozmiar; i++) {
		int liczbaKulek = 1;
		for (int j = 1; j < rozmiar; j++) {
			if (plansza[i][j] == plansza[i][j - 1] && plansza[i][j] != '-') {		//jesli kulka rowna sie kulce poprzedniej i nie jest pusta
				liczbaKulek++;														//to rozpoczyna sie seria
				if (liczbaKulek >= BICIE) {											//jesli seria przekroczy prog bicia
					for (int k = j - BICIE + 1; k <= j; k++) {						// zaczynam od momentu rozpoczecia serii (jak seria jest dluzsza, to od momentu rozpoczecia "5")
						bicia[i][k] = 1;											//oznaczam pole jako "do zbicia"
					}
				}
			}
			else {
				liczbaKulek = 1;													//reset serii
			}
		}
	}
	//sprawdzam pionowo analogicznie tylko dla pionu
	for (int i = 0; i < rozmiar; i++) {
		int liczbaKulek = 1;
		for (int j = 1; j < rozmiar; j++) {
			if (plansza[j][i] == plansza[j - 1][i] && plansza[j][i] != '-') {
				liczbaKulek++;
				if (liczbaKulek >= BICIE) {
					for (int k = j - BICIE + 1; k <= j; k++) {
						bicia[k][i] = 1;
					}
				}
			}
			else {
				liczbaKulek = 1;
			}
		}
	}
	//sprawdzam skos "\"
	for (int i = 0; i <= rozmiar - BICIE; i++) {		//do wymaganego minimum
		for (int j = 0; j <= rozmiar - BICIE; j++) {				//do wymaganego minimum
			char znak = plansza[i][j];
			if (znak != '-') {				//jak pole nie jest puste to sprawdzam
				int liczbaKulek = 1;
				for (int k = 1; k < rozmiar - i && k < rozmiar - j; k++) { //eptla sprawdza kolejne pola po skosie
					if (plansza[i + k][j + k] == znak) { //jak kolejne pole jest rowne poprzedniemu no to analogicznie jak wczesniej
						liczbaKulek++;
						if (liczbaKulek >= BICIE)
						{
							for (int l = 0; l < liczbaKulek; l++) {
								bicia[i + l][j + l] = 1;
							}
						}
					}
					else {
						break;	//jak kolejne pole sie nie zgadza to przerwij
					}
				}
			}
		}
	}
	//sprawdzam skos "/" (podobnie jak wczesniej tylko po innym kierunku)
	for (int i = 0; i <= rozmiar - BICIE; i++)
	{
		for (int j = rozmiar - 1; j >= BICIE - 1; j--)
		{
			char znak = plansza[i][j];
			if (znak != '-')
			{
				int dlugoscSerii = 1;
				for (int k = 1; k < rozmiar - i && j - k >= 0; k++)
				{
					if (plansza[i + k][j - k] == znak)
					{
						dlugoscSerii++;
						if (dlugoscSerii >= BICIE)
						{
							for (int l = 0; l < dlugoscSerii; l++)
							{
								bicia[i + l][j - l] = 1;
							}
						}
					}
					else
					{
						break;
					}
				}
			}
		}
	}
	//sumowanie punktow za bicia bazujac na tablicy gdzie zostaly one ozanczone jako "do zbicia"
	int punkty = 0;
	for (int i = 0; i < rozmiar; i++) {
		for (int j = 0; j < rozmiar; j++) {
			if (bicia[i][j]) {
				plansza[i][j] = '-';
				punkty = punkty + 1; //za kazda zbita kulke jeden punkt
			}
		}
	}
	return punkty;
}
int* Plansza::generujKulki(int ileKulek){		//generowanie kulek do kolejki
	cout << endl<<"Kulki jakie sie pojawia: ";
	int i = 0;
	int *kulki=new int[IleKulekCoKolejke];	//pamiec dla kolejki kulek (ilosc pamieci to ilosc kulek ktora sie pojawia co kolejke)
	while (i < ileKulek) {		//do momentu az nie wyswietli kazdej z kulek
		int losowyKolory = rand() % ILEKOLOROW;	//losowanie koloru w zaleznosci od liczby 0-jasnoniebieska, 1-czerwona itd.
		switch (losowyKolory) {
		case 0:
			kulki[i] = 0;
			cout << JASNONIEBIESKI<< "Jasnoniebieska "<<RESET;	//komunikat dla uzytkownika co go czeka
			break;
		case 1:
			kulki[i] = 1;
			cout << CZERWONY<<"Czerwona "<<RESET;
			break;
		case 2:
			kulki[i] = 2;
			cout << ROZOWY<<"Rozowa "<<RESET;
			break;
		case 3:
			kulki[i] = 3;
			cout << NIEBIESKI<<"Niebieska "<<RESET;
			break;
		case 4:
			kulki[i] = 4;
			cout <<ZIELONY<< "Zielona "<<RESET;
			break;
		case 5:
			kulki[i] = 5;
			cout << ZOLTY<<"Zolta "<<RESET;
			break;
		case 6:
			kulki[i] = 6;
			cout << BIALY<<"Biala "<<RESET;
			break;
		}
		i++;
	}
	cout << endl<<endl;
	return kulki;			//zwroc tablice tych kulek
}
void Plansza::losujKulki(int ileKulek, int *kulki) {	//losowanie kulek na plansze, korzystajac z ilosci tych kulek, i kolejki kulek(tablica)
	int i = 0;
	while (i < ileKulek) {
		if (czyKoniecGry()) break;	//jesli pojawienie sie kulki spowodowalo zakonzcenie gry to skoncz 
		int x = rand() % rozmiar;		//losowanie nowego polozenia dla kulki
		int y = rand() % rozmiar;		//losowanie nowego polozenia dla kulki
		if (plansza[x][y] == '-') {			//sprawdzenie czy nowe losowe pole nie jest zajete
			switch (kulki[i]) {			//w zaleznosci od tego co jest teraz w kolejce
			case 0:
				plansza[x][y] = 'J';	//przypisanie wartosci do pola na planszy 
				break;
			case 1:
				plansza[x][y] = 'C';	//itd...
				break;
			case 2:
				plansza[x][y] = 'R';
				break;
			case 3:
				plansza[x][y] = 'N';
				break;
			case 4:
				plansza[x][y] = 'Z';
				break;
			case 5:
				plansza[x][y] = '¯';
				break;
			case 6:
				plansza[x][y] = 'B';
				break;
			}
			i++;	
		}
	}
}
void Plansza::losujKulkiNaStart(int ileKulek) {		//losowanie kulek na starcie (rozni sie tym ze nie tyczy sie go kolejka, bo gracz jej nie zna przed rozpoczeciem gry)
	int i = 0;			//wszystko analogicznie jak w przypadku losowania kulek z kolejka z roznica....
	while (i < ileKulek) {
		if (czyKoniecGry()) break;			
		int x = rand() % rozmiar;
		int y = rand() % rozmiar;
		if (plansza[x][y] == '-') {
			int losowyKolory = rand() % ILEKOLOROW;			//... ze tutaj od razu losujemy i wstawiamy bez kolejki
			switch (losowyKolory) {
			case 0:
				plansza[x][y] = 'J';
				break;
			case 1:
				plansza[x][y] = 'C';
				break;
			case 2:
				plansza[x][y] = 'R';
				break;
			case 3:
				plansza[x][y] = 'N';
				break;
			case 4:
				plansza[x][y] = 'Z';
				break;
			case 5:
				plansza[x][y] = '¯';
				break;
			case 6:
				plansza[x][y] = 'B';
				break;
			}
			i++;
		}
	}
}