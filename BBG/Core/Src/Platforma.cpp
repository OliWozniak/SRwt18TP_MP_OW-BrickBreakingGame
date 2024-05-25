#include "Platforma.h"

Platforma::Platforma() {}

void Platforma::przesunLewo() {
    polozenie_x -= krok;
}

void Platforma::przesunPrawo() {
    polozenie_x += krok;
}

int Platforma::getPolozenieX() {
    return polozenie_x;
}

int Platforma::getPolozenieY() {
    return polozenie_y;
}

int Platforma::getSzerokosc() {
    return szerokosc;
}

int Platforma::getWysokosc() {
    return wysokosc;
}
