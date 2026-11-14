#pragma once
#include "configuracion.h"
// =============================================================
// Mercado: da el precio de cada hora y el nivel de los embalses (asociacion)
// =============================================================
class Mercado {
public:
    // Precio al azar dentro del rango real de la franja de esa hora
    float precioHora(int hora) {
        int franja = 0;
        // Busca la franja: la primera cuya ultima hora no sea menor que la hora
        while (hora > FRANJA_FIN[franja]) franja++;
        return PRECIO_MIN[franja] + rand() % (PRECIO_MAX[franja] - PRECIO_MIN[franja] + 1);
    }

    // Nivel de los embalses (%) al azar entre EMBALSE_MIN y EMBALSE_MAX
    float nivelEmbalses(int hora) {
        return EMBALSE_MIN + rand() % (EMBALSE_MAX - EMBALSE_MIN + 1);
    }
};