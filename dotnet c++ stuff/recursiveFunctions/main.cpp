// INCLUDES AND NAMESPACES
# include "includes.h"
using namespace std;

// sums the first n elements of an array
int sum(int[], int);

int // ========================================================================
main()
{
	// declarations
	int n = 9;
	int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	int result = sum(arr, n);

	cout << result << endl;

	// get a value for n
	cout << "Please enter an input value for the Factorial function: ";
	cin >> n;

	// plug the values into the factorial function and display the results
	cout << factorial(n);

	cout << "Please enter an input value for the Fibonacci Sequence: ";
	cin >> n;

	cout << Fibonacci(n);

	return 0;
} // end main()


int // --------------------------------------------------------------------------
sum(int arr[], int n)
{
	int currentElement;
	int recursiveCall;

	if(n == 0) {
		return arr[n];
	}
	else {
		currentElement = arr[n];

		recursiveCall = sum(arr, n - 1);

		cout << currentElement + recursiveCall << endl;

		return currentElement + recursiveCall;
	}
}