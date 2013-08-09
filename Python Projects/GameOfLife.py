# IMPORTS
import sys

# GLOBAL CONSTANTS
INPUT_FILE = 'A08S-GOLBoardInterfaceData.dat'
NUM_ROWS   = 10
NUM_COLS   = 10
MARK_LIVE  = 'L'
MARK_DEAD  = 'D'

# FUNCTIONS
def main():

	# create a 2d array that represents the board
	gameBoard = Create2DArray(NUM_ROWS, NUM_COLS)

	# populate the board with dead squares to start
	Initialize2DArray(gameBoard, MARK_DEAD)

	print 'Populating board...'

	# populate the board with live coordinates from the data file
	Populate2DArrayFromFile(gameBoard, INPUT_FILE, MARK_LIVE)

	raw_input('Board populated. Press enter to proceed.')
	
	print 'How many generations would you simulate?'
	desiredGenerations = input('Enter an number: ')
	

	genCount = 0

	# display the initial generation of the board
	DisplayBoard(gameBoard, genCount)
	
	print 'The board is currently at generation zero.'
	raw_input('Press enter to begin the game of life: ')

	for genCount in range(1, desiredGenerations + 1):

		# get the next generation of cells
		gameBoard = RegenBoard(gameBoard, MARK_LIVE, MARK_DEAD)

		# display the next generation of board
		DisplayBoard(gameBoard, genCount)

		raw_input("Press enter to proceed to the next generation: ")

def Create2DArray(rows, cols):

        returnList = []

        for x in range(rows):
                returnList.append([])
                for y in range(cols):
                        returnList[x].append(None)
        return returnList

def Initialize2DArray(board, fillSymbol):

        for x in range( len(board) ):
                for y in range( len(board[x]) ):
                        board[x][y] = fillSymbol


def Populate2DArrayFromFile(array, fileName, fillSymbol):

	# get array coordinates from the data file
	inHandle = open(fileName, 'r')
	coordinates = []
	for buffer in inHandle: coordinates.append(buffer.split())

	inHandle.close()

	# populate array with fillSymbol using coordinates from data file
	for x in range( len(coordinates) ):
		if len(coordinates[x]) != 0:
			try:
				array[int(coordinates[x][0])][int(coordinates[x][1])] = fillSymbol
			except ValueError:
				print "Invalid coordinate found in", fileName, "line", x+1
				print "\n Coordinate ommitted."
			except IndexError: 
				print "The coordinate (",\
				       coordinates[x][0]+",", coordinates[x][1],\
				      "), found on line", x, "of", fileName, "\nis out of range."
				print "Coordinate ommitted."

def DisplayBoard(board, generationLabel):

	# clear the screen
	print '\n' * 200
	# display the top bar
	TopBar("Conway's Game of Life: ", "Generation: "+str(generationLabel))

	# print the board itself
	for row in board:
		for x in range( len(row) ): 
			print ' '*(not bool(x))+('|'*bool(x or x >= len(row)-1)),row[x],
		print '\n '+('---+' * (len(row) - 1)) + '---'

def RegenBoard(board, LifeSymbol, DeathSymbol):

	# create a nextGen board
	nextGen = []
	for row in board:
		nextGen.append([] + row)

	# populate the nextGen board
	for y in range( len(board) ):		
		for x in range( len(board[y]) ):
			LifeCount = 0

			# count cell's living neighbors
			if board[y-1][x-1] == LifeSymbol:
				LifeCount += 1
			if board[y - 1][x] == LifeSymbol:
				LifeCount += 1
			if board[y-1][(x+1) % len(board[y])] == LifeSymbol:
				LifeCount += 1
			if board[y][(x+1) % len(board[y])] == LifeSymbol:
				LifeCount += 1
			if board[(y+1) % len(board)][(x+1) % len(board[y])] == LifeSymbol:
				LifeCount += 1
			if board[(y+1) % len(board)][x]  == LifeSymbol:
				LifeCount += 1
			if board[(y+1) % len(board)][x-1] == LifeSymbol:
				LifeCount += 1
			if board[y][x-1] == LifeSymbol:
				LifeCount += 1

			# populate nextGen element with living or dead cell
			if board[y][x] == DeathSymbol and LifeCount == 3:
				nextGen[y][x] = LifeSymbol
			elif board[y][x] == LifeSymbol and LifeCount == 2 or\
				 board[y][x] == LifeSymbol and LifeCount == 3   :
					nextGen[y][x] = LifeSymbol
			elif board[y][x] == DeathSymbol and LifeCount != 3:
					nextGen[y][x] = DeathSymbol
			else:
				nextGen[y][x] = DeathSymbol
			
	return nextGen

def TopBar(item1, item2):

	print '|===================|', '%-32s' % (item1),
	print '|===================|'
	print '|===================|', '%-32s' % (item2),
	print '|===================|\n'

main()


