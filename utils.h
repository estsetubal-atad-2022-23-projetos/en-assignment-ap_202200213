/**
 * @file utils.h
 * @author ap_202200213
 * @brief Utilizado para definir as funcionalidades implementadas, evitando a dependência circular
 * @version 0.1
 * @date 2023-06-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "input.h"
#include "list.h"
#include "map.h"
#include "stringWrap.h"
#include "countryLocation.h"
#include "countryStatistics.h"
#include "earthquake.h"
#include "date.h"
#include "time.h"

/* Definição de códigos de erro */
#define UTILS_OPERATION_OK 0
#define UTILS_PARAMETER_INVALID 1
#define UTILS_FILE_NOT_FOUND 2
#define UTILS_NO_MEMORY 3
/**
 * @brief Cria um struct para guardar informações extra relativas á informação de cada região
 * 
 */
typedef struct regionInfo {
    char name[30];
    int territoryCount;
    long totalArea;
    long totalPopulation;
    double totalLiteracy;
    long totalGDP;

} RegionInfo;

/* Definição do ponteiro do struct anterior */
typedef RegionInfo *PtRegionInfo;

/**
 * @brief Cria um struct para guardar informações extra relativas á informação de cada país
 * 
 */
typedef struct countryInfo {
    char code[3];
    char territoryName[45];
    int numberOfEarthquakes;
    double totalDepth;
    double totalMagnitude;
} CountryInfo; 

/* Definição do ponteiro do struct anterior */
typedef CountryInfo *PtCountryInfo;

/**
 * @brief Carrega em memória as localizações dos países do ficheiro world_country_locations.csv
 * 
 * @param ptCountryLocation 
 * @param max 
 * @param size 
 * @return UTILS_OPERATION_OK se for executada, ou código de erro dependente do erro provocado 
 */
int loadCL(PtCountryLocation *ptCountryLocation, int max, int *size);

/**
 * @brief Carrega em memória as estatísticas dos países do ficheiro world_country_statistics.csv
 * 
 * @param PtMap 
 * @param max 
 * @return UTILS_OPERATION_OK se for executada, ou código de erro dependente do erro provocado 
 */
int loadST(PtMap *PtMap, int max);

/**
 * @brief Carrega em memória os sismos do ficheiro earthquakes.csv, caso as localizações estejam carregadas
 * 
 * @param ptListRef 
 * @param max 
 * @param ptCountryLocation 
 * @param countryLocationSize 
 * @return UTILS_OPERATION_OK se for executada, ou código de erro dependente do erro provocado 
 */
int loadEA(PtList *ptListRef, int max, PtCountryLocation ptCountryLocation, int countryLocationSize);

/**
 * @brief Executa a função loadCL quando chamada pelo utilizador no main
 * 
 * @param ptCountryLocation 
 * @param countryLocationMax 
 * @param countryLocationSize 
 */
void cmdLoadCL(PtCountryLocation *ptCountryLocation, int countryLocationMax, int *countryLocationSize);

/**
 * @brief Executa a função loadST quando chamada pelo utilizador no main
 * 
 * @param ptMapCountryStatistics 
 * @param countryStatisticsMax 
 */
void cmdLoadST(PtMap *ptMapCountryStatistics, int countryStatisticsMax);

/**
 * @brief Executa a função loadEA quando chamada pelo utilizador no main
 * 
 * @param ptListEarthquake 
 * @param earthquakeMax 
 * @param ptCountryLocation 
 * @param countryLocationSize 
 */
void cmdLoadEA(PtList *ptListEarthquake, int earthquakeMax, PtCountryLocation ptCountryLocation, int countryLocationSize);

/**
 * @brief Caso exista memória alocada pelas funcionalidades de, limpa essa informação, libertando a memória
 * 
 * @param ptListEarthquake 
 * @param ptMapCountryStatistics 
 * @param ptCountryLocation 
 * @param countryLocationSize 
 */
void cmdClear(PtList *ptListEarthquake, PtMap *ptMapCountryStatistics, PtCountryLocation *ptCountryLocation, int *countryLocationSize);

/**
 * @brief Mostra todos os sismos carregados do ficheiro earthquakes.csv
 * 
 * @param ptListEarthquake 
 */
void cmdShowAll(PtList ptListEarthquake);

/**
 * @brief Após perguntar o ano ao utilizador ao utilizador, mostra todos os sismos que ocorreram nesse ano
 * 
 * @param ptListEarthquake 
 */
void cmdShowY(PtList ptListEarthquake);

/**
 * @brief Após perguntar o código do país ou o nome ao utilizador, mostra todos os sismos que ocorreram nesse país
 * 
 * @param ptListEarthquake 
 * @param ptCountryLocation 
 * @param countryLocationSize 
 */
void cmdShowT(PtList ptListEarthquake, PtCountryLocation ptCountryLocation, int countryLocationSize);

/**
 * @brief Após perguntar o código do país/nome e ano ao utilizador, mostra todos os sismos que ocorreram nesse país nesse ano
 * 
 * @param ptListEarthquake 
 * @param ptCountryLocation 
 * @param countryLocationSize 
 */
void cmdShowYT(PtList ptListEarthquake, PtCountryLocation ptCountryLocation, int countryLocationSize);

/**
 * @brief Mostra todos os códigos de países onde haja pelo menos um sismo, não repetindo
 * 
 * @param ptListEarthquake 
 */
void cmdListT(PtList ptListEarthquake);

/**
 * @brief Após perguntar o código do país e um intervalo de magnitude ao utilizador, mostra todos os sismos nesse país nesse intervalo de magnitudes e a percentagem do tipo de magnitude
 * 
 * @param ptListEarthquake 
 */
void cmdCount(PtList ptListEarthquake);

/**
 * @brief Após perguntar o número de países e os países a mostrar, mostra uma tabela com os países, o intervalo de magnitudes e o número de sismos
 * 
 * @param ptListEarthquake 
 */
void cmdHistogram(PtList ptListEarthquake);

/**
 * @brief Após perguntar os critérios de organização dos países ao utilizador, mostra todos os países ordenados pelas especificações
 * 
 * @param ptMapCountryStatistics 
 */
void cmdCountryS(PtMap ptMapCountryStatistics);

/**
 * @brief Mostra a média das estatísticas de uma ou todas as regiões, utilizando para tal as estatísticas de cada país
 * 
 * @param ptMapCountryStatistics 
 */
void cmdRegionAvg(PtMap ptMapCountryStatistics);

/**
 * @brief Após solicitar o número de registos a mostrar, mostra uma lista organizada decrescentemente de 'N' países com mais sismos
 * 
 * @param ptListEarthquake 
 * @param ptCountryLocation 
 * @param countryLocationSize 
 */
void cmdTopN(PtList ptListEarthquake, PtCountryLocation ptCountryLocation, int countryLocationSize);

/**
 * @brief Calcula a distância entre dois pontos utilizando o Teorema de Pitágoras
 * 
 * @param x0 
 * @param y0 
 * @param x1 
 * @param y1 
 * @return Distância entre dois pontos 
 */
float getDistance(float x0, float y0, float x1, float y1);

/**
 *  
 * @brief Obtém a contagem dos sismos para intervalos específicos de magnitudes para um dado país, alocando um ponteiro para devolver
 * @param ptListEartquake
 * @param code
 * @return *magnitudes: pointer para a contagem de sismos por intervalo de magnitudes
 */
int *getMagnitudeCount(PtList ptListEarthquake, char code[3]);

/**
 * @brief Mostra uma linha usada no histograma para observar o número de sismos
 * 
 * @param count 
 * @param code 
 * @param string 
 */
void printHistogramLine(int count, char code[3], char string[13]);