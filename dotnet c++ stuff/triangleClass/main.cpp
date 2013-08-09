# include "includes.h"
using namespace std;

# pragma once
# define OPPOSITE 3
# define ADJACENT 4

int main() {

	// instantiate the class
	Triangle myTriangle;

	// load the values
	myTriangle.SetOppositeLength(OPPOSITE);
	myTriangle.SetAdjacentLength(ADJACENT);

	// display the rectangle
	myTriangle.DisplayTriangle();

	return 0;
}

