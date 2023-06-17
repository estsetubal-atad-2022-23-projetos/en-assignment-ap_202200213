#include <stdio.h>

#include "listElem.h"

void listElemPrint(ListElem elem) {
	printf("\tID:\t%d\n",elem.id);
	printf("\tCountry:\t%s\n",elem.countryCode);
	printf("\tDate:\t%d/%d/%d\n",elem.date.day,elem.date.month,elem.date.year);
	printf("\tTime:\t%d:%d:%d\n",elem.time.hour,elem.time.min,elem.time.sec);
	printf("\tLatitude:\t%f\n",elem.latitude);
	printf("\tLongitude:\t%f\n",elem.longitude);
	printf("\tType:\t%s\n",elem.type);
	printf("\tDepth:\t%f\n",elem.depth);
    printf("\tMagnitude:\t%f\n",elem.magnitude);
	printf("\tMagnitude Type:\t%s\n",elem.magnitudeType);
}