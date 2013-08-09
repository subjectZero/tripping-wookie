# -----------------------------------------------------------------------------
# File: ChangeMode.py
# Author: subjectZero
# Date: 3/10/13
# Description:
# This file contains python code for a module that changes accepts between
# two and five arbitrary modes as arguments, each with a corresponding keyword,
# along with a 'choice' argument and a default argument (md0). The module then
# determines whether the choice matches any of the keywords.
# If a match is found, then the module returns the corresponding mode.
# Otherwise, default/failsafe mode is returned.
# -----------------------------------------------------------------------------




# o.GetMode() ----------------------------------------------------------------
def Two(choice, md0, md1, md2, kw1, kw2):

    # set the mode
    if choice == kw1:
        return md1
    elif choice == kw2:
        return md2
    else:
        return md0

# Three() ----------------------------------------------------------------
def Three(choice, md0, md1, md2, md3, kw1, kw2, kw3):

    # set the mode
    if choice == kw1:
        return md1
    elif choice == kw2:
        return md2
    elif choice == kw3:
        return md3
    else:
        return md0

# Four() ----------------------------------------------------------------
def Four(choice, md0, md1, md2, md3, md4, kw1, kw2, kw3, kw4):

    # set the mode
    if choice == kw1:
        return md1
    elif choice == kw2:
        return md2
    elif choice == kw3:
        return md3
    elif choice == kw4:
        return md4
    else:
        return md0

# Five() ----------------------------------------------------------------
def Five(choice, md0, md1, md2, md3, md4, md5, kw1, kw2, kw3, kw4, kw5):

    # set the mode
    if choice == kw1:
        return md1
    elif choice == kw2:
        return md2
    elif choice == kw3:
        return md3
    elif choice == kw4:
        return md4
    elif choice == kw5:
        return md5
    else:
        return md0
