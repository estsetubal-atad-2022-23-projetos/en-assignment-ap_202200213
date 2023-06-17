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

	int earthquakeMax = 23409;
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
		else if (strcasecmp(command, "LOADALL") == 0) {
			if (ptCountryLocation == NULL) {
				loadCL(&ptCountryLocation, countryLocationMax, &countryLocationSize);
				printf("%d countries were read. ", countryLocationSize);
			}
			else {
				printf("Country location data already loaded.");
			}

			if (ptMapCountryStatistics == NULL) {
				loadST(&ptMapCountryStatistics, countryStatisticsMax);
				int size;
				mapSize(ptMapCountryStatistics, &size);
				printf("%d country statistics were read. ", size);
			}
			else {
				printf("Country statistics data already loaded.");
			}

			if (ptListEarthquake == NULL) {
				if(ptCountryLocation != NULL) {
					loadEA(&ptListEarthquake, earthquakeMax, ptCountryLocation, countryLocationSize);
					int size;
					listSize(ptListEarthquake, &size);
					printf("%d country statistics were read. ", size);
				}
				else {
					printf("Country location data not loaded!");
				}
			}
			else {
				printf("Country statistics data already loaded.");
			}
		}
		else if (strcasecmp(command, "LOADCL") == 0) {
			if (ptCountryLocation == NULL) {
				loadCL(&ptCountryLocation, countryLocationMax, &countryLocationSize);
				printf("%d countries were read.", countryLocationSize);
			}
			else {
				printf("Country location data already loaded.");
			}
		}
		else if (strcasecmp(command, "LOADST") == 0) {
			if (ptMapCountryStatistics == NULL) {
				loadST(&ptMapCountryStatistics, countryStatisticsMax);
				int size;
				mapSize(ptMapCountryStatistics, &size);
				printf("%d country statistics were read.", size);
			}
			else {
				printf("Country statistics data already loaded.");
			}
		}
		else if (strcasecmp(command, "LOADEA") == 0) {
			if (ptListEarthquake == NULL) {
				if(ptCountryLocation != NULL) {
					loadEA(&ptListEarthquake, earthquakeMax, ptCountryLocation, countryLocationSize);
					int size;
					listSize(ptListEarthquake, &size);
					printf("%d country statistics were read.", size);
				}
				else {
					printf("Country location data not loaded!");
				}
			}
			else {
				printf("Country statistics data already loaded.");
			}
		}
		else if (strcasecmp(command, "SHOWALL") == 0) {
			if (ptListEarthquake != NULL) {
				int size;
				listSize(ptListEarthquake, &size);
				int pageCount = ceil(size/50.0f);

				char pageCommand[16];	
				while (true) {
					printf("\nEnter 'back' to return or desired page number out of %d: ", pageCount);
					readString(pageCommand, 16);

					int number;
					if (validIntegerFormat(pageCommand)) number = atoi(pageCommand);
					else number = -1;

					if (strcasecmp(pageCommand, "BACK") == 0) {
						printf("\nReturning to main menu...");
						break;
					} 
					else if (number == -1 || number <= 0 || number > pageCount) {
						printf("\nInvalid number.");
					} 
					else {
						printf("\nShowing page %d out of %d:", number, pageCount);
						printf("\n======================================================= Earthquakes =======================================================");
						printf("\n  ID  Country Code     Date       Time      Latitude  Longitude         Type          Depth    Magnitude  Magnitude Type  ");
						for (int i = 50*(number-1); i < 50*(number) && i < size; i++) {
							Earthquake earthquake;
							listGet(ptListEarthquake, i, &earthquake);
							printf("\n");
							listElemPrint(earthquake);
						}
					}

					waitForKeypress();
				}
			}
			else {
				printf("Earthquake data not loaded!");
			}
			
		}
		else {
			printf("Command not found.");

		}

		waitForKeypress();
	}

	//Cleanup
	free(ptCountryLocation);
	mapDestroy(&ptMapCountryStatistics);
	listDestroy(&ptListEarthquake);

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
