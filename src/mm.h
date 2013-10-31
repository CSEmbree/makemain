/*
 * AUTHOR: Cameron S. Embree
 * CREATED: Wed Oct 16 23:13:14 2013
 *
 */

#ifndef RETURN_RESULT_H
#define RETURN_RESULT_H


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

//#include "returnResult.h"

#include "main_c.c"
#include "main_cpp.c"
#include "main_java.c"
#include "main_py.c"


//enum RETURN_OPTIONS {SUCCESS, FAIL}; 
enum MAIN_OPTIONS {INVALID, C, CPP, PYTHON, JAVA};
enum TRUTH_VALUE {TRUE, FALSE};


//prototypes
int CreateMain(int fileType, char* fileName, char* authorName);
void SetOptions(int numArgs, char** args);
int CheckSupportedMain(char* op);
char* ExtractMainType(char* text);
void DisplayUsage(char* dialogue);


//gobal variables
int makeHeader;


#endif
