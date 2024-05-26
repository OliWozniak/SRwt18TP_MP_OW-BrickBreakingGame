/*
 * platforma.c
 *
 *  Created on: 26 maj 2024
 *      Author: marpo
 */

#include "Platforma.h"

// Inicjalizacja struktury Platforma
void Platforma_init(Platforma* platforma) {
    platforma->polozenie_x = 0;
    platforma->polozenie_y = 0;
    platforma->szerokosc = 0;
    platforma->wysokosc = 0;
    platforma->krok = 0;
}

// Przesunięcie platformy w lewo
void Platforma_przesunLewo(Platforma* platforma) {
    platforma->polozenie_x -= platforma->krok;
}

// Przesunięcie platformy w prawo
void Platforma_przesunPrawo(Platforma* platforma) {
    platforma->polozenie_x += platforma->krok;
}

// Pobranie położenia X platformy
int Platforma_getPolozenieX(const Platforma* platforma) {
    return platforma->polozenie_x;
}

// Pobranie położenia Y platformy
int Platforma_getPolozenieY(const Platforma* platforma) {
    return platforma->polozenie_y;
}

// Pobranie szerokości platformy
int Platforma_getSzerokosc(const Platforma* platforma) {
    return platforma->szerokosc;
}

// Pobranie wysokości platformy
int Platforma_getWysokosc(const Platforma* platforma) {
    return platforma->wysokosc;
}

