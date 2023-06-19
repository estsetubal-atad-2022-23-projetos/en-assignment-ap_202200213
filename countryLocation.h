/**
 * @file countryLocation.h
 * @author ap_202200213
 * @brief Utilizado para declarar o struct CountryLocation e respetivo ponteiro
 * @version 0.1
 * @date 2023-06-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

/**
 * @brief Cria um struct para guardar as informações sobre as localizações dos países
 * 
 */
typedef struct countryLocation {
char code[3]; // Igual a countryStatistics se país mas diferente se for dependente
float latitude;
float longitude;
char territoryName[45]; // Nome do território
char countryName[45]; // Nome do país associado se território dependente, se não N.A.
char territoryRegion[30]; // Nome da região se for território dependente, se não N.A
} CountryLocation;

/* Definição do ponteiro do struct anterior */
typedef CountryLocation* PtCountryLocation;