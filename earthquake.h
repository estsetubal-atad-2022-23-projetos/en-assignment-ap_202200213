#pragma once

#define DATA_OK             0
#define DATA_ERROR          1
#define DATA_FULL           2
#define FILE_NULL           3


/**
 * @brief 
 * 
 */
struct date;

/**
 * @brief 
 * 
 */
struct time;

/**
 * @brief 
 * 
 */
struct earthquake;

/**
 * @brief 
 * 
 */
struct countryStatistics;

/**
 * @brief 
 * 
 */
struct countryLocation;

int loadCL(CountryLocation arr[], int max);
