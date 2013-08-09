/******************************************************************************

Author       : subjetZero                                                           
Course       : CIS111 - C Programming Language                                      
Assignment   : Programming Project #04 - Affine Cipher
Program Name : Derrida
Date created : 10 December 2012                                              
Last modified: 09 August   2013                                                
                                                                             
Description: Derrida is a command line file encryption program that  makes use 
				of a the archaic Affine Cipher algorithm. Key features include
				the ability to select a personal cipher key, generate a cipher
				key at random, switch between different input and output files,
				and  the ability  to  convert  between cipher  and plain  text.
				Derrida can  also display  a list  of  the  files  within  its
				directory,  further  adding  to  the  intuitive  nature of the
				program.

******************************************************************************/

// ----------------------------------------------------------------------------
// PRE-PROCESSOR DIRECTIVES
// ----------------------------------------------------------------------------

// PRAGMA
#pragma warning(disable:4996)
#pragma warning(disable:4005)

// INCLUDES
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>


// DEFINES
#define BUFFER_SIZE 1000
#define ALPHABET_SIZE 26
#define ASCII_OFFSET  97

// default cipher key
#define INVERSE       11
#define A             19
#define B              4

// gen rand range
#define LOWER          1
#define UPPER        300

#ifndef __TRUE_FALSE__
#define __TRUE_FALSE__
#define TRUE           1
#define FALSE          0
#endif

#define NO_INVERSE    -1
#define ERROR         -2


// action codes
#define UNSET          0
#define SET_I_FILE     1
#define SET_O_FILE     2
#define DIR_LIST       3
#define SET_KEY        4
#define ENCRYPT        5 
#define DECRYPT        6
#define QUIT           7

// key codes
#define USER_KEY       1
#define RAND_KEY       2

// PROTOTYPES

// cipher functions
int SetCipherKey(int&,int&, int,int&);
int ModularInverse(int, int);
int CoprimeTest(int, int);
int IsPrime(int);
int genKey();


// file and string handling
int FileOutput(char[30], char[BUFFER_SIZE]);
int EncryptString(char*,  int,  int,  int) ;
int DecryptString(char*,  int,  int,  int) ;
int SetOutputFileName(char[30]) ;

// default file read
int fGetClnStr
	(int mode,
	char rawPT[BUFFER_SIZE],
	char cleanPT[BUFFER_SIZE]);

// user file read
int fGetClnStr(
	int mode,
	char rawPT[BUFFER_SIZE],
	char cleanPT[BUFFER_SIZE],
	char[30]);

// program control
void DispHeader(char[30],char[30],int,int,int) ;
int SelectAction(int) ;
void list_dir( ) ;
void Pause();
void ClearScreen();
void ClearBuf();


// ----------------------------------------------------------------------------
// MAINLINE LOGIC
// ----------------------------------------------------------------------------
int main() {
	
	// declarations
	int  action = UNSET;
	char rawPT[BUFFER_SIZE]    = "";
	char cleanPT[BUFFER_SIZE]  = "";
	int  a = A, b = B, inverse = INVERSE, n = ALPHABET_SIZE;
	char nameInputFile[30]     = "input.txt" ;
	char nameOutputFile[30]    = "output.txt";

	// seed the random number generator
	srand((unsigned int)time(NULL));

	// get ready
	action = fGetClnStr(action, rawPT, cleanPT);
	
	// display title page
	DispHeader(nameInputFile, nameOutputFile, a, b, inverse);
	puts("Welcome to Derrida - the command line Affine Cipher!");
	Pause();

	// detail loop
	while(action != QUIT) {
		ClearScreen();

		DispHeader(nameInputFile, nameOutputFile, a, b, inverse);
		
		// select an action
		action = SelectAction(action);
		
		DispHeader(nameInputFile, nameOutputFile, a, b, inverse);

		// execute action
		switch(action) {
		case SET_I_FILE: // change the input file
			action = fGetClnStr(action, rawPT, cleanPT, nameInputFile);
			break;
		case SET_O_FILE: // change the output file
			action = SetOutputFileName(nameOutputFile);
			break;
		case DIR_LIST: // display directory listing
			list_dir();
			break;
		case SET_KEY: // change cipher key
			action = SetCipherKey(a, b, n, inverse);
			break;
		case ENCRYPT: // encrypt the PT codes

			// display the string before encryption
			printf("Before encryption, the string contains:\n");
			puts(rawPT);
			printf("\n");
			printf("Sanatized, the string contains:\n");
			puts(cleanPT);
			printf("\n");
			// if encryption succeeds, inform the user
			if(EncryptString(cleanPT, a, b, n)) {
				FileOutput(nameOutputFile, cleanPT);
				printf("After encryption, the string contains:\n");
				puts(cleanPT);
				printf("\n");
			}

			Pause();
			break;

		case DECRYPT:
			// display the clean cipher code before decryption
			puts("Before decryption, the string contains:");
			puts(cleanPT);
			puts("\n");
			// if decryption succeeds, inform the user
			if(DecryptString(cleanPT, a, b, n)) {
				FileOutput(nameOutputFile, cleanPT);
				puts("After decryption, the string contains:\n");
				puts(cleanPT);
				puts("\n");
			}

			Pause();
			break;	
		}		
	}

	puts("The program will now exit.");
	Pause();

	// exit program
	return 0;
}
// ----------------------------------------------------------------------------
// FUNCTION IMPLEMENTATIONS
// ----------------------------------------------------------------------------

// dynamic header that goes above user menu
void DispHeader(char nInFile[30],char nOutFile[30], int a, int b, int inverse){
	puts("------------- Derrida: an Affine Cipher - subjectZero-----------");
	puts("----------------------------------------------------------------");
	printf("The current input file is  : %s\n\n", nInFile);
	printf("The current output file is : %s\n\n", nOutFile);
	puts("Affine Cipher - e(x) = (Ax + B) (mod 26)");
	printf("a = %d, a^(-1) = %d\n", a, inverse);
	printf("B = %d\n", b);
	puts("----------------------------------------------------------------");
}

//-----------------------------------------------------------------------------

int DecryptString(char* decryptMe, int a, int b, int n) {
	int i = 0;
	int PTCodes[BUFFER_SIZE];
	
	// check to make sure we are safe for decryption
	int inverseCode = ModularInverse(a, n);
	if( inverseCode == -1 || inverseCode == -2) {
		printf("You cannot encrypt with key (%d,");
		printf("%d) on a (mod %d) ring.\n",a,b,n);
		return FALSE;
	}
	
	// copy the ASCII array codes into the PTCodes array
	for(i = 0; decryptMe[i] != '\0'; i++) {
		PTCodes[i] = decryptMe[i];
	}
	PTCodes[i] = -1;
	
	// reduce character ASCII codes to PT codes
	for(i = 0; PTCodes[i] != -1; i ++) {
		PTCodes[i] -= ASCII_OFFSET;
	}
	
	// decrypt PT codes
	for(i = 0; PTCodes[i] != -1; i++) {
		PTCodes[i] = (( inverseCode * (PTCodes[i] - b)) + (n * inverseCode * b)) % n;
	}
	
	// revert PT codes to ASCII codes
	for(i = 0; PTCodes[i] != -1; i++) {
		PTCodes[i] += ASCII_OFFSET;
	}
	
	// copy the PT codes array back into the ASCII codes array
	for(i = 0; PTCodes[i] != -1; i++) {
		decryptMe[i] = PTCodes[i];
	}
	decryptMe[i] = '\0';

	// return success
	return TRUE;

} // end - DecryptString()

//-----------------------------------------------------------------------------

int EncryptString(char* encryptMe, int a, int b, int n) {

	int i = 0;
	int PTCodes[BUFFER_SIZE];
	
	// check to make sure we are safe for encryption
	int inverseCode = ModularInverse(a, n);
	if( inverseCode == -1 || inverseCode == -2) {
		printf("You cannot encrypt with key (%d, %d)", a, b);
		printf("on a (mod %d) ring.\n", n);
		return FALSE;
	}

	// copy the ASCII array codes into the PTCodes array
	for(i = 0; encryptMe[i] != '\0'; i++) {
		PTCodes[i] = encryptMe[i];
	}
	
	// set sentinal value at end of string
	PTCodes[i] = -1;
	
	// reduce character ASCII codes to PT codes
	for(i = 0; PTCodes[i] != -1;i++) {
		PTCodes[i] -= ASCII_OFFSET;
	}
	
	
	// encrypt the string
	for(i = 0; PTCodes[i] != -1; i++) {
		PTCodes[i] = (PTCodes[i] * a + b) % n;
	}
	
	// revert PT codes to ASCII codes
	for(i = 0; PTCodes[i] != -1; i++) {
		PTCodes[i] += ASCII_OFFSET;
	}
	
	// copy the PT codes array back into the ASCII codes array
	for(i = 0; PTCodes[i] != -1; i++) {
		encryptMe[i] = PTCodes[i];
	}
	encryptMe[i] = '\0';
	
	// return success
	return TRUE;

} // end - EncryptString()

//-----------------------------------------------------------------------------

int genKey() {
	int aValue[9] = {3,5,7,9,11,17,21,23,25};
	return aValue[rand() % 8];
}

//-----------------------------------------------------------------------------

int SetCipherKey(int& a, int& b, int n, int& inverse) {

	inverse = NO_INVERSE;
	
	// integrated validation using for loop
	for( int mode = UNSET; mode == UNSET; ) {
		printf("Please select the action you wish to perform: \n\n");
		printf("1.) PICK  YOUR OWN  KEY -> (enter the # 1)\n\n");
		printf("2.) GENERATE RANDOM KEY -> (enter the # 2)\n\n");
		printf(": ");
		scanf("%d", &mode);
		ClearBuf();
		if(mode == RAND_KEY) {
			a = genKey();
			b = ( (rand() % n));
			inverse = ModularInverse(a, n);

			if(inverse == ERROR) {
				printf("Error occurred during random keygen.");
				return QUIT;
			}
			printf("Your new key is A = %d, B = %d", a, b);
			Pause();
		} 
		else if(mode == USER_KEY) {
			puts("The program will now prompt you to enter your cipher key.");
			puts("Note: The values you provide for A and B must be coprime.");
		
			puts("Please enter a numerical value for A: ");
			scanf("%d", &a);
			ClearBuf();
			puts("Please enter a numerical value for B: ");
			scanf("%d", &b);
			ClearBuf();
	
			// check to make sure we are safe for encryption
			inverse = ModularInverse(a, n);
			if( inverse == NO_INVERSE || inverse == ERROR) {
				printf("Cannot encrypt with key (%d, %d)",a,b);
				printf("on a (mod %d) ring.\n",n);
				puts("Restoring key to default...");
				a = A, b = B, inverse = INVERSE;
				Pause();
			}
		} 
		else {
			mode = UNSET;
		}
	}

	return UNSET;
}

//-----------------------------------------------------------------------------

int ModularInverse(int target, int mod) {
	
	
	// determine if the target has an inverse in this
	// particular modular system
	if( CoprimeTest(target, mod) == FALSE ) {
		return NO_INVERSE;
	}
	
	// if the target has an inverse, find it!
	for(int inverse = 1; inverse <= mod; inverse++) {
		if( (target * inverse) % mod == 1 ) {
			return inverse;
		}
	}

	// if we got through this loop and didn't find an inverse
	// something is not working properly
	return ERROR;

} // end - ModularInverse()

//-----------------------------------------------------------------------------

int IsPrime(int amIPrime) {
	
	int i = 0;
	int isPrime = TRUE;
	
	// check for border cases
	if(amIPrime <= 1) {
		isPrime = FALSE;
	}
	
	// force check the number for primality
	for(i = 2; i < amIPrime; i++) {
		if(amIPrime % i == 0)
			isPrime = FALSE;
	}

	return isPrime;
} // end - IsPrime()

//-----------------------------------------------------------------------------

int CoprimeTest(int numOne, int numTwo) {
	
	int i = 0;
	int areCoprime = TRUE; // disprove whether numbers are Coprime
	int larger = 0;
	int smaller = 0;
	
	// determine that larger of the two numbers
	if(numOne >= numTwo) {
		larger = numOne;
		smaller = numTwo;
	} else {
		larger = numTwo;
		smaller = numOne;
	}
	
	for(i = 1; i <= larger; i++) {
		// find a prime factor for numOne
		if(larger % i == 0 && IsPrime(i)) {
			// determine if numTwo is divisible by the candidate prime
			if(smaller % i == 0) {
				areCoprime = FALSE;
			}
		}
	}

	// return the result
	return areCoprime;

} // end - CoprimeTest()

//-----------------------------------------------------------------------------

void list_dir() {
	
	system("ls");
	printf("\n");
	Pause();
	
	return;
}

//-----------------------------------------------------------------------------

int SetOutputFileName(char nameOutputFile[30]) {
	memset(nameOutputFile, '\0', 30);
	puts("Warning - if the file name you select already exists, any data");
	puts("within that file will be overwritten.");
	Pause();
	puts("Note: existing data will be overwritten.");
	printf("Please enter a name for the output file: ");
	gets(nameOutputFile);
	puts("Outputfile is named: ");
	puts(nameOutputFile);
	Pause();

	return UNSET;
}

//-----------------------------------------------------------------------------

int SelectAction(int mode) {
	int action = UNSET;
	
	// while loop for integrated mode validation
	while(action == UNSET) {
		
		// display action menu
		printf("Please select the action you wish to perform: \n\n" );
		printf("1.)for SELECT   INPUT   FILE -> (enter the # 1)\n\n");
		printf("2.)for SELECT   OUTPUT  FILE -> (enter the # 2)\n\n");
		printf("3.)for GET   DIRECTORY  LIST -> (enter the # 3)\n\n");
		printf("4.)for CHOOSE NEW CIPHER KEY -> (enter the # 4)\n\n");
		printf("5.)for ENCRYPT   INPUT  FILE -> (enter the # 5)\n\n");
		printf("6.)for DECRYPT   INPUT  FILE -> (enter the # 6)\n\n");
		printf("7.)for EXIT PROGRAM -------- -> (enter the # 7)\n\n");
		printf(": ") ;
		scanf("%d", &action);
		ClearBuf();

		// range check for integrated mode validation
		if(action > QUIT || action <= UNSET) {
			action = UNSET;
			puts("Sorry, that's not a valid input.");
			Pause();
		}
		ClearScreen();
	}

	return action;
}

//-----------------------------------------------------------------------------

void Pause() {
	printf("\n");
	puts("Press any key to continue.");
	getchar();
	return;
}

//-----------------------------------------------------------------------------

// default version for module startup
int fGetClnStr(int mode, char rawPT[BUFFER_SIZE], char cleanPT[BUFFER_SIZE]) {
	char charHolder = ' ';
	int i = 0, y = 0;

	// this is a precautionary measure
	memset(rawPT, '\0', BUFFER_SIZE);
	memset(cleanPT, '\0', BUFFER_SIZE);

	// create a file handle
	FILE* inputFile = NULL;

	// open the default input file with read permission
	inputFile = fopen("input.txt", "r");

	// check to ensure the file opened
	if(inputFile == NULL) {
		printf("Error: Default input file could not be opened for reading.\n");
		return QUIT;
	}

	// read data from the file with fgetc
	for(i = 0, y = 0; ( i < BUFFER_SIZE) &&
	   ((charHolder = fgetc(inputFile)) != EOF); i++ )
	{	
		// collect raw PT Code for user
		rawPT[i] = charHolder;

		// collect clean PT Code for cipher
		if(isupper(rawPT[i])) {
			cleanPT[y++] = tolower(rawPT[i]);
		} else if(islower(rawPT[i])) {
			cleanPT[y++] = rawPT[i];
		}
	}

	// rewind the internal file pointer
	rewind(inputFile);

	// close the file
	fclose(inputFile);
	
	// exit module
	return UNSET;
}

//-----------------------------------------------------------------------------

// user input version of module
int fGetClnStr(
	int action,
	char rawPT[BUFFER_SIZE],
	char cleanPT[BUFFER_SIZE],
	char inFileName[30]) 
{
	
	// declare string manipulation
	char charHolder = ' ';
	char oldInFileName[30] = "";
	char oldRawPT[BUFFER_SIZE] = "";
	char oldCleanPT[BUFFER_SIZE] = "";
	
	// declare control variables
	int nFileCreated = FALSE;
	int i = 0, y = 0;

	// store old strings to secondary buffers to avoid
	// data loss due to failed read process
	strcpy(oldInFileName,inFileName);
	strcpy(oldRawPT,rawPT);
	strcpy(oldCleanPT,cleanPT);

	// clear primary buffers
	memset(inFileName, '\0', 30);
	memset(rawPT, '\0', BUFFER_SIZE);
	memset(cleanPT, '\0', BUFFER_SIZE);

	// create a file handle
	FILE* inputFile = NULL;


	// prompt user for input
	puts("Please enter the name of the input file: ");
	gets(inFileName);

	// open the file with read permission
	inputFile = fopen(inFileName, "r");

	// check to make sure file opened. if file does not exist, inform user
	if(inputFile == NULL) {
		printf("Unable to locate file.\n\n");
		memset(inFileName, '\0', 30);	

		// restore primary buffers to previous state by copying data
		// from secondary buffers
		strcpy(inFileName,oldInFileName);
		strcpy(rawPT,oldRawPT);
		strcpy(cleanPT,oldCleanPT);

		// clear secondary buffers for next use
		memset(oldInFileName, '\0', 30);
		memset(oldRawPT, '\0', BUFFER_SIZE);
		memset(oldCleanPT, '\0', BUFFER_SIZE);
		Pause();
		return UNSET;
		
	}
	
	// read PT from file
	for(i = 0, y = 0; ( i < BUFFER_SIZE) &&
	   ((charHolder = fgetc(inputFile)) != EOF); i++)
	{	
		// collect raw PT Code for user
		rawPT[i] = charHolder;

		// collect clean PT Code for cipher
		if(isupper(rawPT[i])) {
			cleanPT[y++] = tolower(rawPT[i]);
		} else if(islower(rawPT[i])) {
			cleanPT[y++] = rawPT[i];
		}
	}

	// if the input file exceeds the buffer, let the user know
	if(charHolder != EOF) {
		puts("Warning: Unable to read entire file. Character limit exceeded.");
		puts("\n");
		puts("Your current message is: ");
		puts(rawPT);
	}
	
	// rewind the internal file pointer
	rewind(inputFile);
	
	// close the input file
	fclose(inputFile);
	
	// clear secondary buffers for next use
	memset(oldInFileName, '\0', 30);
	memset(oldRawPT, '\0', BUFFER_SIZE);
	memset(oldCleanPT, '\0', BUFFER_SIZE);

	// exit program
	return UNSET;
}

//-----------------------------------------------------------------------------

int FileOutput(char nameOutputFile[30], char cleanPT[BUFFER_SIZE]) {

	// create a file handle
	FILE* outputFile = NULL;
	
	// open the file with write permission
	outputFile = fopen(nameOutputFile, "w");
	
	// check to ensure the file opened
	if(outputFile == NULL) {
		printf("Error: the file could not be opened for writing.\n");
		return QUIT;
	}
	
	// put some data in the file with fprintf()
	fprintf(outputFile, cleanPT);

	// close the file
	fclose(outputFile);

	// return to main
	return UNSET;
}

//-----------------------------------------------------------------------------
void ClearScreen() { for(int i = 0; i < 100; i++){puts("");} }
void ClearBuf() { while(getchar() != '\n'); }

/******************************************************************************
 END
******************************************************************************/
