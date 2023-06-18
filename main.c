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
	int countryLocationMax = 244;
	int countryLocationSize = 0;
	PtCountryLocation ptCountryLocation = NULL;

	int countryStatisticsMax = 230;
	PtMap ptMapCountryStatistics = NULL;

	int earthquakeMax = 2340;//23409;
	PtList ptListEarthquake = NULL;


	/* Command interpreter. */
	char command[100];	
	while (true) {
		
		printMenu();
		readString(command, 100);

		if (strcasecmp(command, "QUIT") == 0) {
			// Break loop, effectively leaving the command line
			break;	
		}
		else if (strcasecmp(command, "LOADALL") == 0 || strcasecmp(command, "LOAD") == 0) {
			cmdLoadCL(&ptCountryLocation, countryLocationMax, &countryLocationSize);
			cmdLoadST(&ptMapCountryStatistics, countryStatisticsMax);
			cmdLoadEA(&ptListEarthquake, earthquakeMax, ptCountryLocation, countryLocationSize);
		}
		else if (strcasecmp(command, "LOADCL") == 0) { cmdLoadCL(&ptCountryLocation, countryLocationMax, &countryLocationSize); }
		else if (strcasecmp(command, "LOADST") == 0) { cmdLoadST(&ptMapCountryStatistics, countryStatisticsMax); }
		else if (strcasecmp(command, "LOADEA") == 0) { cmdLoadEA(&ptListEarthquake, earthquakeMax, ptCountryLocation, countryLocationSize); }
		else if (strcasecmp(command, "SHOWALL") == 0) { cmdShowAll(ptListEarthquake); }
		else if (strcasecmp(command, "CLEAR") == 0) { cmdClear(&ptListEarthquake, &ptMapCountryStatistics, &ptCountryLocation, &countryLocationSize); }
		else if (strcasecmp(command, "SHOW_Y") == 0) { cmdShowY(ptListEarthquake); }
		else if (strcasecmp(command, "SHOW_T") == 0) { cmdShowT(ptListEarthquake, ptCountryLocation, countryLocationSize); }
		else if (strcasecmp(command, "SHOW_YT") == 0) { cmdShowYT(ptListEarthquake, ptCountryLocation, countryLocationSize); }
		else if (strcasecmp(command, "LIST_T") == 0) { cmdListT(ptListEarthquake); }
		else if (strcasecmp(command, "COUNT") == 0) { cmdCount(ptListEarthquake); }
		else if (strcasecmp(command, "COUNTRY_S") == 0) { cmdCountryS(ptMapCountryStatistics); }
		else if (strcasecmp(command, "REGION_AVG") == 0) { cmdRegionAvg(ptMapCountryStatistics); }
		else {
			printf("Command not found.");
		}

		waitForKeypress();
	}

	//Cleanup
	cmdClear(&ptListEarthquake, &ptMapCountryStatistics, &ptCountryLocation, &countryLocationSize);
	printf("\n");
	return EXIT_SUCCESS;
}

void printMenu() {
	printf("\n===================================================================================");
	printf("\n                          EarthQuake Data Analysis ");
	printf("\n===================================================================================");
	printf("\nA. Base commands (LOADALL, LOADCL, LOADEA, LOADST, CLEAR).");
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
