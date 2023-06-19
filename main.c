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
	/* Criação das variáveis utilizadas para armazenar a execução das funcionalidades de load */
	int countryLocationMax = 244;
	int countryLocationSize = 0;
	PtCountryLocation ptCountryLocation = NULL;

	int countryStatisticsMax = 230;
	PtMap ptMapCountryStatistics = NULL;

	int earthquakeMax = 2340;//23409; //APAGAR: Altera 2340 para 23409
	PtList ptListEarthquake = NULL;


	/* Interpreta os comandos a serem executados */
	char command[100];	
	while (true) {
		
		printMenu();
		readString(command, 100);

		if (strcasecmp(command, "QUIT") == 0) {
			//Quebra o loop saíndo da aplicação
			break;	
		}
		/* Nova funcionalidade loadAll(): executa as funções das três funcionalidades de load ao mesmo tempo */
		else if (strcasecmp(command, "LOADALL") == 0 || strcasecmp(command, "LOAD") == 0) {
			cmdLoadCL(&ptCountryLocation, countryLocationMax, &countryLocationSize);
			cmdLoadST(&ptMapCountryStatistics, countryStatisticsMax);
			cmdLoadEA(&ptListEarthquake, earthquakeMax, ptCountryLocation, countryLocationSize);
		}
		/* Utilização de todos os comandos criados: todas as funcionalidades têm o prefixo 'cmd' mas equivalem às funcionalidades do enunciado */
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
		else if (strcasecmp(command, "HISTOGRAM") == 0) { cmdHistogram(ptListEarthquake); }
		else if (strcasecmp(command, "COUNTRY_S") == 0) { cmdCountryS(ptMapCountryStatistics); }
		else if (strcasecmp(command, "REGION_AVG") == 0) { cmdRegionAvg(ptMapCountryStatistics); }
		else if (strcasecmp(command, "TOPN") == 0) { cmdTopN(ptListEarthquake, ptCountryLocation, countryLocationSize); }
		else {
			printf("Command not found.");
		}

		waitForKeypress();
	}

	/* Limpa a memória alocada e termina o programa */
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
