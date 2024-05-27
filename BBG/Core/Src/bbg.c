/*
 * bbg.c
 *
 *  Created on: 26 maj 2024
 *      Author: marpo
 */

#include "BBG.h"
#include <stdlib.h>
#include <stdio.h>
#include "main.h"

void BBG_init(BBG* bbg, Platforma * platforma, Klocek ** klocki, Kulka * kulka, int lkl) {

	bbg->liczba_klockow = lkl;
	bbg->platforma = platforma;
	rysuj_platforme(bbg->platforma);

	bbg->klocki = klocki;
	for (int i = 0; i < bbg->liczba_klockow; i++) {
		    uint32_t kolor = i % 2 == 0 ? LCD_COLOR_YELLOW : LCD_COLOR_BLUE;
		    Klocek_init(bbg->klocki[i], i * bbg->klocki[i]->szerokosc, 0, bbg->klocki[i]->szerokosc, bbg->klocki[i]->wysokosc,kolor);
		    rysuj_klocek(bbg->klocki[i]);
		}
	bbg->kulka = kulka;
	rysuj_kulke(bbg->kulka);
}

// Obsługa dotyku ekranu (przykładowa implementacja)
void BBG_obsluzDotykEkranu(BBG* bbg) {
    // Przykładowa obsługa dotyku
    printf("Obsługa dotyku ekranu\n");
}

// Ruch kulki (przykładowa implementacja)
void BBG_ruchKulki(BBG* bbg) {
    // Przykładowy ruch kulki
    Kulka_ruch(bbg->kulka);
}

// Ruch platformy (przykładowa implementacja)
void BBG_ruchPlatformy(BBG* bbg, int x) {
    // Przykładowy ruch platformy
    //Platforma_ruch(&bbg->platforma, x);
}

