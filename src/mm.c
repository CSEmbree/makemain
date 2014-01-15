/*
 * AUTHOR:  Cameron S. Embree
 * CREATED: Wed Oct 16 23:13:14 2013
 *
 * Automatically generate a default main for a few languges
 *
 */


#include "mm.h"


//Option flags for changing program behavior
int makeHeader = FALSE;
int verboseTextFlag = FALSE;


static char* ENV_VAR_PERM_AUTHOR = "MM_AUTHOR"; //optional ENVAR containing permanent author name
static char* DEFAULT_FILE_NAME   = "default.c"; //default filename for debugging, should never show
static char* DEFAULT_AUTHOR_NAME = "<DEFAULT>"; //default author for debugging, should never show



/**
 * @name main
 * @param argc - number of array elements in 'argv'
 * @param argv - array of strings for each argument delimiterized by spaces 
 * 
 * Create a basic main for supported languages.
 * Make sure minimum user inut was provided and input was valid.
 *
 */
int main(int argc, char **argv) {
	char *fileName = DEFAULT_FILE_NAME;
	char *authorName = DEFAULT_AUTHOR_NAME;
	char *permAuthorName = ""; //none assumed at start

	int totResult = TRUE; //result of the whole make creation. Any error along the way makes this FALSE.
	

 
	//debug prints to visually confirm incomming argument input order
	#ifdef DBUG
	printf("mm:: Received the '%d' arguments: ", argc);
	for (int i = 0; i < argc; ++i) printf("%s ", argv[i]);
	printf("\n");
	#endif


	//update author name if it has already been set permanently
	permAuthorName = getenv(ENV_VAR_PERM_AUTHOR);
	if (permAuthorName != NULL) {
		authorName = permAuthorName;

		#ifdef DBUG
		printf("mm:: Main: Author name found in ENVAR: '%s'\n", authorName);
		#endif
	}


	//insure minimum input requirement
	if(argc>=2) {
		
		//Set appropreate option flags to alter behavior
		char *optionsFound = ExtractOptions(argc, argv);
		if (optionsFound != NULL) {
			SetOptions(optionsFound);
		}

		//extract file name that is passed as an argument to mm
		fileName = ExtractFileName(argc, argv);


		//arguments after filename are used as an overloaded author name. 
		// This name overrides any default or permanent one
		char *optionalAuthor = ExtractOptionalAuthorName(argc, argv);			
		if (optionalAuthor != NULL) {
			#ifdef DBUG
			printf("mm:: MAIN: Overrode author from '%s' to '%s'.\n", authorName, optionalAuthor);
			#endif

			authorName = optionalAuthor;
		}
		

		//create main only if a supported language was requested
		int creationResult = CreateMain(fileName, authorName);

		if (creationResult == INVALID) {
			printf("mm:: Main: ERROR: Main Type of '%s' not supported.\n", ExtractMainType(fileName));
			totResult = FALSE; //note to user the creation was unsuccesful
		}


		//display creation results if requested by user
		if (verboseTextFlag == TRUE) {
			DisplayVerbose(fileName, authorName);
		}

	} else { 
		//if minimum arguments to run is not met, display usage info
		DisplayUsage(); 
		totResult = FALSE; //note to user the creation was unsuccesful
	}

	return totResult;
}


/*****************Support Methods*******************/


/**
 * @name CreateMain
 * @param fileName - whole file name requested by user, ex: 'hello.c'
 * @param authorName - author name for main file
 * 
 * Creates main based on the main file type requested with a provided author.
 *
 */
int CreateMain(char* fileName, char* authorName) 
{
	int creationResult = INVALID;

	#ifdef DBUG
	printf("mm:: CreateMain: Creating main type: '%d'...\n", fileType);
	#endif


	//retrive file extention ID for quick identification of which main to make
	char* fileExtention = ExtractMainType(fileName);

	int fileExtentionID = CheckSupportedMain(fileExtention);


	if ( fileExtentionID != INVALID ) {
	    switch (fileExtentionID) {
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
		        creationResult = INVALID; //unsupported fileExtention encountered, throw an error.
		        break; //do nothing
		}
	} else {
	    creationResult = INVALID; //unsupported fileExtention encountered, throw an error.
	}


	//let user know if they have provided an unsupported language file extention
	if (creationResult == INVALID) {
		printf("mm:: CreateMain: ERROR: Encountered unsupported language type: '%s'\n", fileExtention);
	}


	#ifdef DBUG
	printf("mm:: CreateMain: Creation result: %d.\n", creationResult);
	#endif

	return creationResult; //TODO - make sure result from main creation is consistent.
}


/**
 * @name SetOptions
 * @param options - extracted options from origional user input, is in the form '-vba'.
 * 
 * Sets internal flags to alter behavior depending on what options the user has selected.
 * Options are all characters that occured after a dash '-'.
 *
 */
void SetOptions(char* options)
{
	#ifdef DBUG
    printf("mm:: SetOptions: Checking that only supported option where passed by argument...\n");
	#endif

    //check if a supported option was passed and handle it
    //TODO - header flag creates a header with the same file name as the main
    if( strchr(options, 'h') != NULL ) {
        makeHeader = TRUE;
        
        #ifdef DBUG
        printf("mm:: SetOptions: HEADER FLAG SET! - TODO - NOT HANDLED YET\n");       
        #endif
    }

    //TODO - reports the result of makemain at the end of creation for user
    if( strchr(options, 'v') != NULL ) {
        verboseTextFlag = TRUE;
        
        #ifdef DBUG
        printf("mm:: SetOptions: VERBOSE TEXT FLAG SET!\n");       
        #endif
    }


	#ifdef DBUG
    printf("mm:: SetOptions: All options have been checked.\n");
	#endif

    return;
}


/**
 * @name ExtractOptions
 * @param numArgs - number of array elements in 'args'
 * @param args - array of strings for each argument delimiterized by spaces 
 * 
 * Collects and returns any options found as a string. 
 * Options are represented as any character following the '-' character before the next space ' '.
 *
 */
char* ExtractOptions(int numArgs, char** args)
{
	#ifdef DBUG
    printf("mm:: ExtractOptions: Checking if any options where passed by argument...\n");
	#endif


    char* optionsFound = NULL;
    int found = FALSE; //flag for finding first occurance of '-'

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


/**
 * @name ExtractFileName
 * @param numArgs - number of array elements in 'args'
 * @param args - array of strings for each argument delimiterized by spaces 
 * 
 * Collects and returns, as a string, the file name in 'args'. 
 * A file name is represetned as the first occurance of a string containing a perion '.'.
 *
 */
char* ExtractFileName(int numArgs, char** args)
{
	#ifdef DBUG
    printf("mm:: ExtractFileName: Extracting file name...\n");
	#endif


    char* fileName = NULL;
    int found = FALSE; //flag for finding first occurance of period '.'

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


/**
 * @name ExtractOptionalAuthorName
 * @param numArgs - number of array elements in 'args'
 * @param args - array of strings for each argument delimiterized by spaces 
 * 
 * Collects and returns, as a string, any optional overloaded author name found. 
 * Optional overloaded author names are a concatination of all strings occuring after the file name.
 *
 */
char* ExtractOptionalAuthorName(int numArgs, char** args)
{
	#ifdef DBUG
    printf("mm:: ExtractOptionalAuthorName: Extracting optional author name...\n");
	#endif


    char* optionalAuthorName = ""; //set as emtpy instead of NULL at start for convenience
    int found = FALSE; //flag for finding first occurance of period '.'

    for (int i = 0; i < numArgs; ++i) {
    	
    	#ifdef DBUG
    	printf("mm:: ExtractOptionalAuthorName: Checking for file name in: '%s'...\n", args[i]);
	    #endif

    	//first find argument containing the period, because author name is all arguments occurang after it.
        if( (strchr(args[i], '.') != NULL) && (found == FALSE) ) {
        	found = TRUE;
           
	        #ifdef DBUG
            printf("mm:: ExtractOptionalAuthorName: Found file name!\n");
            #endif
        } else if ( (found == TRUE) && (i <= numArgs) ) {
        	optionalAuthorName = concat(optionalAuthorName, args[i]);
        	optionalAuthorName = concat(optionalAuthorName, " "); //for nicer spacing in overloaded author name

	        #ifdef DBUG
        	printf("mm:: ExtractOptionalAuthorName: Concating author name to: '%s'\n", optionalAuthorName);
            #endif
        }
    }


    //if no optional Author name was found, return NULL
    if ( strcmp(optionalAuthorName,"") == 0 ) {
    	optionalAuthorName = NULL;
    }
    

    #ifdef DBUG
    printf("mm:: ExtractOptionalAuthorName: Extracted author name: '%s'.\n", optionalAuthorName);
	#endif

    return optionalAuthorName;
}


/**
 * @name CheckSupportedMain
 * @param op - single character representing the user requested language to make a main for
 * 
 * Checks that the language requested to make is a supported one. 
 * A language is supported if the characters occuring after the perion '.' in the file name are known.
 *
 */
int CheckSupportedMain(char* op)
{
	#ifdef DBUG
	printf("mm:: CheckSupportedMain: Checking if '%s' is a supported option...\n", op);
	#endif


	int optionID = INVALID;

	//supported file extentions
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


/**
 * @name ExtractMainType
 * @param fileName - full name of file including extention
 * 
 * Parses requested file name and extracts the extention at the end. 
 * The extention is all characters occuring after the perion '.' in the file name.
 *
 */
char* ExtractMainType(char* fileName)
{
	char* extractedMainType = NULL;
	extractedMainType = strstr(fileName, ".");


	#ifdef DBUG
	printf("mm:: ExtractMainType: Given: '%s', Extracted: '%s'\n", fileName, extractedMainType+1);
	#endif


	return (extractedMainType+1);
}


/**
 * @name concat
 * @param s1 - first string, occurs first after concatination
 * @param s2 - second string, is concatinated to the end of s2
 * 
 * Concatinates the strings s1, s2 in the order s1s2.
 *
 */
char* concat(char *s1, char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1); //+1 for the zero-terminator
    //TODO - check for errors in malloc
    strcpy(result, s1);
    strcat(result, s2);
    
    return result;
}


/**
 * @name DisplayUsage
 * 
 * Convenience method to display makemain usage info.
 *
 */
void DisplayUsage()
{
	printf("mm:: Generates a plain main file for either C (*.c), CPP (*.{c++,cpp}), Python (*.py).\n\n");

	return;
}


/**
 * @name DisplayVerbose
 * @param file - optional text to be displayed to overload default usage display text
 * @param author - optional text to be displayed to overload default usage display text
 * 
 * Display file creation name and author name to user.
 *
 */
void DisplayVerbose(char* file, char* author)
{
	printf("mm:: Created '%s' with author '%s'.\n", file, author);

	return;
}
