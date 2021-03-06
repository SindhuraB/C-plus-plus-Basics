/********************************************************************
* ASSIGNMENT 3 - LINEAR INSERTION SORT
*
* This program will sort numbers from a given file in ascending file
* Steps:
* 1) The user will be prompted to enter the name of the file that needs to be sorted
* 2) The filename will be validated (whether it exists or not) and then opened
* 3) SortingArray function will sort the numbers in the file into the array required
* 4) The array will sort the numbers using the following method:
*	-> Number of numbers in the file will be found
*	-> First number will be manually entered
*	-> For the rest of the numbers: Each will be taken into a temp variabel newVal.
		newVal will be compared with the array elements. The position where there is
		an element higher than newVal will be recorded. 
	-> If there are elements in the array larger than newVal, the recordedPosition
		will be used to push all the larger elements to the side so the newVal can
		entered at that position
	-> If newVal is larger than all other array elements, it will be put at the end
		of the array.
* 5) Array will be displayed
* 6) User will be asked for new file name. This loop will continue until * is entered. 
*
* Written by Sindhura L Boppudi (slb170330)
* CS 1337. 004
* Professor: John Cole
*********************************************************************/

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ios>

using namespace std;

//FUNCTION PROTOTYPE
string fileNameAndValidation();
void sortingFunction(ifstream &inputFile, string fileName);

int main()
{
	ifstream inputFile;
	string fileName;
	bool fileIsRunning = true;

	while (fileIsRunning)
	{
		fileName = fileNameAndValidation();					//Obtain and validate file name from user

		if (fileName == "0")								//If function returns 0, that means user entered 0 and program ends.
		{
			fileIsRunning = false;
			return 0;
		}
	
		sortingFunction(inputFile, fileName);

	}

	system("pause");

    return 0;
}

//Function to take name of file and validate it.
string fileNameAndValidation()
{
	string fileName;

	ifstream inputFile;

	cout << "Enter the name of the file containing data, or * to exit program: ";			//Prompt user to enter file name
	getline(cin, fileName);

	//If asterix is entered, exit program
	if (fileName == "*")
	{
		return 0;
	}

	inputFile.open(fileName);

	//Validate File
	//Check if it can be opened. If it cannot, prompt user for new file name
	while (!inputFile.is_open())
	{
		cout << "Please enter a valid file name: ";
		getline(cin, fileName);
		
		//If asterix is entered, exit program
		if (fileName == "*")
		{
			return 0;
		}

		inputFile.open(fileName);
	}

	if (fileName == "*")
	{
		return 0;
	}
	else
		return fileName;
}

//Function to sort numbers from file, sort them as they are put into an array and then display the sorted array
void sortingFunction(ifstream &inputFile, string fileName)
{

	double newValue = 0;
	int numValues = 0, index = 0, requiredPosition = 0, arrayCounter = 0;
	const int SIZE = 100;

	inputFile.open(fileName);							//Open File required

	double sortingArray[SIZE];							//Create array of max size 100

	while (inputFile >> newValue)						//Count number of elements in file 
	{
		numValues++;
	}

	inputFile.clear();
	inputFile.seekg(0);									//Go back to beginning of file

	//SORTING STARTS HERE***************************************************************
	
	//Manually insert 1st number from the file

	//First array element
	inputFile >> sortingArray[0];

	//Increase counter to count number of elements in array
	arrayCounter++;

	for (; arrayCounter <= numValues; arrayCounter++)
	{
		inputFile >> newValue;

		//Find the position where the array element before is smaller and after the position is larger. 
		//For this, we only need to find out where the larger numbers end as the array elements are already in ascending order
		//For example: If newVal is 4 and array elements are 1, 3, 5, position would be array[2]
		for (int ix = 0; ix < numValues; ix++)
		{
														//Search for first number larger than newVal
			if (newValue <= sortingArray[ix])
			{
				requiredPosition = ix;					// Once first largest number is found, break from the loop. 
				break;
			}
		}

		//Determine if newVal is the largest number to be introduced into the array. if it is, then put it at the end. 
		//if it isnt, shift array elements and then insert element in newfound position. 
		if (newValue > sortingArray[arrayCounter -1])
		{
				sortingArray[arrayCounter] = newValue;
		}
		else
		{
			//Push larger numbers up one array element
			//Start from the bottom. Compare the new number with each element.

			//Example: Array: 1, 3, 5, 6, 7, 10 ; NewValue = 4; therefore all larger numbers are pushed. 
			//Array would become 1, 3, [], 5, 6, 7, 10. Then 4 would be put in [].

			for (int index = 1; index <= (arrayCounter - requiredPosition); index++)
			{
				if (arrayCounter != numValues)
					sortingArray[arrayCounter - index + 1] = sortingArray[arrayCounter - index];
			}

														//Insert newVal at the postion 
			sortingArray[requiredPosition] = newValue;

		}
	}

	//DISPLAY SORTED ARRAY

	cout << endl << "Here are the numbers in the file given, in ascending order:" << endl;

	for (int ix = 0; ix < numValues; ix++)
	{
		cout << sortingArray[ix] << endl;
	}

	cout << "" << endl << endl;

	//Close the file.
	inputFile.close();

}
