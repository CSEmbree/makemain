/*
 * AUTHOR:  Cameron S. Embree
 * CREATED: Wed Oct 16 23:13:14 2013
 *
 */

#ifndef MAKE_MAIN_H
#define MAKE_MAIN_H


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


//#include "returnResult.h"
#include "envVars.h"

#include "main_c.c"
#include "main_cpp.c"
#include "main_java.c"
#include "main_py.c"


//enum RETURN_OPTIONS {SUCCESS, FAIL}; 
enum MAIN_OPTIONS {INVALID = -1, C, CPP, PYTHON, JAVA};
enum TRUTH_VALUE {TRUE=0, FALSE=1};

typedef struct file_info
{
	char* fileName;
	char* authorName;
	char* fileExtension;
	int fileExtensionID;
	char* options;
} FILE_INFO;


//prototypes
int CreateMain(FILE_INFO *fInfo);
int CheckSupportedMain(char* op);

char* ExtractMainType(char* text);
char* ExtractOptions(int numArgs, char** args);
char* ExtractFileName(int numArgs, char** args);
char* ExtractOptionalAuthorName(int numArgs, char** args);

FILE_INFO* ExtractUserDetails(int numArgs, char** args);

void SetOptions(char* options);

//char* concat(char *s1, char *s2);

void DisplayUsage();
void DisplayVerbose(FILE_INFO* fInfo);



#endif
