/******************************************************************************
* File:          PrimeFactorizor.cpp
* Author:        subjectZero
* Date Created:  02/21/2013
* Last Modified: 02/22/2013 
* Description:   This file contains the source code for a c++ program capable
                 of accepting an integer from the user and factoring it into
				 the product of primes.
******************************************************************************/

# include <iostream>
using namespace std;

// PROTOTYPES
int GetInt(char*);
int IsPrime(int);
int DomainCheck(int);
int FactorInt(int);

// MAIN() =====================================================================
int
main()
{
	// declarations
	int myInt = 0;
	char inputPrompt[45] = "Please enter a number: ";
	
	// get the number from the user
	myInt = GetInt(inputPrompt);
	
	// do a domain check
	if(DomainCheck(myInt))
	{   // factor the int
		FactorInt(myInt);
	}
	return 0;
} // end main()

// FUNCTION IMPLEMENTATIONS ===================================================

// GetInt() -------------------------------------------------------------------
int
GetInt(char* prompt)
{
	// local declarations
	int myInt = 0;
	// get the number from the user
	cout << prompt;
	cin  >> myInt;
	cout << endl;

	return myInt;
} // end GetInt()

// IsPrime() ------------------------------------------------------------------
int
IsPrime(int amIPrime)
{
	// local declarations
	bool isPrime = true;

	// check for border cases
	if(amIPrime <=1) {
		isPrime = false;
	}

	// force check the number for primality
	for(int i = 2; i < amIPrime; i++)
	{
		if(amIPrime % i == 0)
		{
			isPrime = false;
		}
	}

	return isPrime;
} // end IsPrime()

// FactorInt() ----------------------------------------------------------------
int
FactorInt(int myInt)
{
	// factor the composite number
	for(int i = 2; i <= myInt; i++)
	{
		if(myInt % i == 0)
		{
			if(IsPrime(i))
			{
				cout << i 
					 << "has been found as a prime factor." 
					 << endl;
			}
			myInt /= i;
			i = 1;
		}
	}

	return 0;
} // end FactorInt()

// DomainCheck() --------------------------------------------------------------
int
DomainCheck(int myInt)
{
	// local declarations
	int returnCode = 0;

	if(myInt <= 1)
	{   // is myInt a positive natural number but not 1?
		cout << myInt
			 << " is out of our field of consideration."
			 << endl;
	}
	else if(IsPrime(myInt))
	{   // is it a prime number? if it is, we can't factor it
		cout << myInt
			 << " is a PRIME number."
			 << endl;
	}
	else if(!IsPrime(myInt))
	{   // if myInt is a composite int greater than 1, we factor 
		returnCode = 1;
		cout << myInt
			 << " is a COMPOSITE number."
			 << endl;
		     
	}
	else
	{   // an exception has occurred if we've made it this far
		returnCode = -1;
	}

	return returnCode;
} // end DomainCheck()
