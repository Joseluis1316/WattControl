#pragma once
#include "Carga.h"
#include "Medidor.h"
#include "Mercado.h"
// =============================================================
// Negocio: junta todo
// =============================================================
class Negocio {
private:
    // Nombre del negocio
    string nombre;
    // COMPOSICION: el medidor nace y muere con el negocio
    Medidor medidor;
    // AGREGACION: punteros a Carga; las cargas se crean afuera
    Carga* cargas[MAX_CARGAS];
    int numCargas;
    // ASOCIACION: el negocio conoce al mercado y le pide datos
    Mercado* mercado;

    // Resultados de la ultima simulacion (para la opcion 4)
    float costoSin;
    int horasSimuladas, fallas;
    bool emergencia, produccionIncompleta;

    // Decide que cargas se encienden en una hora (reglas 1 a 6).
    // Devuelve en excedio si hubo que aplicar la regla 6
    void decidir(int hora, float precio, float embalses, bool decision[], bool &excedio) {
        float kwEncendidos = 0;
        // Polimorfismo: la misma llamada para todas las cargas
        for (int i = 0; i < numCargas; i++) {
            decision[i] = cargas[i]->debeEncender(hora, precio, embalses);
            if (decision[i]) kwEncendidos += cargas[i]->getPotencia();
        }
        excedio = false;
        // Regla 6: si se pasa de la potencia contratada, se apaga la aplazable de mayor potencia
        if (kwEncendidos > POTENCIA_CONTRATADA) {
            int mayor = -1;
            for (int i = 0; i < numCargas; i++) {
                if (i == INDICE_CRITICA) continue;
                if (decision[i] && (mayor == -1 || cargas[i]->getPotencia() > cargas[mayor]->getPotencia())) {
                    mayor = i;
                }
            }
            if (mayor != -1) {
                decision[mayor] = false;
                excedio = true;
            }
        }
    }

public:
    Negocio(string n, Mercado* m) {
        nombre = n;
        mercado = m;
        numCargas = 0;
        costoSin = 0;
        horasSimuladas = 0;
        fallas = 0;
        emergencia = false;
        produccionIncompleta = false;
    }

    // Agrega una carga ya creada afuera (agregacion)
    void agregarCarga(Carga* c) {
        if (numCargas < MAX_CARGAS) {
            cargas[numCargas] = c;
            numCargas++;
        }
    }

    void mostrar() {
        cout << "Negocio " << nombre << " | potencia contratada " << POTENCIA_CONTRATADA << " kW" << endl;
        for (int i = 0; i < numCargas; i++) {
            cout << "  " << cargas[i]->getNombre() << " (" << cargas[i]->getPotencia() << " kW)" << endl;
        }
    }

    // Opcion 2: que haria cada carga con una lectura (hora, precio, embalses)
    void evaluar(int hora, float precio, float embalses) {
        bool decision[MAX_CARGAS];
        bool excedio;
        if (embalses < NIVEL_ALERTA_EMBALSES) {
            cout << "  ALERTA: riesgo de racionamiento, solo funciona la carga critica" << endl;
        }
        decidir(hora, precio, embalses, decision, excedio);
        for (int i = 0; i < numCargas; i++) {
            cout << "  " << setw(12) << left << cargas[i]->getNombre() << right
                 << (decision[i] ? "ENCENDER" : "APLAZAR") << endl;
        }
        if (excedio) {
            cout << "  ALERTA: se supera la potencia contratada, se apaga la aplazable de mayor potencia" << endl;
        }
    }

    // Opcion 3: simula 24 horas, con gestor y sin gestor
    void simularDia() {
        // Todo empieza de nuevo
        medidor.reiniciar();
        for (int i = 0; i < numCargas; i++) cargas[i]->reiniciar();
        costoSin = 0;
        horasSimuladas = 0;
        fallas = 0;
        emergencia = false;
        produccionIncompleta = false;

        // Potencia de todas las cargas juntas (escenario sin gestor)
        float potenciaTotal = 0;
        for (int i = 0; i < numCargas; i++) potenciaTotal += cargas[i]->getPotencia();

        cout << fixed << setprecision(0);
        cout << setw(5) << "Hora" << setw(8) << "Precio" << setw(8) << "Embal";
        for (int i = 0; i < numCargas; i++) cout << setw(13) << cargas[i]->getNombre();
        cout << setw(9) << "Costo" << endl;

        for (int h = 0; h < HORAS_DIA; h++) {
            // ASOCIACION: el negocio le pide los datos al mercado
            float precio = mercado->precioHora(h);
            float embalses = mercado->nivelEmbalses(h);

            // break: emergencia de racionamiento -> termina la simulacion
            if (precio > PRECIO_EMERGENCIA && embalses < NIVEL_ALERTA_EMBALSES) {
                cout << setw(5) << h << setw(8) << precio << setw(8) << embalses
                     << "  EMERGENCIA DE RACIONAMIENTO: se detiene la simulacion" << endl;
                emergencia = true;
                break;
            }
            horasSimuladas++;

            // Sin gestor: las tres cargas encendidas toda la hora
            costoSin += potenciaTotal * precio;

            // continue: falla la lectura del precio -> solo funciona la carga critica
            if (rand() % FALLA_CADA == 0) {
                float costoFalla = 0;
                for (int i = 0; i < numCargas; i++) {
                    if (i == INDICE_CRITICA) {
                        cargas[i]->encender();
                        costoFalla += cargas[i]->costoHora(precio);
                        medidor.acumular(cargas[i]->getPotencia(), precio);
                    } else {
                        cargas[i]->apagar();
                    }
                }
                fallas++;
                cout << setw(5) << h << setw(8) << "--" << setw(8) << embalses
                     << "  falla de lectura: solo la critica ($" << costoFalla << ")" << endl;
                continue;
            }

            // Con gestor: cada carga decide (polimorfismo) y se aplica la regla 6
            bool decision[MAX_CARGAS];
            bool excedio;
            decidir(h, precio, embalses, decision, excedio);

            float kwHora = 0;
            float costoHora = 0;
            cout << setw(5) << h << setw(8) << precio << setw(8) << embalses;
            for (int i = 0; i < numCargas; i++) {
                if (decision[i]) cargas[i]->encender();
                else cargas[i]->apagar();
                if (cargas[i]->estaEncendida()) kwHora += cargas[i]->getPotencia();
                costoHora += cargas[i]->costoHora(precio);
                cout << setw(13) << (cargas[i]->estaEncendida() ? "ON" : "off");
            }
            // El medidor acumula los kWh y el costo de la hora
            medidor.acumular(kwHora, precio);
            cout << setw(9) << costoHora;
            if (excedio) cout << "  ALERTA: supera potencia contratada";
            cout << endl;
        }

        // Horas minimas: si alguna carga no las cumplio, produccion incompleta
        for (int i = 0; i < numCargas; i++) {
            if (!cargas[i]->cumpleMinimo()) produccionIncompleta = true;
        }
        if (produccionIncompleta) cout << "ALERTA: produccion incompleta" << endl;
        cout << "Simulacion terminada. Vea el resumen con la opcion 4." << endl;
    }

    // Opcion 4: resumen y ahorro
    void resumen() {
        float costoCon = medidor.getCosto();
        cout << fixed << setprecision(0);
        cout << "Negocio " << nombre << endl;
        cout << "Horas simuladas: " << horasSimuladas << " de " << HORAS_DIA
             << " | fallas de lectura: " << fallas << endl;
        if (emergencia) cout << "Hubo emergencia de racionamiento: la simulacion se detuvo." << endl;
        for (int i = 0; i < numCargas; i++) {
            cout << "  " << setw(12) << left << cargas[i]->getNombre() << right
                 << cargas[i]->getHorasUso() << " h, "
                 << cargas[i]->getHorasUso() * cargas[i]->getPotencia() << " kWh" << endl;
        }
        cout << "Energia total: " << medidor.getKWh() << " kWh" << endl;
        cout << "Costo con gestor: $" << costoCon << endl;
        cout << "Costo sin gestor: $" << costoSin << endl;
        cout << "Ahorro:           $" << costoSin - costoCon;
        if (costoSin > 0) cout << " (" << setprecision(1) << (costoSin - costoCon) / costoSin * 100 << " %)";
        cout << endl;
        if (produccionIncompleta) cout << "ALERTA: produccion incompleta" << endl;
    }
};