/*********************************************************************
* ASSIGNMENT 07 - RECURSIVE FUNCTION
*
* This program demonstrates the use of a recursive function to check whether
* a string entered by the user is a palindrome or not. 
*
* It includes two functions:
* (1) RemoveWhitespace: As it's name implies, this function removes whitespace 
*		from the user entered string as well as punctuation and returns a 
*		filtered string that is all lowercase.
* (2) isPalindrome: This function checks whether the filtered string is a 
*		palindrome or not.
*
* Written by Sindhura L Boppudi (slb170330)
* CS 1337. 004
* Professor: John Cole
*********************************************************************/

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <cctype>

using namespace std;

//FUNCTION PROTOTYPE
void removeWhitespace(string&);
bool isPalindrome(string);

int main()
{
	string userInp;

	while (true)
	{
		//Ask user for string
		cout << "Enter a string: ";
		getline(cin, userInp);

		//If user enters string of length 0, exit program all together
		if (userInp == "")
		{
			return 0;
		}

		//Pass user input by reference to function that removes whitespace and punctuation
		removeWhitespace(userInp);

		//Call the recursive function
		if (isPalindrome(userInp))
		{
			cout << "The string you have entered is a palindrome." << endl;
		}
		else
			cout << "The string you have entered is not a palindrome."<< endl;
	
		cout << "" << endl;
	}

    return 0;
}

void removeWhitespace(string &s)
{
	//Create loop to go through each character of the string. 
	//If the character is a whitespace or puntuation, shift all the other characters one space to the left and delete the last character
	//Start checking again from the beggining
	for (int ix = 0; ix < s.length(); ix++)
	{
		if (isspace(s[ix]) || ispunct(s[ix]))
		{
			for (int iy = ix; (iy+1) < s.length(); iy++)
			{
				s[iy] = s[iy + 1];
			}
			s.erase((s.length()-1), 1);
			ix = 0;	//Check from the beginning again
		}
	}

	//Convert all characters to lower case so they can be compared directly later in the program
	for (int ix = 0; ix < s.length(); ix++)
	{
		s.at(ix) = tolower(s.at(ix));
	}
}

bool isPalindrome(string s)
{
	int numChars = s.length();

	if (s.at(0) == s.at(numChars - 1)) //Address the fact that numchars will be one more than the array position of char in string.
	{
		//When string has odd number of characters, it will be reduced to one character if it is a palindrome
		if (numChars <= 1)
		{
			return true;
		}
		//When there are only two characters in the string, if they are equal then it is a palindrome
		else if (numChars == 2)
		{
			return true;
		}

		//This will create a substring with all the same characters of string s without the characters at the two ends that have already been established to be equal to each other
		//Example: "kayak" will become "aya" and isPalindrome function will be called for "aya" string.
		s = s.substr(1, numChars - 2);
		return isPalindrome(s);

	}
	else
		return false;
}