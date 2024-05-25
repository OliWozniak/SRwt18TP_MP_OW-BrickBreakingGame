#include "Kulka.h"

Kulka::Kulka(){

}

void Kulka::ruch() {
    polozenie_x += predkosc_x;
    polozenie_y += predkosc_y;
}

int Kulka::getPolozenieX() {
    return polozenie_x;
}

int Kulka::getPolozenieY() {
    return polozenie_y;
}

int Kulka::getPromien() {
    return promien;
}
