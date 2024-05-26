#ifndef PLATFORMA_H
#define PLATFORMA_H

// Definicja struktury Platforma
typedef struct {
    int polozenie_x;
    int polozenie_y;
    int szerokosc;
    int wysokosc;
    int krok;
} Platforma;

// Deklaracje funkcji operujących na strukturze Platforma
void Platforma_init(Platforma* platforma);
void Platforma_przesunLewo(Platforma* platforma);
void Platforma_przesunPrawo(Platforma* platforma);
int Platforma_getPolozenieX(const Platforma* platforma);
int Platforma_getPolozenieY(const Platforma* platforma);
int Platforma_getSzerokosc(const Platforma* platforma);
int Platforma_getWysokosc(const Platforma* platforma);

#endif // PLATFORMA_H

