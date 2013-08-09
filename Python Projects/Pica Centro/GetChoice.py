# -----------------------------------------------------------------------------
# File: GetChoice.py
# Author: subjectZero
# Date: 3/10/13
# Description:
# This file contains python code for a module that displays a list of options
# to the user, allows the user to choose one of these options, and then returns
# the user's choice to the calling function.
# -----------------------------------------------------------------------------


# Five.GetChoice() ------------------------------------------------------------
def Two(optName, opt1, opt2, kw1, kw2):

    # local declarations
    menuPrompt = ('Enter keyword('+kw1+', '+kw2+'): ')

     # display available choices
    print '%-25s | Keyword' % (optName)
    print ('-' * 26) + '+' + ('-' * 8)
    print '%-25s | %s' % (opt1, kw1)
    print '%-25s | %s' % (opt2, kw2)

    #prompt the user
    print '\nPlease select an option from the list above.'

    # get sanitized player choice
    choice = raw_input(menuPrompt).lower().strip()

    return choice

# Five.GetChoice() ------------------------------------------------------------
def Three(optName, opt1, opt2, opt3, kw1, kw2, kw3):

    # local declarations
    menuPrompt = ('Enter keyword('+kw1+', '+kw2+', '+kw3+'): ')

     # display available choices
    print '%-25s | Keyword' % (optName)
    print ('-' * 26) + '+' + ('-' * 8)
    print '%-25s | %s' % (opt1, kw1)
    print '%-25s | %s' % (opt2, kw2)
    print '%-25s | %s' % (opt3, kw3)

    #prompt the user
    print '\nPlease select an option from the list above.'

    # get sanitized player choice
    choice = raw_input(menuPrompt).lower().strip()

    return choice

# Four.GetChoice() ------------------------------------------------------------
def Four(optName, opt1, opt2, opt3, opt4, kw1, kw2, kw3, kw4):

    # local declarations
    menuPrompt = ('Enter keyword('+kw1+', '+kw2+', '+kw3+', '+kw4+'): ')

     # display available choices
    print '%-25s | Keyword' % (optName)
    print ('-' * 26) + '+' + ('-' * 8)
    print '%-25s | %s' % (opt1, kw1)
    print '%-25s | %s' % (opt2, kw2)
    print '%-25s | %s' % (opt3, kw3)
    print '%-25s | %s' % (opt4, kw4)

    #prompt the user
    print '\nPlease select an option from the list above.'

    # get sanitized player choice
    choice = raw_input(menuPrompt).lower().strip()

    return choice

# Five.GetChoice() ------------------------------------------------------------
def Five(optName, opt1, opt2, opt3, opt4, opt5, kw1, kw2, kw3, kw4, kw5):

    # local declarations
    menuPrompt = ('Enter keyword('+kw1+', '+kw2+', '+kw3+', '+kw4+', '+kw5+'): ')

     # display available choices
    print '%-25s | Keyword' % (optName)
    print ('-' * 26) + '+' + ('-' * 8)
    print '%-25s | %s' % (opt1, kw1)
    print '%-25s | %s' % (opt2, kw2)
    print '%-25s | %s' % (opt3, kw3)
    print '%-25s | %s' % (opt4, kw4)
    print '%-25s | %s' % (opt5, kw5)

    #prompt the user
    print '\nPlease select an option from the list above.'

    # get sanitized player choice
    choice = raw_input(menuPrompt).lower().strip()

    return choice
