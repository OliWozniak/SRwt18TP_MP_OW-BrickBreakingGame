#include "Klocek.h"

Klocek::Klocek(int x, int y, int w, int h) : pozycja_x(x), pozycja_y(y), szerokosc(w), wysokosc(h), widoczny(true) {}

void Klocek::ustawPozycje(int x, int y) {
    pozycja_x = x;
    pozycja_y = y;
}

void Klocek::ustawWidocznosc(bool widocznosc) {
    widoczny = widocznosc;
}

bool Klocek::czyKolizja(int x, int y, int promien) {
    // Sprawdź, czy dany punkt (x, y) znajduje się wewnątrz klocka
    // Możesz zaimplementować dowolną logikę kolizji, która jest odpowiednia dla twojej aplikacji
}

void Klocek::rysuj() {
    if (widoczny) {
        // Narysuj klocek na ekranie na podstawie jego pozycji, szerokości i wysokości
        // Przykładowy kod rysowania na ekranie:
        // BSP_LCD_SetTextColor(LCD_COLOR_RED);
        // BSP_LCD_FillRect(pozycja_x, pozycja_y, szerokosc, wysokosc);
    }
}
