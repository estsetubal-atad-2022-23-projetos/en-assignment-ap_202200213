
#include <stdio.h>
#include "countryLocation.h"

int loadCL(CountryLocation *arr, int max) {
    FILE* stream = fopen("./dataset/world_country_locations.csv", "r");
    if(stream == NULL || max < 0) return -1;

    CountryLocation *ptCountryLocation = (CountryLocation*)malloc(max * sizeof(CountryLocation));

    int count = 0;
    char line[128];
    while (fgets(line, 128, stream))
    {
        if(count == max) break;

        CountryLocation countryLocation;

        char *tmp = strdup(line);
        char **tokens = splitString(tmp, 6, ";");
        free(tmp);

        strcpy(countryLocation.code,tokens[0]);
        countryLocation.latitude = atof(tokens[1]);
        countryLocation.longitude = atof(tokens[2]);
        strcpy(countryLocation.territoryName, tokens[3]);
        strcpy(countryLocation.countryName, tokens[4]);
        strcpy(countryLocation.territoryRegion, tokens[5]);     

        ptCountryLocation[count++] = countryLocation;

	    free(tokens);
    }

    fclose(stream);

    return count;
}