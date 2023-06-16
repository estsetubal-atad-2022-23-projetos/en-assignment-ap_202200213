#include "utils.h"

/**
 * @brief Prints the command menu.
 */
void printMenu();

/**
 * @brief Waits for user to press a key.
 */
void waitForKeypress();

/**
 * @brief Program entry point.
 * @return int error code: EXIT_SUCCESS or EXIT_FAILURE
 */
int main() {
	/* Feel free to change whatever you want. */

	// TODO: variables ?

	/* Command interpreter. */
	/*char command[100];	
	while (true) {
		
		printMenu();
		readString(command, 100);

		if (strcasecmp(command, "QUIT") == 0) {
			// Break loop, effectively leaving the command line	
			break;	
		}
		else if (strcasecmp(command, "LOADCL") == 0) {
			// Insert call for function here ...
			printf("Not implemented yet!");
					
		}
		else if (strcasecmp(command, "SHOWALL") == 0) {
			// Insert call for function here ...
			printf("Not implemented yet!");
		}
		// TODO: Other commands checking through else if's
		else {
			printf("Command not found.");

		}

		waitForKeypress();	
	}

	// TODO: Any memory cleanup before end of program?
	*/

	PtMap ptMap = NULL;
	loadST(&ptMap, 230);
	printf("%p", ptMap);


	int size;
	mapSize(ptMap, &size);

	MapKey *ptMapKeys = mapKeys(ptMap);
	for(int i = 0; i < size; i++) {

		CountryStatistics countryStatistics;
		mapGet(ptMap, ptMapKeys[i], &countryStatistics);
		printf("%s\n",ptMapKeys[i].text);
		printf("\t%s\n",countryStatistics.code);
		printf("\t%s\n",countryStatistics.name);
		printf("\t%s\n",countryStatistics.region);
		printf("\t%ld\n",countryStatistics.population);
		printf("\t%ld\n",countryStatistics.area);
		printf("\t%ld\n",countryStatistics.gdp_capita);
		printf("\t%f\n",countryStatistics.literacy);
		printf("\t%f\n",countryStatistics.birthrate);
		printf("\t%f\n",countryStatistics.deathrate);
	}
	free(ptMapKeys);
	free(ptMap);

	return EXIT_SUCCESS;
}

void printMenu() {
	printf("\n===================================================================================");
	printf("\n                          EarthQuake Data Analysis ");
	printf("\n===================================================================================");
	printf("\nA. Base commands (LOADCL, LOADEA, LOADST, CLEAR).");
	printf("\nB. Aggregated info about earthquakes (SHOWALL, SHOW_Y, SHOW_T, SHOW_YT, LIST_T, COUNT, HISTOGRAM");
	printf("\nC. Aggregated info about countries and regions (COUNTRY_S, REGION_AVG).");
	printf("\nD. Complex indicators; require earthquake and country data (TOPN).");
	printf("\n\nExit (QUIT)\n\n");
	printf("COMMAND?> ");
}

void waitForKeypress() {
	printf("\n\nPress any key to continue ...");
	getchar();
}
