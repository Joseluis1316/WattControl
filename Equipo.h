
// Equipo.h: la clase base abstracta Equipo

#pragma once

#include "configuracion.h"

class Equipo {
protected:
    string nombre;
    float potenciaKW;
    bool encendida;
    int horasUso;

public:
    Equipo(string n, float p) {
        nombre = n;
        potenciaKW = p;
        encendida = false;
        horasUso = 0;
    }

    virtual ~Equipo() {}

    // Polimorfismo: metodo virtual puro
    virtual bool debeEncender(int hora, float precio, float nivel) = 0;

    void encender() {
        encendida = true;
        horasUso++;
    }

    void apagar() {
        encendida = false;
    }

    float costoHora(float precio) {
        if (encendida) {
            return potenciaKW * precio;
        }
        return 0;
    }

    string getNombre() { return nombre; }
    float getPotencia() { return potenciaKW; }
    bool estaEncendido() { return encendida; }
    int getHorasUso() { return horasUso; }
};