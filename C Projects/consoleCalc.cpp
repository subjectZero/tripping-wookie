/******************************************************************************
Author: subjectZero                                                           *
Course: CIS111 - C Programming Language                                       *
Assignment: Programming Project #01 - Grade Calculator                        *
Date created: 29 October 2012                                                 *
Last modified: 9 August 2013                                                  *
                                                                              *
Description: This program allows the user to enter two integer operands		  *
				between -1000 and 1000 inclusive. The program then presents   *
				the user with a list of defined operations to choose from.    *
				After the user selects an operation, the program provides a   *
				result based on the appropriate operation. The user may then  *
				choose to make another calculation, or exit the program. An   *
				experiment involving modulo division is provided at the end   *
				of the program.                                               *
******************************************************************************/

// array size
#define SIZE 2

// arithmetic operations
#define UNSET		    3
#define ADDITION        4
#define SUBTRACTION     5
#define MULTIPLICATION  6
#define DIVISION        7
#define MODULUS         8

#include <stdio.h>

// PROTOTYPES
void inputInt(int&);
void validateInt(int&);
void setMode(int&, int&, int&);
void inputOp(int&, int&, char&);
void validateOp(int&, char&);
int add(int&, int&);
int subtract(int&, int&);
int multiply(int&, int&);
float divide(int&, int&);
int modulus(int&, int&);
void clearBuf(void);

// MAIN -----------------------------------------------------------------------
int
main()
{
	// DECLARATIONS
	int operands[SIZE] =  { 0 } ;
	int opFlag = UNSET ;
	
	// DETAIL LOOP
	for(char shouldCont = 'c' ; shouldCont == 'c' ||
								shouldCont == 'C'   ; opFlag = UNSET)
	{
		// Populate the operand array
		for(int i = 0; i < SIZE ; i++) {
			inputInt(operands[i]);
		}
		printf("\n");
		
		// Set mode 
		setMode(operands[0], operands[1], opFlag);
		
		// Send operands to appropriate arithmetic function then
		// display the result
		switch(opFlag) {
		case ADDITION:
			printf("%d + %d = ", operands[0], operands[1]) ;
			printf("%d\n\n", add(operands[0], operands[1]));
			break;
		case SUBTRACTION:
			printf("%d - %d = ", operands[0], operands[1]) ;
			printf("%d\n\n", subtract(operands[0], operands[1]));
			break;
		case MULTIPLICATION:
			printf("%d * %d = ", operands[0], operands[1]) ;
			printf("%d\n\n", multiply(operands[0], operands[1]));
			break;
		case DIVISION:
			printf("%d / %d = ", operands[0], operands[1]) ;
			printf("%.4f\n\n", divide(operands[0], operands[1]));
			break;
		case MODULUS:
			printf("%d %% %d = ", operands[0], operands[1]);
			printf("%d\n\n", modulus(operands[0], operands[1])) ;
			break;
		default:
			// Default used defensively
			printf("Error.\n\n");
		}

		// User can choose to quit, or can choose to perform another operation
		printf("Please enter the letter 'C' to continue, or enter anything\n");
		printf("else to quit: ");
		scanf("%c", &shouldCont);
		clearBuf();
		printf("\n");
	}
	
	return 0;
}
// FUNCTION IMPLEMENTATIONS ---------------------------------------------------

void 
inputInt(int& myInt)
{
	// User is prompted to input two valid integer operands
	printf("Please enter an integer between -1000 and 1000 inclusive: ");
	scanf("%d", &myInt);
	clearBuf();
	// Sanity check
	validateInt(myInt);
	
	return;
}

void
validateInt(int& myInt)
{
	// Sanity loop used to individually validate integer operands
	while(myInt < -1000 || myInt > 1000) {
		
		printf("I'm sorry, that's not a valid input. Please enter an\n");
		printf("integer between -1000 and 1000 inclusive: ");
		scanf("%d", &myInt);
		clearBuf();
	}
	return;
}

void 
setMode(int& myInt1, int& myInt2, int& opFlag)
{
	char myOp = ' ' ;
	// While operation not selected, have user select operation
	while(opFlag == UNSET)
	{
		inputOp(myInt1, myInt2, myOp);

		// Operation flag set based on user choice
		if(myOp == 'A' || myOp == 'a') {
			opFlag = ADDITION;
		}
		else if(myOp == 'S' || myOp == 's'   ) {
			opFlag = SUBTRACTION;
		}
		else if(myOp == 'M' || myOp == 'm'   ) {
			opFlag = MULTIPLICATION;
		}
		// Division and modulus only defined if myInt2 != 0
		else if((myOp == 'D' || myOp == 'd') &&
				 myInt2 != 0 ) {
					opFlag = DIVISION;
		}
		else if((myOp == 'O' || myOp == 'o') &&
				 myInt2 != 0 ) {
					opFlag = MODULUS;
		}
	}

	return;
}
void
clearBuf(void)
{
	while( getchar() != '\n');
}
// PICK A VALID OPERATION
void
inputOp(int& myInt1, int& myInt2, char& myOp)
{
	// User is prompted to select from a list of defined operations
	printf("Please enter the operation to go in the blank space: \n\n");
	printf("A - ADDITION\n");
	printf("S - SUBTRACTION\n");
	printf("M - MULTIPLICATION\n");

	// If myInt2 = zero, division and modulus neither defined nor listed 
	if(myInt2 != 0) {
		printf("D - DIVISION\n");
		printf("O - MODULUS\n");
	}
	printf("\n");
	printf("%d ___ %d = ", myInt1, myInt2);
	scanf("%c", &myOp);
	clearBuf();

	return;
}

// ARITHMETIC FUNCTIONS
int add(int& myInt1, int& myInt2) {
	return myInt1 + myInt2;
}

int subtract(int& myInt1, int& myInt2) {
	return myInt1 - myInt2;
}

int multiply(int& myInt1, int& myInt2) {
	return myInt1 * myInt2;
}

float divide(int& myInt1, int& myInt2) {
	// Expression cast as float to avoid loss of data
	return float(myInt1) / myInt2;
}

int modulus(int& myInt1, int& myInt2)  {
	return myInt1 % myInt2;
}


/******************************************************************************
MODULO EXPERIMENT: 
a)
9 % 2 = 1
b)
-9 % 2 = -1
c)
9 % -2 = 1
d)
-9 % -2 = -1

Modulo in C is implementation defined. If the dividend is a positive integer,
then C arbitrarily outputs a positive remainder. However, should the dividend
be negative, then the remainder will be negative as well. In short; the sign
of the remainder will always be the same sign as the dividend.
******************************************************************************/
