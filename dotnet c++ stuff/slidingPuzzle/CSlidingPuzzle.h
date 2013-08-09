# include <iostream>
# include <string>
# include <conio.h>
# include <ctype.h>
# include <Windows.h>
# include <stdlib.h>
# include <time.h>
using namespace std;

# ifndef __CSLIDING_PUZZLE__
class //-----------------------------------------------------------------------
CSlidingPuzzle
{
	private:
		// ints
		int blank_y;
		int blank_x;
		int lastEvent;
		// structs
		struct
		ArrowKeys
		{
			int SlideUp, SlideDown, SlideRight, SlideLeft;
		}
		BoardEvent;
		// enums
		enum eventCodes {QUIT = 'q', SCRAMBLE = 32, RESET = 'r', CALIBRATE = 'c'};
		enum keyPress {W = 'w', S = 's', D = 'd', A = 'a'};
		enum directions {UP, DOWN, LEFT, RIGHT};
		enum Colors {WHITE = 15, GREEN = 10, RED = 12, YELLOW = 14} oColor;
		enum boardStuff {ROWS = 3, COLS = 3, BLANK = 0};
		// private methods
		int theBoard[ROWS][COLS];
		void InitializeBoard();
		bool IsBoardSolved();
		void GetBlankLocation();
		bool IsScrambled();
		void ScrambleBoard();
		bool SlideTile(int);
		bool CalibrateBoard(); // credit goes to Miles for the calibration idea
		int GetKeyStroke();

	public:
		// public methods
		CSlidingPuzzle();
		void PrintBoard();
		bool SetEvent();
}; // end CSlidingPuzzle definition
# endif