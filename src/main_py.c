/*
 * AUTHOR:  Cameron S. Embree
 * CREATED: Wed Oct 16 23:13:14 2013
 *
 */

//#include "main_python.h"


int MainInPython(char* fileName, char* authorName, char* templatePath);


int MainInPython(char* fileName, char* authorName, char* templatePath)
{
    char* sourceTemplate = concat(templatePath, "/template_python.py");


    FILE* sourceFile = fopen(sourceTemplate, "r");
    FILE* destFile = fopen(fileName, "w");

	//make sure files can be opened
    if(sourceFile==NULL || destFile==NULL) {
    	printf("mm:: MainInPython: ERROR: There was a problem creating the file: '%s'\n", fileName);
    	return -1;
    }


    #ifdef DBUG
    printf("mm:: MainInPython: Creating file '%s' with:\n\tauthor: %s\n", fileName, authorName);
    #endif


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

    strcat( intro, modified );
    strcat( intro, ctime(&currentTime) );
    strcat( intro, "#\n");
	

	//output intro text followed by default c template
    fputs( intro, destFile);


    //fill the rest of the default c from template
    char ch;
    while( (ch = fgetc(sourceFile)) != EOF ) {
    	fputc( ch, destFile );
    }

	
	//cleanup
	fclose(sourceFile);
	fclose(destFile);

	return 0;
}
