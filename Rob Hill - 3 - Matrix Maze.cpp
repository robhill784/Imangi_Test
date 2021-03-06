/*
Imagni Studios Q3 - Matrix Spiral
By: Robert Hill

Want to showcase function pointers and pointer arithmetic to solve this

Time: ~ 1 hour
*/

#include "stdafx.h"
#include <iostream>
#include <stdio.h>


// struct to store info of the input matrix
struct myMatrix
{
	myMatrix(int* pFirstElement, int NumRows, int NumColumns)
	{
		pBegin = pFirstElement;
		minRowItteration = 0;
		minColumnItteration = 0;
		maxRowItteration = NumRows;
		maxColumnItteration = NumColumns;
		numRows = NumRows;
		numColums = NumColumns;
	}

	int* pBegin; // first element of matrix
	int minRowItteration;
	int minColumnItteration;
	int maxRowItteration;
	int maxColumnItteration;
	int numRows;
	int numColums;
	bool (*condition)(const int& x, const int& y); // function pointer of conditional in for loop
	int (*direction)(int z); // function pointer to increment or decrement in for loop
	int* (*getIndex)(const myMatrix& m, const int& i); // function pointer to get the address of matrix element
};

/* 
Below are fuction pointers to handle diferent ways to access data in a matrix 
int* (*getIndex)(myMatrix m, int i)

These hadle the general formula:
   matrix[I][J] =  firstElement + I x Number_Of_Columns + J
*/
int* goRight(const myMatrix& m, const int& i)
{
	return m.pBegin + m.minRowItteration * m.numColums + i;
}

int* goDown(const myMatrix& m, const int& i)
{
	return m.pBegin + i * m.numColums + (m.maxColumnItteration - 1);
}

int* goLeft(const myMatrix& m, const int& i)
{
	return m.pBegin + (m.maxRowItteration - 1) * m.numColums + i;
}

int* goUp(const myMatrix& m, const int& i)
{
	return m.pBegin + i * m.numColums + m.minColumnItteration;
}

/*
Below are fuction pointers to handle a conditional of a forloop
bool(*condition)(int x, int y)
*/
bool lessThan(const int& x, const int& y)
{
	return x < y ? true : false;
}

bool greaterThanOrEqual(const int& x, const int& y)
{
	return x >= y ? true : false;
}

/*
Below are fuction pointers to handle itteration (increment or decrement) of a for loop
int(*direction)(int z);
*/
int inc(int x)
{
	return x += 1;
}

int dec(int x)
{
	return x -= 1;
}

/*
A general function to copy value of matrix[i][j] to buffer.
Uses funtion pointers to decide behavior of the for loop and access to
the matrix element.

ASSUMPTION: OutBuffer is 1000 chars
*/
void traverseMatrix(
	int* Matrix,
	int start,
	int end,
	myMatrix curMatrix,
	char* OutBuffer
	)
{
	for (int i = start; curMatrix.condition(i, end); i = curMatrix.direction(i))
	{	
		char tmpBuffer[10] = {'\0'}; 	
		int* pValue = curMatrix.getIndex(curMatrix, i);
		_itoa_s(*pValue, tmpBuffer, sizeof(tmpBuffer), 10);
		strcat_s(OutBuffer, 1000, tmpBuffer);
		strcat_s(OutBuffer, 1000, ", ");
	}
}

/*
Entry function. Uses function pointers to drive the behavior and pointer arithmatic
to access values in the  matrix.

ASSUMPTIONS:
	1: OutBuffer is a null teminated c-string of length 1000 chars.
	2: Matrix, NumRows and NumColums are valid parameters passed in
*/
void BuildStringFromMatrix(int* Matrix, int NumRows, int NumColumns, char* OutBuffer)
{
	myMatrix theMatrix(Matrix, NumRows, NumColumns);
	while (
		theMatrix.minRowItteration < theMatrix.maxRowItteration &&
		theMatrix.minColumnItteration < theMatrix.maxColumnItteration)
	{		
		// Go Right
		// Initialize function pointers for traverseMatrix() 
		theMatrix.condition = lessThan;
		theMatrix.direction = inc;
		theMatrix.getIndex = goRight;

		traverseMatrix(
			Matrix,
			theMatrix.minColumnItteration,
			theMatrix.maxColumnItteration,
			theMatrix,
			OutBuffer
			);
		theMatrix.minRowItteration++;

		// Go down
		theMatrix.condition = lessThan;
		theMatrix.direction = inc;
		theMatrix.getIndex = goDown;
		traverseMatrix(
			Matrix,
			theMatrix.minRowItteration,
			theMatrix.maxRowItteration,
			theMatrix,
			OutBuffer
		);
		theMatrix.maxColumnItteration--;

		// Go Left
		if (theMatrix.minRowItteration < theMatrix.maxRowItteration)
		{
			theMatrix.condition = greaterThanOrEqual;
			theMatrix.direction = dec;
			theMatrix.getIndex = goLeft;
			traverseMatrix(Matrix,
				theMatrix.maxColumnItteration - 1,
				theMatrix.minColumnItteration,
				theMatrix,
				OutBuffer
			);
			theMatrix.maxRowItteration--;
		}

		// Go up
		if (theMatrix.minColumnItteration < theMatrix.maxColumnItteration)
		{
			theMatrix.condition = greaterThanOrEqual;
			theMatrix.direction = dec;
			theMatrix.getIndex = goUp;
			traverseMatrix(Matrix,
				theMatrix.maxRowItteration - 1,
				theMatrix.minRowItteration,
				theMatrix,
				OutBuffer
			);
			theMatrix.minColumnItteration++;
		}
	}
}


int main()
{
	int x = 3;
	int y = 4;
	// ASSUMING char buffer[0] = '\0'
	char buffer[1000] = {'\0'};

	int gh[2][2] = { {1,2},{1,2} };
	int* bh = &gh[0][0];


	int matrix[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
	
	BuildStringFromMatrix(matrix, 3, 4, buffer);

	//int matrix[25] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25 };

	//BuildStringFromMatrix(matrix, 5, 5, buffer);

	std::cout << buffer << '\n';

	system("pause");
    return 0;
}
