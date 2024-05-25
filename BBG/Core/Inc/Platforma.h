#ifndef PLATFORMA_H
#define PLATFORMA_H

class Platforma {
private:
    int polozenie_x;
    int polozenie_y;
    int szerokosc;
    int wysokosc;
    int krok;

public:
    Platforma();
    void przesunLewo();
    void przesunPrawo();
    int getPolozenieX();
    int getPolozenieY();
    int getSzerokosc();
    int getWysokosc();
};

#endif
