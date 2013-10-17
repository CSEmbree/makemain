/*
 * AUTHOR: Cameron S. Embree
 * CREATED: Wed Oct 16 23:13:14 2013
 *
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


enum RETURN_OPTIONS {SUCCESS, FAIL};
enum MAIN_OPTIONS {INVALID, C, CPP, PYTHON, JAVA};


//prototypes
int CreateMain(int fileType, char* fileName, char* authorName);
int CheckValidOption(char* op);
char* ExtractOption(char* text);
void DisplayUsage(char* dialogue);

int MainInC(char* fileName, char* authorName);
int MainInCPP(char* fileName, char* authorName);
int MainInPython(char* fileName, char* authorName);
int MainInJava(char* fileName, char* authorName);


//gobal variables
int makeHeader;