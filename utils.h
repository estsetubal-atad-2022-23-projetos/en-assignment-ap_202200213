#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "earthquake.h"
#include "countryLocation.h"
#include "countryStatistics.h"
#include "input.h"
#include "list.h"
#include "listElem.h"
#include "map.h"
#include "mapElem.h"
#include "stringWrap.h"

int loadCL(PtCountryLocation ptCountryLocation, int max);

int loadEA(PtList ptList, int max);

