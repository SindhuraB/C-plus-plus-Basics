/**************************************************************************
* ASSIGNMENT 2 - MAGIC SQUARE PROGRAM
*
* This program will create a magic square of an order chosen by the user. 
* First the user will be prompted to enter a valid number which will be 
* passed on as the order for the dynamic array used to create the magic 
* square. This array will be filled using the method specified by French 
* diplomat de la Loubère. 
*
* The working and specifications are mentioned in the comments before each function.
*
* Written by Sindhura L Boppudi (slb170330)
* CS 1337. 004
* Professor: John Cole
**************************************************************************/

//HEADERS
#include "stdafx.h"
#include <iostream>
#include <iomanip>

/*FUNCTION PROTOTYPES******************************************************
* There will be two functions in this program: 
* 
* (1) To get users input: 
* The user will be prompted to enter a number. The number will be validated
* and returned to the main function.
* 
* (2) To calculate and display the magic square:
* This function will take the user's input, use it to create a dynamic array 
* of the same order, and proceed to display the magic square to the user.
* It will also display the magic sum of the magic square.
* 
***************************************************************************/
int getUserInput();
void calculateSquare(int);

using namespace std;

int main()
{
	int userInput;

	userInput = getUserInput();

	//Until user ends program, keep asking for input and printing magic sqaure
	while (userInput != 0)
	{
		cout << " " << endl;

		calculateSquare(userInput);

		userInput = getUserInput();

	}

	system("pause");

    return 0;
}

/*WORKING************************************************************************
* The user will be prompted to enter an odd number larger than or equal to 3
* If they enter a non-integer character, an even number or a number less than 3,
* they will be shown an error message and re-prompted.
* If 0 is entered, the user will exit the program.
********************************************************************************/
int getUserInput()
{
	int userInput;

	cout << "*Enter an odd number greater than or equal to 3, or 0 to exit: ";
	cin >> userInput;

	//End program if user enters 0
	if (userInput == 0)
		return 0;
	
	//VALIDATE INPUT.
	while ((userInput < 3) || userInput % 2 == 0 || cin.fail())
	{
	
		//End program if user enters 0
		if (userInput == 0)
			return 0;

		cout << "Input is invalid." << endl;

		//Display that only numbers must be entered if user enters a letter/any other character
		if (cin.fail())
		{
			cout << "Only numbers must be entered." << endl;

			//Clear input stored
			cin.clear();
			cin.ignore(100, '\n');

			//Display common error message and ask user for input again
			cout << "*Enter an odd number greater than or equal to 3, or 0 to exit: ";
			cin >> userInput;
		}

		
		//Display that user must enter an odd number if number entered is even
		if (userInput % 2 == 0)
		{
			cout << "Number must be an odd number." << endl;

			//Display common error message and ask user for input again
			cout << "*Enter an odd number greater than or equal to 3, or 0 to exit: ";
			cin >> userInput;
		}


		//Display that number must be above 3 or 0 
		if (userInput < 3 && userInput != 0)
		{
			cout << "Number must be 3 or above." << endl;

			//Display common error message and ask user for input again
			cout << "*Enter an odd number greater than or equal to 3, or 0 to exit: ";
			cin >> userInput;
		}		
	}
	return userInput;
}

/*WORKING************************************************************************
* The user input will act as the order for the dynamic array created here.
* 
* To Fill Square:
* Step 1: 1 is assigned to middle square of the first row (order/2 +1)
* Step 2: The next number is filled by moving diagonally up and right.
*
* NOTE 1: If moving diagonally results in exiting the magic square, the next 
* number is filled by wrapping around the square.
* NOTE 2: If the spot which is diagonal from the current number is filled,
* the spot below the current number is filled and then Step 2 continues.\
*
* The last element of the square is not filled by the method layed out above, 
* and must be filled in seperately. 
* 
*******************************************************************************/

void calculateSquare(int input)
{
	int ORDER = input;

	//Create 2D Dynamic Array
	int* magicSquare = new int[ORDER * ORDER];

	//Initialize array so all elements are 0
	for (int ix = 0; ix < ORDER * ORDER; ix++)
		magicSquare[ix] = 0;
	
	int currentRow = 0;						//For current element
	int currentCol = (ORDER / 2);			//For current element
	int newRow, newCol;						//Variables to determine where the next element should be entered
	int magicSum = 0;						//To store the magic sum

	//The Last element must be filled in seperately 
	//It will always be on the opposite side of 1.
	magicSquare[(ORDER - 1) *	ORDER + currentCol] = ORDER * ORDER;

	//Loop to fill in elements diagonally in the array
	for (int arrayElement = 1; arrayElement < ORDER * ORDER; arrayElement++)
	{
		magicSquare[currentRow * ORDER + currentCol] = arrayElement;

		//Assign new row and column
		//These variables are needed to test if the array is filled or not, later in the code
		newRow = currentRow - 1;
		newCol = currentCol + 1;

		//If the new row or new column causes the element to exit the box then WRAP AROUND
		
		//Check if row is within the box
		if (newRow < 0)
			newRow = ORDER - 1;
		
		//Check if column is within the box
		if (newCol > (ORDER - 1))
			newCol = 0;

		//If array spot is filled, go down one space from the current element
		//Otherwise assign new row and column values to current row and col variables for the loop
		if (!magicSquare[newRow * ORDER + newCol] == 0)
		{
			newRow = currentRow + 1;
			newCol = currentCol;

			if (newRow > (ORDER - 1))
				newRow = 0;
		}

		if (magicSquare[newRow * ORDER + newCol] == 0)
		{
			currentRow = newRow;
			currentCol = newCol;
		}
	}

	//Print the magic square
	for (int rowCount = 0; rowCount < ORDER; rowCount++)
	{
		for (int colCount = 0; colCount < ORDER; colCount++)
		{
			cout << magicSquare[rowCount * ORDER + colCount] << " " ;
		}
		cout << endl;
	}

	//Calculate Magic Sum
	//Set the column as a constant and move through the row
	for (int tempRow = 0; tempRow < ORDER; tempRow++)
	{
		magicSum += magicSquare[tempRow * ORDER + 0];
	}

	//Display the Magic Sum
	cout << " " << endl;
	cout << "The Magic Sum of a Magic Square of order " << ORDER << "x" << ORDER << " is " << magicSum << endl;
	cout << " " << endl;

	delete[] magicSquare;
}