#pragma once

/**
 * @brief 
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

typedef CountryStatistics* PtCountryStatistcs;