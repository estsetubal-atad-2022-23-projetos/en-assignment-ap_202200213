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
	printf("\n%*s", 2, value.code);   
	printf(" %*s", -32, value.name);
	printf(" %*s", -20, value.region);
	printf(" %*ld", 10, value.population);
	printf(" %*ld", 8, value.area);
	if(value.gdp_capita >= 0) printf(" %*ld", 5, value.gdp_capita);
	else printf("    - ");
	if(value.literacy >= 0) printf(" %*.2f", 6, value.literacy);
	else printf("    -  ");
	if(value.birthrate >= 0) printf(" %*.2f", 5, value.birthrate);
	else printf("   -  ");
	if(value.deathrate >= 0) printf(" %*.2f", 5, value.deathrate);
	else printf("   -  ");
}

int mapKeyCompare(MapKey key1, MapKey key2) {
	// in case of integer keys:
	return (strcmp(key1.text,key2.text)); 
}