
#include "utils.h"

int loadCL(PtCountryLocation *ptCountryLocation, int max, int *size) {
    FILE* stream = fopen("./dataset/world_country_locations.csv", "r");
    if(stream == NULL || max < 0) return -1;

    *ptCountryLocation = (PtCountryLocation)malloc(max * sizeof(CountryLocation));

    int count = 0;
    int lineNumber = 0;
    char line[128];
    while (fgets(line, 128, stream))
    {
        if (count == max) break;
        if (lineNumber++ == 0) continue;

        char *tmp = strdup(line);
        char **tokens = splitString(tmp, 6, ";");

        CountryLocation countryLocation;

        strcpy(countryLocation.code, tokens[0]);
        countryLocation.latitude = atof(tokens[1]);
        countryLocation.longitude = atof(tokens[2]);
        strcpy(countryLocation.territoryName, tokens[3]);
        strcpy(countryLocation.countryName, tokens[4]);
        strcpy(countryLocation.territoryRegion, tokens[5]);

        (*ptCountryLocation)[count++] = countryLocation;

	    free(tokens);
        free(tmp);
    }
    fclose(stream);
    *size = count;

    return count;
}