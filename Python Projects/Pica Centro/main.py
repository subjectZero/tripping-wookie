#------------------------------------------------------------------------------
# File: PicaCentro.py
# Author: subjectZero
# Date: 3/10/13
# Description:
# This file contains Python code for Pica Centro, a game of logic
# and deductive reasoning.
# -----------------------------------------------------------------------------

# GLOBALS AND CONSTANTS
# modes
UNSET        = 0
PLAY         = 1
LEVEL        = 2
HOW_2        = 3
SET_PLYRS    = 4
QUIT         = 5
# difficulty levels
EASY         = 'Easy'
MED          = 'Medium'
HARD         = 'Hard'
PSYCHIC      = 'Rasputin'
# global variables
gDifficulty  = MED
gMultiplayer = True
gMPlyrPrompt = 'Multiplayer'
gMPlayerAlt  = 'Single Player'

# IMPORTS
import random
import AuxModules
import ChangeMode
import GetChoice
import GetNum


# MAIN() ----------------------------------------------------------------------
def main():
    # global permissions
    global gMultiplayer

    # priming read for main loop
    mode = UNSET

    # main loop cycles through options
    while True:

        # clear the display after each change in state
        AuxModules.ClearScreen()

        # call appropriate function based on state
        if mode == UNSET:
            mode = SetMode()
        elif mode == PLAY:
            mode = PlayGame()
            mode = UNSET
        elif mode == LEVEL:
            if gMultiplayer == False:
                mode = SetLevel()
            else:
                mode = -1
            mode = UNSET
        elif mode == HOW_2:
            mode = DispMan()
            mode = UNSET
        elif mode == SET_PLYRS:
            mode = SetMultiPlayer()
            mode = UNSET
        else:
            # error has occurred
            print 'Error - unable to determine mode.'
            mode = -1

        # do-while emulation using control break
        if mode >= QUIT or mode < UNSET:
            break

    if mode < 0 or mode > QUIT:
        print 'An error occurred'

    print 'The program will now exit.'

# SetMode() -------------------------------------------------------------------

def SetMode():

    global gDifficulty
    global gMultiplayer
    global gMPlyrPrompt
    global gMPlayerAlt

    # priming read
    mode = UNSET

    # integrated sanity check
    while mode == UNSET:

        # display the top bar
        AuxModules.TopBar('Welcome to Pica Centro!', gMPlyrPrompt)

        # get user input
        if gMultiplayer == True:

            # Get the player input
            choice = GetChoice.Four(
                                'Option',
                                'Play the Game',
                                'How to Play',
                                'Switch to ' + gMPlayerAlt,
                                'Quit the Game',
                                'start',
                                'how',
                                'players',
                                'quit')

            # Set the mode
            mode = ChangeMode.Four(
                                choice,
                                UNSET,
                                PLAY,
                                HOW_2,
                                SET_PLYRS,
                                QUIT,
                                'start',
                                'how',
                                'players',
                                'quit')
        elif gMultiplayer == False:

            # Get the Player input
            choice = GetChoice.Five(
                                'Option',
                                'Play the Game',
                                'Set Difficulty Level',
                                'How to Play',
                                'Switch to ' + gMPlayerAlt,
                                'Quit the Game',
                                'start',
                                'level',
                                'how',
                                'players',
                                'quit')

            # Set the mode
            mode = ChangeMode.Five(
                                choice,
                                UNSET,
                                PLAY,
                                LEVEL,
                                HOW_2,
                                SET_PLYRS,
                                QUIT,
                                'start',
                                'level',
                                'how',
                                'players',
                                'quit')
        else:
            print 'Error in SetMode() - single/multipayer undetermined.'
            return -1

        # if input invalid, notify user
        if mode == UNSET:
            print "\n\nThat's not a valid input."
            raw_input('Press enter to try again.')

            # clear the display for usability purposes
            AuxModules.ClearScreen();

    return mode

# PlayGame() ------------------------------------------------------------------
# Input:
def PlayGame():

    # SET UP THE GAME
    # global permissions
    global gMultiplayer
    global gMPlyrPrompt

    # local declarations
    plyr1prompt = 'Number Guesser, please enter your name: '
    plyr2prompt = 'Number Picker, please enter your name: '

    # clear screen of information from previous mode
    AuxModules.ClearScreen()

    #display the top bar
    AuxModules.TopBar('Pica Centro!', gMPlyrPrompt)

    # get player1's name
    player1 = raw_input(plyr1prompt)

    if gMultiplayer:

        # set up a multiplayer game
        player2 = raw_input(plyr2prompt)

        # inform player(s) that the game will proceed
        print player2, 'will now choose a secret number.'

        # reset the display for usability purposes
        AuxModules.ClearScreen()
        AuxModules.TopBar(
                    'Pica Centro: Multiplayer',
                    player1 + ' vs. ' + player2)

        # get all 3 digits of the secret number
        secNum1 = GetDigit(player2, 'first', 'secret number')
        secNum2 = GetDigit(player2, 'second', 'secret number')
        secNum3 = GetDigit(player2, 'third', 'secret number')

    elif (not gMultiplayer):

        # set up a single player game
        print 'The computer will now choose a number.'
        player2 = 'Dijkstra'


        # randomly generate all three digits of the secret number
        secNum1 = random.randint(0,9)
        secNum2 = random.randint(0,9)
        secNum3 = random.randint(0,9)

    # clear the screen
    AuxModules.ClearScreen()

    # get the number of guesses for each
    guesses = SetMaxGuesses()

    # display the top bar with player info and starting guesses
    AuxModules.TopBar(player1+' vs '+player2, ('Guesses Left: '+str(guesses)))

    # PLAY THE GAME
    while True:

        # reset the pica count and centro count to zero at start of round
        centros = 0
        picas = 0

        # get the guesser's guesses, one digit at a time
        pGuess1 = GetDigit(player1, 'first', 'guess.')
        pGuess2 = GetDigit(player1, 'second', 'guess.')
        pGuess3 = GetDigit(player1, 'third', 'guess.')

        # is pGuess1 a pica or centro?
        if pGuess1 == secNum1:
            centros += 1
        elif pGuess1 == secNum2:
            picas += 1
        elif pGuess1 == secNum3:
            picas += 1

        # is pGuess2 a pica or centro?
        if pGuess2 == secNum2:
            centros += 1
        elif pGuess2 == secNum3:
            picas += 1
        elif pGuess2 == secNum1:
            picas += 1

        # is pGuess3 a pica or centro?
        if pGuess3 == secNum3:
            centros += 1
        elif pGuess3 == secNum1:
            picas += 1
        elif pGuess3 == secNum2:
            picas += 1

        # decrement remaining guesses by one after guess is made and checked
        guesses -= 1

        # CHECK FOR VICTORY
        if centros == 3:

            # clear reset the display for asthetic purposes
            AuxModules.ClearScreen();
            AuxModules.TopBar(
                            player1 + ' DEFEATED ' + player2 + '!',
                            'Guesses remaining: ' + str(guesses));

            # if all three digits are centros, then the guesser has won
            print 'The number was:', secNum1, secNum2, secNum3,\
                  '\n\n', player1, 'successfully guessed the secret number!'\
                  '\n', player1, 'wins the game!\n'

            # return to main menu when player is ready
            raw_input("Press the ENTER key to return to the main menu...")
            break;

        elif guesses <= 0:

            # clear and reset the display for asthetic purposes
            AuxModules.ClearScreen();
            AuxModules.TopBar(
                            player2 + ' DEFEATED ' + player1 + '!',
                            'Guesses remaining: ' + str(guesses) );

            # if the guesser runs out of guesses, then the number picker wins
            print 'The number was:', secNum1, secNum2, secNum3,\
                   '\n\n', player1, 'was unable to guess the secret number.'\
                   '\n', player2, 'wins the game!\n'

            # return to the main menu when player is ready
            raw_input("Press the ENTER key to return to the main menu...")
            break;

        # clear the screen to prepare for the next round
        AuxModules.ClearScreen()

        # display the updated top bar with player info and remaining guesses
        AuxModules.TopBar(
                    player1+' vs '+player2,
                    'Guesses Left: '+str(guesses) )

        # display picas, centros, and guesses remaining
        DispGameStats(picas, centros,  pGuess1, pGuess2, pGuess3)

# GetDigit() ------------------------------------------------------------------
def GetDigit(player2, prompt1, prompt2):

    # create some prompts for user input
    promptA = ', please enter the '+prompt1+' digit of your ' + prompt2
    promptB = 'Enter a positive integer less than 10: '


    # get the first digit of the secretNum, reprompt if invalid
    while True:


        print player2 + promptA

        # get an integer
        digit = GetNum.Int(promptB)

        # check if input is reasonable
        if digit >= 0 and digit < 10:
            break;
        else:
            print 'That was not a valid input.'

    return digit

# SetLevel() ------------------------------------------------------------------
def SetLevel():

    # global declarations
    global gDifficulty

    # create local version of gDifficulty variable
    lDif = 'UNSET'

    # user is reprompted until they enter a valid input
    while lDif == 'UNSET':

        # display the current state and difficulty level through the top bar
        AuxModules.TopBar(
                    'Set Difficulty Level',
                    'Difficulty: ' + gDifficulty)

        # get user input
        choice = GetChoice.Four(
                            'Difficulty Level',
                            EASY,
                            MED,
                            HARD,
                            PSYCHIC,
                            'easy',
                            'medium',
                            'hard',
                            'psychic')

        # change the difficulty level
        lDif = ChangeMode.Four(
                           choice,
                           'UNSET',
                           EASY,
                           MED,
                           HARD,
                           PSYCHIC,
                           'easy',
                           'medium',
                           'hard',
                           'psychic')

        # if input invalid, notify user
        if lDif == 'UNSET':
            print "\n\nThat's not a valid input."
            raw_input('Press enter to try again.')

    # set the global once proper input has been established
    gDifficulty = lDif

    # reset the program mode
    return UNSET

# SetMultiPlayer() ------------------------------------------------------------
def SetMultiPlayer():

    # global permissions
    global gMultiplayer
    global gMPlyrPrompt
    global gMPlayerAlt

    # prompt user until input is valid
    while True:

        # display top bar
        AuxModules.TopBar(
                    'Pica Centro',
                    'Currently set to: ' + gMPlyrPrompt)

        choice = GetChoice.Two(
                  'options',
                  'Switch to ' + gMPlayerAlt,
                  'Do nothing', 'switch', 'cancel')

        # switch mode upon user request, then control break
        if choice == 'switch':
            gMultiplayer =  (not gMultiplayer)
            swap = gMPlyrPrompt
            gMPlyrPrompt = gMPlayerAlt
            gMPlayerAlt = swap
            break;

        # if user chooses to cancel, control break
        elif choice == 'cancel':
            break;

        # user input invalid - notify user and reprompt
        else:

            print "\n\nThat's not a valid input."
            raw_input('Press enter to try again...')
            AuxModules.ClearScreen();

    return UNSET

# DispMan() -------------------------------------------------------------------
def DispMan():

    # global permissions
    global gMPlyrPrompt

    # display a growing bullet point list of instructions
    for x in range(0,7):

        # clear screen and display the top bar
        AuxModules.ClearScreen()
        AuxModules.TopBar('Pica Centro: ', 'How to Play')

        if x >= 0:
            print '1. The number selector, be it a player or the computer,'
            print '    selects a 3 digit number, entering it into the console.'
            print ''
        if x >= 1:
            print '2. The number picker must then try and guess the number'
            print '    before his or her allotted guesses run out.\n'
        if x >= 2:
            print '3. If the guess is correct, then the player wins the game.'
            print ''
        if x >= 3:
            print '4. If the guess is incorrect, then the player recieves a'
            print '    response as a count of picas and centros.\n'
        if x >= 4:
            print '5. A pica is given if one guesser\'s digits is correct,'
            print '    but in the wrong position.\n'
        if x >= 5:
            print '6. A centro is given if one guesser\'s digits is correct,'
            print '    and the correct position.\n'
        if x >= 6:
            print '7. The game ends when the number picker guesses the correct'
            print '    number and wins, or runs out of guesses and loses.\n'

        # tactile feedback keeps user's attention for greater comprehension
        raw_input('Press enter to continue...')

    # reset the mode
    return UNSET

# SetMaxGuesses() -------------------------------------------------------------
def SetMaxGuesses():

    global gDifficulty
    global gMultiplayer

    # if in multiplayer mode, then guesses are set to 10
    if gMultiplayer:
        return 10

    # otherwise, return number of guesses based on the difficulty level
    if gDifficulty == EASY:
        return 20
    elif gDifficulty == MED:
        return 10
    elif gDifficulty == HARD:
        return 7
    elif gDifficulty == PSYCHIC:
        return 3

# DispGameStats() -------------------------------------------------------------
def DispGameStats(picas, centros, pGuess1, pGuess2, pGuess3):
	# this creates a game status display on either side of the screen
    print '+'+('-' * 19)+'+'+(' ' * 34)+'+'+('-' * 9)+'+'+('-' * 9)+'+'
    print '| %-17s | %32s | %-7s | %-7s |'\
           % ('Your Guess', ' ', 'Pica', 'Centro')
    print '+'+('-' * 19)+'+'+(' ' * 34)+'+'+('-' * 9)+'+'+('-' * 9)+'+'
    print '| %-2d %-2d %-11d | %32s | %-7s | %-7s |' \
           % (pGuess1, pGuess2, pGuess3, ' ', picas, centros)
    print '+'+('-' * 19)+'+'+(' ' * 34)+'+'+('-' * 9)+'+'+('-' * 9)+'+'

main()

