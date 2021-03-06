/*
Imagni Studios Q5 - Fibonacci
By: Robert Hill

given the formula of the Nth Fibonacci number:
fib(n) = fib(n-2) + fib(n-1)

One would assume we can just make recursive calls. However, that is not efficent
since there would be a lot of repeated calculations. So the better way is to do the
calculation in place. 

ASSUMPTION: Input is a valid integer

Time: Under 30 minutes
*/
#include "stdafx.h"
#include <iostream>
#include <stdio.h>


int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cout << "program takes only one argumant, a number";
		return -1;
	}

	int input = atoi(argv[1]);

	int firstInSequence = 0;
	int secondInSequence = 1;
	int nextInSequence = 0;

	for (int i = 2; i <= input; i++)
	{
		nextInSequence = firstInSequence + secondInSequence;
		// we got the next value in sequence, so overwrite first and second in sequnce
		// with already calulated values
		firstInSequence = secondInSequence;
		secondInSequence = nextInSequence;
	}
	std::cout << secondInSequence << '\n';

	system("pause");
	return 0;
}

