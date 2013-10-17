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
		mainType = CheckValidOption(ExtractOption(fileName));

		if(argc==3)
			authorName = argv[2];

		if( mainType != INVALID ) {
			CreateMain(mainType, fileName, authorName);
		} else {
			printf("mm:: Main: ERROR: Main Type of '%s' not supported.\n", ExtractOption(fileName));
			DisplayUsage(NULL);
			return FAIL;
		}
	}
	else 
		DisplayUsage(NULL);


	return SUCCESS;
}


////////////////////////////////////////////////////////////////////


int CreateMain(int fileType, char* fileName, char* authorName)
{
	int creationResult = FAIL;

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

	return SUCCESS;
}


int CheckValidOption(char* op)
{
	printf("mm:: CheckValidOption: Checking if '%s' is a supported option.\n", op);

	int optionID = INVALID;

	if( strcmp(op, "c") == 0 )
		optionID = C;
	else if ( strcmp(op, "c++") == 0 || strcmp(op, "cpp") == 0 )
		optionID = CPP;
	else if ( strcmp(op, "py") == 0 )
		optionID = PYTHON;
	else if ( strcmp(op, "java") == 0 )
		optionID = JAVA;

	printf("mm:: CheckValidOption: option '%s' is of type: '%d'\n", op, optionID);

	return optionID;
}


char* ExtractOption(char* text)
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


int MainInC(char* fileName, char* authorName)
{
	FILE* sourceFile = fopen("templates/template_c.c", "r");
    FILE* destFile = fopen(fileName, "w");

	//make sure files can be opened
    if(sourceFile==NULL || destFile==NULL) {
    	printf("mm:: MainInC: ERROR: There was a problem creating the file: '%s'\n", fileName);
    	return FAIL;
    }
    printf("mm:: MainInC: Creating file '%s' with:\n\tauthor: %s\n", fileName, authorName);


    //put default intro at the head of the C file
    char intro[1000] = "";
    char *author   = " * AUTHOR:   ";
    char *created  = " * CREATED:  ";
    char *modified = " * MODIFIED: ";
    time_t currentTime = time(NULL);


    //prep intro text
    strcat( intro, "/*\n" );
    
    strcat( intro, author );
    strcat( intro, authorName);
    strcat( intro, "\n");

    strcat( intro, created );
    strcat( intro, ctime(&currentTime) );
    strcat( intro, " * \n");
	strcat( intro, " */\n");


    //output intro text followed by default c template
    fputs( intro, destFile);


    //fill the rest of the default c from template
    char ch;
    while( (ch = fgetc(sourceFile)) != EOF )
    	fputc( ch, destFile );

	
	//cleanup
	fclose(sourceFile);
	fclose(destFile);


	return SUCCESS;
}


int MainInCPP(char* fileName, char* authorName)
{
	FILE* sourceFile = fopen("templates/template_cpp.cpp", "r");
    FILE* destFile = fopen(fileName, "w");

	//make sure files can be opened
    if(sourceFile==NULL || destFile==NULL) {
    	printf("mm:: MainInCPP: ERROR: There was a problem creating the file: '%s'\n", fileName);
    	return FAIL;
    }
    printf("mm:: MainInCPP: Creating file '%s' with:\n\tauthor: %s\n", fileName, authorName);


    //put default intro at the head of the C file
    char intro[1000] = "";
    char *author   = " * AUTHOR:   ";
    char *created  = " * CREATED:  ";
    char *modified = " * MODIFIED: ";
    time_t currentTime = time(NULL);


    //prep intro text
    strcat( intro, "/*\n" );
    
    strcat( intro, author );
    strcat( intro, authorName);
    strcat( intro, "\n");

    strcat( intro, created );
    strcat( intro, ctime(&currentTime) );
    strcat( intro, " * \n");
	strcat( intro, " */\n");


    //output intro text followed by default c template
    fputs( intro, destFile);


    //fill the rest of the default c from template
    char ch;
    while( (ch = fgetc(sourceFile)) != EOF )
    	fputc( ch, destFile );

	
	//cleanup
	fclose(sourceFile);
	fclose(destFile);


	return SUCCESS;	
}


int MainInPython(char* fileName, char* authorName)
{
	FILE* sourceFile = fopen("templates/template_python.py", "r");
    FILE* destFile = fopen(fileName, "w");

	//make sure files can be opened
    if(sourceFile==NULL || destFile==NULL) {
    	printf("mm:: MainInPython: ERROR: There was a problem creating the file: '%s'\n", fileName);
    	return FAIL;
    }
    printf("mm:: MainInPython: Creating file '%s' with:\n\tauthor: %s\n", fileName, authorName);


    //put default intro at the head of the Python file
    char intro[1000] = "";
    char *author   = "# AUTHOR:   ";
    char *created  = "# CREATED:  ";
    char *modified = "# MODIFIED: ";
    time_t currentTime = time(NULL);


    //prep intro text
    strcat( intro, "#!/usr/bin/env python\n" );
    strcat( intro, "#\n" );

    strcat( intro, author );
    strcat( intro, authorName);
    strcat( intro, "\n");

    strcat( intro, created );
    strcat( intro, ctime(&currentTime) );
    strcat( intro, "#\n");
	

	//output intro text followed by default c template
    fputs( intro, destFile);


    //fill the rest of the default c from template
    char ch;
    while( (ch = fgetc(sourceFile)) != EOF )
    	fputc( ch, destFile );

	
	//cleanup
	fclose(sourceFile);
	fclose(destFile);


	return SUCCESS;
}


int MainInJava(char* fileName, char* authorName)
{
	FILE* sourceFile = fopen("templates/template_java.java", "r");
    FILE* destFile = fopen(fileName, "w");

	//make sure files can be opened
    if(sourceFile==NULL || destFile==NULL) {
    	printf("mm:: MainInJava: ERROR: There was a problem creating the file: '%s'\n", fileName);
    	return FAIL;
    }
    printf("mm:: MainInJava: Creating file '%s' with:\n\tauthor: %s\n", fileName, authorName);


    //put default intro at the head of the Python file
    char intro[1000] = "";
    char *author   = " * AUTHOR:   ";
    char *created  = " * CREATED:  ";
    char *modified = " * MODIFIED: ";
    time_t currentTime = time(NULL);


    //prep intro text
    strcat( intro, "/*\n" );
    
    strcat( intro, author );
    strcat( intro, authorName);
    strcat( intro, "\n");

    strcat( intro, created );
    strcat( intro, ctime(&currentTime) );
    strcat( intro, " *\n");
    strcat( intro, " */\n");
	

	//output intro text followed by default c template
    fputs( intro, destFile);


    //fill the rest of the default c from template
    char ch;
    while( (ch = fgetc(sourceFile)) != EOF )
    	fputc( ch, destFile );

	
	//cleanup
	fclose(sourceFile);
	fclose(destFile);


	return SUCCESS;
}