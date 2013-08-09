#ifndef __FACTORIAL__
#define __FACTORIAL__

int
factorial(int n)
{
	int result;
	if(n == 0)
	{
		result = 1;
		std::cout << result << std::endl;
		return 1;
	}
	else
	{
		result = n * factorial(n - 1);
		std::cout << result << std::endl;
		return result;
	}
}

#endif
