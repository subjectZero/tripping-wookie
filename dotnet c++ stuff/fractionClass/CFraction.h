#ifndef __CFRACTION__
#define __CFRACTION__

# include <iostream>
# include <math.h>
using namespace std;

class
CFraction
{
	public:
		CFraction();
		CFraction(int numerator, int denominator);
		int GetNumerator();
		int GetDenominator();
		void SetNumerator(int);
		int SetDenominator(int);

		// operator overloads
		const CFraction operator+(const CFraction&) const;
		const CFraction operator-(const CFraction&) const;
		const CFraction operator*(const CFraction&) const;
		const CFraction operator/(const CFraction&) const;
		const CFraction operator+(const int&) const;
		const CFraction operator-(const int&) const;
		const CFraction operator*(const int&) const;
		const CFraction operator/(const int&) const;
		CFraction& operator=(const CFraction&);
		CFraction& operator+=(const CFraction&);
		CFraction& operator-=(const CFraction&);
		CFraction& operator*=(const CFraction&);
		CFraction& operator/=(const CFraction&);
		CFraction& operator=(const int&);
		CFraction& operator+=(const int&);
		CFraction& operator-=(const int&);
		CFraction& operator*=(const int&);
		CFraction& operator/=(const int&);
		bool operator==(const CFraction&) const;
		bool operator==(const int&) const;
		bool operator!=(const CFraction&) const;
		bool operator!=(const int&) const;
		friend ostream& operator<<(ostream& , const CFraction&);

	private:
		int numerator;
		int denominator;
		void Reduce();
};

#endif