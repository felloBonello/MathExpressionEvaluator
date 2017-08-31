/**	@file: UI_Prototype_main.cpp
@author Garth Santor/Trinh Han
@author garth.santor@sympatico.ca
@author http://www.gats.ca/
@version 0.0.2
@date 2012-11-13
@note Compiles under Visaul C++ v120

@brief Demonstrates and ee user interface.
*/
#include <iostream>

#include "expression_evaluator.hpp"
#include <locale>
#include <string>
using namespace std;

int main() {
	cout.imbue(locale(""));
	cout << "Expression Evaluator, (c) 1998-2015 Justin Bonello\n";
	for (unsigned count = 0; ; ++count) {
		try
		{
		cout << "> ";
		string command;
		getline(cin, command);
		if (!cin || command.empty())
			break;

		auto result = ExpressionEvaluator().evaluate(command);
		cout << "[" << count << "] = " << result->to_string() << endl;
		}
		catch (exception e)
		{
			cout << e.what() << endl;
			continue;
		}
	}
}


/*=============================================================

Revision History

Version 0.0.2: 2014-10-29
Updated copyright.

Version 0.0.1: 2012-11-13
Updated copyright.

Version 0.0.0: 2009-11-26
Alpha release.

=============================================================

Copyright Garth Santor/Trinh Han

The copyright to the computer program(s) herein
is the property of Garth Santor/Trinh Han of Canada.
The program(s) may be used and/or copied only with
the written permission of Garth Santor/Trinh Han
or in accordance with the terms and conditions
stipulated in the agreement/contract under which
the program(s) have been supplied.
=============================================================*/