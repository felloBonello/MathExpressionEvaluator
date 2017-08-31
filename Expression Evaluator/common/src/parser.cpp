/** @file: parser.cpp
	@author Garth Santor/Trinh Han
	@author garth.santor@sympatico.ca
	@author http://www.gats.ca/
	@version 1.0.0
	@date 2012-11-13
	@note Compiles under Visaul C++ v120

	@brief Parser class implementation.
	*/

#include "parser.hpp"
#include "function.hpp"
#include "operand.hpp"
#include "operator.hpp"
#include "pseudo_operation.hpp"


TokenList Parser::parse( TokenList const& infixTokens ) {
	TokenList outPutQ;
	TokenList opStack;

	for (unsigned int i = 0; i < infixTokens.size(); ++i) 
	{
		if (std::dynamic_pointer_cast<Operand>(infixTokens[i]))
			outPutQ.push_back(infixTokens[i]);
		else if (std::dynamic_pointer_cast<Function>(infixTokens[i]))
			opStack.push_back(infixTokens[i]);
		else if (std::dynamic_pointer_cast<ArgumentSeparator>(infixTokens[i]))
		{ 
			int j = opStack.size() - 1;
			while (j >= 0 && !(std::dynamic_pointer_cast<LeftParenthesis>(opStack[j])))
			{
				outPutQ.push_back(opStack[j]);
				opStack.pop_back();
				--j;
			}
		}
		else if (std::dynamic_pointer_cast<LeftParenthesis>(infixTokens[i]))
			opStack.push_back(infixTokens[i]);
		else if (std::dynamic_pointer_cast<RightParenthesis>(infixTokens[i]))
		{
			int j = opStack.size() - 1;
			while (j >= 0 && !(std::dynamic_pointer_cast<LeftParenthesis>(opStack[j])))
			{
				outPutQ.push_back(opStack[j]);
				opStack.pop_back();
				--j;
			}
			if (j < 0)
			{
				std::cout << "Right parenthesis, has no matching left parenthesis";
				return TokenList();
			}
			opStack.pop_back();
			if (opStack.size() > 0 && std::dynamic_pointer_cast<Function>(opStack[opStack.size() - 1]))
			{ 
				outPutQ.push_back(opStack[opStack.size() - 1]);
				opStack.pop_back();
			}
		}
		else if (std::dynamic_pointer_cast<Operator>(infixTokens[i]))
		{
			while (opStack.size() > 0)
			{
				if (!std::dynamic_pointer_cast<Operator>(opStack[opStack.size() - 1]))
					break;
				if(std::dynamic_pointer_cast<UnaryOperator>(infixTokens[i]))
					break;
				auto pLAO = std::dynamic_pointer_cast<LAssocOperator>(infixTokens[i]);
				auto pO = std::dynamic_pointer_cast<Operator>(opStack[opStack.size() - 1]);
				if (pLAO && (pLAO->get_precedence() > pO->get_precedence()))
					break;
				auto pRAO = std::dynamic_pointer_cast<RAssocOperator>(infixTokens[i]);
				if (pRAO && (pRAO->get_precedence() >= pO->get_precedence()))
					break;
				outPutQ.push_back(opStack[opStack.size() - 1]);
				opStack.pop_back();
			}
			opStack.push_back(infixTokens[i]);
		}
		else
		{
			std::cout << "Unknown token";
			return TokenList();
		}
	}
	while (opStack.size() > 0)
	{
		if (std::dynamic_pointer_cast<LeftParenthesis>(opStack[opStack.size() - 1]))
		{
			std::cout << "Missing right-parenthesis";
			return TokenList();
		}
		outPutQ.push_back(opStack[opStack.size() - 1]);
		opStack.pop_back();
	}
	return outPutQ;
}


/*=============================================================

Revision History
Version 1.0.0: 2014-10-31
Visual C++ 2013

Version 0.0.1: 2012-11-13
C++ 11 cleanup

Version 0.0.0: 2009-12-02
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
