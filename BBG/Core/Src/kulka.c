/*
 * kulka.c
 *
 *  Created on: 26 maj 2024
 *      Author: marpo
 */


#include "Kulka.h"
#include "main.h"

// Inicjalizacja struktury Kulka
void Kulka_init(Kulka* kulka, int x, int y, int r, int vx, int vy, uint32_t kol) {
    kulka->polozenie_x = x;
    kulka->polozenie_y = y;
    kulka->promien = r;
    kulka->predkosc_x = vx;
    kulka->predkosc_y = vy;
    kulka->kolor = kol;
}

void rysuj_kulke(Kulka* kulka){
	BSP_LCD_SetTextColor(kulka->kolor);
	BSP_LCD_FillCircle(kulka->polozenie_x, kulka->polozenie_y, kulka->promien);
}
// Ruch kulki
void Kulka_ruch(Kulka* kulka) {
    kulka->polozenie_x += kulka->predkosc_x;
    kulka->polozenie_y += kulka->predkosc_y;
}

// Pobranie położenia X kulki
int Kulka_getPolozenieX(const Kulka* kulka) {
    return kulka->polozenie_x;
}

// Pobranie położenia Y kulki
int Kulka_getPolozenieY(const Kulka* kulka) {
    return kulka->polozenie_y;
}

// Pobranie promienia kulki
int Kulka_getPromien(const Kulka* kulka) {
    return kulka->promien;
}
