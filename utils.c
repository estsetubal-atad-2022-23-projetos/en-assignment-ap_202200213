#include "utils.h"

int loadCL(PtCountryLocation *ptCountryLocationRef, int max, int *size) {
    if (max < 0) return UTILS_PARAMETER_INVALID;

    FILE* stream = fopen("./dataset/world_country_locations.csv", "r");
    if (stream == NULL) return UTILS_FILE_NOT_FOUND;

    PtCountryLocation ptCountryLocation = NULL;
    ptCountryLocation = (PtCountryLocation)malloc(max * sizeof(CountryLocation));
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

        ptCountryLocation[count++] = countryLocation;

	    free(tokens);
        free(tmp);
    }
    fclose(stream);
    *size = count;
    *ptCountryLocationRef = ptCountryLocation;

    return UTILS_OPERATION_OK;
}

int loadST(PtMap *ptMapRef, int max) {
    if (max < 0) return UTILS_PARAMETER_INVALID;

    FILE* stream = fopen("./dataset/world_country_statistics.csv", "r");
    if (stream == NULL) return UTILS_FILE_NOT_FOUND;

    PtMap ptMap = NULL;
    ptMap = mapCreate();
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

        mapPut(ptMap, mapkey, countryStatistics);

        count++;
	    free(tokens);
        free(tmp);
    }
    fclose(stream);
    *ptMapRef = ptMap;

    return UTILS_OPERATION_OK;
}

int loadEA(PtList *ptListRef, int max, PtCountryLocation ptCountryLocation, int countryLocationSize) {
    if (max < 0 || ptCountryLocation == NULL || countryLocationSize < 0) return UTILS_PARAMETER_INVALID;

    FILE* stream = fopen("./dataset/earthquakes.csv", "r");
    if (stream == NULL) return UTILS_FILE_NOT_FOUND;

    PtList ptList = NULL;
    ptList = listCreate();
    if(ptList == NULL) { 
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

        char **dateTokens = splitString(tokens[1], 4, "/");
        char **timeTokens = splitString(tokens[2], 3, ":");

        Date date;
        date.day = atoi(dateTokens[1]);
        date.month = atoi(dateTokens[0]);
        date.year = atoi(dateTokens[2]);

        Time time;
        time.hour = atoi(timeTokens[0]);
        time.min = atoi(timeTokens[1]);
        time.sec = atoi(timeTokens[2]);

        Earthquake earthquake;

        earthquake.id = atoi(tokens[0]);
        earthquake.date = date;
        earthquake.time = time;
        earthquake.latitude = atof(tokens[3]);
        earthquake.longitude = atof(tokens[4]);
        strcpy(earthquake.type, tokens[5]);
        earthquake.depth = atof(tokens[6]);
        earthquake.magnitude = atof(tokens[7]);
        strcpy(earthquake.magnitudeType, tokens[8]);
        //Calcular mais proximo

        if (countryLocationSize == 0) strcpy(earthquake.countryCode, "##");
        else {
            CountryLocation closestCountry = ptCountryLocation[0];
            int distance = getDistance(earthquake.latitude, earthquake.longitude, closestCountry.latitude, closestCountry.longitude);
            for(int i = 1; i < countryLocationSize; i++) {
                int newDistance = getDistance(earthquake.latitude, earthquake.longitude, ptCountryLocation[i].latitude, ptCountryLocation[i].longitude);
                if(newDistance < distance) {
                    closestCountry = ptCountryLocation[i];
                    distance = newDistance;
                }
            }
            strcpy(earthquake.countryCode, closestCountry.code);
        }

        int size;
        listSize(ptList, &size);
        listAdd(ptList, size, earthquake);

        count++;
        free(timeTokens);
        free(dateTokens);
	    free(tokens);
        free(tmp);
    }
    fclose(stream);
    *ptListRef = ptList;

    return UTILS_OPERATION_OK;
}

void show_y(PtList ptListEarthquake, int year) {
    int count = 0;
    int size;
    listSize(ptListEarthquake, &size);

    printf("\n======================================================= Earthquakes =======================================================");
    printf("\n  ID  Country Code     Date       Time      Latitude  Longitude         Type          Depth    Magnitude  Magnitude Type  ");

    for (int i = 0; i < size; i++) {
        Earthquake earthquake;
        listGet(ptListEarthquake, i, &earthquake);

        int earthquakeYear = earthquake.date.year; // Extrai o ano da data

        if (earthquakeYear == year) {
            count++;
            printf("\n");
            listElemPrint(earthquake);
        }
    }

    if (count == 0) {
        printf("\nEarthquake data not available for year %d.", year);
    } else {
        printf("\n\n%d earthquake(s) found for year %d.", count, year);
    }
}

void show_te(PtList ptListEarthquake, const char* countryCode) {
    int count = 0;
    int size;
    listSize(ptListEarthquake, &size);

    printf("\n======================================================= Earthquakes =======================================================");
    printf("\n  ID  Country Code     Date       Time      Latitude  Longitude         Type          Depth    Magnitude  Magnitude Type  ");

    // Converter o código de país/território para letras minúsculas para comparação sem distinção entre maiúsculas e minúsculas
    char lowercaseCode[3];
    lowercaseCode[0] = tolower(countryCode[0]);
    lowercaseCode[1] = tolower(countryCode[1]);
    lowercaseCode[2] = '\0';

    for (int i = 0; i < size; i++) {
        Earthquake earthquake;
        listGet(ptListEarthquake, i, &earthquake);

        // Converter o código de país/território do terremoto para letras minúsculas para comparação
        char lowercaseEarthquakeCode[3];
        lowercaseEarthquakeCode[0] = tolower(earthquake.countryCode[0]);
        lowercaseEarthquakeCode[1] = tolower(earthquake.countryCode[1]);
        lowercaseEarthquakeCode[2] = '\0';

        if (strcmp(lowercaseEarthquakeCode, lowercaseCode) == 0) {
            count++;
            printf("\n");
            listElemPrint(earthquake);
        }
    }

    if (count == 0) {
        printf("\nEarthquake data not available for %s.", countryCode);
    } else {
        printf("\n\n%d earthquake(s) found for %s.", count, countryCode);
    }
}

void show_yt(PtList ptListEarthquake, const char* countryCode, int year) {
    int count = 0;
    int size;
    listSize(ptListEarthquake, &size);

    printf("\n======================================================= Earthquakes =======================================================");
    printf("\n  ID  Country Code     Date       Time      Latitude  Longitude         Type          Depth    Magnitude  Magnitude Type  ");

    // Converter o código de país/território para letras minúsculas para comparação sem distinção entre maiúsculas e minúsculas
    char lowercaseCode[3];
    lowercaseCode[0] = tolower(countryCode[0]);
    lowercaseCode[1] = tolower(countryCode[1]);
    lowercaseCode[2] = '\0';

    for (int i = 0; i < size; i++) {
        Earthquake earthquake;
        listGet(ptListEarthquake, i, &earthquake);

        // Converter o código de país/território do terremoto para letras minúsculas para comparação
        char lowercaseEarthquakeCode[3];
        lowercaseEarthquakeCode[0] = tolower(earthquake.countryCode[0]);
        lowercaseEarthquakeCode[1] = tolower(earthquake.countryCode[1]);
        lowercaseEarthquakeCode[2] = '\0';

        int earthquakeYear = earthquake.date.year; // Extrair o ano da data

        if (strcmp(lowercaseEarthquakeCode, lowercaseCode) == 0 && earthquakeYear == year) {
            count++;
            printf("\n");
            listElemPrint(earthquake);
        }
    }

    if (count == 0) {
        printf("\nEarthquake data not available for country %s in year %d.", countryCode, year);
    } else {
        printf("\n\n%d earthquake(s) found for country %s in year %d.", count, countryCode, year);
    }
}

float getDistance(float x0, float y0, float x1, float y1) {
    return sqrt(pow(x0-x1,2)+pow(y0-y1,2));
}
