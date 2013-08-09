# ifndef __TRIANGLE__
# define __TRIANGLE__

# include <iostream>
class Triangle {

public:
	// CONSTRUCTOR
	Triangle();
	// MUTATORS
	// getters
	double GetOppositeLength();
	double GetAdjacentLength();
	double GetHypotenuseLength();
	double GetArea();
	double GetPerimeter();
	// setters
	bool SetOppositeLength(double);
	bool SetAdjacentLength(double);
	// other methods
	void DisplayTriangle();

private:
	double opposite, adjacent, hypotenuse;
	double area, perimeter;
	void SetHypotenuse();
	void SetPerimeter();
	void SetArea();
}; // end Triangle

# endif