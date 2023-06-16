#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"
#include "list.h"
#include "listElem.h"
#include "map.h"
#include "mapElem.h"
#include "stringWrap.h"
#include "countryLocation.h"
#include "countryStatistics.h"
#include "earthquake.h"
#include "date.h"
#include "time.h"


int loadCL(PtCountryLocation *ptCountryLocation, int max, int *size);

int loadEA(PtList *ptList, int max);

//int splitString(char *string, char delimiter, char *tokens[]);