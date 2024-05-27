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

//void BBG_init(BBG* bbg, Platforma * platforma, Klocek ** klocki, Kulka * kulka, int lkl) {
//
////	bbg->liczba_klockow = lkl;
////	bbg->platforma = platforma;
////	rysuj_platforme(bbg->platforma);
////
////	bbg->klocki = klocki;
////	for (int i = 0; i < bbg->liczba_klockow; i++) {
////		rysuj_klocek(bbg->klocki[i]);
////	}
////
////	bbg->kulka = kulka;
////	rysuj_kulke(bbg->kulka);
//}

void BBG_init(BBG* bbg, Platforma *platforma, Klocek **klocki, Kulka *kulka, int lkl) {
    bbg->liczba_klockow = lkl;
    bbg->platforma = platforma;
    rysuj_platforme(bbg->platforma);

    bbg->klocki = klocki;
    for (int i = 0; i < bbg->liczba_klockow; i++) {
        rysuj_klocek(bbg->klocki[i]);
    }

    bbg->kulka = kulka;
    rysuj_kulke(bbg->kulka);
}




void BBG_obsluga_zbicia_klocka(BBG* bbg) {
    for (int i = 0; i < bbg->liczba_klockow; i++) {
        // Sprawdź, czy kulka zderzyła się z klockiem
        if (bbg->kulka->polozenie_y + bbg->kulka->promien >= bbg->klocki[i]->pozycja_y &&
            bbg->kulka->polozenie_y - bbg->kulka->promien <= bbg->klocki[i]->pozycja_y + bbg->klocki[i]->wysokosc &&
            bbg->kulka->polozenie_x + bbg->kulka->promien >= bbg->klocki[i]->pozycja_x &&
            bbg->kulka->polozenie_x - bbg->kulka->promien <= bbg->klocki[i]->pozycja_x + bbg->klocki[i]->szerokosc) {

            // Odwróć kierunek prędkości kulki
            bbg->kulka->predkosc_x *= -1;
            bbg->kulka->predkosc_y *= -1;

            // zamaluj miejsce zbitego klocka
            BSP_LCD_SetBackColor(LCD_COLOR_RED);
			BSP_LCD_SetTextColor(LCD_COLOR_RED);
			BSP_LCD_FillRect(bbg->klocki[i]->pozycja_x, bbg->klocki[i]->pozycja_y, bbg->klocki[i]->szerokosc, bbg->klocki[i]->wysokosc);

            // Usuń trafiony klocek z tablicy klocków
            //free(bbg->klocki[i]);

            // Przesuń pozostałe klocki w tablicy, aby zapełnić lukę po usuniętym klocku
            for (int j = i; j < bbg->liczba_klockow - 1; j++) {
                bbg->klocki[j] = bbg->klocki[j + 1];
            }

            // Zmniejsz liczbę klocków o 1
            bbg->liczba_klockow--;

            // Przerwij pętlę, gdy trafiony zostanie tylko jeden klocek
            if (bbg->liczba_klockow == 0) {
                break;
            }
        }
    }
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
    rysuj_kulke(bbg->kulka);
}

// Ruch platformy (przykładowa implementacja)
void BBG_ruchPlatformy(BBG* bbg, int x) {
    // Przykładowy ruch platformy
    //Platforma_ruch(&bbg->platforma, x);
}

