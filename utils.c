#include "utils.h"

int loadCL(PtCountryLocation *ptCountryLocation, int max, int *size) {
    if (max < 0) return UTILS_PARAMETER_INVALID;

    FILE* stream = fopen("./dataset/world_country_locations.csv", "r");
    if (stream == NULL) return UTILS_FILE_NOT_FOUND;

    *ptCountryLocation = (PtCountryLocation)malloc(max * sizeof(CountryLocation));
    if(ptCountryLocation == NULL) { 
        fclose(stream); 
        return UTILS_NO_MEMORY; 
    };

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

    return UTILS_OPERATION_OK;
}

int loadST(PtMap *ptMap, int max) {
    if (max < 0) return UTILS_PARAMETER_INVALID;

    FILE* stream = fopen("./dataset/world_country_statistics.csv", "r");
    if (stream == NULL) return UTILS_FILE_NOT_FOUND;

    *ptMap = mapCreate((unsigned int)max);
    if(ptMap == NULL) { 
        fclose(stream); 
        return UTILS_NO_MEMORY; 
    };

    int count = 0;
    int lineNumber = 0;
    char line[128];
    while (fgets(line, 128, stream))
    {
        if (count == max) break;
        if (lineNumber++ == 0) continue;

        char *tmp = strdup(line);
        char **tokens = splitString(tmp, 9, ";");

        CountryStatistics countryStatistics;

        strcpy(countryStatistics.code, tokens[0]);
        strcpy(countryStatistics.name, tokens[1]);
        strcpy(countryStatistics.region, tokens[2]);
        countryStatistics.population = atol(tokens[3]);
        countryStatistics.area = atol(tokens[4]);

        if(validIntegerFormat(tokens[5])) countryStatistics.gdp_capita = atol(tokens[5]);
        else countryStatistics.gdp_capita = -1;

        if(validDoubleFormat(tokens[6])) countryStatistics.literacy = atof(tokens[6]);
        else countryStatistics.literacy = -1;
        
        if(validDoubleFormat(tokens[7])) countryStatistics.birthrate = atof(tokens[7]);
        else countryStatistics.birthrate = -1;

        if(validDoubleFormat(tokens[8])) countryStatistics.deathrate = atof(tokens[8]);
        else countryStatistics.deathrate = -1;

        StringWrap mapkey = stringWrapCreate(countryStatistics.code);

        mapPut(*ptMap, mapkey, countryStatistics);

	    free(tokens);
        free(tmp);
    }
    fclose(stream);

    return UTILS_OPERATION_OK;
}
