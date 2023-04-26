/**
 * @file stringWrap.c
 * @author Bruno Silva (bruno.silva@estsetubal.ips.pt)
 * @brief Implementation of StringWrap related functions.
 *
 * @version 1
 * @date 2021-02-20
 * 
 * @copyright Copyright (c) 2021
 */

#include "stringWrap.h"
#include <string.h>

StringWrap stringWrapCreate(char *str) {
    StringWrap sw;
    strcpy(sw.text, str);
    return sw;
}
