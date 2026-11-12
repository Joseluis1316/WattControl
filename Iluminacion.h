// =============================================================
// Iluminacion.h: la clase Iluminacion (hereda de Equipo)
// =============================================================
#pragma once

#include "Equipo.h"

class Iluminacion : public Equipo {
public:
    // Constructor: le pasa el nombre y la potencia a Equipo
    Iluminacion(string n, float p) : Equipo(n, p) {}

    // Regla de la iluminacion: se enciende automaticamente en horario nocturno
    bool debeEncender(int hora, float precio, float nivel) override {
        return (hora >= NOCHE_INICIO || hora <= NOCHE_FIN);
    }
};