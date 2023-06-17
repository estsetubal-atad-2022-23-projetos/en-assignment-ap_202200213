/**
 * @file mapElem.c
 * @brief Implements operations for types MapKey and MapValue.
 * 
 * @author Bruno Silva (brunomnsilva@gmail.com)
 * @bug No known bugs.
 */

#include "mapElem.h"
#include <stdio.h>

void mapKeyPrint(MapKey key) {
	printf("%s\n", key.text);
}

void mapValuePrint(MapValue value) {
	printf("\t%s\n",value.code);
	printf("\t%s\n",value.name);
	printf("\t%s\n",value.region);
	printf("\t%ld\n",value.population);
	printf("\t%ld\n",value.area);
	printf("\t%ld\n",value.gdp_capita);
	printf("\t%f\n",value.literacy);
	printf("\t%f\n",value.birthrate);
	printf("\t%f\n",value.deathrate);
	
}

int mapKeyCompare(MapKey key1, MapKey key2) {
	// in case of integer keys:
	return (strcmp(key1.text,key2.text)); 
}