#pragma once
#include "configuracion.h"

class Tanque {
private:
    float nivel;
public:
    Tanque(float nivelInicial) {
        nivel = nivelInicial;
    }
    float getNivel() { return nivel; }
    void consumir(float porcentaje) {
        nivel = nivel - porcentaje;
        if (nivel < 0) nivel = 0;
    }
    void llenar(float porcentaje) {
        nivel = nivel + porcentaje;
        if (nivel > 100) nivel = 100;
    }
};