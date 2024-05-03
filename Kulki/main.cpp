#include <iostream>
#include <locale.h>
#include <cstdlib>
#include "plansza.h"
#include "funkcje.h"
#include "gracze.h"
int main() {
	srand(time(NULL));			//nowe ziarno losowania
	setlocale(LC_CTYPE, "Polish");			//jezyk polski w konsoli
	Logo();								//wypisanie loga gry
	Menu();					//realizacja gry
	return 0;	
}