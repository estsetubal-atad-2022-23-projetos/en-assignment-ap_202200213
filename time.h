/**
 * @file time.h
 * @author ap_202200213
 * @brief Utilizado para declarar o struct Time e respetivo ponteiro
 * @version 0.1
 * @date 2023-06-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

/**
 * @brief Cria um struct para guardar as informações sobre o tempo
 * 
 */
typedef struct time {
int hour, min, sec;
} Time;

/* Definição do ponteiro do struct anterior */
typedef Time* PtTime;