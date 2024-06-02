#ifndef PLATFORMA_H
#define PLATFORMA_H

#include <stdio.h>
// Definicja struktury Platforma
typedef struct {
    int polozenie_x;
    int polozenie_y;
    int szerokosc;
    int wysokosc;
    int krok;
    uint32_t kolor;
} Platforma;

// Deklaracje funkcji operujących na strukturze Platforma
void Platforma_init(Platforma* platforma, int x, int y ,int w, int h, int k, uint32_t kol);
void rysuj_platforme(Platforma* platforma);
void zmaz_platforme(Platforma* platforma);
void Platforma_przesunLewo(Platforma* platforma);
void Platforma_przesunPrawo(Platforma* platforma);
void Platforma_przesunDo(Platforma* platforma, int x);
int Platforma_getPolozenieX(const Platforma* platforma);
int Platforma_getPolozenieY(const Platforma* platforma);
int Platforma_getSzerokosc(const Platforma* platforma);
int Platforma_getWysokosc(const Platforma* platforma);
int Platforma_getKrok(const Platforma* platforma);

#endif // PLATFORMA_H

