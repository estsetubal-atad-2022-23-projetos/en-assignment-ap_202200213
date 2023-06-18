#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "input.h"
#include "list.h"
#include "map.h"
#include "stringWrap.h"
#include "countryLocation.h"
#include "countryStatistics.h"
#include "earthquake.h"
#include "date.h"
#include "time.h"

#define UTILS_OPERATION_OK 0
#define UTILS_PARAMETER_INVALID 1
#define UTILS_FILE_NOT_FOUND 2
#define UTILS_NO_MEMORY 3

typedef struct regionInfo {
    char name[30];
    int territoryCount;
    long totalArea;
    long totalPopulation;
    double totalLiteracy;
    long totalGDP;

} RegionInfo;

typedef RegionInfo *PtRegionInfo;

int loadCL(PtCountryLocation *ptCountryLocation, int max, int *size);

int loadST(PtMap *PtMap, int max);

int loadEA(PtList *ptListRef, int max, PtCountryLocation ptCountryLocation, int countryLocationSize);

void cmdLoadCL(PtCountryLocation *ptCountryLocation, int countryLocationMax, int *countryLocationSize);

void cmdLoadST(PtMap *ptMapCountryStatistics, int countryStatisticsMax);

void cmdLoadEA(PtList *ptListEarthquake, int earthquakeMax, PtCountryLocation ptCountryLocation, int countryLocationSize);

void cmdClear(PtList *ptListEarthquake, PtMap *ptMapCountryStatistics, PtCountryLocation *ptCountryLocation, int *countryLocationSize);

void cmdShowAll(PtList ptListEarthquake);

void cmdShowY(PtList ptListEarthquake);

void cmdShowT(PtList ptListEarthquake, PtCountryLocation ptCountryLocation, int countryLocationSize);

void cmdShowYT(PtList ptListEarthquake, PtCountryLocation ptCountryLocation, int countryLocationSize);

void cmdListT(PtList ptListEarthquake);

void cmdCount(PtList ptListEarthquake);

void cmdCountryS(PtMap ptMapCountryStatistics);

void cmdRegionAvg(PtMap ptMapCountryStatistics);

float getDistance(float x0, float y0, float x1, float y1);