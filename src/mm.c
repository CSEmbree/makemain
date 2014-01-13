/*
 * AUTHOR:  Cameron S. Embree
 * CREATED: Wed Oct 16 23:13:14 2013
 *
 * Automatically generate a default main for a few languges
 *
 * EX: default c file format:
 *     ./mm <fileName>.c
 */


#include "mm.h"


int makeHeader = FALSE;
int optionalAuthorFlag = FALSE;
int verboseTextFlag = FALSE;

static char* ENV_VAR_PERM_AUTHOR = "MM_AUTHOR";


int main(int argc, char **argv) {
	int mainType = INVALID;
	char *fileName = "default.c";
	char *authorName = "<DEFAULT>";
	char *permAuthorName = "";
	

	
	printf("mm:: Received the '%d' arguments: ", argc); //TEST
	for (int i = 0; i < argc; ++i) printf("%s ", argv[i]); //TEST
	printf("\n"); //TEST


	//set author name if it has been set permanently
	permAuthorName = getenv(ENV_VAR_PERM_AUTHOR);
	if (permAuthorName != NULL) {
		authorName = permAuthorName;
	}
	printf("Author name set to: %s\n", authorName);


	if(argc>=2) {
		
		//Set appropreate flags to alter behavior depending on optional arguments
		char *optionsFound = ExtractOptions(argc, argv);
		if (optionsFound != NULL) {
			SetOptions(optionsFound);
		}


		fileName = ExtractFileName(argc, argv);


		if (optionalAuthorFlag == TRUE) {
			//free(authorName);
			authorName = ExtractOptionalAuthorName(argc, argv);			
		}
		


				
	
		//fileName = argv[1];
		//if(argc==3) authorName = argv[2];


		//ensure only supported Languages are selected
		mainType = CheckSupportedMain(ExtractMainType(fileName));




		if( mainType != INVALID ) {
			CreateMain(mainType, fileName, authorName);
		} else {
			printf("mm:: Main: ERROR: Main Type of '%s' not supported.\n", ExtractMainType(fileName));
			DisplayUsage(NULL);
			return -1;
		}
	} else { 
		DisplayUsage(NULL);
	}

	return 0;
}


////////////////////////////////////////////////////////////////////


int CreateMain(int fileType, char* fileName, char* authorName) 
{
	int creationResult = -1;

	printf("mm:: CreateMain: Creating main type: '%d'...\n", fileType);

	switch(fileType) {
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
		    break; //do nothing
	}

	printf("mm:: CreateMain: Creation result: %d.\n", creationResult);

	return 0;
}


void SetOptions(char* options)
{
    printf("mm:: SetOptions: Checking that only supported option where passed by argument...\n");

    if( strchr(options, 'h') != NULL ) {
        makeHeader = TRUE;
        printf("mm:: SetOptions: HEADER FLAG SET! - TODO-NOT HANDLED YET\n");       
    }

    if( strchr(options, 'a') != NULL ) {
        optionalAuthorFlag = TRUE;
        printf("mm:: SetOptions: OPTIONAL AUTHOR FLAG SET!\n");       
    }

    if( strchr(options, 'v') != NULL ) {
        verboseTextFlag = TRUE;
        printf("mm:: SetOptions: VERBOSE TEXT FLAG SET!\n");       
    }

    printf("mm:: SetOptions: All options have been checked.\n");

    return;
}


char* ExtractOptions(int numArgs, char** args)
{
    printf("mm:: ExtractOptions: Checking if any options where passed by argument...\n");

    char* optionsFound = NULL;

    for (int i = 0; i < numArgs; ++i) {
    	printf("mm:: ExtractOptions: Checking for options in: '%s'...\n", args[i]);

        if( strchr(args[i], '-') != NULL ) {
           printf("mm:: ExtractOptions: Found option(s)!\n");
           optionsFound = malloc(sizeof(strlen(args[i]))*sizeof(char)+1); //+1 for the zero-terminator
           optionsFound = args[i]; //take all the options at once   
        }
    }
    
    printf("mm:: ExtractOptions: All options have been checked, FOUND: '%s'.\n", optionsFound);

    return optionsFound;
}


char* ExtractFileName(int numArgs, char** args)
{
    printf("mm:: ExtractFileName: Extracting file name...\n");

    char* fileName = NULL;

    if (optionalAuthorFlag == FALSE) {
    	fileName = malloc(sizeof(strlen(args[numArgs-1]))*sizeof(char)+1); //+1 for the zero-terminator
    	fileName = args[numArgs-1];
    } else {
    	fileName = malloc(sizeof(strlen(args[numArgs-2]))*sizeof(char)+1); //+1 for the zero-terminator
    	fileName = args[numArgs-2];
    } 
    
    printf("mm:: ExtractFileName: Extracted file name: '%s'.\n", fileName);

    return fileName;
}


char* ExtractOptionalAuthorName(int numArgs, char** args)
{
    printf("mm:: ExtractFileName: Extracting optional author name...\n");

    char* optionalAuthorName = NULL;

    optionalAuthorName = malloc(sizeof(strlen(args[numArgs]))*sizeof(char)+1); //+1 for the zero-terminator
    optionalAuthorName = args[numArgs-1];
    
    printf("mm:: ExtractFileName: Extracted author name: '%s'.\n", optionalAuthorName);

    return optionalAuthorName;
}


int CheckSupportedMain(char* op)
{
	printf("mm:: CheckSupportedMain: Checking if '%s' is a supported option...\n", op);

	int optionID = INVALID;

	if( strcmp(op, "c") == 0 ) {
		optionID = C;
	} else if ( strcmp(op, "c++") == 0 || strcmp(op, "cpp") == 0 ) {
		optionID = CPP;
	} else if ( strcmp(op, "py") == 0 ) {
		optionID = PYTHON;
	} else if ( strcmp(op, "java") == 0 ) {
		optionID = JAVA;
	}

	printf("mm:: CheckSupportedMain: option '%s' is of type: '%d'\n", op, optionID);

	return optionID;
}


char* ExtractMainType(char* text)
{
	char* extractedOption = NULL;
	extractedOption = strstr(text, ".");

	printf("mm:: ExtractMainType: Given: '%s', Extracted: '%s'\n", text, extractedOption+1);

	return (extractedOption+1);
}


char* concat(char *s1, char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1); //+1 for the zero-terminator
    //TODO - check for errors in malloc
    strcpy(result, s1);
    strcat(result, s2);
    
    return result;
}


void DisplayUsage(char* dialogue)
{
	if(dialogue == NULL) {
		printf("mm (MakeMain): generates a main file for either C (*.c), CPP (*.{c++,cpp}), Python (*.py).\n\n");
	} else {
		printf("%s\n", dialogue);
	}

	return;
}
