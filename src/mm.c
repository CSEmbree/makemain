/*
 * AUTHOR: Cameron S. Embree
 * CREATED: Wed Oct 16 23:13:14 2013
 *
 * Automatically generate a default main for a few languges
 *
 * EX: default c file format:
 *     ./mm <fileName>.c
 */


#include "mm.h"


int main(int argc, char **argv)
{
	int mainType = 0;
	char *fileName = "hello.c";
	char *authorName = "Cameron S. Embree";
	

	if(argc>=2) 
	{
		fileName = argv[1];

        SetOptions(argc, argv);

		mainType = CheckSupportedMain(ExtractMainType(fileName));

		if(argc==3)
			authorName = argv[2];

		if( mainType != INVALID ) {
			CreateMain(mainType, fileName, authorName);
		} else {
			printf("mm:: Main: ERROR: Main Type of '%s' not supported.\n", ExtractMainType(fileName));
			DisplayUsage(NULL);
			return -1;
		}
	}
	else 
		DisplayUsage(NULL);


	return 0;
}


////////////////////////////////////////////////////////////////////


int CreateMain(int fileType, char* fileName, char* authorName)
{
	int creationResult = -1;

	printf("mm:: CreateMain: Creating main type: '%d'\n", fileType);

	switch(fileType)
	{
		case C:
		    creationResult = MainInC(fileName, authorName); 
		    break;
		case CPP:
		    creationResult = MainInCPP(fileName, authorName); 
		    break;
		case PYTHON:
		    creationResult = MainInPython(fileName, authorName);
		    break;
		case JAVA:
		    creationResult = MainInJava(fileName, authorName);
		    break;
		default: 
		    break;//do nothing
	}

	return 0;
}


void SetOptions(int numArgs, char** args)
{
    printf("mm:: CheckOptions: Checking if a supported option was passed by argument.\n");

    for (int i = 0; i < numArgs; ++i)
    {
        if( strcmp(args[i], "-h") == 0 )
        {
           makeHeader = TRUE;
           printf("mm:: CheckOptions: HEADER FLAG SET!\n");       
        }
    }
    
    printf("mm:: CheckOptions: Options have been chcked.\n");

}


int CheckSupportedMain(char* op)
{
	printf("mm:: CheckSupportedMain: Checking if '%s' is a supported option.\n", op);

	int optionID = INVALID;

	if( strcmp(op, "c") == 0 )
		optionID = C;
	else if ( strcmp(op, "c++") == 0 || strcmp(op, "cpp") == 0 )
		optionID = CPP;
	else if ( strcmp(op, "py") == 0 )
		optionID = PYTHON;
	else if ( strcmp(op, "java") == 0 )
		optionID = JAVA;

	printf("mm:: CheckSupportedMain: option '%s' is of type: '%d'\n", op, optionID);

	return optionID;
}


char* ExtractMainType(char* text)
{
	char* extractedOption = NULL;
	extractedOption = strstr(text, ".");

	printf("mm:: ExtractOption: Given: '%s', Extracted: '%s'\n", text, extractedOption+1);

	return (extractedOption+1);
}


void DisplayUsage(char* dialogue)
{
	if(dialogue == NULL)
		printf("mm (MakeMain): generates a main file for either C (*.c), CPP (*.{c++,cpp}), Python (*.py).\n C FORM:\n\t mm hello.c\n CPP FORM:\n\t mm hello.py\n\n");
	else
		printf("%s\n", dialogue);
}
