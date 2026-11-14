// configuracion.h: librerias, directivas y constantes del taller
#pragma once
// =============================================================
// WattControl v2 - Gestor de energia de un negocio (El Nino 2026)
// Negocio: TALLER DE MECANIZADO (ultimo digito 2 - 3)
// =============================================================
// --- Librerias --------------------------------------------------------------
// iostream: cout y cin
#include <iostream>
// iomanip: setw y setprecision
#include <iomanip>
// string: el tipo string
#include <string>
// cstdlib: rand() y srand()
#include <cstdlib>

using namespace std;

// --- Directivas del preprocesador -------------------------------------------
// Horas de la simulacion: un dia
#define HORAS_DIA 24
// Cuantas cargas tiene el negocio: 1 critica + 2 aplazables
#define MAX_CARGAS 3
// Semilla de rand(): misma semilla, mismos precios
#define SEMILLA 2026

// =============================================================
// CONSTANTES DEL NEGOCIO (si cambia el negocio, solo se cambia este bloque)
// Valores de la tabla de la seccion 3 del proyecto de aula (taller de mecanizado)
// =============================================================
const string NOMBRE_NEGOCIO = "Taller de mecanizado";
// Nombres de las cargas
const string NOMBRE_CRITICA = "Iluminacion";
const string NOMBRE_APLAZABLE_1 = "Torno CNC";
const string NOMBRE_APLAZABLE_2 = "Compresor";
// kW de cada carga
const float POTENCIA_CRITICA = 1.5;
const float POTENCIA_APLAZABLE_1 = 7.5;
const float POTENCIA_APLAZABLE_2 = 3.0;
// kW: potencia contratada
const float POTENCIA_CONTRATADA = 10.0;
// COP/kWh: si el precio pasa de aqui, la energia esta cara
const float PRECIO_CARO = 750.0;
// Horas minimas de funcionamiento al dia de cada aplazable (justificar en el PDF)
const int HORAS_MIN_APLAZABLE_1 = 6;
const int HORAS_MIN_APLAZABLE_2 = 4;

// =============================================================
// CONSTANTES GENERALES (iguales para todos los negocios)
// =============================================================
// La hora pico va de 18 h a 20 h (incluidas)
const int PICO_INICIO = 18;
const int PICO_FIN = 20;
// %: por debajo de este nivel de embalses hay riesgo de racionamiento
const float NIVEL_ALERTA_EMBALSES = 40.0;
// COP/kWh: con embalses bajos, por encima de este precio hay emergencia de racionamiento
const float PRECIO_EMERGENCIA = 1500.0;
// 1 de cada 20 lecturas del precio falla
const int FALLA_CADA = 20;
// Rango (%) de los embalses que genera el Mercado al azar
const int EMBALSE_MIN = 35;
const int EMBALSE_MAX = 85;
// Posicion de la carga critica en el arreglo de cargas
const int INDICE_CRITICA = 0;
// Limites de las lecturas manuales
const int HORA_MIN = 0;
const int HORA_MAX = 23;
const float EMBALSE_PORC_MIN = 0;
const float EMBALSE_PORC_MAX = 100;
// Numero de franjas horarias del Mercado
const int NUM_FRANJAS = 5;
// Ultima hora de cada franja: madrugada, manana-mediodia, tarde, pico, noche
const int FRANJA_FIN[NUM_FRANJAS] = {6, 14, 17, 20, 23};
// Precio minimo y maximo real de cada franja (COP/kWh, Anexo B, XM 21-27 sep 2026)
const int PRECIO_MIN[NUM_FRANJAS] = {398, 456, 596, 705, 565};
const int PRECIO_MAX[NUM_FRANJAS] = {640, 970, 1040, 1612, 970};