/******************************************************************************
** File:        main.cpp
** Project:     Procedural Sliding Tile Puzzle Simulator
** Author:      subjectZero
** Date:        5/01/2013
** Description:
**              This c++ source file contains driver code for testing the
**				CFraction class.
******************************************************************************/

# include <iostream>
# include "CFraction.h"
using namespace std;

int
main()
{
	// make some CFractions
	CFraction frac1;
	CFraction frac2;
	CFraction temp;
	CFraction result;

	// set values
	frac1.SetNumerator(10);
	frac1.SetDenominator(5);
	frac2.SetNumerator(18);
	frac2.SetDenominator(4);

	cout << "Welcome to the CFRaction Class field test!\n\n\n";

	// test binary operations
	cout << "Testing binary operators:\n";
	result = frac1 + frac2;
	cout << frac1 << " + " << frac2 << " = " << result;
	cout << endl;

	result = frac1 + 1;
	cout << frac1 << " + " << 1 << " = " << result;
	cout << endl;

	result = frac1 - frac2;
	cout << frac1 << " - " << frac2 << " = " << result;
	cout << endl;

	result = frac1 - 1;
	cout << frac1 << " - " << 1 << " = " << result;
	cout << endl;

	result = frac1 * frac2;
	cout << frac1 << " * " << frac2 << " = " << result;
	cout << endl;

	result = frac1 * 2;
	cout << frac1 << " * " << 2 << " = " << result;
	cout << endl;

	result = frac1 / frac2;
	cout << frac1 << " / " << frac2 << " = " << result;
	cout << endl << endl << endl;

	result = frac1 / 2;
	cout << frac1 << " / " << 2 << " = " << result;
	cout << endl << endl << endl;

	frac1.SetNumerator(1);
	frac1.SetDenominator(4);
	frac2.SetNumerator(1);
	frac2.SetDenominator(-6);

	// test unary operations
	cout << "Testing unary operators:\n";
	temp = frac1;
	frac1 += frac2;
	cout << temp << " += " << frac2 << " = " << frac1;
	cout << endl;

	temp = frac1;
	frac1 += 1;
	cout << temp << " += " << 1 << " = " << frac1;
	cout << endl;

	temp = frac1;
	frac1 -= frac2;
	cout << temp << " -= " << frac2 << " = " << frac1;
	cout << endl;

	temp = frac1;
	frac1 -= 1;
	cout << temp << " -= " << 1 << " = " << frac1;
	cout << endl;

	temp = frac1;
	frac1 *= frac2;
	cout << temp << " *= " << frac2 << " = " << frac1;
	cout << endl;

	temp = frac1;
	frac1 *= 2;
	cout << temp << " *= " << 2 << " = " << frac1;
	cout << endl;

	temp = frac1;
	frac1 /= frac2;
	cout << temp << " /= " << frac2 << " = " << frac1;
	cout << endl << endl << endl;

	temp = frac1;
	frac1 /= 2;
	cout << temp << " /= " << 2 << " = " << frac1;
	cout << endl << endl << endl;

	cout << "Testing domain restrictions:\n";
	// test domain restrictions
	frac1.SetDenominator(0);
	frac1.SetDenominator(1);
	frac1.SetNumerator(0);

	frac2.SetDenominator(1);
	frac2.SetNumerator(1);

	result = frac2 / frac1;
	frac2 /= frac1;

	result = frac2 / 0;
	frac2 /= 0;

	// test comparison operators
	frac1.SetNumerator(1);
	frac1.SetDenominator(2);
	frac2.SetNumerator(1);
	frac2.SetDenominator(4);

	cout << "Testing comparison operators:\n"
			 << frac1 << " == " << frac2 << endl;
	frac1 == frac2 ? cout << "True.\n" : cout << "False.\n";
	cout << frac1 << " != " << frac2 << endl;
	frac1 != frac2 ? cout << "True.\n" : cout << "False.\n";

	frac2.SetNumerator(2);
	frac2.SetDenominator(4);

	cout << "Testing comparison operators with unsimplified fractions:\n"
			 << frac1 << " == " << frac2 << endl;
	frac1 == frac2 ? cout << "True.\n" : cout << "False.\n";
	cout << frac1 << " != " << frac2 << endl;
	frac1 != frac2 ? cout << "True.\n" : cout << "False.\n";

	frac1.SetNumerator(1);
	frac1.SetDenominator(1);

	cout << "Testing comparison operators with integers:\n"
			 << frac1 << " == " << 1 << endl;
	frac1 == 1 ? cout << "True.\n" : cout << "False.\n";
	cout << frac1 << " != " << 1 << endl;
	frac1 != 1 ? cout << "True.\n" : cout << "False.\n";

	// testing the overloaded assignment operator on an int
	cout << "One more test... \n";
	frac2 = 3;
	cout << frac2 << "==" << 3 << endl;

	cout << "... and that concludes our testing!\n\n";

	return 0;

}
