/*
 * bbg.c
 *
 *  Created on: 26 maj 2024
 *      Author: marpo
 */

#include "BBG.h"
#include <stdlib.h>
#include <stdio.h>

// Inicjalizacja struktury BBG
void BBG_init(BBG* bbg) {
    // Inicjalizacja platformy
    Platforma_init(&bbg->platforma);

    // Inicjalizacja tablicy klocków
    bbg->liczbaKlockow = 10; // Przykładowa liczba klocków
    bbg->klocki = (Klocek*)malloc(bbg->liczbaKlockow * sizeof(Klocek));
    for (int i = 0; i < bbg->liczbaKlockow; i++) {
    	uint32_t kolor = i % 2 == 0 ? LCD_COLOR_YELLOW : LCD_COLOR_BLUE;
        Klocek_init(&bbg->klocki[i], i * 10, 0, 10, 5 , kolor); // Przykładowe pozycje i rozmiary
    }

    // Inicjalizacja kulki
    Kulka_init(&bbg->kulka);
}

// Dealokacja pamięci struktury BBG
void BBG_deinit(BBG* bbg) {
    free(bbg->klocki);
}

// Obsługa dotyku ekranu (przykładowa implementacja)
void BBG_obsluzDotykEkranu(BBG* bbg) {
    // Przykładowa obsługa dotyku
    printf("Obsługa dotyku ekranu\n");
}

// Ruch kulki (przykładowa implementacja)
void BBG_ruchKulki(BBG* bbg) {
    // Przykładowy ruch kulki
    Kulka_ruch(&bbg->kulka);
}

// Ruch platformy (przykładowa implementacja)
void BBG_ruchPlatformy(BBG* bbg, int x) {
    // Przykładowy ruch platformy
    Platforma_ruch(&bbg->platforma, x);
}

// Rysowanie obiektów (przykładowa implementacja)
void BBG_rysuj(const BBG* bbg) {
    // Rysowanie platformy
    Platforma_rysuj(&bbg->platforma);

    // Rysowanie klocków
    for (int i = 0; i < bbg->liczbaKlockow; i++) {
        Klocek_rysuj(&bbg->klocki[i]);
    }

    // Rysowanie kulki
    Kulka_rysuj(&bbg->kulka);
}


