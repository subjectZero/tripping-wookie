
/******************************************************************************
** File:        main.cpp
** Project:     Sort Time Analysis
** Author:      subjectZero
** Description:
**              This c++ source file contains the driver code for a
**              program that compares the strengths and weaknesses of
**				three algorithms - bubble, selection, and insertion sort - 
**				by implementing them on integer arrays of varying size.
******************************************************************************/

# include <iostream>
# include "CSorting.h"
using namespace std;

# define NUM_FILE_100K "NumFile100K.txt"
# define NUM_FILE_25K "NumFile25K.txt"
# define NUM_FILE_500 "NumFile500.txt"
# define NUM_FILE_5K "NumFile5K.txt"

int
main()
{

	CSorting mySorter;

	if( mySorter.SortAnalysis(NUM_FILE_500) )
		cout << "Unable to sort" << NUM_FILE_500 << endl;
	if( mySorter.SortAnalysis(NUM_FILE_5K) )
		cout << "Unable to sort" << NUM_FILE_5K << endl;
	if( mySorter.SortAnalysis(NUM_FILE_100K) )
		cout << "Unable to sort" << NUM_FILE_100K << endl;
	if( mySorter.SortAnalysis(NUM_FILE_25K) )
		cout << "Unable to sort" << NUM_FILE_25K << endl;

	return EXIT_SUCCESS;

}
