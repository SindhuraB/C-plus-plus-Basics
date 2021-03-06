/*********************************************************************************
* ASSIGNMENT 05 - EMPLOYEE TRACKING SYSTEM
* 
* This program will perform multiple tasks to keep track of a maximum of 100 
* employees and all their information.
* 
* It will check if a file "Employee.txt" already exists. If it doesnt, one will be created.
* If it does exist, all the information will be taken from the file and put into a new
* object (Employee class, one object for each employee) via a dynamically allocated array. 
* The number of employee records will be determined and stored for later use.
* 
* The menu will have 5 options:
* (1) Add new employee: 
*	->This function will ask the user to enter the data of the new employee
*	->The number of employees that have been entered from the file will be used to 
*		determine the position of array of pointers.
*	->A new Employee object will be created at this position, initialised using the data
*	->The counter for number of employees will be increased and passed back to main 
*		function by reference
* 
* (2) Display Employee Info:
*	->This function will use bubble sort to arrange all the employees in alphabetic order
*		(according to their last names)
*	->It will then display all the information of the employees in that order.
*
*(3) Search for Employee:
*	->User will be asked for employee ID.
*	->ID will be taken in and compared with all the id's stored
*	->If it matches an existing id, the information of that employee will be displayed
*	->If it does not match an existing id, an error message will be shown
*
*(4) Delete Employee:
*	->User will be asked for employee ID
*	->Position of the employee with that ID will be recorded
*	->If employee with that id does not exist, error message will be shown
*	->If employee with that ID does exist, that employee object will be deleted
*		and the employees recorded after that employee in the array of pointers will
*		be moved up so there isn't an empty array element.
*	->Counter keeping track of number of employees will be decremented.
*
*(5) Save data to file
*	->Employee.txt file will be cleared
*	->All employee objects will be saved to the file.
*
* Written by Sindhura L Boppudi (slb170330)
* CS 1337. 004
* Professor: John Cole
*********************************************************************************/

#include "stdafx.h"
#include <iostream>
#include "Employee.h"
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

//Global const for size of dynamic array
const int MAX = 100;

//FUNCTION PROTOTYPES
/********************************************************************/
int insertEmployeeInfo(fstream &employeeFile, Employee *empInfo[MAX]);
void newEmployee(int &numEmps, Employee *empInfo[MAX]);
void displayInfo(int numEmps, Employee *empInfo[MAX]);
void searchAndDisplay(int numEmps, Employee *empInfo[MAX]);
void deleteEmployee(int &numEmps, Employee *empInfo[MAX]);
void saveData(int numEmps, Employee *empInfo[MAX]);
/********************************************************************/

int main()
{
	//Variable for user's input for menu choice
	int userChoice;
	
	//Keep a counter for number of employees . It will also be 
	//used as a counter for the dynamic array so the position of a newEmployee will be determined
	int numEmps = 0;

	//Create dynamically allocated array
	Employee *empInfo[MAX];

	//Initialise File so that it can be read from and written to.

	fstream employeeFile("Employee.txt", ios::in | ios::out | ios::app);
	//(ios::in | ios::out | ios::app) allows the Employee file to act as an input and output file

	if (employeeFile.is_open())
	{
		//Get new entryPoint for dynamic array counter, after employee info from file is put in. This will also be the number of employees in the file.
		numEmps = insertEmployeeInfo(employeeFile, empInfo);
	}

	//Open file.
	employeeFile.open("Employee.txt");

	while (true)
	{
		//Create menu
		cout << "Choose one of the following menu options:" << endl;
		cout << "(1) Enter new employee information" << endl;
		cout << "(2) Display all employee information" << endl;
		cout << "(3) Search for employee, using employee ID" << endl;
		cout << "(4) Remove/Delete employee from database" << endl;
		cout << "(5) Save all data to external file and exit" << endl;

		cin >> userChoice;

		//Navigate menu
		switch (userChoice)
		{
		case 1:	//Create new employee
			newEmployee(numEmps, empInfo);
			numEmps++;
			break;
		
		case 2:	//Display all employee info
			displayInfo(numEmps, empInfo);
			break;
		
		case 3:	//Search for a specific employee
			searchAndDisplay(numEmps, empInfo);
			break;
		
		case 4:	//Delete a certain employee
			deleteEmployee(numEmps, empInfo);
			break;
		
		case 5:	//Write all employee information to Employee.txt file and exit program
			saveData(numEmps, empInfo);
			return 0;
		
		default:
			cout << "Please enter valid menu option." << endl;
		}
	}
    return 0;
}

/***WORKING**************************************************************
* Find number of employees in file 
* Take in employee info and make a new object with info as parameters
************************************************************************/
int insertEmployeeInfo(fstream &employeeFile, Employee *empInfo[MAX])
{
	//Variables for needed employee info
	string employeeID, lastName, firstName, birthDate, startDate, temp;
	char gender;
	double salary;
	int numLines = 0;

	//Count number of lines, aka employees, in file for for loop that will be used to enter employee info into dynamic array. 
	while (getline(employeeFile, temp, '\n'))
	{
		numLines++;
	}

	//Go back to the beginning of the file so it can be processed
	employeeFile.clear();
	employeeFile.seekg(0, ios::beg);

	for (int ix = 0; ix < numLines; ix++)
	{
		employeeFile >> employeeID >> lastName >> firstName >> birthDate >> gender >> startDate >> salary;
		
		//Create new object in dynamic array
		empInfo[ix] = new Employee(employeeID, lastName, firstName, birthDate, gender, startDate, salary);
		
	}
	return numLines;
}

/***WORKING*************************************************************
* This function will ask the user to enter the data of the new employee
* The number of employees that have been entered from the file will be used to 
*	determine the position of array of pointers.
* A new Employee object will be created at this position, initialised using the data
* The counter for number of employees will be increased and passed back to main 
*	function by reference
************************************************************************/
void newEmployee(int &numEmps,Employee *empInfo[MAX])
{
	//Variables for needed employee info
	string employeeID, lastName, firstName, birthDate, startDate;
	char gender;
	double salary;

	cout << "Enter the following information to add a new employee:" << endl;
	cout << "Employee ID: ";
	cin >> employeeID;
	cout << "First Name: ";
	cin >> firstName;
	cout << "Last Name: ";
	cin >> lastName;
	cout << "Birth Date: ";
	cin >> birthDate;
	cout << "Gender: ";
	cin >> gender;
	cout << "Start Date: ";
	cin >> startDate;
	cout << "Salary: ";
	cin >> salary;

	empInfo[numEmps] = new Employee(employeeID, lastName, firstName, birthDate, gender, startDate, salary);
}

/***WORKING****************************************************************
* Using bubble sort, the employees will be sorted in alphabetical order
*	->A do-while loop will be used. 
*	->All last names will be compared in a for loop. 
*	->If statement will be used to swap employee info and set boolean to true 
*	->Boolean will be set to true only when swapping takes place, so once 
*		swapping is finished, boolean will remain false and do-while loop will end.
*	->Employee info will be displayed.
***************************************************************************/
void displayInfo(int numEmps, Employee *empInfo[MAX])
{
	bool swap;
	Employee *temp[1];
	do
	{
		swap = false;

		for (int ix = 0; ix+1 < numEmps; ix++)
		{
			//Compare strings 
			if (empInfo[ix + 1]->getLastName() < empInfo[ix]->getLastName())
			{
				temp[0] = empInfo[ix];
				empInfo[ix] = empInfo[ix + 1];
				empInfo[ix + 1] = temp[0];
				swap = true;

			}
		}
	} while (swap);

	cout << setw(15) << "Employee ID" << setw(15)  << "Last Name" << setw(15)  << "First Name" << setw(15) << "Birth Date";
	cout << setw(10) << "Gender" << setw(15) << "Start Date" << setw(15) << "Salary" << endl;

	for (int ix = 0; ix < numEmps; ix++)
	{
		cout << setw(15) << empInfo[ix]->getEmpID();
		cout << setw(15) << empInfo[ix]->getLastName() << setw(15) << empInfo[ix]->getFirstName();
		cout << setw(15) << empInfo[ix]->getBirthDate() << setw(10) << empInfo[ix]->getGender();
		cout << setw(15) << empInfo[ix]->getStartDate() << setw(10) << fixed << setprecision(0) << empInfo[ix]->getSalary() << endl;
	}
}

/***WORKING*************************************************************
* User will be asked for employee ID.
* ->ID will be taken in and compared with all the id's stored using a 
*		for loop.
* ->If-statement will be used to switch boolean to true to break the 
*		for-loop when id is found. Position will be recorded. 
* ->If it matches an existing id, the information of that employee will be displayed
* ->If it does not match an existing id, an error message will be shown
***********************************************************************/
void searchAndDisplay(int numEmps, Employee *empInfo[MAX])
{
	string empID;
	int reqPosition;
	bool idExists = false;

	cout << "Enter the ID of the employee: ";
	cin >> empID;

	//Compare entered id with stored id's
	for (int ix = 0; ix < numEmps; ix++)
	{
		if (empInfo[ix]->getEmpID() == empID)
		{
			idExists = true;	//Once the id is found, set boolean to true
			reqPosition = ix;	//Record position of matching id
			break;				//Exit loop
		}
	}

	if (idExists)		//Display info
	{
		cout << endl << "Employee ID: " << empInfo[reqPosition]->getEmpID() << endl;
		cout << "Name: " << empInfo[reqPosition]->getFirstName() << " " << empInfo[reqPosition]->getLastName() << endl;
		cout << "Birth Date: " << empInfo[reqPosition]->getBirthDate() << endl;
		cout << "Gender: " << empInfo[reqPosition]->getGender() << endl;
		cout << "Start Date: " << empInfo[reqPosition]->getStartDate() << endl;
		cout << "Salary: " << empInfo[reqPosition]->getSalary() << endl;
		cout << "" << endl;
	}
	else				//Display error message
	{
		cout << "There is no employee with this ID" << endl << endl;
	}
}

/***WORKING****************************************************************
* Ask user for id of employee they want to delete
* Find position of that employee using for loop. When the id is found, position
*	in array will be recorded and loop will be broken
* If ID doesnt exist, error message will be shown, otherwise:
* Delete that employee object
* Shift all other employee objects so that the array is still continuous
*	using for loop
**************************************************************************/
void deleteEmployee(int &numEmps, Employee *empInfo[MAX])
{
	string empID;
	int reqPosition;
	bool idExists = false;

	cout << "Enter the ID of the employee: ";
	cin >> empID;

	//Compare entered id with all stored id's
	for (int ix = 0; ix < numEmps; ix++)
	{
		if (empInfo[ix]->getEmpID() == empID)
		{
			idExists = true;	//Once the id is found, set boolean to true
			reqPosition = ix;	//Record position of matching id
			break;				//Exit loop
		}
	}

	if (idExists)		//If id is valid, delete the employee
	{
		delete empInfo[reqPosition];

		for (int ix = reqPosition; ix < numEmps; ix++)
		{
			empInfo[ix] = empInfo[ix + 1];
		}

		numEmps--;
	}
	else
	{
		cout << "ID entered is invalid." << endl;		//If id in invalid, show error message
	}
}

/***WORKING****************************************************************
* Employee.txt file will be cleared.
* All the employee objects will be saved in Employee.txt using a for loop.
***************************************************************************/
void saveData(int numEmps, Employee *empInfo[MAX])
{
	//Clear file.
	fstream employeeFile("Employee.txt", ios::in | ios::out | ios::trunc);

	//Save all data to it
	for (int ix = 0; ix < numEmps; ix++)
	{
		employeeFile << empInfo[ix]->getEmpID() << " " << empInfo[ix]->getLastName() << " " << empInfo[ix]->getFirstName() << " ";
		employeeFile << empInfo[ix]->getBirthDate() << " " << empInfo[ix]->getGender() << " " << empInfo[ix]->getStartDate() << " " << empInfo[ix]->getSalary() << endl;
	}
}
