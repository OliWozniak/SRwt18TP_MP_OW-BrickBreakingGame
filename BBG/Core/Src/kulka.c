/*
 * kulka.c
 *
 *  Created on: 26 maj 2024
 *      Author: marpo
 */


#include "Kulka.h"

// Inicjalizacja struktury Kulka
void Kulka_init(Kulka* kulka) {
    kulka->polozenie_x = 0;
    kulka->polozenie_y = 0;
    kulka->promien = 0;
    kulka->predkosc_x = 0;
    kulka->predkosc_y = 0;
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
