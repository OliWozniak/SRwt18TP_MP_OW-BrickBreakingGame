#ifndef KLOCEK_H
#define KLOCEK_H

class Klocek {
private:
    int pozycja_x;
    int pozycja_y;
    int szerokosc;
    int wysokosc;
    bool widoczny;

public:
    Klocek(int x, int y, int w, int h);
    void ustawPozycje(int x, int y);
    void ustawWidocznosc(bool widocznosc);
    bool czyKolizja(int x, int y, int promien);
    void rysuj();
};

#endif
