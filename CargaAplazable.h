// =============================================================
// Bomba.h: la clase Bomba (hereda de Equipo)
// =============================================================
#pragma once

#include "Equipo.h"

class Bomba : public Equipo {
public:
    // Constructor: le pasa el nombre y la potencia al constructor de Equipo
    Bomba(string n, float p) : Equipo(n, p) {}

    // Regla de la bomba (sobreescribe el metodo virtual de Equipo)
    bool debeEncender(int hora, float precio, float nivel) override {
        bool horaPico = hora >= PICO_INICIO && hora <= PICO_FIN;

        // Bombea si el tanque esta critico (< 20%) o si no es hora pico y la energia esta barata
        return nivel < NIVEL_CRITICO ||
               (!horaPico && precio < PRECIO_BARATO && nivel < NIVEL_OBJETIVO);
    }
};