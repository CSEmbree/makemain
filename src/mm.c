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


//static char* DEFAULT_FILE_NAME = "default.c"; //default filename for debugging, should never show
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
	
	int totResult = TRUE; //result of the whole make creation. Any error along the way makes this FALSE.
	
 
	//debug prints to visually confirm incomming argument input order
	#ifdef DBUG
	printf("mm:: Received the '%d' arguments: ", argc);
	for (int i = 0; i < argc; ++i) printf("%s ", argv[i]);
	printf("\n");
	#endif


	//update author name if it has already been set permanently
	char* defaultAuthorName = getenv(ENV_VAR_PERM_AUTHOR);
	
	
	if (defaultAuthorName != NULL) {
		#ifdef DBUG
		printf("mm:: Main: Author name found in ENVAR: '%s'.\n", defaultAuthorName);
		#endif
	} else {
		//no ENVAR was found, use placeholder deafult
		defaultAuthorName = DEFAULT_AUTHOR_NAME;

		#ifdef DBUG
		printf("mm:: Main: Author name NOT found in ENVAR.\n");
	    #endif
	}


	//insure minimum input requirement
	if(argc>=2) {
		
		//get all the file info the user provided
		FILE_INFO *fInfo = ExtractUserDetails(argc, argv);
		#ifdef DBUG
		DisplayFileInfo(fInfo);
		#endif


		//Set appropreate option flags to alter behavior
		char *optionsFound = ExtractOptions(argc, argv);
		if (optionsFound != NULL) {
			SetOptions(optionsFound);
		}


		//arguments after filename are the overloaded author name and override any default
		if (fInfo->authorName != NULL) {
			#ifdef DBUG
			printf("mm:: MAIN: Overrode author from '%s' to '%s'.\n", defaultAuthorName, fInfo->authorName);
			#endif
		} else {
			fInfo->authorName = defaultAuthorName;
		}
		

		//create main only if a supported language was requested
		int creationResult = CreateMain(fInfo);

		if (creationResult == INVALID) {
			if(fInfo->fileName == NULL) {
				printf("mm:: Main: ERROR: No file extension was provided in '%s'.\n", fInfo->fileName);
			} else {
				printf("mm:: Main: ERROR: Main Type of '%s' not supported.\n", ExtractMainType(fInfo->fileName));
			}
			totResult = FALSE; //note to user the creation was unsuccesful
		}


		//display creation results if requested by user
		if (verboseTextFlag == TRUE) {
			DisplayVerbose(fInfo);
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
 * @param fInfo - struct with file and author name
 * 
 * Creates main based on the main file type requested with a provided author.
 *
 */
int CreateMain(FILE_INFO *fInfo) 
{
	int creationResult = INVALID;

	#ifdef DBUG
	printf("mm:: CreateMain: Creating main type from: '%s'...\n", fInfo->fileName);
	#endif


	//retrive file extention ID for quick identification of which main to make
	char* fileExtention = ExtractMainType(fInfo->fileName);
	int fileExtentionID = CheckSupportedMain(fileExtention);

	char* templatePath = getenv(ENV_VAR_TEMP_PATH);
    

	if ( fileExtentionID != INVALID ) {
	    switch (fileExtentionID) {
		    case C:
		        creationResult = MainInC(fInfo->fileName, fInfo->authorName, templatePath); 
		        break;
		    case CPP:
		        creationResult = MainInCPP(fInfo->fileName, fInfo->authorName, templatePath); 
		        break;
		    case PYTHON:
		        creationResult = MainInPython(fInfo->fileName, fInfo->authorName, templatePath);
		        break;
		    case JAVA:
		        creationResult = MainInJava(fInfo->fileName, fInfo->authorName, templatePath);
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
		printf("mm:: CreateMain: ERROR: Encountered unsupported extension: '%s'\n", fileExtention);
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
	if(op != NULL) {
		if( strcmp(op, "c") == 0 ) {
			optionID = C;
		} else if ( strcmp(op, "c++") == 0 || strcmp(op, "cpp") == 0 ) {
			optionID = CPP;
		} else if ( strcmp(op, "py") == 0 ) {
			optionID = PYTHON;
		} else if ( strcmp(op, "java") == 0 ) {
			optionID = JAVA;
		}
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
	#ifdef DBUG
	printf("mm:: ExtractMainType: Extracting main type from: '%s'\n", fileName);
	#endif


	char* extractedMainType = NULL;

	if(fileName != NULL) {
		extractedMainType = strstr(fileName, ".");
		extractedMainType = extractedMainType+1;
	}


	#ifdef DBUG
	printf("mm:: ExtractMainType: Given: '%s', Extracted: '%s'\n", fileName, extractedMainType);
	#endif

	return extractedMainType;
}



FILE_INFO *ExtractUserDetails(int numArgs, char** args)
{
	#ifdef DBUG
    printf("mm:: ExtractUserDetails: Extracting optional author name...\n");
	#endif


    FILE_INFO *fileInfo = malloc(sizeof(FILE_INFO));

    char* fileName = NULL;
    char* optionalAuthorName = NULL;
    int fileNameFound = FALSE; //flag for finding first occurance of period '.' indicated filename w/ extension

    
    for (int i = 0; i < numArgs; ++i) {
    	
    	#ifdef DBUG
    	printf("mm:: ExtractUserDetails: Checking for file name in: '%s'...\n", args[i]);
	    #endif

    	//first find argument containing the period, because author name is all arguments occurang after it.
        if( (strchr(args[i], '.') != NULL) && (fileNameFound == FALSE) ) {
        	//file name is the string with the first occurance of a '.' char
        	fileName = strdup(args[i]);
        	fileNameFound = TRUE;

	        //If there may be an author name, prep for receiving it
        	if( i < (numArgs-1) ) {
        		optionalAuthorName = "";
        	}
           
	        #ifdef DBUG
            printf("mm:: ExtractUserDetails: Found file name: '%s'\n", fileName);
            #endif
        } else if ( (fileNameFound == TRUE) && (i <= numArgs) ) {
        	optionalAuthorName = concat(optionalAuthorName, args[i]);
        	optionalAuthorName = concat(optionalAuthorName, " "); //for nicer spacing in overloaded author name

	        #ifdef DBUG
        	printf("mm:: ExtractUserDetails: Concating author name to: '%s'\n", optionalAuthorName);
            #endif
        }
    }

    //prep local file info for returning
    fileInfo->fileName = fileName;
    fileInfo->authorName = optionalAuthorName;
    fileInfo->fileExtension = ExtractMainType(fileName);
    fileInfo->fileExtensionID = CheckSupportedMain(fileInfo->fileExtension);


	return fileInfo;
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
 * @param fInfo - struct containing author and file name
 *
 * Display file creation name and author name to user.
 *
 */
void DisplayVerbose(FILE_INFO *fInfo)
{
	if(fInfo != NULL) {
		printf("mm:: Created '%s' with author '%s'.\n", fInfo->fileName, fInfo->authorName);
	} else {
		printf("mm:: ERROR: Invalid file info provided!\n");
	}

	return;
}


/**
 * @name DisplayFileInfo
 * @param fInfo - struct containing author and file name
 *
 * Conveient way to display FILE_INFO struct contents
 *
 */
void DisplayFileInfo(FILE_INFO *fInfo)
{
	if(fInfo != NULL) {
		printf("mm:: DisplayFileInfo: FileName: '%s', AuthorName: '%s'.\n", fInfo->fileName, fInfo->authorName);
	} else {
		printf("mm:: DisplayFileInfo: ERROR: Invalid file Info encountered.\n");
	}

	return;
}

