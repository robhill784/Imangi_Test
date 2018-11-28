/* 
Imagni Studios Q1 - Fizz Buzz
By: Robert Hill

Standard fizzbuzz exercise

Time: under 15 minutes
*/

#include "stdafx.h"
#include <iostream>

int main()
{

	for (int i = 1; i <= 100; i++)
	{
		if (((i % 3) == 0) && ((i % 5) ==0))
			std::cout << "fizzbuzz\n";
		else if (!(i % 5))
			std::cout << "buzz\n";
		else if (!(i % 3))
			std::cout << "fizz\n";
		else
			std::cout << i << "\n";
	}
	system("pause");
    return 0;
}
