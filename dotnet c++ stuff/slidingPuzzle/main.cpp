/******************************************************************************
** File:        main.cpp
** Program:     Sliding Tile Puzzle Simulator
** Author:      subjectZero
** Date:        3/17/2013
** Description:
**              This c++ source file contains the main driver program for a
**              real time, object oriented sliding tile puzzle simulator.
******************************************************************************/

# include "includes.h"
# include "CSlidingPuzzle.h"

using namespace std;

int
main()
{
	
	CSlidingPuzzle CMyPuzzle;

	while(CMyPuzzle.SetEvent());

	
	return 0;
}
