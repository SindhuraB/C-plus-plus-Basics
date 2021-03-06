/*********************************************************************************
* ASSIGNMENT 06 - BANK CLASSES
* 
* This program enables the user to create three types of bank accounts: general, savings and checking
* The user will be able to enter the account number, account holder's name, balance 
* and additional info depending on the account type.
*
* 3 Classes are implemented in this program. 1 base class (Bank) and 2 derived classes (savings and checking)
* 
* The user will first be prompted to pick an option from a menu. Each option will call a different function.
* (1) Create Savings account: 
*		This will enable the user to enter the general bank info along with additional parameters
*		such as annual interest and compund period. Once the account number is entered, itll check if 
*		the account already exists. If the account exists, the user will be asked if they want to go back
*		to the main menu or enter another account number. If account with the entered account number does
*		not exists, a new Savings account object will be created. 
* (2) Create Checkings accout:
*		Works similar to the create savings accoutn function but will create a Checkings Account object
*		with the extra bank info parameters of minimum balance and monthly fee. Will validate account number
*		similar to Savings account function.
* (3) Create general account:
*		Will create a bank account without any additonal parameters. Will validate account number similar to 
*		Savings account function.
* (4) Deposit money: 
*		Will ask user to enter account number. Will validate that account number. Amount to be deposited will be asked. 
*		Amount will be deposited in required account. 
* (5) Withdraw money: 
*		Will ask user to enter account number. Will validate that account number. Amount to be withdrawn will be asked. 
*		Amount will be witdrawn in required account. 
* (6) Display Info:
*		All the info entered will be displayed. Checkings and Savings accounts will be specified. 
* (7) Zero to Exit:
*		Will exit the function.
*
* Written by Sindhura L Boppudi (slb170330)
* CS 1337. 004
* Professor: John Cole
*********************************************************************************/

#include "stdafx.h"
#include "Bank.h"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

//max number of accounts ie size of array of pointers to bank objects
const int MAX = 10;

//FUNCTION PROTOTYPES
void createSavingsAccount(Bank *account[MAX], int &accountNum);
void createCheckingsAccount(Bank *account[MAX], int &accountNum);
void createGeneralAccount(Bank *account[MAX], int &accountNum);
void depositMoney(Bank *account[MAX], int accountNum);
void withdrawMoney(Bank *account[MAX], int accountNum);
void displayAccountInfo(Bank *account[MAX], int accountNum);

int main()
{
	int menuOption, accountNum = 0;

	//Dynamically allocate an array of objects 
	Bank *account[MAX];

	while (true)
	{
		account[accountNum] = new Bank;

		//Create  and display menu
		cout << "(1) Create a Savings account" << endl;
		cout << "(2) Create a Checkings account" << endl;
		cout << "(3) Create a general Bank account" << endl;
		cout << "(4) Deposit to Bank account" << endl;
		cout << "(5) Withdraw from Bank account" << endl;
		cout << "(6) Display information for all accounts" << endl;
		cout << "(7) Exit the program" << endl;

		cin >> menuOption;

		switch (menuOption)
		{
			case 1:
			{
				createSavingsAccount(account, accountNum);
				break;
			}
			case 2:
			{
				createCheckingsAccount(account, accountNum);
				break;
			}
			case 3:
			{
				createGeneralAccount(account, accountNum);
				break;
			}

			case 4:
			{
				depositMoney(account, accountNum);
				break;
			}
			case 5:
			{
				withdrawMoney(account, accountNum);
				break;
			}
			case 6:
			{
				displayAccountInfo(account, accountNum);
				break;
			}
			case 7: 
				return 0;
			default:
			{
				cout << "Please enter a valid menu option." << endl;
			}
		}
	}
    return 0;
}

/***WORKING********************************************************
User is asked for account number 
Account number is validated
	-> If account already exists, display error message and ask user to 
	either go back to the main menu or enter another account number
	-> If account doesnt exists, continue
User is asked for name, balance, annual interest and compound period. 
Savings account object is created in the array of pointers to bank objects
with all the required parameters.
Counter to keep track of number of accounts is increased
*******************************************************************/
void createSavingsAccount(Bank *account[MAX], int &accountNum)
{
	int userOption, cp;
	double aN, balance, annInt;
	bool accountExists = true;
	string name;

	cout << "Enter the account number: ";
	cin >> aN;

	//Check if account already exists and validate it
	/***VALIDATION METHOD****************************************************
	* Within a while loop, bool is set to false. A for-loop is used
	*	to go through all the existing bank objects (savings and checking).
	* If-statement within the for-loop compares all the account numbers
	*	of the created bank objects with the user entered account no.
	* If identical account number is found,boolean value is set to true
	*	so when/if new account number is entered, it will be validated again.
	* Loop will exit if account number entered by number is not already used
	*	because boolean is set to false intitally within the while-loop
	***********************************************************************/
	while (accountExists)
	{
		accountExists = false;

		for (int ix = 0; ix < accountNum; ix++)
		{
			if (account[ix]->getAccountNumber() == aN)
			{
				accountExists = true;			//If account number exists, set bool to true and show error message

				cout << "An account with the number you have entered already exists." << endl;
				cout << "Enter 0 to return to main menu or 1 to enter a different account number." << endl;
				cin >> userOption;

				if (userOption == 0)			//Return to main function and display menu again
				{
					return;
				}
				else							//Ask for new account number.
				{
					cout << "Enter the account number: ";
					cin >> aN;
					ix = 0;						//Set for-loop counter to 0 so new account number can be checked with all Bank array elements
				}

			}
		}
	}

	//Ask for the rest of the information
	cout << "Enter account holder's name: ";
	cin >> name;
	cout << "Enter current balance in account: ";
	cin >> balance;
	cout << "Enter rate of annual interest: ";
	cin >> annInt;
	cout << "Enter the compounding period (in days): ";
	cin >> cp;

	cout << "" << endl;

	account[accountNum] = new SavingsAccount (aN, name, balance, annInt, cp);
	accountNum++;
}

/***WORKING********************************************************
User is asked for account number
Account number is validated
	-> If account already exists, display error message and ask user to
	either go back to the main menu or enter another account number
	-> If account doesnt exists, continue
User is asked for name, balance, minimum balance and monthly fee.
Checking account object is created in the array of pointers to bank objects
with all the required parameters.
Counter to keep track of number of accounts is increased
*******************************************************************/
void createCheckingsAccount(Bank *account[MAX], int &accountNum)
{
	int userOption;
	double aN, balance, mb, mf;
	bool accountExists = true;
	string name;

	cout << "Enter the account number: ";
	cin >> aN;

	//Check if account already exists and validate it
	/***VALIDATION METHOD****************************************************
	* Within a while loop, bool is set to false. A for-loop is used
	*	to go through all the existing bank objects (savings and checking).
	* If-statement within the for-loop compares all the account numbers
	*	of the created bank objects with the user entered account no.
	* If identical account number is found,boolean value is set to true
	*	so when/if new account number is entered, it will be validated again.
	* Loop will exit if account number entered by number is not already used
	*	because boolean is set to false intitally within the while-loop
	***********************************************************************/
	while (accountExists)
	{
		accountExists = false;

		for (int ix = 0; ix < accountNum; ix++)
		{
			if (account[ix]->getAccountNumber() == aN)
			{
				accountExists = true;			//If account number exists, set bool to true and show error message

				cout << "An account with the number you have entered already exists." << endl;
				cout << "Enter 0 to return to main menu or 1 to enter a different account number." << endl;
				cin >> userOption;

				if (userOption == 0)			//Return to main function and display menu again
				{
					return;
				}
				else							//Ask for new account number.
				{
					cout << "Enter the account number: ";
					cin >> aN;
					ix = 0;						//Set for-loop counter to 0 so new account number can be checked with all Bank array elements
				}

			}
		}
	}

	//Ask for the rest of the information
	cout << "Enter account holder's name: ";
	cin >> name;
	cout << "Enter current balance in account: ";
	cin >> balance;
	cout << "Enter minimum balance (in dollars): ";
	cin >> mb;
	cout << "Enter monthly fee (in dollars): ";
	cin >> mf;

	cout << "" << endl;

	account[accountNum] = new CheckingAccount(aN, name, balance, mb, mf);

	accountNum++;
}

/***WORKING********************************************************
User is asked for account number
Account number is validated
	-> If account already exists, display error message and ask user to
	either go back to the main menu or enter another account number
	-> If account doesnt exists, continue
User is asked for name and balance
Bank object is created in the array of pointers to bank objects
with all the required parameters.
Counter to keep track of number of accounts is increased
*******************************************************************/
void createGeneralAccount(Bank *account[MAX], int &accountNum)
{
	int userOption;
	double aN, balance;
	bool accountExists = true;
	string name;

	cout << "Enter the account number: ";
	cin >> aN;

	//Check if account already exists and validate it
	/***VALIDATION METHOD****************************************************
	* Within a while loop, bool is set to false. A for-loop is used
	*	to go through all the existing bank objects (savings and checking).
	* If-statement within the for-loop compares all the account numbers 
	*	of the created bank objects with the user entered account no.
	* If identical account number is found,boolean value is set to true 
	*	so when/if new account number is entered, it will be validated again. 
	* Loop will exit if account number entered by number is not already used
	*	because boolean is set to false intitally within the while-loop
	***********************************************************************/
	while (accountExists)
	{
		accountExists = false;

		for (int ix = 0; ix < accountNum; ix++)
		{
			if (account[ix]->getAccountNumber() == aN)
			{
				accountExists = true;			//If account number exists, set bool to true and show error message

				cout << "An account with the number you have entered already exists." << endl;
				cout << "Enter 0 to return to main menu or 1 to enter a different account number." << endl;
				cin >> userOption;

				if (userOption == 0)			//Return to main function and display menu again
				{
					return;
				}
				else							//Ask for new account number.
				{
					cout << "Enter the account number: ";
					cin >> aN;
					ix = 0;						//Set for-loop counter to 0 so new account number can be checked with all Bank array elements
				}

			}
		}
	}

	//Ask for the rest of the information
	cout << "Enter account holder's name: ";
	cin >> name;
	cout << "Enter current balance in account: ";
	cin >> balance;
	cout << "" << endl;

	account[accountNum] = new Bank;

	account[accountNum]->setActNum(aN);
	account[accountNum]->setName(name);
	account[accountNum]->setBalance(balance);

	accountNum++;
}

/***WORKING***************************************************************
Boolean is created and initialised to false.
User will be asked for account number. 
Account number will be validated
	An if-statement within a for-loop will compare all the account numbers 
		of existing accounts with user-entered account number
	If account number exists, the array position will be recorded and boolean 
		will be set to true. 
	If account number does not exist, program continues without altering boolean
Boolean will be checked and used to determine if account exists or not. 
If account does not exists, user will be shown an error message and returned to main menu
If account exists, user will be asked for amount to deposit, bank object deposit 
	function will be called. This function will add the amount to the balance.
*************************************************************************/
void depositMoney(Bank *account[MAX], int accountNum)
{
	double reqAcctNumber, depAmt;
	int reqAcct;
	bool accountExists = false;

	//Ask user for act number to which funds need to be deposited
	cout << "Enter the account number: ";
	cin >> reqAcctNumber;

	//Acquire the array element position of the account. 
	for (int ix = 0; ix < accountNum; ix++)
	{
		if (account[ix]->getAccountNumber() == reqAcctNumber)
		{
			reqAcct = ix;
			accountExists = true;		//Bool used to determine if account exists in database or not
			break;
		}
	}

	if (accountExists)	//Deposit how much ever money into the account
	{
		cout << "Enter amount to be deposited into the account: ";
		cin >> depAmt;
		account[reqAcct]->deposit(depAmt);
	}
	else				//If account doesnt exist, give user error message and return to main menu
	{
		cout << "The account number entered is invalid." << endl;
		return;
	}
}

/***WORKING***************************************************************
Boolean is created and initialised to false.
User will be asked for account number.
Account number will be validated
	An if-statement within a for-loop will compare all the account numbers
		of existing accounts with user-entered account number
	If account number exists, the array position will be recorded and boolean
		will be set to true.
	If account number does not exist, program continues without altering boolean
Boolean will be checked and used to determine if account exists or not.
If account does not exists, user will be shown an error message and returned to main menu
If account exists, user will be asked for amount to withdraw, bank object withdraw
	function will be called. 
This function will subtract the amount from the balance.
*************************************************************************/
void withdrawMoney(Bank *account[MAX], int accountNum)
{
	double reqAcctNumber, wtdrwAmt;
	int reqAcct;
	bool accountExists = false;

	//Ask user for act number to which funds need to be deposited
	cout << "Enter the account number: ";
	cin >> reqAcctNumber;

	//Acquire the array element position of the account. 
	for (int ix = 0; ix < accountNum; ix++)
	{
		if (account[ix]->getAccountNumber() == reqAcctNumber)
		{
			reqAcct = ix;
			accountExists = true;		//Bool used to determine if account exists in database or not
			break;
		}
	}

	if (accountExists)	//Deposit how much ever money into the account
	{
		cout << "Enter amount to be withdrawn from account: ";
		cin >> wtdrwAmt;
		account[reqAcct]->withdraw(wtdrwAmt);
	}
	else				//If account doesnt exist, give user error message and return to main menu
	{
		cout << "The account number entered is invalid." << endl;
		return;
	}
}

/***WORKING***********************************************************
Within a for loop:
General bank info will be dislpayed first. 
Account type will be compared and respective extra info will be displayed
**********************************************************************/
void displayAccountInfo(Bank *account[MAX], int accountNum)
{
	//Print general bank info, determine which accounts are checking and which are saving, display respective extrainfo.
	for (int ix = 0; ix < accountNum; ix++)
	{
		//Display general bank info
		cout << setw(30) << left << "Account Number" << ": " << account[ix]->getAccountNumber() << endl;
		cout << setw(30) << left << "Account Type" << ": " << account[ix]->getAccountType() << endl;
		cout << setw(30) << left << "Name of Account Holder" << ": " << account[ix]->getName() << endl;
		cout << setw(30) << left << "Current Balance" << ": " << account[ix]->getBalance() << endl;

		//Check account type
		if (account[ix]->getAccountType() == "Savings")
		{
			//Display bank info for savings
			cout << setw(30) << left << "Annual Interest" << ": " << ((SavingsAccount*)account[ix])->getAnnInt() << endl;
			cout << setw(30) << left << "Compounding Period (in days)" << ": " << ((SavingsAccount*)account[ix])->getNumDays() << endl;

		}
		else if (account[ix]->getAccountType() == "Checking")
		{
			//Display extra bank info for checking account
			cout << setw(30) << left << "Minimum Balance" << ": " << ((CheckingAccount*)account[ix])->getMinBalance() << endl;
			cout << setw(30) << left << "Monthly Fee" << ": " << ((CheckingAccount*)account[ix])->getMonthlyFee() << endl;
		}

		cout << "" << endl;
	}
}