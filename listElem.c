#include <stdio.h>

#include "listElem.h"

void listElemPrint(ListElem elem) {
    printf("%*d",5,elem.id);
    printf("       %s",elem.countryCode);
    printf("      %0*d/%0*d/%0*d", 2, elem.date.day, 2, elem.date.month, 4, elem.date.year);
    printf("  %0*d:%0*d:%0*d", 2, elem.time.hour, 2, elem.time.min, 2, elem.time.sec);
    printf("%*.3f", 11, elem.latitude);
    printf("%*.3f", 11, elem.longitude);
    printf("%*s", 20, elem.type);
    printf("%*.0f", 8, elem.depth);
    printf("%*.1f", 11, elem.magnitude);
    printf("%*s", 13, elem.magnitudeType);
}