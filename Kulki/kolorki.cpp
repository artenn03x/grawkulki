#include "kolorki.h"
#define RESET   "\033[0m"							//sekwencja ucieczki ASCII
#define JASNONIEBIESKI  "\033[94m"
#define CZERWONY     "\033[31m"
#define ROZOWY	"\033[95m"
#define NIEBIESKI    "\033[34m"
#define ZIELONY   "\033[32m"
#define ZOLTY	 "\033[33m"
#define BIALY   "\033[37m"
using namespace std;
void Kolorki(char plansza[MAX_ROZMIAR_PLANSZY][MAX_ROZMIAR_PLANSZY], int i, int j) {
	if (plansza[i][j] == 'J') {										//jesli jest znak J to pokoloruj go na jasnoniebieski a nastepnie zresetuj do koloru podstawowego
		cout << JASNONIEBIESKI << plansza[i][j] << RESET;
	}
	else if (plansza[i][j] == 'C') {								//analogicznie...
		cout << CZERWONY << plansza[i][j] << RESET;
	}
	else if (plansza[i][j] == 'R') {
		cout << ROZOWY << plansza[i][j] << RESET;
	}
	else if (plansza[i][j] == 'N') {
		cout << NIEBIESKI << plansza[i][j] << RESET;
	}
	else if (plansza[i][j] == 'Z') {
		cout << ZIELONY << plansza[i][j] << RESET;
	}
	else if (plansza[i][j] == '¯') {
		cout << ZOLTY << plansza[i][j] << RESET;
	}
	else if (plansza[i][j] == 'B') {
		cout << BIALY << plansza[i][j] << RESET;
	}
	else if (plansza[i][j] == '-') {
		cout << BIALY << plansza[i][j] << RESET;
	}
}