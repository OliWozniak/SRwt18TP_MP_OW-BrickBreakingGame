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
//sizeof(Klocek) = 24 -> 12 Bajtów
typedef struct {
	uint8_t pozycja_x;
    uint8_t pozycja_y;
    uint8_t szerokosc;
    uint8_t wysokosc;
    uint32_t kolor;
    uint8_t is_there; // Jak jest 1 to jest obecny na planszy, jak 0 to nie istnieje
    uint8_t is_breakable; // Jak jest 1 to jest zwykły klocek, jak 0 to ściana
} Klocek;

// Deklaracje funkcji operujących na strukturze Klocek
void Klocek_init(Klocek* k, int x, int y, int w, int h, uint32_t kol, uint8_t brk, uint8_t thr);
void rysuj_klocek(Klocek* k);
void Klocek_ustawPozycje(Klocek* k, int x, int y);
bool Klocek_czyKolizja(const Klocek* k, int x, int y, int promien);

#endif /* INC_KLOCEK_H_ */
