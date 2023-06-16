#include "utils.h"

/*
int loadEA(Earthquake arr[], int max) {
    FILE* stream = fopen("./dataset/earthquakes.csv", "r");
    if(stream == NULL || max < 0) return -1;

    Earthquake *ptEarthquake = (Earthquake*)malloc(max * sizeof(Earthquake));
    
    int count = 0;
    char line[128];
    while (fgets(line, 128, stream))
    {
        if(count == max) break;

        char *tmp = strdup(line);
        char **tokens = splitString(tmp, 9, ";");
        free(tmp);

        Date *date = (Date*)malloc(sizeof(Date));
        Time *time = (Time*)malloc(sizeof(Time));

        char **dataTokens = splitString(tokens[1],3,"/");
        date->day = atoi(dataTokens[0]);
        date->month = atoi(dataTokens[1]);
        date->year = atoi(dataTokens[2]);
        free(dataTokens);

        char **timeTokens = splitString(tokens[2],3,":");
        time->hour = atoi(timeTokens[0]);
        time->min = atoi(timeTokens[1]);
        time->sec = atoi(timeTokens[2]);
        free(timeTokens);

        ptEarthquake->id = atoi(tokens[0]);
        ptEarthquake->date = date;
        ptEarthquake->time = time;
        ptEarthquake->latitude = atof(tokens[3]);
        ptEarthquake->longitude = atof(tokens[4]);
        strcpy(ptEarthquake->type, tokens[5])
        ptEarthquake->depth = atof(tokens[6]);
        ptEarthquake->magnitude = atof(tokens[7]);
        strcpy(ptEarthquake->magnitudeType, tokens[8]);


        // Código de 2 letras do país ou território mais próximo (countryLocation)
        //char countryCode[3]; // Calculado a partir das localizações durante importação



        

	    free(tokens);
        free(tmp);
    }

    fclose(stream);

    return count;
}
*/