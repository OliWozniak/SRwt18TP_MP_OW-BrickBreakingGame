#ifndef KULKA_H
#define KULKA_H

#include <stdio.h>

// Definicja struktury Kulka
typedef struct {
    int polozenie_x;
    int polozenie_y;
    int promien;
    int predkosc_x;
    int predkosc_y;
    uint32_t kolor;
} Kulka;

// Deklaracje funkcji operujących na strukturze Kulka
void Kulka_init(Kulka* kulka, int x, int y, int r, int vx, int vy, uint32_t kol);
void Kulka_ruch(Kulka* kulka);
void rysuj_kulke(Kulka* kulka);
int Kulka_getPolozenieX(const Kulka* kulka);
int Kulka_getPolozenieY(const Kulka* kulka);
int Kulka_getPromien(const Kulka* kulka);

#endif // KULKA_H
