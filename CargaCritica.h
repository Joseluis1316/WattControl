#pragma once
#include "Carga.h"
// =============================================================
// Herencia: CargaCritica ES UNA Carga (nunca se apaga)
// =============================================================
class CargaCritica : public Carga {
public:
    CargaCritica(string n, float p) : Carga(n, p) {}

    // Regla 1: la critica siempre permanece encendida
    bool debeEncender(int hora, float precio, float embalses) override {
        return true;
    }
};