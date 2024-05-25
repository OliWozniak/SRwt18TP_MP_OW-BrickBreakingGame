#ifndef BBG_H
#define BBG_H

#include "Platforma.h"
#include "Klocek.h"
#include "Kulka.h"
#include <vector>
#include "main.h"

class BBG {
private:
    Platforma platforma;
    std::vector<Klocek> klocki;
    Kulka kulka;

public:
    BBG();
    void obsluzDotykEkranu();
    void ruchKulki();
    void ruchPlatformy(int x);
    void rysuj();
};

#endif
