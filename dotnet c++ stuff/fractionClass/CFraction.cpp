# include "CFraction.h"

// ctor -----------------------------------------------------------------------
CFraction::CFraction() {numerator = 0; denominator = 1;}

// ctor -----------------------------------------------------------------------
CFraction::CFraction(int numerator, int denominator)
{
	this->numerator = numerator;
	if(!(denominator))
	{
		cout << "Zero is not within the domain of the denominator."
				<< "Denominator set to the value 1 by default.\n";
		denominator = 0;
	}
	this->denominator = denominator;
}

int // ------------------------------------------------------------------------
CFraction::GetNumerator() {Reduce(); return this->numerator;}

int // ------------------------------------------------------------------------
CFraction::GetDenominator() {Reduce(); return this->denominator;}

void // -----------------------------------------------------------------------
CFraction::SetNumerator(int numerator) {this->numerator = numerator;}

int // ------------------------------------------------------------------------
CFraction::SetDenominator(int denominator)
{
	if(!denominator)
	{
		cout << "Denominators of zero are not allowed.\n";
		return EXIT_FAILURE;
	}
	this->denominator = denominator;
	return EXIT_SUCCESS;
}

CFraction& // -----------------------------------------------------------------
CFraction::operator=(const CFraction& rhs)
{
	if (this != &rhs)
	{
		this->numerator = rhs.numerator;
		this->denominator = rhs.denominator;
	};
	return *this;
}

CFraction& // -----------------------------------------------------------------
CFraction::operator=(const int& rhs)
{

	this->numerator = rhs;
	this->denominator = 1;

	return *this;
}

CFraction& // -----------------------------------------------------------------
CFraction::operator+=(const CFraction& rhs)
{
	if (this != &rhs)
	{   
		int tempNumerator = rhs.numerator * this->denominator;
		this->numerator *= rhs.denominator;
		this->numerator += tempNumerator;
		this->denominator *= rhs.denominator;
	};
	return *this;
}

CFraction& // -----------------------------------------------------------------
CFraction::operator+=(const int& rhs)
{
	int tempInteger = rhs * this->denominator;
	this->numerator += tempInteger;
	return *this;
}

CFraction& // -----------------------------------------------------------------
CFraction::operator-=(const CFraction& rhs)
{
	if (this != &rhs)
	{   
		int tempNumerator = rhs.numerator * this->denominator;
		this->numerator *= rhs.denominator;
		this->numerator -= tempNumerator;
		this->denominator *= rhs.denominator;
	};
	return *this;
}

CFraction& // -----------------------------------------------------------------
CFraction::operator-=(const int& rhs)
{
	int tempInteger = rhs * this->denominator;
	this->numerator -= tempInteger;
	return *this;
}

CFraction& // -----------------------------------------------------------------
CFraction::operator*=(const CFraction& rhs)
{
	if (this != &rhs)
	{   
		this->numerator *= rhs.numerator;
		this->denominator *= rhs.denominator;
	};
	return *this;
}

CFraction& // -----------------------------------------------------------------
CFraction::operator*=(const int& rhs)
{
	this->numerator *= rhs;
	return *this;
}

CFraction& // -----------------------------------------------------------------
CFraction::operator/=(const CFraction& rhs)
{
	if (this != &rhs)
	{   
		if(!(rhs.numerator))
		{
			cout << "Not able to divide by zero.\n";
			return *this;
		}
		this->numerator *= rhs.denominator;
		this->denominator *= rhs.numerator;
	};
	return *this;
}

CFraction& // -----------------------------------------------------------------
CFraction::operator/=(const int& rhs)
{  
	if(!(rhs))
	{
		cout << "Not able to divide by zero.\n";
		return *this;
	}
	this->denominator *= rhs;

	return *this;
}

const CFraction // ------------------------------------------------------------
CFraction::operator+(const CFraction& rhs) const
{
	
	CFraction ResultFraction = *this;
	int tempNumerator = rhs.numerator * ResultFraction.denominator;
	ResultFraction.numerator *= rhs.denominator;
	ResultFraction.numerator += tempNumerator;
	ResultFraction.denominator *= rhs.denominator;

	return ResultFraction;
}

const CFraction // ------------------------------------------------------------
CFraction::operator+(const int& rhs) const
{
	
	CFraction ResultFraction = *this;
	int tempInteger = rhs * ResultFraction.denominator;
	ResultFraction.numerator += tempInteger;

	return ResultFraction;
}


const CFraction // ------------------------------------------------------------
CFraction::operator-(const CFraction& rhs) const
{
	
	CFraction ResultFraction = *this;
	int tempNumerator = rhs.numerator * ResultFraction.denominator;
	ResultFraction.numerator *= rhs.denominator;
	ResultFraction.numerator -= tempNumerator;
	ResultFraction.denominator *= rhs.denominator;

	return ResultFraction;
}

const CFraction // ------------------------------------------------------------
CFraction::operator-(const int& rhs) const
{
	
	CFraction ResultFraction = *this;
	int tempInteger = rhs * ResultFraction.denominator;
	ResultFraction.numerator -= tempInteger;

	return ResultFraction;
}

const CFraction // ------------------------------------------------------------
CFraction::operator*(const CFraction& rhs) const
{
	
	CFraction ResultFraction = *this;
	ResultFraction.numerator *= rhs.numerator;
	ResultFraction.denominator *= rhs.denominator;

	return ResultFraction;
}

const CFraction // ------------------------------------------------------------
CFraction::operator*(const int& rhs) const
{
	
	CFraction ResultFraction = *this;
	ResultFraction.numerator *= rhs;

	return ResultFraction;
}

const CFraction // ------------------------------------------------------------
CFraction::operator/(const CFraction& rhs) const
{
	
	CFraction ResultFraction = *this;
	if(!(rhs.numerator))
	{
			cout << "Division by zero is not permitted.\n";
			return *this;
	}
	ResultFraction.numerator *= rhs.denominator;
	ResultFraction.denominator *= rhs.numerator;

	return ResultFraction;
}

const CFraction // ------------------------------------------------------------
CFraction::operator/(const int& rhs) const
{
	
	CFraction ResultFraction = *this;
	if(!(rhs))
	{
			cout << "Division by zero is not permitted.\n";
			return *this;
	}
	ResultFraction.denominator *= rhs;

	return ResultFraction;
}

bool // ------------------------------------------------------------------------
CFraction::operator==(const CFraction& otherValue) const
{
	CFraction otherValueCpy = otherValue;
	CFraction selfCpy = *this;
	if(selfCpy.GetDenominator() == otherValueCpy.GetDenominator() &&
		selfCpy.GetNumerator() == otherValueCpy.GetNumerator()      )
			return true;
	else
		return false;
}

bool // -----------------------------------------------------------------------
CFraction::operator==(const int& otherValue) const
{
	CFraction selfCpy = *this;
	if(selfCpy.GetDenominator() == 1 && selfCpy.GetNumerator() == otherValue)
		return true;
	else
		return false;
}

bool // -----------------------------------------------------------------------
CFraction::operator!=(const CFraction& otherValue) const
{
	CFraction otherValueCpy = otherValue;
	CFraction selfCpy = *this;
	if(selfCpy.GetDenominator() == otherValueCpy.GetDenominator() &&
		selfCpy.GetNumerator() == otherValueCpy.GetNumerator()      )
			return false;
	else
		return true;
}

bool // -----------------------------------------------------------------------
CFraction::operator!=(const int& otherValue) const
{
	CFraction selfCpy = *this;
	if(selfCpy.GetDenominator() == 1 && selfCpy.GetNumerator() == otherValue)
		return false;
	else
		return true;
}

void // -----------------------------------------------------------------------
CFraction::Reduce()
{
	int numerator = this->numerator, denominator = this->denominator;
	int sign;
	
	// less than zero?
	if(numerator < 0 && denominator > 0)
		sign = -1;
	else if(numerator > 0 && denominator < 0)
		sign = -1;
	else
		sign = 1;

	numerator = abs(numerator), denominator = abs(denominator);

	// reduce the fraction
	for(int i = 2; i <= numerator; ++i)
	{
		if(numerator % i == 0 && denominator % i == 0)
		{
			numerator /= i;
			denominator /= i;
			i = 1;
		}
	}

	// restore sign of fraction
	numerator *= sign;
	this->numerator = numerator;
	this->denominator = denominator;
}

// non member functions
ostream& // -------------------------------------------------------------------
operator<<(ostream& out, const CFraction& myCFraction)
{
	CFraction myFractCopy = myCFraction; 
	out << "( " << myFractCopy.GetNumerator() << " / " 
			<< myFractCopy.GetDenominator() << " )";
	return out;
}