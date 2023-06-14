#pragma once

/**
 * @brief 
 * 
 */
typedef struct countryLocation {
char code[3]; // Igual a countryStatistics se país mas diferente se for dependente
float latitude;
float longitude;
char territoryName[45]; // Nome do território
char countryName[45]; // Nome do país associado se território dependente, se não N.A.
char territoryRegion[30]; // Nome da região se for território dependente, se não N.A
// Existem duas novas regiões INDIAN OCEAN e SOUTH ATLANTIC
} CountryLocation;

typedef CountryLocation* PtCountryLocation;