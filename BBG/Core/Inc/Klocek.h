/*
 * klocek.h
 *
 *  Created on: 26 maj 2024
 *      Author: marpo
 */

#ifndef INC_KLOCEK_H_
#define INC_KLOCEK_H_

#include <stdbool.h>
#include <stdio.h>

// Definicja struktury Klocek
typedef struct {
    int pozycja_x;
    int pozycja_y;
    int szerokosc;
    int wysokosc;
    uint32_t kolor;
} Klocek;

// Deklaracje funkcji operujących na strukturze Klocek
void Klocek_init(Klocek* k, int x, int y, int w, int h, uint32_t kol);
void rysuj_klocek(Klocek* k);
void Klocek_ustawPozycje(Klocek* k, int x, int y);
bool Klocek_czyKolizja(const Klocek* k, int x, int y, int promien);

#endif /* INC_KLOCEK_H_ */
