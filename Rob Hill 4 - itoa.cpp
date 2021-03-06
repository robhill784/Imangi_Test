/*
Imagni Studios Q4 - my itoa
By: Robert Hill

I use a stack to store all characters as it is LIFO.

ASSUMPTION: All inputs are valid

Time: ~1 hour 
*/

#include "stdafx.h"
#include <iostream>

enum FormatType
{
	Decimal,
	Octal,
	Hexadecimal
};

class charStack
{
public:
	charStack()
	{
		pTopOfStack = NULL;
	}
	~charStack()
	{
		makeEmpty();
	}

	bool isEmpty()
	{
		return pTopOfStack == NULL;
	}
	void makeEmpty()
	{
		while (!isEmpty())
		{
			pop();
		}
	}

	char pop()
	{
		if (isEmpty())
			return '\0';

		ListChar* pTop = pTopOfStack;
		char ret = pTopOfStack->data;
		pTopOfStack = pTopOfStack->pNext;
		delete pTop;
		return ret;
	}

	void push(char input)
	{
		pTopOfStack = new ListChar(input, pTopOfStack);
	}

private:
	struct ListChar
	{
		ListChar(const char& input, ListChar * pN = NULL)
			:data(input),
			pNext(pN)
		{}
		char data;
		ListChar* pNext;
	};

	ListChar* pTopOfStack;
};

// Get the numeric base based on format
int getBase(const FormatType& inFormat)
{
	int base;
	switch (inFormat)
	{
		case 1:
		{
			base = 8;
			break;
		}
		case 2:
		{
			base = 16;
			break;
		}
		case 0:
		default:
		{
			base = 10;
		}
	}
	return base;
}

char* itoa(int inNumber, char* outString, FormatType inFormat)
{
	int base = getBase(inFormat);
	int index = 0;
	bool isNegative = false;
	charStack stack;

	// make sure to make inNumber positive for decimal
	if (base == 10 && inNumber < 0)
	{
		isNegative = true;
		inNumber = -inNumber;
	}

	if (inNumber == 0)
	{
		outString[0] = '0';
		outString[1] = '\0';
		return outString;
	}
	
	// push the null character
	stack.push('\0');

	while (inNumber != 0)
	{
		int remainder = inNumber % base;
		if (remainder > 9)
		{
			stack.push('a' + (remainder - 10));
		}
		else
		{
			stack.push('0' + remainder);
		}
		inNumber = inNumber / base;
	}

	if (isNegative)
		stack.push('-');

	// write our string!
	while (!stack.isEmpty())
	{
		outString[index] = stack.pop();
		index++;
	}

	return outString;
}

int main()
{
	char buffer[100];
	char* output;
	int x = 1234;
	output = itoa(x, buffer, Decimal);
	std::cout << output << "\n";
	x = -1234;
	output = itoa(x, buffer, Decimal);
	std::cout << output << "\n";
	x = 1234;
	output = itoa(x, buffer, Octal);
	std::cout << output << "\n";
	output = itoa(x, buffer, Hexadecimal);
	std::cout << output << "\n";

	int c;
	std::cin >> c;
	return 0;
}
