/*
 * kulka.c
 *
 *  Created on: 26 maj 2024
 *      Author: marpo
 */
#include "Kulka.h"
#include "main.h"

// Inicjalizacja struktury Kulka
void Kulka_init(Kulka* kulka, int x, int y, int r, int vx, int vy, uint32_t kol) {
    kulka->polozenie_x = x;
    kulka->polozenie_y = y;
    kulka->promien = r;
    kulka->predkosc_x = vx;
    kulka->predkosc_y = vy;
    kulka->kolor = kol;
}

void rysuj_kulke(Kulka* kulka){
	BSP_LCD_SetTextColor(kulka->kolor);
	BSP_LCD_FillCircle(kulka->polozenie_x, kulka->polozenie_y, kulka->promien);
}
void Kulka_ruch(Kulka* kulka) {
	// Zamaluj stary stan kulki
	BSP_LCD_SetTextColor(0xFFFF0000); // Czerwony kolor
	BSP_LCD_FillCircle(kulka->polozenie_x, kulka->polozenie_y, kulka->promien);

	// Oblicz nowe położenie kulki
	int nowe_polozenie_x = kulka->polozenie_x + kulka->predkosc_x;
	int nowe_polozenie_y = kulka->polozenie_y + kulka->predkosc_y;

	// Sprawdź zderzenie z lewą i prawą krawędzią ekranu
	if (nowe_polozenie_x - kulka->promien < 0 || nowe_polozenie_x + kulka->promien > BSP_LCD_GetXSize()) {
		// Zderzenie z lewą lub prawą krawędzią, zmień kierunek prędkości poziomej
		kulka->predkosc_x = -kulka->predkosc_x;
	}

	// Sprawdź zderzenie z górną i dolną krawędzią ekranu
	if (nowe_polozenie_y - kulka->promien < 0 || nowe_polozenie_y + kulka->promien > BSP_LCD_GetYSize()) {
		// Zderzenie z górną lub dolną krawędzią, zmień kierunek prędkości pionowej
		kulka->predkosc_y = -kulka->predkosc_y;
	}

	// Aktualizuj położenie kulki na nowe pozycje
	kulka->polozenie_x = nowe_polozenie_x;
	kulka->polozenie_y = nowe_polozenie_y;

	// Narysuj kulke na nowej pozycji
	BSP_LCD_SetTextColor(kulka->kolor);
	BSP_LCD_FillCircle(kulka->polozenie_x, kulka->polozenie_y, kulka->promien);
}


// Pobranie położenia X kulki
int Kulka_getPolozenieX(const Kulka* kulka) {
    return kulka->polozenie_x;
}

// Pobranie położenia Y kulki
int Kulka_getPolozenieY(const Kulka* kulka) {
    return kulka->polozenie_y;
}

// Pobranie promienia kulki
int Kulka_getPromien(const Kulka* kulka) {
    return kulka->promien;
}
