#include "BBG.h"
#include "ltdc.h"
#include "stdio.h"
#include "ts_calibration.c"


BBG::BBG()
{

}

void BBG::obsluzDotykEkranu() {
    TS_StateTypeDef TS_State;
    BSP_TS_GetState(&TS_State);

    if (TS_State.TouchDetected) {
        // Pobierz pozycję dotknięcia ekranu
        uint32_t x = Calibration_GetX(TS_State.X);
        uint32_t y = Calibration_GetY(TS_State.Y);

        // Sprawdź, czy dotknięcie ekranu jest w obszarze platformy
        // Jeśli tak, przesuń platformę w kierunku dotknięcia
        // W przeciwnym razie ignoruj dotyk ekranu
    }
}

void BBG::ruchKulki() {
    // Sprawdź, czy piłka koliduje z platformą, klockami lub krawędziami ekranu
    // Jeśli tak, zmień jej kierunek ruchu lub zniszcz klocek
    // W przeciwnym razie, kontynuuj ruch piłki
}

void BBG::ruchPlatformy(int x) {
    // Przesuń platformę do określonej pozycji x
}

void BBG::rysuj() {
    // Narysuj platformę, klocki i piłkę na ekranie
}
