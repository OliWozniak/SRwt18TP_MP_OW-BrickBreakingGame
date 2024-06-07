/*
 * klocek.c
 *
 *  Created on: 26 maj 2024
 *      Author: marpo
 */

#include "klocek.h"
#include "main.h"

// Inicjalizacja struktury Klocek
void Klocek_init(Klocek *k, int x, int y, int w, int h, uint32_t kol, uint8_t brk, uint8_t thr)
{
    k->pozycja_x = x;
    k->pozycja_y = y;
    k->szerokosc = w;
    k->wysokosc = h;
    k->kolor = kol;
    k->is_breakable = brk; // Jak 1 to da się zepuć, jak 0 to nie
    k->is_there = thr; // Jak jest 1 to jest obecny na planszy, jak 0 to nie istnieje
}

void rysuj_klocek(Klocek *k)
{
    BSP_LCD_SetTextColor(k->kolor);
    BSP_LCD_FillRect(k->pozycja_x, k->pozycja_y, k->szerokosc, k->wysokosc);
}
// Ustawienie pozycji klocka
void Klocek_ustawPozycje(Klocek *k, int x, int y)
{
    k->pozycja_x = x;
    k->pozycja_y = y;
}

// Sprawdzenie kolizji
bool Klocek_czyKolizja(const Klocek *k, int x, int y, int promien)
{
    // Proste sprawdzenie kolizji dla przykładu
    int deltaX = x - k->pozycja_x;
    int deltaY = y - k->pozycja_y;
    int dystans = deltaX * deltaX + deltaY * deltaY;
    int promienSum = promien + k->szerokosc / 2; // Zakładamy, że szerokość to średnica klocka
    return dystans <= (promienSum * promienSum);
}
