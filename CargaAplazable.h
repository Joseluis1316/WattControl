#pragma once
#include "Carga.h"
// =============================================================
// Herencia: CargaAplazable ES UNA Carga (se aplaza en pico, con energia cara
// o con embalses bajos)
// =============================================================
class CargaAplazable : public Carga {
private:
    // Horas minimas que debe funcionar al dia
    int horasMinimas;

public:
    CargaAplazable(string n, float p, int hMin) : Carga(n, p) {
        horasMinimas = hMin;
    }

    // Reglas 2 a 5 en una sola condicion compuesta:
    // se APLAZA si embalses < 40 % || es hora pico || precio > precio caro.
    // Se enciende si NO ocurre ninguna de las tres (regla 5)
    bool debeEncender(int hora, float precio, float embalses) override {
        bool horaPico = hora >= PICO_INICIO && hora <= PICO_FIN;
        return !(embalses < NIVEL_ALERTA_EMBALSES || horaPico || precio > PRECIO_CARO);
    }

    // true si ya funciono las horas minimas del dia
    bool cumpleMinimo() override {
        return horasUso >= horasMinimas;
    }
};