#pragma once
#include "configuracion.h"

class Mercado {
public:
    float precioHora(int hora) {
        int minimo, maximo;
        if (hora <= 6) {
            minimo = 398; maximo = 640;
        } else if (hora <= 14) {
            minimo = 456; maximo = 970;
        } else if (hora <= 17) {
            minimo = 596; maximo = 1040;
        } else if (hora <= 20) {
            minimo = 705; maximo = 1612;
        } else {
            minimo = 565; maximo = 970;
        }
        return minimo + rand() % (maximo - minimo + 1);
    }

    float consumoAgua(int hora) {
        if (hora <= 6) return 2;
        if (hora <= 14) return 5;
        if (hora <= 17) return 4;
        if (hora <= 20) return 7;
        return 4;
    }
};