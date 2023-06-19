/**
 * @file utils.c
 * @author ap_202200213
 * @brief Implementação das funcionalidades do ficheiro "utils.h"
 * @version 0.1
 * @date 2023-06-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

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

void cmdLoadCL(PtCountryLocation *ptCountryLocation, int countryLocationMax, int *countryLocationSize) {
    if (*ptCountryLocation != NULL) {
        printf("Country location data already loaded. ");
        return;
    }

    int code = loadCL(ptCountryLocation, countryLocationMax, countryLocationSize);

    if(code == UTILS_OPERATION_OK) {
        printf("%d countries were read. ", *countryLocationSize);
    }
    else if(code == UTILS_FILE_NOT_FOUND) {
        printf("Country location data file not found. ");
    }
}

void cmdLoadST(PtMap *ptMapCountryStatistics, int countryStatisticsMax) {
    if (*ptMapCountryStatistics != NULL) {
        printf("Country statistics data already loaded. ");
        return;
    }

    int code = loadST(ptMapCountryStatistics, countryStatisticsMax);

    if(code == UTILS_OPERATION_OK) {
        int size;
        mapSize(*ptMapCountryStatistics, &size);
        printf("%d country statistics were read. ", size);
    }
    else if(code == UTILS_FILE_NOT_FOUND) {
        printf("Country statistics data file not found. ");
    }
}

void cmdLoadEA(PtList *ptListEarthquake, int earthquakeMax, PtCountryLocation ptCountryLocation, int countryLocationSize) {
    if(*ptListEarthquake != NULL) {
        printf("Earthquake data already loaded. ");
        return;
    }

    if(ptCountryLocation == NULL) {
        printf("Country location data not loaded! ");
        return;
    }

    int code = loadEA(ptListEarthquake, earthquakeMax, ptCountryLocation, countryLocationSize);

    if(code == UTILS_OPERATION_OK) {
        int size;
        listSize(*ptListEarthquake, &size);
        printf("%d country statistics were read. ", size);
    }
    else if(code == UTILS_FILE_NOT_FOUND) {
        printf("Earthquake data file not found. ");
    }
}

void cmdClear(PtList *ptListEarthquake, PtMap *ptMapCountryStatistics, PtCountryLocation *ptCountryLocation, int *countryLocationSize) {
    if (*ptListEarthquake != NULL) {
        int size;
        listSize(*ptListEarthquake, &size);
        printf("%d records deleted from Earthquakes. ", size);
        listDestroy(ptListEarthquake);
        *ptListEarthquake = NULL;
    }

    if (*ptMapCountryStatistics != NULL) {
        int size;
        mapSize(*ptMapCountryStatistics, &size);
        printf("%d records deleted from Country Statistics. ", size);
        mapDestroy(ptMapCountryStatistics);
        *ptMapCountryStatistics = NULL;
    }

    if (*ptCountryLocation != NULL) {
        printf("%d records deleted from Country Locations. ", *countryLocationSize);
        free(*ptCountryLocation);       
        *ptCountryLocation = NULL;
        *countryLocationSize = 0;
    }
}

void cmdShowAll(PtList ptListEarthquake) {
    if (ptListEarthquake == NULL) {
		printf("Earthquake data not loaded!");
        return;
    }

    int size;
    listSize(ptListEarthquake, &size);
    printf("%d entries loaded.", size);

    int pageCount = ceil(size/50.0f);

    int number = 0;
    char pageCommand[16];
    while (true) {
        printf("\n\nEnter 'back' to return, 'next' or press enter for next page, 'prev' for previous page or desired page number out of %d: ", pageCount);
        readString(pageCommand, 16);

        if(strcasecmp(pageCommand, "") == 0 || strcasecmp(pageCommand, "next") == 0 || strcasecmp(pageCommand, "nt") == 0) {
            if (number < 1) number = 1;
            else if (number >= pageCount) number = pageCount;
            else number++;
        }
        else if(strcasecmp(pageCommand, "previous") == 0 || strcasecmp(pageCommand, "prev") == 0 || strcasecmp(pageCommand, "pv") == 0) {
            if (number > pageCount) number = pageCount;
            else if (number <= 1) number = 1;
            else number--;
        }
        else if (validIntegerFormat(pageCommand)) number = atoi(pageCommand);
        else number = -1;

        if (strcasecmp(pageCommand, "BACK") == 0 || strcasecmp(pageCommand, "QUIT") == 0) {
            printf("\nReturning to main menu...");
            break;
        }
        else if (number < 1 || number > pageCount) {
            printf("\nInvalid number.");
        } 
        else {
            printf("\nShowing page %d out of %d:", number, pageCount);
            printf("\n======================================================= Earthquakes =======================================================");
            printf("\n  ID  Country Code     Date       Time      Latitude  Longitude         Type          Depth    Magnitude  Magnitude Type  ");
            for (int i = 50*(number-1); i < 50*(number) && i < size; i++) {
                Earthquake earthquake;
                listGet(ptListEarthquake, i, &earthquake);
                printf("\n");
                listElemPrint(earthquake);
            }
        }
    }
} 

void cmdShowY(PtList ptListEarthquake) {
    if (ptListEarthquake == NULL) {
		printf("Earthquake data not loaded!");
        return;
    }

    PtList ptFilteredList = listCreate();
    if (ptFilteredList == NULL) {
        printf("Error: No memory available! How did we get here?");
        return;
    }

    int year = 0;
    int count = 0;
    int size;
    listSize(ptListEarthquake, &size);
    while (true) {
        printf("\n\nEnter desired year or '-1' to return: ");
        readInteger(&year);

        if (year == 0 || year == -1) {
            printf("\nReturning to main menu...");
            listDestroy(&ptFilteredList);
            return;
        }

        //Filter by year
        for (int i = 0; i < size; i++) {
            Earthquake earthquake;
            listGet(ptListEarthquake, i, &earthquake);
            if (earthquake.date.year == year) 
                listAdd(ptFilteredList, count++, earthquake);
        }

        if(count != 0) break;

        printf("\nNo earthquake data available for year %d, select another year.", year);
        listClear(ptFilteredList);
        count = 0;
    }

    printf("%d earthquake entries found for year %d", count, year);

    int pageCount = ceil(count/50.0f);

    int number = 0;
    char pageCommand[16];
    while (true) {
        printf("\n\nEnter 'back' to return, 'next' or press enter for next page, 'prev' for previous page or desired page number out of %d: ", pageCount);
        readString(pageCommand, 16);

        if(strcasecmp(pageCommand, "") == 0 || strcasecmp(pageCommand, "next") == 0 || strcasecmp(pageCommand, "nt") == 0) {
            if (number < 1) number = 1;
            else if (number >= pageCount) number = pageCount;
            else number++;
        }
        else if(strcasecmp(pageCommand, "previous") == 0 || strcasecmp(pageCommand, "prev") == 0 || strcasecmp(pageCommand, "pv") == 0) {
            if (number > pageCount) number = pageCount;
            else if (number <= 1) number = 1;
            else number--;
        }
        else if (validIntegerFormat(pageCommand)) number = atoi(pageCommand);
        else number = -1;

        if (strcasecmp(pageCommand, "BACK") == 0 || strcasecmp(pageCommand, "QUIT") == 0) {
            printf("\nReturning to main menu...");
            break;
        }
        else if (number < 1 || number > pageCount) {
            printf("\nInvalid number.");
        } 
        else {
            printf("\nShowing page %d out of %d:", number, pageCount);
            printf("\n======================================================= Earthquakes =======================================================");
            printf("\n  ID  Country Code     Date       Time      Latitude  Longitude         Type          Depth    Magnitude  Magnitude Type  ");
            for (int i = 50*(number-1); i < 50*(number) && i < count; i++) {
                Earthquake earthquake;
                listGet(ptFilteredList, i, &earthquake);
                printf("\n");
                listElemPrint(earthquake);
            }
        }
    }

    listDestroy(&ptFilteredList);
}

void cmdShowT(PtList ptListEarthquake, PtCountryLocation ptCountryLocation, int countryLocationSize) {
    if (ptListEarthquake == NULL) {
		printf("Earthquake data not loaded!");
        return;
    }

    PtList ptFilteredList = listCreate();
    if (ptFilteredList == NULL) {
        printf("Error: No memory available! How did we get here?");
        return;
    }

    int count = 0;
    int size;
    listSize(ptListEarthquake, &size);
    char codeCommand[64];
    char code[3] = "";
    while (true) {
        printf("\n\nEnter desired country code or respective name or 'back' to return: ");
        readString(codeCommand, 64);
        
        if (strcasecmp(codeCommand, "QUIT") == 0 || strcasecmp(codeCommand, "BACK") == 0) {
            printf("\nReturning to main menu...");
            listDestroy(&ptFilteredList);
            return;
        }

        //Find code of country with provided name
        if(ptCountryLocation != NULL) {
            for(int i = 0; i < countryLocationSize; i++) {
                if(strcasecmp(ptCountryLocation[i].territoryName, codeCommand) == 0) {
                    strcpy(code, ptCountryLocation[i].code);
                    break;
                }
            }
        }

        //Filter by code
        for (int i = 0; i < size; i++) {
            Earthquake earthquake;
            listGet(ptListEarthquake, i, &earthquake);

            if (strcasecmp(earthquake.countryCode, codeCommand) == 0) 
                listAdd(ptFilteredList, count++, earthquake);
            else if(ptCountryLocation != NULL && strcasecmp(earthquake.countryCode, code) == 0)
                listAdd(ptFilteredList, count++, earthquake);
        }

        if(count != 0) break;

        printf("\nNo earthquake data available for country name/code %s, select another country.", codeCommand);
        listClear(ptFilteredList);
        count = 0;
        strcpy(code,"");
    }

    printf("%d earthquake entries found for country of code %s", count, code);

    int pageCount = ceil(count/50.0f);

    int number = 0;
    char pageCommand[16];
    while (true) {
        printf("\n\nEnter 'back' to return, 'next' or press enter for next page, 'prev' for previous page or desired page number out of %d: ", pageCount);
        readString(pageCommand, 16);

        if(strcasecmp(pageCommand, "") == 0 || strcasecmp(pageCommand, "next") == 0 || strcasecmp(pageCommand, "nt") == 0) {
            if (number < 1) number = 1;
            else if (number >= pageCount) number = pageCount;
            else number++;
        }
        else if(strcasecmp(pageCommand, "previous") == 0 || strcasecmp(pageCommand, "prev") == 0 || strcasecmp(pageCommand, "pv") == 0) {
            if (number > pageCount) number = pageCount;
            else if (number <= 1) number = 1;
            else number--;
        }
        else if (validIntegerFormat(pageCommand)) number = atoi(pageCommand);
        else number = -1;

        if (strcasecmp(pageCommand, "BACK") == 0 || strcasecmp(pageCommand, "QUIT") == 0) {
            printf("\nReturning to main menu...");
            break;
        }
        else if (number < 1 || number > pageCount) {
            printf("\nInvalid number.");
        } 
        else {
            printf("\nShowing page %d out of %d:", number, pageCount);
            printf("\n======================================================= Earthquakes =======================================================");
            printf("\n  ID  Country Code     Date       Time      Latitude  Longitude         Type          Depth    Magnitude  Magnitude Type  ");
            for (int i = 50*(number-1); i < 50*(number) && i < count; i++) {
                Earthquake earthquake;
                listGet(ptFilteredList, i, &earthquake);
                printf("\n");
                listElemPrint(earthquake);
            }
        }
    }

    listDestroy(&ptFilteredList);
}

void cmdShowYT(PtList ptListEarthquake, PtCountryLocation ptCountryLocation, int countryLocationSize) {
    if (ptListEarthquake == NULL) {
		printf("Earthquake data not loaded!");
        return;
    }

    PtList ptFilteredList = listCreate();
    if (ptFilteredList == NULL) {
        printf("Error: No memory available! How did we get here?");
        return;
    }

    int count = 0;
    int size;
    listSize(ptListEarthquake, &size);
    char codeCommand[64];
    char selectedCountry[64] = "";
    char code[3] = "";
    int year = 0;
    while (true) {
        printf("\n\nEnter desired country code or respective name or 'back' to return: ");
        readString(codeCommand, 64);

        if (strcasecmp(codeCommand, "QUIT") == 0 || strcasecmp(codeCommand, "BACK") == 0) {
            printf("\nReturning to main menu...");
            listDestroy(&ptFilteredList);
            return;
        }
        strcpy(selectedCountry, codeCommand);

        printf("\n\nEnter desired year or '-1' to return: ");
        readInteger(&year);

        if (year == 0 || year == -1) {
            printf("\nReturning to main menu...");
            listDestroy(&ptFilteredList);
            return;
        }

        //Find code of country with provided name
        if(ptCountryLocation != NULL) {
            for(int i = 0; i < countryLocationSize; i++) {
                if(strcasecmp(ptCountryLocation[i].territoryName, codeCommand) == 0) {
                    strcpy(code, ptCountryLocation[i].code);
                    break;
                }
            }
        }

        //Filter by code
        for (int i = 0; i < size; i++) {
            Earthquake earthquake;
            listGet(ptListEarthquake, i, &earthquake);

            if(earthquake.date.year != year) continue;

            if (strcasecmp(earthquake.countryCode, codeCommand) == 0) 
                listAdd(ptFilteredList, count++, earthquake);
            else if(ptCountryLocation != NULL && strcasecmp(earthquake.countryCode, code) == 0)
                listAdd(ptFilteredList, count++, earthquake);
        }

        if(count != 0) break;

        printf("\nNo earthquake data available for country name/code %s for provided year %d, select another country and/or year.", selectedCountry, year);
        listClear(ptFilteredList);
        count = 0;
        year = 0;
        strcpy(code,"");
        strcpy(selectedCountry, "");
    }

    printf("%d earthquake entries found for country of code %s and year %d", count, code, year);

    int pageCount = ceil(count/50.0f);

    int number = 0;
    char pageCommand[16];
    while (true) {
        printf("\n\nEnter 'back' to return, 'next' or press enter for next page, 'prev' for previous page or desired page number out of %d: ", pageCount);
        readString(pageCommand, 16);

        if(strcasecmp(pageCommand, "") == 0 || strcasecmp(pageCommand, "next") == 0 || strcasecmp(pageCommand, "nt") == 0) {
            if (number < 1) number = 1;
            else if (number >= pageCount) number = pageCount;
            else number++;
        }
        else if(strcasecmp(pageCommand, "previous") == 0 || strcasecmp(pageCommand, "prev") == 0 || strcasecmp(pageCommand, "pv") == 0) {
            if (number > pageCount) number = pageCount;
            else if (number <= 1) number = 1;
            else number--;
        }
        else if (validIntegerFormat(pageCommand)) number = atoi(pageCommand);
        else number = -1;

        if (strcasecmp(pageCommand, "BACK") == 0 || strcasecmp(pageCommand, "QUIT") == 0) {
            printf("\nReturning to main menu...");
            break;
        }
        else if (number < 1 || number > pageCount) {
            printf("\nInvalid number.");
        } 
        else {
            printf("\nShowing page %d out of %d:", number, pageCount);
            printf("\n======================================================= Earthquakes =======================================================");
            printf("\n  ID  Country Code     Date       Time      Latitude  Longitude         Type          Depth    Magnitude  Magnitude Type  ");
            for (int i = 50*(number-1); i < 50*(number) && i < count; i++) {
                Earthquake earthquake;
                listGet(ptFilteredList, i, &earthquake);
                printf("\n");
                listElemPrint(earthquake);
            }
        }
    }

    listDestroy(&ptFilteredList);
}

void cmdListT(PtList ptListEarthquake) {
    if (ptListEarthquake == NULL) {
		printf("Earthquake data not loaded!");
        return;
    }

    PtMap ptMapUniqueCountries = mapCreate();
    if (ptMapUniqueCountries == NULL) {
        printf("Error: No memory available! How did we get here?");
        return;
    }

    //Counting
    int size = 0;
    listSize(ptListEarthquake, &size);
    CountryStatistics dummyCountry;
    for (int i = 0; i < size; i++) {
        Earthquake earthquake;
        listGet(ptListEarthquake, i, &earthquake);
        StringWrap stringWrap;
        strcpy(stringWrap.text, earthquake.countryCode);
        if(!mapContains(ptMapUniqueCountries, stringWrap)) {
            mapPut(ptMapUniqueCountries,stringWrap,dummyCountry);
        }
    }

    mapSize(ptMapUniqueCountries, &size);
    MapKey *codes = mapKeys(ptMapUniqueCountries);
    printf("%d unique codes found, showing codes of countries with earthquakes:", size);
    for (int i = 0; i < size; i++) {
        printf("\n%s", codes[i].text);
    }

    free(codes);
    mapDestroy(&ptMapUniqueCountries);
}

void cmdCount(PtList ptListEarthquake) {
    if (ptListEarthquake == NULL) {
		printf("Earthquake data not loaded!");
        return;
    }

    PtList ptFilteredList = listCreate();
    if (ptFilteredList == NULL) {
        printf("Error: No memory available! How did we get here?");
        return;
    }

    int count = 0;
    int size;
    listSize(ptListEarthquake, &size);
    char codeCommand[8];
    char code[8] = "";
    double minMagnitude = 0;
    double maxMagnitude = 0;
    int countPerType[7];
    for(int i = 0; i < 7; i++) countPerType[i] = 0;

    printf("\n\nEnter desired country code or 'back' to return: ");
    readString(codeCommand, 8);

    if (strcasecmp(codeCommand, "BACK") == 0 || strcasecmp(codeCommand, "QUIT") == 0) {
        printf("\nReturning to main menu...");
        listDestroy(&ptFilteredList);
        return;
    }
    strcpy(code, codeCommand);

    printf("\n\nEnter desired minimum magnitude or '-1' to return: ");
    readDouble(&minMagnitude);

    if (minMagnitude == 0 || minMagnitude == -1) {
        printf("\nReturning to main menu...");
        listDestroy(&ptFilteredList);
        return;
    }

    printf("\n\nEnter desired maximum magnitude or '-1' to return: ");
    readDouble(&maxMagnitude);

    if (maxMagnitude == 0 || maxMagnitude == -1) {
        printf("\nReturning to main menu...");
        listDestroy(&ptFilteredList);
        return;
    }

    //Filter by code
    for (int i = 0; i < size; i++) {
        Earthquake earthquake;
        listGet(ptListEarthquake, i, &earthquake);

        if (strcasecmp(earthquake.countryCode, codeCommand) != 0) continue;
        if (earthquake.magnitude < minMagnitude || earthquake.magnitude > maxMagnitude) continue;
        listAdd(ptFilteredList, count++, earthquake);

        if(strcasecmp(earthquake.magnitudeType, "MB") == 0) countPerType[0]++;
        else if(strcasecmp(earthquake.magnitudeType, "MD") == 0) countPerType[1]++;
        else if(strcasecmp(earthquake.magnitudeType, "MH") == 0) countPerType[2]++;
        else if(strcasecmp(earthquake.magnitudeType, "ML") == 0) countPerType[3]++;
        else if(strcasecmp(earthquake.magnitudeType, "MS") == 0) countPerType[4]++;
        else if(strcasecmp(earthquake.magnitudeType, "MW") == 0) countPerType[5]++;
        else countPerType[6]++;
    }

    if(count == 0) {
        bool foundMagnitude = false;
        bool foundCountry = false;
        for (int i = 0; i < size; i++) {
            Earthquake earthquake;
            listGet(ptListEarthquake, i, &earthquake);

            if (earthquake.magnitude >= minMagnitude && earthquake.magnitude <= maxMagnitude) foundMagnitude = true; 
            if (strcasecmp(earthquake.countryCode, codeCommand) == 0) foundCountry = true;

            if(foundMagnitude && foundCountry) break;
        }

        if (!foundMagnitude) printf("Earthquake data not available for magnitudes between [%lf,%lf]", minMagnitude, maxMagnitude);
        if (!foundCountry) printf("Earthquake data not available for %s", code);
        listDestroy(&ptFilteredList);
        return;
    }

    printf("\nNumber of earthquakes within constraints: %d", count);
    printf("\nEarthquakes percentage per type:");
    printf("\n|");
    for(int i = 0; i < 7; i++) {
        if(countPerType[i] == 0) continue;
        switch (i) {
            case 0:
                printf("   MB  |");
                break;
            case 1:
                printf("   MD  |");
                break;
            case 2:
                printf("   MH  |");
                break;
            case 3:
                printf("   ML  |");
                break;
            case 4:
                printf("   MS  |");
                break;
            case 5:
                printf("   MW  |");
                break;
            case 6:
                printf(" Other |");
                break;
        }
    };

    printf("\n|");
    for(int i = 0; i < 7; i++) { 
        if(countPerType[i] == 0) continue;
        printf("%*.1lf%% |", 5, (double)countPerType[i] / count * 100);
    }

    listDestroy(&ptFilteredList);
}

void cmdCountryS(PtMap ptMapCountryStatistics) {
    if (ptMapCountryStatistics == NULL) {
		printf("Country statistics data not loaded!");
        return;
    }

    int size;
    mapSize(ptMapCountryStatistics, &size);

    if(size == 0) {
         printf("No countries to display.");
         return;
    }

    PtCountryStatistics ptCountryStatistics = (PtCountryStatistics)malloc(size*sizeof(CountryStatistics));
    if (ptCountryStatistics == NULL) {
        printf("Error: No memory available! How did we get here?");
        return;
    }

    MapKey *codes = mapKeys(ptMapCountryStatistics);
    for(int i = 0; i < size; i++) mapGet(ptMapCountryStatistics, codes[i], &ptCountryStatistics[i]);
    free(codes);

    bool sortByLiteracy = true;
    bool sortAscending = true;
    char command[16];

    printf("\n\nEnter desired criteria, 'literacy' or 'gdp' to select or 'back' to return: ");
    readString(command, 16);
    if (strcasecmp(command, "BACK") == 0 || strcasecmp(command, "QUIT") == 0) {
        printf("\nReturning to main menu...");
        free(ptCountryStatistics);
        return;
    }
    else if(strcasecmp(command, "LITERACY") == 0) sortByLiteracy = true;
    else if(strcasecmp(command, "GDP") == 0) sortByLiteracy = false;
    else printf("Invalid input, defaulting to sort by %s.", sortByLiteracy ? "literacy" : "gdp");

    printf("\n\nEnter 'back' to return or sort by ascending order <y/n>?: ");
    readString(command, 16);
    if (strcasecmp(command, "BACK") == 0 || strcasecmp(command, "QUIT") == 0) {
        printf("\nReturning to main menu...");
        free(ptCountryStatistics);
        return;
    }
    else if(strcasecmp(command, "YES") == 0 || strcasecmp(command, "Y") == 0) sortAscending = true;
    else if(strcasecmp(command, "NO") == 0 || strcasecmp(command, "N") == 0) sortAscending = false;
    else printf("Invalid input, defaulting to sort by %s order.", sortAscending ? "ascending" : "descending");

    //Sort
    for (int i = 0; i < size-1; i++) {
        for (int k = 0; k < size-1; k++) {
            if (sortByLiteracy) {
                if (ptCountryStatistics[k].literacy > ptCountryStatistics[k+1].literacy) {
                    CountryStatistics tempStats = ptCountryStatistics[k];
                    ptCountryStatistics[k] = ptCountryStatistics[k+1];
                    ptCountryStatistics[k+1] = tempStats;
                }
                else if (ptCountryStatistics[k].literacy == ptCountryStatistics[k+1].literacy) {
                    if (ptCountryStatistics[k].gdp_capita > ptCountryStatistics[k+1].gdp_capita) {
                        CountryStatistics tempStats = ptCountryStatistics[k];
                        ptCountryStatistics[k] = ptCountryStatistics[k+1];
                        ptCountryStatistics[k+1] = tempStats;
                    }
                    else if (ptCountryStatistics[k].gdp_capita == ptCountryStatistics[k+1].gdp_capita) {
                        if(strcasecmp(ptCountryStatistics[k].code,ptCountryStatistics[k+1].code) > 0) {
                            CountryStatistics tempStats = ptCountryStatistics[k];
                            ptCountryStatistics[k] = ptCountryStatistics[k+1];
                            ptCountryStatistics[k+1] = tempStats;
                        }
                    }
                }
            }
            else {
                if (ptCountryStatistics[k].gdp_capita > ptCountryStatistics[k+1].gdp_capita) {
                    CountryStatistics tempStats = ptCountryStatistics[k];
                    ptCountryStatistics[k] = ptCountryStatistics[k+1];
                    ptCountryStatistics[k+1] = tempStats;
                }
                else if (ptCountryStatistics[k].gdp_capita == ptCountryStatistics[k+1].gdp_capita) {
                    if (ptCountryStatistics[k].literacy > ptCountryStatistics[k+1].literacy) {
                        CountryStatistics tempStats = ptCountryStatistics[k];
                        ptCountryStatistics[k] = ptCountryStatistics[k+1];
                        ptCountryStatistics[k+1] = tempStats;
                    }
                    else if (ptCountryStatistics[k].literacy == ptCountryStatistics[k+1].literacy) {
                        if(strcasecmp(ptCountryStatistics[k].code,ptCountryStatistics[k+1].code) > 0) {
                            CountryStatistics tempStats = ptCountryStatistics[k];
                            ptCountryStatistics[k] = ptCountryStatistics[k+1];
                            ptCountryStatistics[k+1] = tempStats;
                        }
                    }
                }
            }
        }
    }

    printf("\nCountry statistics ordered:");
    printf("\n\nCd Name                             Region               Population Area     GDP   Lit    BRate DRate");
    if (sortAscending) {
        for (int i = 0; i < size; i++) mapValuePrint(ptCountryStatistics[i]); 
    }
    else {
        for (int i = size-1; i >= 0; i--) mapValuePrint(ptCountryStatistics[i]);
    }

    free(ptCountryStatistics);
}

void cmdRegionAvg(PtMap ptMapCountryStatistics) {
    if (ptMapCountryStatistics == NULL) {
        printf("Country statistics data not loaded!");
        return;
    }

    int size;
    mapSize(ptMapCountryStatistics, &size);

    if(size == 0) {
         printf("No countries to display.");
         return;
    }

    PtRegionInfo ptRegionInfo = (PtRegionInfo)malloc(11*sizeof(RegionInfo));
    if (ptRegionInfo == NULL) {
        printf("Error: No memory available! How did we get here?");
        return;
    }

    for(int i = 0; i < 11; i++) { 
        switch (i) {
            case 0: strcpy(ptRegionInfo[i].name, "OCEANIA"); break;
            case 1: strcpy(ptRegionInfo[i].name, "ASIA (EX. NEAR EAST)"); break;
            case 2: strcpy(ptRegionInfo[i].name, "LATIN AMER. & CARIB"); break;
            case 3: strcpy(ptRegionInfo[i].name, "WESTERN EUROPE"); break;
            case 4: strcpy(ptRegionInfo[i].name, "C.W. OF IND. STATES"); break;
            case 5: strcpy(ptRegionInfo[i].name, "NORTHERN AMERICA"); break;
            case 6: strcpy(ptRegionInfo[i].name, "EASTERN EUROPE"); break;
            case 7: strcpy(ptRegionInfo[i].name, "BALTICS"); break;
            case 8: strcpy(ptRegionInfo[i].name, "ANTARCTICA"); break;
            case 9: strcpy(ptRegionInfo[i].name, "UNKNOWN"); break;
            case 10: strcpy(ptRegionInfo[i].name, "ALL"); break;
        }
        ptRegionInfo[i].territoryCount = 0;
        ptRegionInfo[i].totalArea = 0;
        ptRegionInfo[i].totalPopulation = 0;
        ptRegionInfo[i].totalLiteracy = 0;
        ptRegionInfo[i].totalGDP = 0;
    }

    int considered = 0;
    int rejected = 0;
    MapKey *codes = mapKeys(ptMapCountryStatistics);
    for(int i = 0; i < size; i++) {
        CountryStatistics countryStatistics;
        mapGet(ptMapCountryStatistics, codes[i], &countryStatistics);

        if(countryStatistics.gdp_capita < 0 || countryStatistics.literacy < 0 || countryStatistics.birthrate < 0 || countryStatistics.deathrate < 0) {
            rejected++;
            continue;
        }
        else considered++;

        bool found = false;
        for(int i = 0; i < 9; i++) {
            if(strcasecmp(ptRegionInfo[i].name, countryStatistics.region) == 0) {
                found = true;
                ptRegionInfo[i].territoryCount++;
                ptRegionInfo[i].totalArea += countryStatistics.area;
                ptRegionInfo[i].totalPopulation += countryStatistics.population;
                ptRegionInfo[i].totalLiteracy += countryStatistics.literacy * countryStatistics.population;
                ptRegionInfo[i].totalGDP = countryStatistics.gdp_capita * countryStatistics.population;
            }
        }
        if (!found) {
            ptRegionInfo[9].territoryCount++;
            ptRegionInfo[9].totalArea += countryStatistics.area;
            ptRegionInfo[9].totalPopulation += countryStatistics.population;
            ptRegionInfo[9].totalLiteracy += countryStatistics.literacy * countryStatistics.population;
            ptRegionInfo[9].totalGDP = countryStatistics.gdp_capita * countryStatistics.population;
        }

        ptRegionInfo[10].territoryCount++;
        ptRegionInfo[10].totalArea += countryStatistics.area;
        ptRegionInfo[10].totalPopulation += countryStatistics.population;
        ptRegionInfo[10].totalLiteracy += countryStatistics.literacy * countryStatistics.population;
        ptRegionInfo[10].totalGDP = countryStatistics.gdp_capita * countryStatistics.population;
    }
    free(codes);

    char command[32];
    while (true) {
        printf("\n\nEnter desired region name, 'every' to show every regions' statistics or 'back' to return: ");
        readString(command, 32);
        if (strcasecmp(command, "QUIT") == 0 || strcasecmp(command, "BACK") == 0) {
            printf("\nReturning to main menu...");
            free(ptRegionInfo);
            return;
        }
        else if (strcasecmp(command, "") == 0 || strcasecmp(command, "EVERY") == 0) {
            printf("\n%d countries considered for that region and %d ignored by lack of data", considered, rejected);
            printf("\nRegion               Total Population     Total Area       Population Density   Avg Literacy    GDP per Capita   GDP Region  ");
            for(int i = 0; i < 11; i++) {   
                printf("\n%*s", -20, ptRegionInfo[i].name);
                    printf(" %*ld", -20, ptRegionInfo[i].totalPopulation);
                    printf(" %*ld", -16, ptRegionInfo[i].totalPopulation);
                    if(ptRegionInfo[i].totalArea != 0) printf(" %*.2lf", -20, (double)ptRegionInfo[i].totalPopulation / ptRegionInfo[i].totalArea);
                    else printf(" %*s", -20, "----------");
                    if(ptRegionInfo[i].totalPopulation != 0) printf(" %*.2lf", -15, (double)ptRegionInfo[i].totalLiteracy / ptRegionInfo[i].totalPopulation * 100.0f);
                    else printf(" %*s", -15, "----------");
                    if(ptRegionInfo[i].totalPopulation != 0) printf(" %*.2lf", -16, (double)ptRegionInfo[i].totalGDP / ptRegionInfo[i].totalPopulation);
                    else printf(" %*s", -16, "----------");
                    printf(" %*ld", -16, ptRegionInfo[i].totalGDP);
            }
        }
        else {
            bool found = false;
            printf("\n%d countries considered for that region and %d ignored by lack of data", considered, rejected);
            printf("\nRegion               Total Population     Total Area       Population Density   Avg Literacy    GDP per Capita   GDP Region  ");
            for(int i = 0; i < 11; i++) { 
                if(strcasecmp(command, ptRegionInfo[i].name) == 0) {
                    found = true; 
                    printf("\n%*s", -20, ptRegionInfo[i].name);
                    printf(" %*ld", -20, ptRegionInfo[i].totalPopulation);
                    printf(" %*ld", -16, ptRegionInfo[i].totalPopulation);
                    if(ptRegionInfo[i].totalArea != 0) printf(" %*.2lf", -20, (double)ptRegionInfo[i].totalPopulation / ptRegionInfo[i].totalArea);
                    else printf(" %*s", -20, "----------");
                    if(ptRegionInfo[i].totalPopulation != 0) printf(" %*.2lf", -15, (double)ptRegionInfo[i].totalLiteracy / ptRegionInfo[i].totalPopulation * 100.0f);
                    else printf(" %*s", -15, "----------");
                    if(ptRegionInfo[i].totalPopulation != 0) printf(" %*.2lf", -16, (double)ptRegionInfo[i].totalGDP / ptRegionInfo[i].totalPopulation);
                    else printf(" %*s", -16, "----------");
                    printf(" %*ld", -16, ptRegionInfo[i].totalGDP);
                    break;
                }
            }
            if(!found) printf("\nRegion not found.");
        }
        strcpy(command, "");
    }
    

    free(ptRegionInfo);
}

float getDistance(float x0, float y0, float x1, float y1) {
    return sqrt(pow(x0-x1,2)+pow(y0-y1,2));
}
