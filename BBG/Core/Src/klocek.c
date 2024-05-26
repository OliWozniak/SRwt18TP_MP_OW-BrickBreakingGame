/*
 * klocek.c
 *
 *  Created on: 26 maj 2024
 *      Author: marpo
 */

#include "klocek.h"
#include <stdio.h>
#include "main.h"


// Inicjalizacja struktury Klocek
void Klocek_init(Klocek* k, int x, int y, int w, int h, uint32_t kol) {
    k->pozycja_x = x;
    k->pozycja_y = y;
    k->szerokosc = w;
    k->wysokosc = h;
    k->kolor = kol;

    BSP_LCD_SetTextColor(kol);
	BSP_LCD_FillRect(k->pozycja_x, k->pozycja_y, k->szerokosc, k->wysokosc);


	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize() - 80, (uint8_t*)"X:", LEFT_MODE);
	BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize() - 80, (uint8_t*)k->pozycja_x, CENTER_MODE);


	BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize() - 112, (uint8_t*)"Y:", LEFT_MODE);
	BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize() - 112, (uint8_t*) k->pozycja_y, CENTER_MODE);
}

// Ustawienie pozycji klocka
void Klocek_ustawPozycje(Klocek* k, int x, int y) {
    k->pozycja_x = x;
    k->pozycja_y = y;
}



// Sprawdzenie kolizji
bool Klocek_czyKolizja(const Klocek* k, int x, int y, int promien) {
    // Proste sprawdzenie kolizji dla przykładu
    int deltaX = x - k->pozycja_x;
    int deltaY = y - k->pozycja_y;
    int dystans = deltaX * deltaX + deltaY * deltaY;
    int promienSum = promien + k->szerokosc / 2; // Zakładamy, że szerokość to średnica klocka
    return dystans <= (promienSum * promienSum);
}




