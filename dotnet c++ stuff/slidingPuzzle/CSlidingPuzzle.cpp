# include "CSlidingPuzzle.h"

// CTOR // --------------------------------------------------------------------
CSlidingPuzzle::CSlidingPuzzle()
{
	InitializeBoard();
	oColor = WHITE;
	srand(unsigned int (time(NULL)));

	CalibrateBoard();
	system("cls");


} // end CSlidingPuzzle::CSlidingPuzzle()

void // -----------------------------------------------------------------------
CSlidingPuzzle::InitializeBoard()
{
	for(int i = 0; i < ROWS; ++i)
	{
		for(int j = 0; j < COLS; ++j)
		{   // populate the board with numbers 1 to 9 then 0
			theBoard[i][j] = (3 * i + j + 1 ) % 9;
		}
	}
} // end CSlidingPuzzle::InitializeBoard()

bool // -----------------------------------------------------------------------
CSlidingPuzzle::IsBoardSolved()
{
	int solvedElements = 0;
	for(int i = 0; i < ROWS; ++i)
	{
		for(int j = 0; j < COLS; ++j)
		{   // tally correctly positioned elements
			if(theBoard[i][j] == (3 * i + j + 1 ) % 9)
				++solvedElements;
		}
	}
	// compare tally to number of elements
	if(solvedElements == ROWS * COLS)
		return true;
	else
		return false;
} // end CSlidingPuzzle::IsBoardSolved()

void // -----------------------------------------------------------------------
CSlidingPuzzle::GetBlankLocation()
{
	for(int i = 0; i < COLS; ++i)
    {
        for(int j = 0; j < ROWS; ++j)
        {
            if(theBoard[i][j] == BLANK)
            {
                blank_x = j;
                blank_y = i;
                break;
            }
        }
    }
} // end CSlidingPuzzle::GetBlankLocation()

bool // -----------------------------------------------------------------------
CSlidingPuzzle::IsScrambled()
{
	for(int i = 0; i < ROWS; ++i)
    {
        for(int j = 0; j < COLS; ++j)
        {
			// if a piece is in correct position, then board not scrambled
            if(theBoard[i][j] == (3 * i + j + 1 ) % 9)
                return false;
        }
    }
	// if we've made it this far without returning, then board is scrambled
	return true;

}
void // -----------------------------------------------------------------------
CSlidingPuzzle::ScrambleBoard()
{
	InitializeBoard();
	do // a series of random moves to create solvable and scrambled board
	{
		SlideTile(rand() % 4);

	}
	while( !(IsScrambled()) );
} // end ScrambleBoard()


bool // -----------------------------------------------------------------------
CSlidingPuzzle::SlideTile(int direction)
{

	GetBlankLocation();


	// slide tiles if movement key is pressed
    if(direction == UP && blank_y < ROWS - 1)
    {
        theBoard[blank_y][blank_x] = theBoard[blank_y + 1][blank_x];
        theBoard[blank_y + 1][blank_x] = BLANK;
    }
    else if(direction == DOWN && blank_y > 0)
    {
        theBoard[blank_y][blank_x] = theBoard[blank_y - 1][blank_x];
        theBoard[blank_y - 1][blank_x] = BLANK;
    }
    else if(direction == RIGHT && blank_x > 0)
    {
        theBoard[blank_y][blank_x] = theBoard[blank_y][blank_x - 1];
        theBoard[blank_y][blank_x - 1] = BLANK;
    }
    else if(direction == LEFT && blank_x < COLS - 1)
    {
        theBoard[blank_y][blank_x] = theBoard[blank_y][blank_x + 1];
        theBoard[blank_y][blank_x + 1] = BLANK;
    }
    else
    {
        return false;
    }
    return true;
} // end SlideTile()

bool // -----------------------------------------------------------------------
CSlidingPuzzle::SetEvent()
{
	PrintBoard();
	int keyStroke = GetKeyStroke();
	cout << keyStroke << endl;
	
	system("cls");
	if(keyStroke == BoardEvent.SlideUp || keyStroke == W)
	{   // take appropriate action
		SlideTile(UP);
	}
	else if(keyStroke == BoardEvent.SlideDown || keyStroke == S)
	{   // take appropriate action
		SlideTile(DOWN);
	}
	else if(keyStroke == BoardEvent.SlideRight || keyStroke == D)
	{   // take appropriate action
		SlideTile(RIGHT);
	}
	else if(keyStroke == BoardEvent.SlideLeft || keyStroke == A)
	{   // take appropriate action
		SlideTile(LEFT);
	}
	else if(keyStroke == QUIT)
	{   // take appropriate action
		return false;
	}
	else if(keyStroke == SCRAMBLE)
	{   // take appropriate action
		ScrambleBoard();
	}
	else if(keyStroke == RESET)
	{   // take appropriate action
		InitializeBoard();
	}
	else if(keyStroke == CALIBRATE)
	{   // credit goes to Miles for calibration idea
		CalibrateBoard();
	}
	return true;
}

void // -----------------------------------------------------------------------
CSlidingPuzzle::PrintBoard()
{
	bool boardSolved = IsBoardSolved();
	int puzzleColor;
	// used to create dynamic UI)
    string UIStrings[ROWS] = {" | |  Up:    W          ^",
                              " | |  Down:  S          |",
                              " | |  Left:  A       A<--->D"};
    string solutionMessage[2] = {" Not     ", "         "};
	// get the handle for the console
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// set the puzzle color based on board state
	if(boardSolved)
		puzzleColor = GREEN;
	else
		puzzleColor = RED;

	SetConsoleTextAttribute(hConsole, WHITE);
	// begin to print user interface
	cout << "========================================" << endl
			<< "        Realtime Sliding Puzzle         " << endl
				<< "========================================" << endl
					<< " Puzzle   |  Direction Keys:"             << endl
						<< "+-------+ |                    W"         << endl;
	// print sliding puzzle pieces
    for(int i = 0; i < ROWS; ++i)
    {
        cout << "|";
        for(int j = 0; j < COLS; ++j)
        {
            if(theBoard[i][j] == 0)
			{
                cout << "  ";
			}
            else
			{   // if the board is solved, but position correct, then...
				if(!(boardSolved) && theBoard[i][j] == (3 * i + j + 1 ) % 9)
				{   // display pieces in yellow
					SetConsoleTextAttribute(hConsole, YELLOW);
				}
				else
				{   // otherwise just use the predetermined puzzle color 
					SetConsoleTextAttribute(hConsole, puzzleColor);
				}
                cout << " " << theBoard[i][j];
				SetConsoleTextAttribute(hConsole, WHITE);
			}
        }
        cout << UIStrings[i] << endl;
    }
	// continue to print user interface
    cout << "+-------+ |  Right: D          |"   << endl
			<< solutionMessage[boardSolved]
				<< " |                    v"			 << endl
					<< " Solved.  |  Quit:  Q          S"	<< endl;
	cout << "          |  Calibrate: C"					 << endl
			<< "          |  Reset: R"						<< endl
				<< "          |  Scramble: spacebar"			<< endl
					<< "----------+-----------------------------"    << endl;
	cout << "To slide the puzzle pieces, press a"      << endl
			<< "    direction key from the list above."    << endl
				<< "To scramble the tiles, press the space"    << endl
					<< "    bar. Press Q to quit."                 << endl;
							// end UI code
} // end PrintBoard()

bool // -----------------------------------------------------------------------
CSlidingPuzzle::CalibrateBoard()
{   // credit goes to Miles for the idea of calibration screen
	cout << "Please press your up arrow key.\n\n";
	BoardEvent.SlideUp = GetKeyStroke();
	cout << "Please press your down arrow key.\n\n";
	BoardEvent.SlideDown = GetKeyStroke();
	cout << "Please press your right arrow key.\n\n";
	BoardEvent.SlideRight = GetKeyStroke();
	cout << "Please press your left arrow key.\n\n";
	BoardEvent.SlideLeft = GetKeyStroke();
	system("cls");

	return 0;
}

int // ------------------------------------------------------------------------
CSlidingPuzzle::GetKeyStroke()
{
	int keyPress;
	keyPress = getch();
	if(!(keyPress) || keyPress == 224)
		keyPress = getch();

	return tolower(keyPress);
} // end GetKeyStroke()