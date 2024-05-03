#ifndef FUNKCJE_H
#define FUNKCJE_H
#include <iostream>
#include "gracze.h"
void czyszczenieBufora();	//funkcja czyszczaca bufor klawiatury
void Logo();				//funkcja wyswietlajaca logo KULKI
void komunikatODodaniuPunktow(int punktyDoDodania);		//funkcja wyswietlajac komunikat o dodaniu punktow wraz z ich iloscia
void podajNick(char* nick);		//funkcja pozwalajaca na podanie nicku
void zapiszDaneDoPliku(const char* nazwaPliku, const char* nick, int punkty);	//funkcja zapisujaca dane do pliku, nick oraz punkty
void tekstDoWyborow();		//funkcja wypisujaca menu gracza, gdzie moze dokonac wyboru co chce zrobic
int wybory();				//funkcja pobierajaca wybor gracza
void Werdykt(Gracz& gracz1, Gracz& gracz2);			//funkcja sprawdzajaca kto wygral
void graJednegoGracza();	//funkcja realizujaca gre jednego gracza
void graGraczvsGracz();		//funkcja realizuajca gre Gracz kontra Gracz (kazdy swoja plansza)
void graGraczvsKomputer();		//funkcja realizujaca gre Gracz kontra Komputer (kazdy swoja plansza)
void odczytywanieDanych(const char* nazwaPliku); //funkcja odczytujaca dane z pliku w tym przypadku tabeli
void Menu();		//funkcja realizujaca de facto gre, laczac wybory gracza, i ich efekt w "Menu"
#endif