#pragma once
#include "configuracion.h"
// =============================================================
// Medidor: parte del Negocio (composicion)
// =============================================================
class Medidor {
private:
    // kWh acumulados y costo acumulado (COP)
    float kWhTotal;
    float costoTotal;

public:
    Medidor() {
        kWhTotal = 0;
        costoTotal = 0;
    }

    // Suma una hora de consumo: kW x 1 h = kWh; costo = kWh x precio
    void acumular(float kW, float precio) {
        kWhTotal += kW;
        costoTotal += kW * precio;
    }

    void reiniciar() {
        kWhTotal = 0;
        costoTotal = 0;
    }

    float getKWh() { return kWhTotal; }
    float getCosto() { return costoTotal; }
};