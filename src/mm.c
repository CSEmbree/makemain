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
int verboseTextFlag = FALSE;

static char* ENV_VAR_PERM_AUTHOR = "MM_AUTHOR";
static char* DEFAULT_FILE_NAME   = "default.c";
static char* DEFAULT_AUTHOR_NAME = "<DEFAULT>";


int main(int argc, char **argv) {
	int mainType = INVALID;
	char *fileName = DEFAULT_FILE_NAME;
	char *authorName = DEFAULT_AUTHOR_NAME;
	char *permAuthorName = ""; //none assumed at start
	

	#ifdef DBUG
	if (verboseTextFlag) {
	    printf("mm:: Received the '%d' arguments: ", argc);
	    for (int i = 0; i < argc; ++i) printf("%s ", argv[i]);
	    printf("\n");
	}
	#endif


	//set author name if it has been set permanently
	permAuthorName = getenv(ENV_VAR_PERM_AUTHOR);
	if (permAuthorName != NULL) {
		authorName = permAuthorName;

		#ifdef DBUG
		printf("mm:: Main: Author name found in ENVAR: '%s'\n", authorName);
		#endif
	}


	if(argc>=2) {
		
		//Set appropreate flags to alter behavior depending on optional arguments
		char *optionsFound = ExtractOptions(argc, argv);
		if (optionsFound != NULL) {
			SetOptions(optionsFound);
		}


		fileName = ExtractFileName(argc, argv);


		char *optionalAuthor = ExtractOptionalAuthorName(argc, argv);			
		if (optionalAuthor != NULL) {
			#ifdef DBUG
			printf("mm:: MAIN: Overrode author from '%s' to '%s'.\n", authorName, optionalAuthor);
			#endif

			authorName = optionalAuthor;
		}
		

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

	#ifdef DBUG
	printf("mm:: CreateMain: Creating main type: '%d'...\n", fileType);
	#endif


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


	#ifdef DBUG
	printf("mm:: CreateMain: Creation result: %d.\n", creationResult);
	#endif

	return 0;
}


void SetOptions(char* options)
{
	#ifdef DBUG
    printf("mm:: SetOptions: Checking that only supported option where passed by argument...\n");
	#endif


    if( strchr(options, 'h') != NULL ) {
        makeHeader = TRUE;
        printf("mm:: SetOptions: HEADER FLAG SET! - TODO-NOT HANDLED YET\n");       
    }

    if( strchr(options, 'v') != NULL ) {
        verboseTextFlag = TRUE;
        printf("mm:: SetOptions: VERBOSE TEXT FLAG SET!\n");       
    }


	#ifdef DBUG
    printf("mm:: SetOptions: All options have been checked.\n");
	#endif

    return;
}


char* ExtractOptions(int numArgs, char** args)
{
	#ifdef DBUG
    printf("mm:: ExtractOptions: Checking if any options where passed by argument...\n");
	#endif


    char* optionsFound = NULL;
    int found = FALSE;

    for (int i = 0; (i < numArgs) && (found == FALSE); ++i) {
    	
    	#ifdef DBUG
    	printf("mm:: ExtractOptions: Checking for options in: '%s'...\n", args[i]);
	    #endif

        if( strchr(args[i], '-') != NULL ) {
           
	       #ifdef DBUG
           printf("mm:: ExtractOptions: Found option(s)!\n");
           #endif

           optionsFound = malloc(strlen(args[i])*sizeof(char)+1); //+1 for the zero-terminator
           optionsFound = args[i]; //take all the options at once  

           found = TRUE; 
        }
    }
    

    #ifdef DBUG
    printf("mm:: ExtractOptions: All options have been checked, FOUND: '%s'.\n", optionsFound);
	#endif

    return optionsFound;
}


char* ExtractFileName(int numArgs, char** args)
{
	#ifdef DBUG
    printf("mm:: ExtractFileName: Extracting file name...\n");
	#endif


    char* fileName = NULL;
    int found = FALSE;

    for (int i = 0; (i < numArgs) && (found == FALSE); ++i) {
    	
    	#ifdef DBUG
    	printf("mm:: ExtractFileName: Checking for options in: '%s'...\n", args[i]);
	    #endif

        if( strchr(args[i], '.') != NULL ) {
            fileName = args[i]; //file name is the string with the first occurance of a '.' char
            found = TRUE;

	        #ifdef DBUG
            printf("mm:: ExtractFileName: Found option(s)! File Name is: '%s'\n", fileName);
            #endif
        }
    }


	#ifdef DBUG    
    printf("mm:: ExtractFileName: Extracted file name: '%s'.\n", fileName);
	#endif

    return fileName;
}


char* ExtractOptionalAuthorName(int numArgs, char** args)
{
	#ifdef DBUG
    printf("mm:: ExtractOptionalAuthorName: Extracting optional author name...\n");
	#endif


    char* optionalAuthorName = "";
    int found = FALSE;

    for (int i = 0; i < numArgs; ++i) {
    	
    	#ifdef DBUG
    	printf("mm:: ExtractOptionalAuthorName: Checking for file name in: '%s'...\n", args[i]);
	    #endif

        if( (strchr(args[i], '.') != NULL) && (found == FALSE) ) {
        	found = TRUE;
           
	        #ifdef DBUG
            printf("mm:: ExtractOptionalAuthorName: Found file name!\n");
            #endif
        } else if ( (found == TRUE) && (i <= numArgs) ) {
        	optionalAuthorName = concat(optionalAuthorName, args[i]);
        	optionalAuthorName = concat(optionalAuthorName, " "); //for nicer spacing of overloaded author name

	        #ifdef DBUG
        	printf("mm:: ExtractOptionalAuthorName: Concating author name to: '%s'\n", optionalAuthorName);
            #endif
        }
    }


    //if no optional Author name was found, return NULL not an empty string
    if ( strcmp(optionalAuthorName,"") == 0 ) {
    	optionalAuthorName = NULL;
    }
    

    #ifdef DBUG
    printf("mm:: ExtractOptionalAuthorName: Extracted author name: '%s'.\n", optionalAuthorName);
	#endif

    return optionalAuthorName;
}


int CheckSupportedMain(char* op)
{
	#ifdef DBUG
	printf("mm:: CheckSupportedMain: Checking if '%s' is a supported option...\n", op);
	#endif


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


	#ifdef DBUG
	printf("mm:: CheckSupportedMain: option '%s' is of type: '%d'\n", op, optionID);
	#endif

	return optionID;
}


char* ExtractMainType(char* text)
{
	char* extractedOption = NULL;
	extractedOption = strstr(text, ".");


	#ifdef DBUG
	printf("mm:: ExtractMainType: Given: '%s', Extracted: '%s'\n", text, extractedOption+1);
	#endif


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
		printf("mm (makemain):: generates a plain main file for either C (*.c), CPP (*.{c++,cpp}), Python (*.py).\n\n");
	} else {
		printf("%s\n", dialogue);
	}

	return;
}
