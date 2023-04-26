/**
 * @file stringWrap.h
 * @author Bruno Silva (bruno.silva@estsetubal.ips.pt)
 * @brief Provides the StringWrap type.
 * 
 * The usage of this type is highly advised when
 * storing strings inside collections; if not,
 * you are storing only the pointer.
 * 
 * With this type a string is statically stored
 * inside a struct type. 
 *
 * @version 1
 * @date 2021-02-20
 * 
 * @copyright Copyright (c) 2021
 */
#pragma once


typedef struct stringWrap {
    char text[100];
    /* 
        Note: 100 characters should be enough, 
        but you can change it towards your needs.
    */
} StringWrap;

/**
 * @brief Creates a wrapper around a string.
 * 
 * 
 * @param str the string to wrap
 * @return StringWrap instance with str inside
 */
StringWrap stringWrapCreate(char *str);
