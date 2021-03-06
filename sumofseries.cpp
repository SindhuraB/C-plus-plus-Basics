/*****************************************************************************************************
* ASSIGNMENT 1 - SUM OF A SERIES PROGRAM
*
* This program will calculate the sum of a series using the formula 1/N+ 2/(N-1) + ... N/1,
* where N is user's input.
* The user will be prompted to enter a number above 1, or 0 if they wish to exit the program. 
* If a number below 0 or the number 1 is entered, an error message will be shown and the user
* will be re-prompted to enter another number.
* If a non-number character is entered, an error message will be shown and the user will be told 
* to only enter valid numbers and re prompted for input
* The program will continue to ask user for input, show the sum, and re prompt user for next output 
* until 0 is entered
*
* Written by Sindhura L Boppudi (slb170330)
* CS 1337. 004
* Professor: John Cole
******************************************************************************************************/

#include "stdafx.h"
#include <iostream>

using namespace std;


/****Function Prototypes*************************************
Two functions in addition to the main function will be used
One is to prompt the user for input and validate it
The second is to calculate the sum of the series and display it
****************************************************************/

int getNumber();
void calculateAndDisplay(int);

int main()
{
	int userInput;

	//Call function to get number from the user
	userInput = getNumber();

	//Loop to keep prompting the user for input until 0 is entered
	while (userInput != 0)
	{
		calculateAndDisplay(userInput);

		//Ask for new number again
		userInput = getNumber();
	}

	system("pause");
    return 0;
}

int getNumber() 
{
	//Create variable for user input
	int input;

	//Ask for input
	cout << "Enter a number greater than 1, or 0 to exit: ";
	cin >> input;
	
	//Validate input
	
	//If input is not integer type (as previously initialized) then show error message and ask for new input
	while (cin.fail())	
	{
		cout << "Only numbers must be entered." << endl << "Enter a number above 1, or 0 to exit: ";

		//Clear input stored
		cin.clear();
		cin.ignore(100, '\n');

		//Ask for new input
		cin >> input;
	}

	while (input <= 0 || input == 1)
	{	
		//Exit program if number entered is 0. Return it if it isn't 0
		if (input == 0)
			exit(0);

		//Ask user to re enter a number if it is a 1, or less than 0, or not a number
		cout << "Number entered is not valid. Enter a number above 1, or 0 to exit: ";
		cin >> input;
	}

	return input;
}

void calculateAndDisplay(int userInput)
{
	//Make variable for sum
	double sum = 0;

	//Loop to calculate sum. ix will be the variable that changes the fractions
	for (int ix = 0; ix < userInput; ix++)
	{
		//Add to sum starting from 1/userInput till userInput/1
		sum += (1.0 + ix) / (userInput - ix);
	}

	cout << "The number entered is " << userInput << endl;
	cout << "The sum of the series is " << sum << endl;
}