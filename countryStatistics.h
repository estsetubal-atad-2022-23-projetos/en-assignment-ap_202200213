/**
 * @file countryStatistics.h
 * @author ap_202200213
 * @brief Utilizado para declarar o struct CountryStatistics e respetivo ponteiro
 * @version 0.1
 * @date 2023-06-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

/**
 * @brief Cria um struct para guardar as informações sobre as estatísticas dos países
 * 
 */
typedef struct countryStatistics {
char code[3]; // Código de 2 letras que representa o país
char name[40];
char region[30]; // UN Regions + ANTARCTICA + SOUTH ATLANTIC + INDIAN OCEAN
long population;
long area;
long gdp_capita; // Produto interno bruto per capita. Contém valores N.A.
float literacy; // Percentagem de literacia. Contém valores N.A.
float birthrate; // Número de nascimentos por 1000 pessoas por ano. Contém valores N.A.
float deathrate; // Número de mortes por 1000 pessoas por ano. Contém valores N.A.
} CountryStatistics;

/* Definição do ponteiro do struct anterior */
typedef CountryStatistics* PtCountryStatistics;