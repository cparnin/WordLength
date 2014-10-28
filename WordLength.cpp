/******************* Read Words From A File  ********************
Name:  Chad Parnin
Date:  Feb 2, 2014
Homework#:  HW 1
Source File:  Hw1.cpp
Action:  Program inputs a text file, then counts word lengths.
	     It will display the frequency of various word lengths as 
		 well as the average length of each word.
		 Words are counted as alphanumeric characters and apostrophes.
		 Hyphens are not counted as word length, however
		 words that are hyphenated followed by a newline are counted
		 as one word, but the hyphen is not included (just like a nor-
		 mal word would be).
		 Words longer than 15 are treated as a 15 letter word.
*******************************************************************/

#include <iostream>
#include <iomanip>
using namespace std;

int WordLength();
void DisplayResults(int WordLengths[15 + 1], double TotalLengths, int Words);

int main()
{
	int WordLengths[15 + 1] = { 0 };  // array of word frequencies
	double TotalWordLength = 0;
	int TotalWords = 0;

	int Length = WordLength();  // get a word length
	while (Length != 0)
	{
		if (Length > 15)
			Length = 15;
		++WordLengths[Length];  // increment the index of that word length
		TotalWordLength += Length;
		++TotalWords;
		Length = WordLength();  // get another
	}
	
	DisplayResults(WordLengths, TotalWordLength, TotalWords);

	return 0;
}

/*************  Count Word Length  *******************
Action:  Calculates the length of a single word
Parameters:  None
Returns:  The word length
Precondition:  None
*****************************************************/

int WordLength()
{
	int Length = 0;
	char Ch;

	cin.get(Ch);

	while (Ch == ' ')  // if it starts with spaces, get another
		cin.get(Ch);

	while ((cin.good()) && (Ch != ' ') && (Ch != '\n'))  // while not eof, space, newline
	{
		if (isalnum(Ch) || (Ch == '\''))  // increment length if alphanumeric or apostrophe
		{
			++Length;
		}
		else if (Length == 0)  // if no length, get another
		{
			cin.get(Ch);
			if ((isalnum(Ch)) || (Ch == '\''))
			{
				++Length;  // NOW if it's valid, increment length and get another
				cin.get(Ch);
				continue;  // go back to while condition
			}
			else
			{
				while ((!isalnum(Ch)) || (Ch != '\''))  // while not valid, get another
				{
					cin.get(Ch);
					if ((isalnum(Ch)) || (Ch == '\''))  // if valid NOW, increment length and break out of while loop
					{
						++Length;
						break;
					}
				}
			}
		}
		else if ((Ch == '-') && (cin.peek() == '\n'))  // if line ends with hyphen, ignore both (to accumulate word length)
			cin.ignore(2, '\n');
		else if ((Ch == '-') && (cin.peek() != '\n'))  // if hyphen in middle of line, return length of word
			return Length;
		cin.get(Ch);  // get another
	}

	return Length;  // return length of word
}

/***************   Display Results  **********************
Action:			Displays table showing word frequencies
Parameters
		IN:		The total Length of all words
				The number of words
		OUT:	The array holding the frequency of various
				word lengths (although it doesn't need to 
				go back to the main function)
Returns:		Nothing
Precondition:   WordLengths points to an integer array
			    and is within the boundary of the array
**********************************************************/

void DisplayResults(int WordLengths[15 + 1], double TotalLengths, int Words)
{
	cout << "\n\nWord Length" << "\t" << "Frequency" << endl;
	cout << setfill('-') << setw(11) << "-" << "\t";
	cout << setfill('-') << setw(9) << "-" << endl;;

	for (int i = 1; i < 16; i++)  // displays table
	{
		cout << setfill(' ') << setw(6) << i << "\t";
		cout << setw(13) << WordLengths[i] << endl;
	}

	if (TotalLengths == 0)  // if no words
		cout << "\nAverage Word Length: 0" << endl << endl;
	else
	{
		cout << "\nAverage Word Length: ";
		cout << setprecision(7) << (TotalLengths / Words) << endl << endl;
	}
}