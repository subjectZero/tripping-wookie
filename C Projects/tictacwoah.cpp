
 
// INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef __TRUE_FALSE__
#define __TRUE_FALSE__
#define TRUE            1
#define FALSE           0
#endif

#ifndef __HEADS_TAILS__
#define __HEADS_TAILS__
#define HEADS           1
#define TAILS           0
#endif
 
#define UNCERTAINTY    ' '

// BOARD DIMENSIONS
#define MAXROWS         9
#define MAXCOLS         9
#define MIN_ROWS        3
#define MIN_COLS        3

// MARKER CODES
#define MARKONE        'X'
#define MARKTWO        'O'
#define BLANK          ' '
#define DEADSPACE      '*'

// VICTORY CODES
#define NOWIN           0 
#define MARKONEVICTORY  1
#define MARKTWOVICTORY  2
#define TIE             3 
#define ERROR           4 
#define EPIC_FAIL       5

// GAME PARAMETER CODES
#define WIN_REQUIREMENT 3

// GAMESTATES
#define GAMEOVER	    0
#define PLAYERONETURN   1
#define PLAYERTWOTURN   2

// PROTOTYPES

// board manipulation
void InitializeBoard(char[MAXROWS][MAXCOLS]);
void SetBoard(char[MAXROWS][MAXCOLS], int&, int&);
void SetRowsCols(int&);
int  ValidateRowsCols(int);
void DispBoard(char board[MAXROWS][MAXCOLS], int, int);
void PrntColsLabel(int cols);
void PrntRowsLabel(int&, int, int);
void PlayerMove(int, char, char [MAXROWS][MAXCOLS], int, int);
int  InputRow(int, char);
int  InputCol(int, char);

// game controls
void SetMarksToWin(int& , int, int);
void SetFirstMove(int&, int&, int&);
void PromptMoveOrForfeit(int &);
void VictoryCheck(int, char[MAXROWS][MAXCOLS], int, int, int&);
void ScanFTW(char, int, int, int, char[MAXROWS][MAXCOLS], int&, int, int);
void DispVictryTxt(int);
void InputWinReq(int&, int);
void ValidateWinReq(int&, int);


// misc
void DisplayTitlePage();
void PauseGame();
int  FlipACoin();
void ClearBuf();
void ClearScreen();

//-| MAIN |--------------------------------------------------------------------

int main () {
	
	srand((unsigned int)time(NULL));

	// max game parameters
	char board[MAXROWS][MAXCOLS];
	int winRequirement = WIN_REQUIREMENT;
	int rows = MAXROWS;
	int cols = MAXCOLS;

	// state declarations
	int gameState = PLAYERONETURN;
	int victoryCode = EPIC_FAIL;
	int symbol = MARKONE;
	int forfeit = FALSE;
	int winIfForfeit = MARKTWOVICTORY;
	
	// set up the game
	DisplayTitlePage();
	InitializeBoard(board);
	SetBoard(board, rows, cols);
	SetMarksToWin(winRequirement, rows, cols);
	
	// determine who gets first move
	SetFirstMove(symbol, gameState, winIfForfeit);

	
	// play the game
	while(gameState != GAMEOVER)
	{
		
		// announce which player goes next
		DispBoard(board, rows, cols);
		printf("Player %d's turn.\n\n", gameState);
		PauseGame();
		
		// accept player move or forfeit 
		DispBoard(board, rows, cols);
		PromptMoveOrForfeit(forfeit);
		if(forfeit == 'F' || forfeit == 'f') {
			printf("Player %d forfeits.", gameState);
			victoryCode = winIfForfeit;
		}
		else {
			// check for victory
			PlayerMove(gameState, symbol, board, rows, cols);
			VictoryCheck(winRequirement, board, rows, cols, victoryCode);	
		}
		// display victory message
		DispBoard(board, rows, cols);
		DispVictryTxt(victoryCode);

		// change game state
		if(victoryCode == NOWIN) {
			// switch players
			switch(gameState) {
			case PLAYERONETURN:
				gameState = PLAYERTWOTURN;
				symbol = MARKTWO;
				winIfForfeit = MARKONEVICTORY;
				break;
			case PLAYERTWOTURN:
				gameState = PLAYERONETURN;
				symbol = MARKONE;
				winIfForfeit = MARKTWOVICTORY;
				break;
			default:
				perror("tictacwoah : gamestate");
				exit(1);
			}
		}
		// end game
		else {
			gameState = GAMEOVER;
		}
	}
	
	
	return 0;
}
//-| FUNCTION IMPLEMENTATIONS |------------------------------------------------

// BOARD CONTROLS

void InitializeBoard(char board[MAXROWS][MAXCOLS]) {
	// board initialized to deadspace
	for(int y = 0; y < MAXROWS; y++) {
		for(int x = 0; x < MAXCOLS; x++) {
			board[y][x] = DEADSPACE;
		}
	}
	return;
}

void DispBoard(char board[MAXROWS][MAXCOLS],int rows,int cols) {
	
	// clear the screen
	ClearScreen();

	// heading
	printf("*******************");
	printf(" Tic Tac Toe");
	printf("*******************\n\n");
	PrntColsLabel(cols);
	// left margin
	printf("         ");

	// column numbers
	for(int x = 1; x <= cols ; x++) {
		printf("%-4d", x);
	}
	printf("\n");

	// left margin
	printf("       +");

	// horizontal spacers
	for(int x = 0; x < cols; x++){
			printf("---+");
	}
	printf("\n");

	// rows and columns with verticle spacers
	for(int y = 0, k = 0; y < rows; y++) {

		// print the ROWS label
		PrntRowsLabel(k, y, rows);

		// print the ROW numbers
		printf("%3d |", (y+1));

		// print the spaces
		for(int x = 0; x < cols; x++){
			printf("%2c |", board[y][x]);
		}
		printf("\n       +");
		for(int y = 0; y < cols; y++){
			printf("---+");
		}
		printf("\n");
	}
	printf("\n");

	return;
}

void PrntColsLabel(int cols) {
	// appearance of COLUMNS label changes depending on the rows specified
	switch(cols) {
	case 3:
		printf("\n        C O L U M N\n\n");
		break;
	case 4:
		printf("\n         C O L U M N S\n\n");
		break;
	case 5:
		printf("\n            C O L U M N\n\n");
		break;
	case 6:
		printf("\n          C  O  L  U  M  N  S\n\n");
		break;
	case 7:
		printf("\n           C   O   L   U   M   N\n\n");
		break;
	case 8:
		printf("\n              C  O  L  U  M  N  S\n\n");
		break;
	case 9:
		printf("\n             C   O   L   U   M   N   S\n\n");
		break;
	default:
		perror("tictacwoah : col labels");
		exit(1);
	}
	return;
}

void PrntRowsLabel(int& k, int y, int rows) {
	char rowsLabel[MAXROWS] = "ROWS";
	//printf("  ");
	// algorithm for proper ROW label formatting
	if(rows <= 4) {
		printf("%3c", rowsLabel[k++]);
	}
	else if(rows <= 6 && y > 0 && y < rows - 1) {
		printf("%3c", rowsLabel[k++]);
	}
	else if((rows == 7 || rows == 9) && y % 2 != 0) {
		printf("%3c", rowsLabel[k++]);
	}
	else if(rows == 8 && y > 1 && y < 7) {
		printf("%3c", rowsLabel[k++]);
	}
	else {
		printf("   ");
	}

	return;
}

// PLAYER MOVE

void 
PlayerMove(
	int gameState,
	char symbol,
	char board[MAXROWS][MAXCOLS],
	int rows,
	int cols)
{
	int move2Row = 0, move2Col = 0;
	int moveValid = FALSE;

	// validate and implement player move
	while(moveValid == FALSE)
	{
		
		// input player move
		DispBoard(board, rows, cols);
		move2Row = InputRow(gameState, symbol);
		DispBoard(board, rows, cols);
		move2Col = InputCol(gameState, symbol);

		// player move within board parameters
		if (move2Row < rows && move2Row >= 0 &&
			move2Col < cols && move2Col >= 0   )
		{
				// player moves to blank space
				if (board[move2Row][move2Col] == BLANK)
				{		
					board[move2Row][move2Col] = symbol;
					DispBoard(board, rows, cols);
					printf("Player %d moves to ROW %d, ", gameState, move2Row);
					printf("COLUMN %d.\n\n", move2Col);
					moveValid = TRUE;
					break;
				}

				// player attemts to move to a space they already control
				else if(board[move2Row][move2Col] == symbol)
				{
					DispBoard(board, rows, cols);
					printf("You already have a piece there!\n\n");
					printf("Press any key to try again.");
					getchar();
				}
				else if (board[move2Row][move2Col] != BLANK)
				{
					DispBoard(board, rows, cols);
					printf("Hold it! Your opponent has already taken\n");
					printf("that space! Press any key to try again.");
					getchar();
				}
		}
		else
		{
			DispBoard(board, rows, cols);
			printf("You're trying to move somewhere that's not\n");
			printf("even on the board! Press any key to try again.");
			getchar();
		}
	}

	return;
}

int InputRow(int gameState, char symbol)
{
	int move2Row = 0;
	printf("Please enter row number: ");
	scanf("%d", &move2Row);
	ClearBuf();
	return move2Row - 1;

}

int InputCol(int gameState, char symbol)
{
	int move2Col = 0;
	printf("Please enter column number: ");
	scanf("%d", &move2Col);
	ClearBuf();
	return move2Col - 1;
}

void
VictoryCheck(
	int winRequirement,
	char board[MAXROWS][MAXCOLS],
	int rows,
	int cols,
	int& victoryCode)
{
	int marksInRow  = 0;
	int fBlankSeen  = FALSE;
	int fMarkOneWin = FALSE;
	int fMarkTwoWin = FALSE;

	for(int y = 0; y < rows; y++)
	{
		for(int x = 0; x < cols; x++)
		{
			
			// check to see if board is blank
			if(board[y][x] == BLANK)
			{
				fBlankSeen = TRUE;
			}
			// scan for MARKONE victory
			else if(board[y][x] == MARKONE)
			{
				ScanFTW(
					MARKONE,
					y,
					x,
					winRequirement,
					board,
					fMarkOneWin,
					rows,
					cols);
			}
			// scan for MARKTWO victory
			else if(board[y][x] == MARKTWO)
			{
				ScanFTW(
					MARKTWO,
					y,
					x,
					winRequirement,
					board,
					fMarkTwoWin,
					rows,
					cols);
			}
		}
	}
			
	// SET VICTORY CODE
	if(fMarkOneWin  ==  FALSE && fMarkTwoWin  ==  FALSE)
	{
		// game continues - no winner, yet board not full
		if(fBlankSeen == TRUE)
		{
			victoryCode = NOWIN;
		}
		// tie - no winner, but board is full
		else if(fBlankSeen == FALSE)
		{
			victoryCode = TIE;
		}
		else 
		{
			perror("tictacwoah : victory check failed");
			exit(1);
		}
	}
	// player 1 victory
	else if(fMarkOneWin == TRUE && fMarkTwoWin == FALSE)
	{
		victoryCode = MARKONEVICTORY;
	}
	// player 2 victory
	else if(fMarkOneWin == FALSE && fMarkTwoWin == TRUE)
	{
		victoryCode = MARKTWOVICTORY;
	}
	// error - both players seem to have won 
	else if(fMarkOneWin == TRUE && fMarkTwoWin == TRUE )
	{
		victoryCode = ERROR;
	}
	return;
}


void
ScanFTW(
	char mark,
	int y,
	int x,
	int winRequirement, 
	char board[MAXROWS][MAXCOLS],
	int& fMarkWin,
	int rows,
	int cols)
{
	int marksInRow = 0;
		
	// horizontal scan
	if(x - (winRequirement - 1) >= 0)
	{
		for(int i = 0; i < winRequirement; i++)
		{
			if (board[y][x - i] == mark)
			{
				marksInRow++;
			}
			if(marksInRow == winRequirement)
			{
				fMarkWin = TRUE;
			}
		}
		marksInRow = 0;
	}
				
	// verticle scan
	if(y - (winRequirement - 1) >= 0)
	{
		for(int i = 0; i < winRequirement; i++)
		{
			if (board[y - i][x] == mark)
			{
				marksInRow++;
			}
			if(marksInRow == winRequirement)
			{
				fMarkWin = TRUE;
			}
		}
		marksInRow = 0;
	}
				
	// negative slope diagonal scan
	if(y + (winRequirement - 1) < rows &&
	   x + (winRequirement - 1) < cols   )
	{
		for(int i = 0; i < winRequirement; i++)
		{
			if (board[y + i][x + i] == mark)
			{
				marksInRow++;
			}
			if(marksInRow == winRequirement) {
				fMarkWin = TRUE;
			}
		}
		marksInRow = 0;
	}

	// positive slope diagonal scan
	if(y + (winRequirement - 1) < rows &&
	   x - (winRequirement - 1) >= 0     )
	{
		for(int i = 0; i < winRequirement; i++)
		{
			if (board[y + i][x - i] == mark)
			{
				marksInRow++;
			}
			if(marksInRow == winRequirement)
			{
				fMarkWin = TRUE;
			}
		}
		marksInRow = 0;
	}
	return;
}

void DispVictryTxt(int victoryCode) {
	
	// display the victory condition results
	switch(victoryCode) {
	case NOWIN:
		printf("There is still no winner.\n\n");
		break;
	case MARKONEVICTORY:
		printf("MARKONE has won the game.\n\n");
		break;
	case MARKTWOVICTORY:
		printf("MARKTWO has won the game.\n\n");
		break;
	case TIE:
		printf("The game is a draw.\n\n");
		break;
	case ERROR:
		printf("Something bad happened... MARKONE and MARKTWO have\n");
		printf("both won. The BAN HAMMER approaches.\n\n");
		break;
	case EPIC_FAIL:
		printf("Something bad happened... VictoryCheck() has produced\n" );
		printf("an impossible combination of return code indicators.\n\n");
		break;
	default:
		perror("tictacwoah : DispVictryTxt");
		exit(1);
	}
	PauseGame();
}

void SetBoard(char board[MAXROWS][MAXCOLS], int& rows, int& cols) {
	// user given instructions on how to set up the board
	printf("You will now be prompted to select how many\n");
	printf("rows and how many columns the board should have.\n\n");
	PauseGame();
	ClearScreen();
	
	// for usability, emphasis is placed on specifying min/max
	// board dimimensions
	printf("Important: The board must have, at minimum, 3 ROWS\n");
	printf("and 3 COLUMNS.\n\n");
	PauseGame();
	ClearScreen();
	printf("The board may have up to, at maximum, 9 ROWS\n");
	printf("and 9 COLUMNS.\n\n");
	PauseGame();
	ClearScreen();

	// user prompted to input number of rows
	printf("How many rows should the board have?\n\n");
	SetRowsCols(rows);
	rows = ValidateRowsCols(rows);

	// user prompted to input number of columns
	printf("How many columns should the board have?\n");
	SetRowsCols(cols);
	cols = ValidateRowsCols(cols);
	
	// set board playable area
	for(int y = 0; y < rows; y++) {
		for(int x = 0; x < cols; x++) {
			board[y][x] = BLANK;
		}
	}

	return;
}

void SetRowsCols(int& RowsCols) {
	printf("Please enter between a number between 3 and 9 inclusive: ");
	scanf("%d", &RowsCols);
	ClearBuf();
	return;
}


int ValidateRowsCols(int RowsCols) {
	// bounds for rows and cols identical,
	// validate with rows
	while (RowsCols < MIN_ROWS || RowsCols > MAXROWS) {
		printf("I'm sorry, that's not a valid entry.\n\n");
		SetRowsCols(RowsCols);
	}
	ClearScreen();
	return RowsCols;
}

void SetMarksToWin(int& winRequirement, int rows, int cols) {
	ClearScreen();
	// declare variable for winReq restrictions
	int winReqMax = 0;
	
	// set winRequirement restrictions
	if (rows < cols) {
		winReqMax = rows;
	}
	// at this point we know that cols >= rows, so we use value of cols
	else  {
		winReqMax = cols;
	}

	// inform user of winRequirement restrictions
	printf("You may choose how many consecutive marks will be\n\n");
	printf("required for a victory.\n\n");
	printf("However, you must choose between 3 and %d ", winReqMax);
	printf("consecutive marks.\n\n");
	PauseGame();
	ClearScreen();

	// input winRequirement and validate it
	InputWinReq(winRequirement, winReqMax);
	ValidateWinReq(winRequirement, winReqMax);

	return;
}

void InputWinReq(int& winRequirement, int winReqMax) {
	ClearScreen();
	printf("Please enter a win requirement ranging from 3 ");
	printf("to %d inclusive: ", winReqMax);
	scanf("%d", &winRequirement);
	ClearBuf();
	ClearScreen();
	return;
}

void ValidateWinReq(int& winRequirement, int winReqMax) {
	while(winRequirement < MIN_ROWS || winRequirement > winReqMax) {
		printf("I'm sorry, that's not a valid entry.\n");
		PauseGame();
		InputWinReq(winRequirement, winReqMax);
	}
}

void PromptMoveOrForfeit(int& forfeit) {
	printf("Enter the letter \"F\" to forfeit.\n");
		printf("Enter any other character to make a move: \n");
		scanf("%c", &forfeit);
		ClearBuf();
		ClearScreen();
}


// MISC
void DisplayTitlePage() {
	ClearScreen();
	// header bar
	for(int i = 0; i < 40; i++) {
		printf("*");
	}
	printf("\n\n\n");
	printf("%11cTIC-TAC-TOE WOAH!!!\n\n\n\n\n\n", UNCERTAINTY);
	printf("%11cAuthor: subjectZero\n\n\n\n\n\n", UNCERTAINTY);
	printf("%5c <website url will go here>\n\n\n", UNCERTAINTY);

	// footer bar
	for(int i = 0; i < 40; i++) {
		printf("*");
	}
	printf("\n\n");
	// prompt the user to play tic tac toe
	printf("Press any key to start playing...");
	getchar();
	printf("\n");
	// clear the screen
	ClearScreen();

	return;

}

void PauseGame() {
	printf("Press any key to continue...");
	getchar();
	return;
}

void ClearScreen() {
	for(int i = 0; i < 100; i++) {
		printf("\n");
	}
}
void ClearBuf() {
	while( getchar() != '\n');
}

void SetFirstMove(int& symbol, int& gameState, int& winIfForfeit) {
	int firstMove = 0;
	firstMove = FlipACoin();
	printf("Press any key to flip a coin to determine\n\n");
	printf("which player goes first...");
	getchar();
	ClearScreen();
	switch(firstMove) {
	case HEADS:
		printf("The result was HEADS.\n\n");
		printf("Player 1 goes first.");
		gameState = PLAYERONETURN;
		symbol = MARKONE;
		winIfForfeit = MARKTWOVICTORY;
		break;
	case TAILS:
		printf("The result was TAILS.\n\n");
		printf("Player 2 goes first.");
		gameState = PLAYERTWOTURN;
		symbol = MARKTWO;
		winIfForfeit = MARKONEVICTORY;
		break;
	default:
		perror("tictacwoah : SetFirstMove() failure");
		exit(1);
	}
	return;
}

int FlipACoin() {
	return rand() % 2;
}
