// INCLUDES AND NAMESPACES
# include "Triangle.h"
# include <iostream>
# include <iomanip>
# include <math.h>
using namespace std;

// CONSTRUCTOR
Triangle::Triangle() {
	opposite = 0;
	adjacent = 0;
	hypotenuse = 0;
	area = 0;
	perimeter = 0;
};

// GETTERS
double Triangle::GetOppositeLength() { return opposite; }
double Triangle::GetAdjacentLength() { return adjacent; }
double Triangle::GetHypotenuseLength() { return hypotenuse; }
double Triangle::GetArea() { return area; }
double Triangle::GetPerimeter() { return perimeter; }

// SETTERS
bool Triangle::SetAdjacentLength(double myAdjacent) {
	
	// set adjacent if it is valid
	if (myAdjacent < 0) {
		cout << "Invalid call to SetAdjacentLength(). . . "
				<< "length must be greater than 0" << endl;
		return false;
	}
	adjacent = myAdjacent;

	Triangle::SetHypotenuse();
	Triangle::SetPerimeter();
	Triangle::SetArea();

	return true;
}

bool Triangle::SetOppositeLength(double myOpposite) {
	
	// set adjacent if it is valid
	if (myOpposite < 0) {
		cout << "Invalid call to SetOppositeLength(). . . "
				<< "length must be greater than 0" << endl;
		return false;
	}
	opposite = myOpposite;

	Triangle::SetHypotenuse();
	Triangle::SetPerimeter();
	Triangle::SetArea();

	return true;
}

void Triangle::SetHypotenuse() {
	hypotenuse = sqrt( pow(opposite, 2) + pow(adjacent, 2) );
}

void Triangle::SetPerimeter() {
	perimeter = opposite + adjacent + hypotenuse;
}

void Triangle::SetArea() {
	area = (opposite * adjacent) / 2;
}

// OTHER METHODS
void Triangle::DisplayTriangle() {
	
	cout << setprecision(2) << setw(20) << " " << "*\n";
	for (int i = 0; i < 13; ++i) {
	
		if (i == 4) { 
			cout << setw(16) << left << "Opposite Side = "
					<< setw(4) << opposite << right;
		}
		else if (i < 9) {
			cout << setw(20) << " ";
		}
		cout << "*";
		if (i > 0 && i < 8) {
			cout << setw(i + 1) << "*";
			if (i == 4) {
				cout << setw(21) << "Hypotenuse Side = " << hypotenuse;
			}
			cout << endl;
		}
		else {
			cout << "*";
		}
		if (i == 0) {
			cout << endl;
		}
	}
	cout << endl << endl << setw(35) << "Adjacent Side = "
			<< adjacent << endl << endl << left
				<< "The area of the triangle is     : " << setw(4) << area
					<< endl << "The perimeter of the triangle is: " << setw(4)
						<< perimeter << endl;
}













