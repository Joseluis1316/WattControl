// =============================================================
// main.cpp: Orquestador de la simulacion WattControl
// =============================================================
#include <iostream>
#include <vector>
#include <iomanip>
#include "configuracion.h"
#include "Tanque.h"
#include "Mercado.h"
#include "Equipo.h"
#include "Bomba.h"
#include "Iluminacion.h"

using namespace std;

int main() {
    srand(SEMILLA);
    Tanque tanque(NIVEL_INICIAL);
    Mercado mercado;

    vector<Equipo*> equipos;
    equipos.push_back(new Bomba("Bomba de Agua", POTENCIA_BOMBA));
    equipos.push_back(new Iluminacion("Iluminacion Edificio", POTENCIA_LUCES));

    cout << "===================================================\n";
    cout << "         INICIANDO SIMULACION WATTCONTROL          \n";
    cout << "===================================================\n\n";

    float costoTotal = 0;

    for (int hora = 0; hora < HORAS_DIA; hora++) {
        float precio = mercado.precioHora(hora);
        float consumoAguaHora = mercado.consumoAgua(hora);

        tanque.consumir(consumoAguaHora);

        cout << "[Hora " << setw(2) << setfill('0') << hora << ":00] ";
        cout << "Precio: $" << fixed << setprecision(1) << precio << " | ";
        cout << "Tanque: " << tanque.getNivel() << "% | ";

        for (size_t i = 0; i < equipos.size(); i++) {
            Equipo* eq = equipos[i];
            if (eq->debeEncender(hora, precio, tanque.getNivel())) {
                eq->encender();
                if (eq->getNombre() == "Bomba de Agua") {
                    tanque.llenar(SUBIDA_HORA);
                }
            } else {
                eq->apagar();
            }

            float costo = eq->costoHora(precio);
            costoTotal += costo;
            cout << eq->getNombre() << (eq->estaEncendido() ? " [ON]" : " [OFF]") << " ";
        }
        cout << "\n";
    }

    cout << "\n===================================================\n";
    cout << "FIN DE LA SIMULACION. Costo Total: $" << costoTotal << "\n";
    cout << "===================================================\n";

    // Liberar memoria dinamica
    for (size_t i = 0; i < equipos.size(); i++) {
        delete equipos[i];
    }

    return 0;
}