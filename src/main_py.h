/*
 * AUTHOR:  Cameron S. Embree
 * CREATED: Wed Oct 16 23:13:14 2013
 *
 */

#ifndef MAIN_PYTHON_H
#define MAIN_PYTHON_H


//#include "returnResult.h"
enum RETURN_OPTIONS {SUCCESS, FAIL}; 


int MainInPython(char* fileName, char* authorName, char* templatePath);


#endif
