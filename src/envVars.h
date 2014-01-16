/*
 * AUTHOR:  Cameron S. Embree
 * CREATED: Wed Oct 16 23:13:14 2013
 *
 */

#ifndef ENV_VAR_H
#define ENV_VAR_H


#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include <time.h>


static char* ENV_VAR_PERM_AUTHOR = "MM_PERM_AUTHOR"; //optional ENVAR containing permanent author name
//static char* ENV_VAR_EXEC_PATH = "MM_EXEC_PATH"; //ENVAR containing path to executable install location
static char* ENV_VAR_TEMP_PATH = "MM_TEMP_PATH"; //ENVAR containing path to templates


/**
 * @name concat
 * @param s1 - first string, occurs first after concatination
 * @param s2 - second string, is concatinated to the end of s2
 * 
 * Concatinates the strings s1, s2 in the order s1s2.
 *
 */
char* concat(char *s1, char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1); //+1 for the zero-terminator
    //TODO - check for errors in malloc
    strcpy(result, s1);
    strcat(result, s2);
    
    return result;
}


#endif
