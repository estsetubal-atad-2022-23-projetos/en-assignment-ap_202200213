/**
 * @file earthquake.h
 * @author ap_202200213
 * @brief Utilizado para declarar o struct Earthquake e respetivo ponteiro
 * @version 0.1
 * @date 2023-06-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once
#include "date.h"
#include "time.h"

/**
 * @brief Cria um struct para guardar as informações sobre os sismos
 * 
 */

typedef struct earthquake {
    int id;
    // Código de 2 letras do país ou território mais próximo (countryLocation)
    char countryCode[3]; // Calculado a partir das localizações durante importação
    Date date;
    Time time;
    float latitude;
    float longitude;
    char type[20]; // Earthquake | Explosion | Nuclear Explosion | Rock Burst
    float depth;
    float magnitude;
    char magnitudeType[3]; // MB | MD | MH | ML | MS | MW
} Earthquake;

/* Definição do ponteiro do struct anterior */
typedef Earthquake* PtEarthquake;