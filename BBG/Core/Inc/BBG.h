#ifndef BBG_H
#define BBG_H

#include "Platforma.h"
#include "Klocek.h"
#include "Kulka.h"
#include "main.h"
#include <stdbool.h>

// Definicja struktury BBG
typedef struct {
    Platforma * platforma;
    Klocek ** klocki;
    Kulka * kulka;
    int liczba_klockow;
    int liczba_warstw;
} BBG;

// Deklaracje funkcji operujących na strukturze BBG
void BBG_init(BBG* bbg , Platforma * platforma, Klocek ** klocki, Kulka * kulka, int lkl);
void BBG_obsluzDotykEkranu(BBG* bbg, TS_StateTypeDef  TS_State);
int BBG_ruchKulki(BBG* bbg);
void BBG_ruchPlatformy(BBG* bbg, int x);
void BBG_rysuj(const BBG* bbg);
void BBG_obsluga_zbicia_klocka(BBG* bbg);
#endif // BBG_H
