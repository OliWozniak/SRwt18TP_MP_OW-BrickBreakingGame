/*
 *
 * platforma.c
 *
 *  Created on: 26 maj 2024
 *      Author: marpo
 */

#include "Platforma.h"
#include "main.h"

// Inicjalizacja struktury Platforma
void Platforma_init(Platforma *platforma, int x, int y, int w, int h, int k, uint32_t kol)
{
    platforma->polozenie_x = x;
    platforma->polozenie_y = y;
    platforma->szerokosc = w;
    platforma->wysokosc = h;
    platforma->krok = k;
    platforma->kolor = kol;
    rysuj_platforme(platforma);
}

void zmaz_platforme(Platforma *platforma)
{
    BSP_LCD_SetTextColor(0xFFFF0000); // Czerwony kolor
    BSP_LCD_FillRect(platforma->polozenie_x, platforma->polozenie_y, platforma->szerokosc, platforma->wysokosc);
}

void rysuj_platforme(Platforma *platforma)
{
    BSP_LCD_SetTextColor(platforma->kolor);
    BSP_LCD_FillRect(platforma->polozenie_x, platforma->polozenie_y, platforma->szerokosc, platforma->wysokosc);
}

void Platforma_przesunDo(Platforma *platforma, int x)
{
    platforma->polozenie_x = x;
}

// Przesunięcie platformy w lewo
void Platforma_przesunLewo(Platforma *platforma)
{
    platforma->polozenie_x -= platforma->krok;
}

// Przesunięcie platformy w prawo
void Platforma_przesunPrawo(Platforma *platforma)
{
    platforma->polozenie_x += platforma->krok;
}

// Pobranie położenia X platformy
int Platforma_getPolozenieX(const Platforma *platforma)
{
    return platforma->polozenie_x;
}

// Pobranie położenia Y platformy
int Platforma_getPolozenieY(const Platforma *platforma)
{
    return platforma->polozenie_y;
}

// Pobranie szerokości platformy
int Platforma_getSzerokosc(const Platforma *platforma)
{
    return platforma->szerokosc;
}

// Pobranie wysokości platformy
int Platforma_getWysokosc(const Platforma *platforma)
{
    return platforma->wysokosc;
}

int Platforma_getKrok(const Platforma *platforma)
{
    return platforma->krok;
}
