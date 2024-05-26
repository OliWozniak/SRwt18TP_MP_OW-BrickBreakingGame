#ifndef BBG_H
#define BBG_H

#include "Platforma.h"
#include "Klocek.h"
#include "Kulka.h"
#include "main.h"
#include <stdbool.h>

// Definicja struktury BBG
typedef struct {
    Platforma platforma;
    Klocek* klocki;
    int liczbaKlockow;
    Kulka kulka;
} BBG;

// Deklaracje funkcji operujących na strukturze BBG
void BBG_init(BBG* bbg);
void BBG_deinit(BBG* bbg);
void BBG_obsluzDotykEkranu(BBG* bbg);
void BBG_ruchKulki(BBG* bbg);
void BBG_ruchPlatformy(BBG* bbg, int x);
void BBG_rysuj(const BBG* bbg);

#endif // BBG_H
