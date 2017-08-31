/** @file: expression_evaluator.cpp
	@author Garth Santor/Trinh Han
	@author garth.santor@sympatico.ca
	@author http://www.gats.ca/
	@version 0.0.1
	@date 2012-11-13
	@note Compiles under Visaul C++ v110

	@brief ExpressionEvaluator class implementation.
	*/

#include "expression_evaluator.hpp"
#include "tokenizer.hpp"
#include "parser.hpp"
#include "RPNEvaluator.hpp"
#include "function.hpp"

#if defined(SHOW_STEPS)
#include <iostream>
#endif

ExpressionEvaluator::result_type ExpressionEvaluator::evaluate( ExpressionEvaluator::expression_type const& expr ) {
	TokenList infixTokens = tokenizer_.tokenize( expr );
#if defined(SHOW_STEPS)
	{ using namespace std;
		cout << "Lexer output" << endl;
		copy( infixTokens.begin(), infixTokens.end(), ostream_iterator<Token::pointer_type>( cout, " " ) );
		std::cout << std::endl;
	}
#endif

	TokenList postfixTokens = parser_.parse( infixTokens );
#if defined(SHOW_STEPS)
	{ using namespace std;
		cout << "Parser output" << endl;
		copy( postfixTokens.begin(), postfixTokens.end(), ostream_iterator<Token::pointer_type>( cout, " " ) );
		std::cout << std::endl;
	}
#endif

	Operand::pointer_type result = rpn_.evaluate( postfixTokens );
	//Result::push( result );
	//if (is<Variable>(result))
	//	return convert<Variable>(result)->get_value();


	return result;
}

/*=============================================================

Revision History

Version 0.0.0: 2010-10-31
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
