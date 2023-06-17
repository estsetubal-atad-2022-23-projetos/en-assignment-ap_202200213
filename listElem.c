#include <stdio.h>

#include "listElem.h"

void listElemPrint(ListElem elem) {
	/*printf("\tID:\t%d\n",elem.id);
	printf("\tCountry:\t%s\n",elem.countryCode);
	printf("\tDate:\t%d/%d/%d\n",elem.date.day,elem.date.month,elem.date.year);
	printf("\tTime:\t%d:%d:%d\n",elem.time.hour,elem.time.min,elem.time.sec);
	printf("\tLatitude:\t%f\n",elem.latitude);
	printf("\tLongitude:\t%f\n",elem.longitude);
	printf("\tType:\t%s\n",elem.type);
	printf("\tDepth:\t%f\n",elem.depth);
    printf("\tMagnitude:\t%f\n",elem.magnitude);
	printf("\tMagnitude Type:\t%s\n",elem.magnitudeType);*/
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