/***********************************************************************
* Source:
*    Infix.cpp
* Summary:
*    This will contain just the prototype for the convertInfixToPostfix()
*    function
* Author
*    Justin Chandler, Jeremy Chandler, Nathan Bench
************************************************************************/

#include "infix.h"
#include <string>
using namespace std;
	/*****************************************************
	 * TEST INFIX TO POSTFIX
	 * Prompt the user for infix text and display the
	 * equivalent postfix expression
	 *****************************************************/
	void testInfixToPostfix()
	{
		// The Infix expression which the user inputs
		string input;
		
		char token, topToken;
		Stack<char> opStack;

		// The postFix expressoin
		string postFixExp;

		const string BLANK = " ";
		for (int i = 0; i < input.length(); i++)
		{
			token = input[i];
			switch (token)
			{
			case '*': break;
			default: break;

			}

		}

		cout << "Enter an infix equation. Type \"quit\" when done."
			<< "\ninfix > ";
		getline(cin, input);
		
	}

	/*****************************************************
	 * TEST INFIX TO ASSEMBLY
	 * Prompt the user for infix text and display the
	 * resulting assembly instructions
	 *****************************************************/
	void testInfixToAssembly()
	{

	}


