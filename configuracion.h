#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>

using namespace std;

#define HORAS_DIA 24
#define MAX_EQUIPOS 5
#define SEMILLA 2026

const float POTENCIA_BOMBA = 5.5;
const float POTENCIA_LUCES = 1.2;
const float SUBIDA_HORA = 12.0;
const float NIVEL_INICIAL = 50.0;
const float NIVEL_CRITICO = 20.0;
const float NIVEL_OBJETIVO = 80.0;
const float PRECIO_BARATO = 600.0;
const float PRECIO_ESCASEZ = 1500.0;
const int PICO_INICIO = 18;
const int PICO_FIN = 20;
const int NOCHE_INICIO = 18;
const int NOCHE_FIN = 5;
const int FALLA_CADA = 20;