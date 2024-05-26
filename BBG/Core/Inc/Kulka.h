#ifndef KULKA_H
#define KULKA_H

// Definicja struktury Kulka
typedef struct {
    int polozenie_x;
    int polozenie_y;
    int promien;
    int predkosc_x;
    int predkosc_y;
} Kulka;

// Deklaracje funkcji operujących na strukturze Kulka
void Kulka_init(Kulka* kulka);
void Kulka_ruch(Kulka* kulka);
int Kulka_getPolozenieX(const Kulka* kulka);
int Kulka_getPolozenieY(const Kulka* kulka);
int Kulka_getPromien(const Kulka* kulka);

#endif // KULKA_H
