#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
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

int loadCL(PtCountryLocation *ptCountryLocation, int max, int *size);

int loadST(PtMap *PtMap, int max);

int loadEA(PtList *ptList, int max);
