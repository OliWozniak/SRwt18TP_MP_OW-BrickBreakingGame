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
            bbg->kulka->predkosc_x *= -1;
            bbg->kulka->predkosc_y *= -1;

            // Odwróć kierunek prędkości kulki
        	if(bbg->kulka->polozenie_x >= bbg->klocki[i]->pozycja_x &&
               bbg->kulka->polozenie_x <= bbg->klocki[i]->pozycja_x + bbg->klocki[i]->szerokosc) {
                bbg->kulka->predkosc_x *= -1;

        	}
        	if(bbg->kulka->polozenie_y >= bbg->klocki[i]->pozycja_y &&
                    bbg->kulka->polozenie_y <= bbg->klocki[i]->pozycja_y + bbg->klocki[i]->wysokosc){
                bbg->kulka->predkosc_y *= -1;
        	}

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
void BBG_obsluzDotykEkranu(BBG* bbg,  TS_StateTypeDef  TS_State) {
	if (TS_State.TouchDetected) {
		int platforma_x = Platforma_getPolozenieX(bbg->platforma);
		int platforma_szerokosc = Platforma_getSzerokosc(bbg->platforma);
		int platforma_krok = Platforma_getKrok(bbg->platforma);

	          uint32_t x = Calibration_GetX(TS_State.X);
	          uint32_t y = Calibration_GetY(TS_State.Y);
	          if ((x < BSP_LCD_GetXSize() / 2 ) &( x > 0)) {
	        	  platforma_x = max(0, platforma_x - platforma_krok);  // Move left
	          } else if ((x > BSP_LCD_GetXSize() / 2) & (x <  BSP_LCD_GetXSize())) {
	        	  platforma_x = min(BSP_LCD_GetXSize() - platforma_szerokosc, platforma_x + platforma_krok);  // Move right
	          }
	          BBG_ruchPlatformy(bbg, platforma_x);
	      }
}

// Ruch kulki (przykładowa implementacja)
void BBG_ruchKulki(BBG* bbg) {
    // Przykładowy ruch kulki
    Kulka_ruch(bbg->kulka);
    rysuj_kulke(bbg->kulka);
}

// Ruch platformy (przykładowa implementacja)
void BBG_ruchPlatformy(BBG* bbg, int x) {
	zmaz_platforme(bbg->platforma);
	Platforma_przesunDo(bbg->platforma,x);
	rysuj_platforme(bbg->platforma);
}

