/** @file: RPNEvaluator.cpp
	@author Garth Santor/Trinh Han
	@author garth.santor@sympatico.ca
	@author http://www.gats.ca/
	@version 0.0.1
	@date 2012-11-13
	@note Compiles under Visaul C++ v110

	@brief RPN Evaluator class implementation.
	*/

#include "RPNEvaluator.hpp"
#include "integer.hpp"
#include "operator.hpp"
#include "operation.hpp"
#include "operand.hpp"
#include "variable.hpp"
#include <cassert>
#include <stack>
#include <list>
#include <map>
#include "boost/function.hpp"
#include <functional>





Operand::pointer_type RPNEvaluator::evaluate( TokenList const& rpnExpression )
{

	std::stack<Operand::pointer_type> operandStack;

	for( TokenList::const_iterator currentTokenPtr = rpnExpression.begin(); currentTokenPtr != rpnExpression.end(); ++currentTokenPtr ) {
		// process operands
		if( is<Operand>( *currentTokenPtr ) ) {
			operandStack.push( convert<Operand>( *currentTokenPtr ) );
			continue;
		}

		// token is an operation
		Operation::pointer_type operation = convert<Operation>( *currentTokenPtr );
		assert( operation && "Expecting operation but none found" );

		// enough params?
		unsigned nArgs = operation->number_of_args();
		if( nArgs > operandStack.size() ) {
			std::string error( "Insufficient # operands for operation" );
			error += operation->to_string();
			throw std::exception( error.c_str() );
		}

		// make a param list
		OperandList params;
		while( nArgs-- ) {
			params.push_front( operandStack.top() );
			operandStack.pop();
		}
		if (!(is<Assignment>(operation))) 
		{
			if (is<Variable>(params.front()))
			{
				Variable::value_type var = get_value<Variable>(params.front());
				params.pop_front();
				params.push_front(var) ;
			}
			if (is<Variable>(params.back()))
			{
				Variable::value_type var = get_value<Variable>(params.back());
				params.pop_back();
				params.push_back(var);
			}
		}			
			
		operandStack.push( operation->perform(params) );
	}



	if( operandStack.size() > 1 )
		throw std::exception( "Error: too many operands" );

	if( operandStack.empty() )
		throw std::exception( "Error: insufficient operands" );



	return operandStack.top();
}



/*=============================================================

Revision History

Version 0.0.1: 2012-11-13
C++ 11 cleanup

Version 0.0.0: 2009-12-10
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
