// main.cpp: WattControl v2 (taller de mecanizado), cada clase en su archivo
#include "CargaCritica.h"
#include "CargaAplazable.h"
#include "Mercado.h"
#include "Negocio.h"


// main: el programa empieza aqui
int main() {
    srand(SEMILLA);

    // El mercado existe por su cuenta
    Mercado mercado;
    // Las cargas se crean afuera del negocio
    CargaCritica critica(NOMBRE_CRITICA, POTENCIA_CRITICA);
    CargaAplazable aplazable1(NOMBRE_APLAZABLE_1, POTENCIA_APLAZABLE_1, HORAS_MIN_APLAZABLE_1);
    CargaAplazable aplazable2(NOMBRE_APLAZABLE_2, POTENCIA_APLAZABLE_2, HORAS_MIN_APLAZABLE_2);
    // El negocio conoce al mercado (asociacion)
    Negocio negocio(NOMBRE_NEGOCIO, &mercado);
    // Se le agregan las cargas (agregacion); la critica va primero
    negocio.agregarCarga(&critica);
    negocio.agregarCarga(&aplazable1);
    negocio.agregarCarga(&aplazable2);
    negocio.mostrar();

    // Lectura manual: valores de ejemplo
    int hora = 12;
    float precio = 500, embalses = 70;
    bool haySimulacion = false;
    int opcion;

    do {
        cout << endl << "===== WattControl v2 =====" << endl;
        cout << "1. Ingresar lectura manual (hora, precio, embalses)" << endl;
        cout << "2. Evaluar decision de cada carga" << endl;
        cout << "3. Simular un dia completo (24 h)" << endl;
        cout << "4. Ver resumen de la ultima simulacion" << endl;
        cout << "0. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            do {
                cout << "Hora (" << HORA_MIN << " a " << HORA_MAX << "): ";
                cin >> hora;
                if (hora < HORA_MIN || hora > HORA_MAX) cout << "  Hora invalida." << endl;
            } while (hora < HORA_MIN || hora > HORA_MAX);
            do {
                cout << "Precio de bolsa (COP/kWh): ";
                cin >> precio;
                if (precio <= 0) cout << "  El precio debe ser mayor que 0." << endl;
            } while (precio <= 0);
            do {
                cout << "Nivel de los embalses (" << EMBALSE_PORC_MIN << " a " << EMBALSE_PORC_MAX << " %): ";
                cin >> embalses;
                if (embalses < EMBALSE_PORC_MIN || embalses > EMBALSE_PORC_MAX) cout << "  Embalses invalidos." << endl;
            } while (embalses < EMBALSE_PORC_MIN || embalses > EMBALSE_PORC_MAX);
            cout << "Lectura guardada." << endl;
            break;
        case 2:
            cout << "Hora " << hora << " | precio " << precio << " | embalses " << embalses << " %" << endl;
            negocio.evaluar(hora, precio, embalses);
            break;
        case 3:
            negocio.simularDia();
            haySimulacion = true;
            break;
        case 4:
            if (haySimulacion) negocio.resumen();
            else cout << "Primero simule un dia con la opcion 3." << endl;
            break;
        case 0:
            cout << "Hasta luego." << endl;
            break;
        default:
            cout << "Opcion invalida." << endl;
        }
        if (opcion != 0) {
            cout << endl << "Presione Enter para continuar...";
            cin.ignore();
            cin.get();
        }
    } while (opcion != 0);

    return 0;
}