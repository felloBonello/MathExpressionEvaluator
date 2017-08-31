/**	@file: ut_tokens_main.cpp
	@author Garth Santor/Trinh Han
	@author garth.santor@sympatico.ca
	@author http://www.gats.ca/
	@version 0.2.0
	@date 2012-11-16
	@note Compiles under Visaul C++ v110

	@brief Token unit test.
	*/

// unit test library
#define BOOST_TEST_MODULE TokensUnitTest
#include <boost/test/auto_unit_test.hpp>

// Tokenizer system
#include "boolean.hpp"
#include "function.hpp"
#include "integer.hpp"
#include "operator.hpp"
#include "pseudo_operation.hpp"
#include "real.hpp"
#include "variable.hpp"

#include <boost/lexical_cast.hpp>
using boost::lexical_cast;
#include <string>
using namespace std;

#include <ut_test_phase.hpp>



#if TEST_INTEGER
BOOST_AUTO_TEST_CASE(integer_test) {
	BOOST_CHECK(Integer().get_value() == 0);
	BOOST_CHECK(Integer(42).get_value() == 42);
	BOOST_CHECK(
		Integer(Integer::value_type("123456789012345678901234567890")).get_value() == 
		Integer::value_type("123456789012345678901234567890"));
}
#endif // TEST_INTEGER



#if TEST_REAL
BOOST_AUTO_TEST_CASE(real_test) {
	BOOST_CHECK(Real().get_value() == 0.0);
	BOOST_CHECK(Real(4.2).get_value() == 4.2);
	BOOST_CHECK(
		Real(Real::value_type("12345678901234567890.1234567890")).get_value() ==
		Real::value_type("12345678901234567890.1234567890"));
}
#endif // TEST_REAL



#if TEST_BOOLEAN
BOOST_AUTO_TEST_CASE(boolean_test) {
	BOOST_CHECK(Boolean(false).get_value() == false);
	BOOST_CHECK(Boolean(true).get_value() == true);
	BOOST_CHECK(False().get_value() == false);
	BOOST_CHECK(True().get_value() == true);
}
#endif // TEST_BOOLEAN



#if TEST_VARIABLE
BOOST_AUTO_TEST_CASE(variable_test) {
	Integer::pointer_type pi(new Integer(4));
	Variable v;
	v.set_value(convert<Operand>(pi));
	BOOST_CHECK(v.get_value()->to_string() == pi->to_string());
}
#endif // TEST_VARIABLE




/** Test to see that all listed tokens are leaves. */
BOOST_AUTO_TEST_CASE( leaf_test )
{
	TokenList tl;
#define LOAD(type)\
	tl.push_back( make<type>() )


#if TEST_INTEGER
	LOAD(Integer);
#endif // TEST_INTEGER


#if TEST_UNARY_OPERATOR
	LOAD(Factorial);
	LOAD(Identity);
	LOAD(Negation);
#endif // TEST_UNARY_OPERATOR

#if TEST_BINARY_OPERATOR
	LOAD(Addition);
	LOAD(Division);
	LOAD(Multiplication);
	LOAD(Modulus);
	LOAD(Subtraction);
	LOAD(Power);
#endif // TEST_BINARY_OPERATOR


#if TEST_PARENTHESIS
	// Psuedo-operations
	LOAD(LeftParenthesis);
	LOAD(RightParenthesis);
#endif // TEST_PARENTHESIS


#if TEST_FUNCTION && TEST_SINGLE_ARG
	LOAD(Abs);
#endif // TEST_FUNCTION && TEST_SINGLE_ARG


#if TEST_FUNCTION && TEST_MULTI_ARG
	LOAD(Max);
	LOAD(Min);
	LOAD(Pow);
	LOAD(ArgumentSeparator);
#endif // TEST_INTEGER_MULTIPLE_PARAM_FUNCTIONS


#if TEST_REAL
	LOAD(Pi);
	LOAD(E);

	#if TEST_FUNCTION 
		#if TEST_SINGLE_ARG
			LOAD(Arccos);
			LOAD(Arcsin);
			LOAD(Arctan);
			LOAD(Ceil);
			LOAD(Cos);
			LOAD(Exp);
			LOAD(Floor);
			LOAD(Lb);
			LOAD(Ln);
			LOAD(Log);
			LOAD(Sin);
			LOAD(Sqrt);
			LOAD(Tan);
		#endif // TEST_SINGLE_ARG
		#if TEST_MULTI_ARG
			LOAD(Arctan2);
		#endif // TEST_MULTI_ARG
	#endif // TEST_FUNCTION
#endif // TEST_REAL

			
#if TEST_BOOLEAN
	LOAD(True);
	LOAD(False);
	
	#if TEST_UNARY_OPERATOR
		LOAD(Not);
	#endif // TEST_UNARY_OPERATOR
		
	#if TEST_BINARY_OPERATOR
		LOAD(And);
		LOAD(Nand);
		LOAD(Nor);
		LOAD(Or);
		LOAD(Xor);
		LOAD(Xnor);
		#if TEST_RELATIONAL_OPERATOR
			LOAD(Equality);
			LOAD(Greater);
			LOAD(GreaterEqual);
			LOAD(Inequality);
			LOAD(Less);
			LOAD(LessEqual);
		#endif // TEST_RELATIONAL_OPERATOR
	#endif // TEST_BINARY_OPERATOR
#endif // 


#if TEST_VARIABLE
	LOAD(Variable);
	
	#if TEST_BINARY_OPERATOR
		LOAD(Assignment);
	#endif // TEST_BINARY_OPERATOR


	#if TEST_FUNCTION
		#if TEST_SINGLE_ARG
			LOAD(Result);
		#endif // TEST_SINGLE_ARG
	#endif // TEST_FUNCTION
#endif // TEST_VARIABLE
#undef LOAD


	// validate non-convertability of leaf types
	for( size_t iCaller = 0; iCaller < tl.size() - 1; ++iCaller )
		for( size_t iResponder = iCaller + 1; iResponder < tl.size(); ++iResponder )
		{
			string s = string("Caller[") + boost::lexical_cast<string>(iCaller) + "] = " +
				tl[iCaller]->to_string() + "  Responder[" + lexical_cast<string>(iResponder) + "] = " +
				tl[iResponder]->to_string();
			BOOST_CHECK_MESSAGE( !tl[iCaller]->is_convertable_from( tl[iResponder] ), s.c_str() );

			s = string("Responder[") + boost::lexical_cast<string>(iResponder) + "] = " +
				tl[iResponder]->to_string() + "  Caller[" + lexical_cast<string>(iCaller) + "] = " +
				tl[iCaller]->to_string();
			BOOST_CHECK_MESSAGE( !tl[iResponder]->is_convertable_from( tl[iCaller] ), s.c_str() );
		}
}


/*=============================================================

Revision History

Version 1.0.0: 2014-10-29
Updated to Visual C++ 12

Version 0.2.0: 2012-11-16
Added BitAnd, BitNot, BitOr, BitShiftLeft, BitShiftRight

Version 0.1.0: 2012-11-15
Added BinaryInteger, Binary <function>

Version 0.0.1: 2012-11-13
C++ 11 cleanup.

Version 0.0.0: 2009-11-30
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
