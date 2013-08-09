/******************************************************************************
** File:          numericalAnalysisEngine.cpp
** Author:        subjectZero
** Date Created:  3/3/2013
** Last Modified: 3/3/2013
** Description:
**                This file contains the c++ source code for a command line
				  program that determines the  largest and smallest numbers
				  within  an integer array.  The program  also converts any
				  lowercase  letters  within a string  of  characters  into
				  uppercase letters.
******************************************************************************/

// INCLUDES
#include <iostream>
using namespace std;

// DEFINES
#define INT_MAX  20
#define CHAR_MAX 50

// PROTOTYPES
int ReturnLargest(int[], int);
int ReturnSmallest(int*, int);
int ToUpperCase(char*);

int
main()
{
	// declarations
	int intArray[INT_MAX] =  { 1, -12,  24, -16,  25, -54,  35,  -8,  18, -60, 
	                          55, -36,  65, -70, -75, -96,  85, -54,  57, -60};
	char charArray[CHAR_MAX] = "The QuiCk BroWn FOx JuMPEd OvER the LAZY DoG.";
	int count;
	
	// find and display largest integer in intArray[]
	cout << "The largest int is: "
			<< ReturnLargest(intArray, INT_MAX)
				<< endl << endl;

	// find and display smallest integer in intArray[]
	cout << "The smallest int is: "
			<< ReturnSmallest(intArray, INT_MAX)
				<< endl << endl;

	// display the contents of charArray[] before conversion
	cout << "Before being converted to all caps, charArray"
			<< endl << "contains \""
				<< charArray
					<< endl << endl;

	// convert charArray[] to all caps: keep count
	count = ToUpperCase(charArray);

	// display the newly converted string
	cout << "After being converted to all caps, charArray"
			<< endl << "contains \""
				<< charArray
					<< endl << endl;

	// display conversion count
	cout << "A total of "
			<< count
				<< " letters were converted from lowercase to uppercase."
					<< endl << endl;

	return 0;
} // end - main()

// FUNCTION IMPLEMENTATIONS

int
ReturnLargest(int intArray[], int arrMax)
{
	// priming read
	int greatestInt = intArray[0];

	// find the greatest integer in the array
	for(int i = 1; i < arrMax; i++)
	{
		if(intArray[i] > greatestInt) 
		{
			greatestInt = intArray[i];
		}
	}
	return greatestInt;
} // end - ReturnLargest()

int
ReturnSmallest(int* intArray, int arrMax)
{
	// priming read
	int leastInt = *intArray;

	// find the least integer in the array
	for(int i = 1; i < arrMax; i++)
	{
		if( *(intArray + i) < leastInt)
		{
			leastInt = *(intArray + i);
		}
	}
	return leastInt;
} // end - ReturnSmallest()

int
ToUpperCase(char* myString)
{
	// declarations
	int count = 0;

	// convert all lowercase chars in myString uppercase
	for(int i = 0; *(myString + i) != '\0'; i++)
	{
		if(myString[i] >= 'a' && myString[i] <= 'z')
		{
			*(myString + i) -= 32;
			count++; // count conversions
		}
	}
	return count;
} // end - ToUpperCase()
