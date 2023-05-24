#include <stdio.h>
#include "earthquake.h"

typedef struct date {
int day, month, year;
} Date;

typedef struct time {
int hour, min, sec;
} Time;

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
} CountryStatistcs;

typedef struct countryLocation {
char code[3]; // Igual a countryStatistics se país mas diferente se for dependente
float latitude;
float longitude;
char territoryName[45]; // Nome do território
char countryName[45]; // Nome do país associado se território dependente, se não N.A.
char territoryRegion[30]; // Nome da região se for território dependente, se não N.A
// Existem duas novas regiões INDIAN OCEAN e SOUTH ATLANTIC
} CountryLocation;

int loadCL(CountryLocation arr[], int max) {
    FILE* stream = fopen("world_country_locations.csv", "r");
    if(stream == NULL) return -1;

    int count = 0;
    char line[128];
    while (fgets(line, 128, stream))
    {
        if(count == max) break;

        char* tmp = strdup(line);
        
        /* creates tokens[3] array, with tokens read from the file line */
        char** tokens = splitString(tmp, 6, ";");
        
        char code[3] = strcpy(tokens[0]);
        float latitude = atof;




        arr[count++] = fortniteItemCreate(tokens[0], tokens[1], vbucks);

	    free(tokens);
        free(tmp);
    }

    fclose(stream);

    return count;
}
