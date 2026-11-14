#pragma once
#include "configuracion.h"
// =============================================================
// Clase base abstracta Carga
// =============================================================
class Carga {
protected:
    // Nombre de la carga
    string nombre;
    // Potencia en kW
    float potenciaKW;
    // true si esta encendida en esta hora
    bool encendida;
    // Horas que ha estado encendida
    int horasUso;

public:
    Carga(string n, float p) {
        nombre = n;
        potenciaKW = p;
        encendida = false;
        horasUso = 0;
    }

    // Destructor virtual: obligatorio en una clase base con metodos virtuales
    virtual ~Carga() {}

    // Polimorfismo: metodo virtual puro; cada hija aplica su propia regla.
    // Esto hace que Carga sea ABSTRACTA
    virtual bool debeEncender(int hora, float precio, float embalses) = 0;

    // Por defecto una carga cumple su minimo; la aplazable lo reemplaza
    virtual bool cumpleMinimo() { return true; }

    void encender() {
        encendida = true;
        horasUso++;
    }

    void apagar() { encendida = false; }

    // Deja la carga como nueva (para repetir la simulacion)
    void reiniciar() {
        encendida = false;
        horasUso = 0;
    }

    // Costo de esta hora: kW x precio si esta encendida, 0 si no
    float costoHora(float precio) {
        if (encendida) return potenciaKW * precio;
        return 0;
    }

    string getNombre() { return nombre; }
    float getPotencia() { return potenciaKW; }
    bool estaEncendida() { return encendida; }
    int getHorasUso() { return horasUso; }
};