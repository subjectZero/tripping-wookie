# -----------------------------------------------------------------------------
# File: GetNum.py
# Author: subjectZero
# Date: 3/10/13
# Description:
# This file contains a Python module that gets a numeric input from the user.
# GetNum has two functions - Int and Float - for use with their respective
# data types.
# -----------------------------------------------------------------------------


# Int.GetNum() ----------------------------------------------------------------
def Int(prompt):

    # priming read
    inputSuccess = False

    # integrated type checking
    while inputSuccess == False:

        # get a number from the user
        inputSuccess = True
        myStr = raw_input(prompt)
        try:
            myNum = int(myStr)
        except ValueError:
            print "That's not a valid input."
            inputSuccess = False

    return myNum

# Float.GetNum() --------------------------------------------------------------
def float(prompt):

    # priming read
    inputSuccess = False

    # integrated type checking
    while inputSuccess == False:

        # get a number from the user
        inputSuccess = True
        myStr = raw_input(prompt)
        try:
            myNum = float(myStr)
        except ValueError:
            print "That's not a valid input."
            inputSuccess = False

    return myNum
