#ifndef KULKA_H
#define KULKA_H

class Kulka {
private:
    int polozenie_x;
    int polozenie_y;
    int promien;
    int predkosc_x;
    int predkosc_y;

public:
    Kulka();
    void ruch();
    int getPolozenieX();
    int getPolozenieY();
    int getPromien();
};

#endif
