/*
 * AUTHOR:  Cameron S. Embree
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
enum TRUTH_VALUE {TRUE=0, FALSE=1};


//prototypes
int CreateMain(int fileType, char* fileName, char* authorName);
int CheckSupportedMain(char* op);
char* ExtractMainType(char* text);
void DisplayUsage(char* dialogue);

char* ExtractOptions(int numArgs, char** args);
void SetOptions(char* options);
char* ExtractFileName(int numArgs, char** args);
char* ExtractOptionalAuthorName(int numArgs, char** args);
char* concat(char *s1, char *s2);



#endif
