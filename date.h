/**
 * @file date.h
 * @author ap_202200213
 * @brief Utilizado para declarar o struct Date e respetivo ponteiro
 * @version 0.1
 * @date 2023-06-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

/**
 * @brief Cria um struct para guardar as informações sobre a data
 * 
 */
typedef struct date {
int day, month, year;
} Date;

/* Definição do ponteiro do struct anterior */
typedef Date* PtDate;