/** @file: tokenizer.cpp
	@author Garth Santor/Trinh Han
	@author garth.santor@sympatico.ca
	@author http://www.gats.ca/
	@version 0.2.0
	@date 2012-11-16
	@note Compiles under Visaul C++ v110

	@brief Tokenizer class implementation.
	*/

#include "tokenizer.hpp"
#include "boolean.hpp"
#include "function.hpp"
#include "integer.hpp"
#include "operator.hpp"
#include "pseudo_operation.hpp"
#include "real.hpp"
#include "variable.hpp"

#include <exception>
#include <limits>
#include <sstream>
#include <stack>
#include <string>
using namespace std;
using value_type = boost::multiprecision::cpp_int;

/** Default constructor loads the keyword dictionary. */
Tokenizer::Tokenizer() {
	keywords_["ARCTAN2"] = make<Arctan2>();
	keywords_["MAX"]			= make<Max>();
	keywords_["MIN"]				= make<Min>();
	keywords_["POW"]			= make<Pow>();

	keywords_["ARCCOS"]		= make<Arccos>();
	keywords_["ARCSIN"]			= make<Arcsin>();
	keywords_["ARCTAN"]		= make<Arctan>();
	keywords_["CEIL"]				= make<Ceil>();
	keywords_["COS"]				= make<Cos>();
	keywords_["EXP"]					= make<Exp>();
	keywords_["FLOOR"]			= make<Floor>();
	keywords_["LB"]					= make<Lb>();
	keywords_["LN"]					= make<Ln>();
	keywords_["LOG"]				= make<Log>();
	keywords_["SIN"]					= make<Sin>();
	keywords_["SQRT"]				= make<Sqrt>();
	keywords_["TAN"]				= make<Tan>();

	keywords_["PI"]		= make<Pi>();
	keywords_["E"]		= make<E>();

	keywords_["ABS"]		= make<Abs>();
	keywords_["RESULT"]	= make<Result>();
	keywords_["BINARY"] = make<Binary>(); 
	
	keywords_["TRUE"]		= make<True>();
	keywords_["FALSE"]	= make<False>();
	keywords_["MOD"]		= make<Modulus>();
	keywords_["AND"]		= make<And>();
	keywords_["OR"]			= make<Or>();
	keywords_["XOR"]		= make<Xor>();
	keywords_["NAND"]		= make<Nand>();
	keywords_["NOR"]		= make<Nor>();
	keywords_["XNOR"]		= make<Xnor>();
	keywords_["NOT"]		= make<Not>();
}




/** Get an identifier from the expression.
	Assumes that the currentChar is pointing to a alphabetic.
	*/
Token::pointer_type Tokenizer::_get_identifier( Tokenizer::string_type::const_iterator& currentChar, Tokenizer::string_type const& expression ) {
	// accumulate identifier
	static dictionary_type variables_;
	string_type ident;
	do
		ident += toupper(*currentChar++);
	while( currentChar != end(expression) && isalnum( *currentChar ) );

	// check for predefined identifier
	dictionary_type::iterator keyIter = keywords_.find(ident);
	dictionary_type::iterator varIter = variables_.find(ident);
	if (keyIter != end(keywords_))
		return keyIter->second;
	else if (varIter != end(variables_))
		return varIter->second;
	else
	{
		variables_[ident] = make<Variable>();
		return variables_.find( ident )->second;
	}
}




/** Get a number token from the expression.
	@return One of BinaryInteger, Integer, or Real.
	@param currentChar [in,out] an iterator to the current character.  Assumes that the currentChar is pointing to a digit.
	@param expression [in] the expression being scanned.
*/
Token::pointer_type Tokenizer::_get_number(Tokenizer::string_type::const_iterator& currentChar, Tokenizer::string_type const& expression) {
	assert( isdigit( *currentChar ) && "currentChar must pointer to a digit" );
	
	value_type accumulator = *currentChar - '0';
	++currentChar;

	while (currentChar != end(expression) && isdigit(*currentChar)) {
		accumulator = (accumulator * 10) + (*currentChar - '0');
		++currentChar;
	}

	if (currentChar != end(expression) && *currentChar == '.')
	{
		using RealNum = boost::multiprecision::number < boost::multiprecision::cpp_dec_float<1000, int32_t, void>>;
		++currentChar;
		int count = 0;
		while (currentChar != end(expression) && isdigit(*currentChar)) {
			++count;
			accumulator = (accumulator * 10) + (*currentChar - '0');
			++currentChar;
		}
		RealNum realNum = RealNum(accumulator);
		RealNum decimal = RealNum("0.1");

		for (int i = 0; i < count; ++i)
		{
			realNum *= decimal;
		}

		RealNum conversion = pow(10, -count);
		//realNum *= conversion;
		return make<Real>(realNum);
	}
	else
		return make<Integer>( accumulator );
}

Token::pointer_type Tokenizer::_internalAnalyzer(Tokenizer::string_type::const_iterator& currentChar, Token::pointer_type& prevToken, Tokenizer::string_type const& expression)
{
	// check of end of expression
	if (*currentChar == '/0')
		return make<EndOfExpression>();

	// check for a number
	if (isdigit(*currentChar)) {
		return _get_number(currentChar, expression);
	}

	if (*currentChar == '=')
	{ 
		++currentChar;
		if (currentChar != end(expression) && *currentChar == '=')
		{ 
			++currentChar;
			return make<Equality>();
		}
		else
		{
			return make<Assignment>();
		}
	}

	if (*currentChar == '(')
	{
		++currentChar;
		return make<LeftParenthesis>();
	}

	if (*currentChar == ')')
	{
		++currentChar;
		return make<RightParenthesis>();
	}

	if (*currentChar == '*')
	{
		++currentChar;
		return make<Multiplication>();
	}

	if (*currentChar == '/')
	{
		++currentChar;
		return make<Division>();
	}

	if (*currentChar == '%')
	{
		++currentChar;
		return make<Modulus>();
	}

	if (*currentChar == '#')
	{
		++currentChar;
		return make<Power>();
	}

	if (*currentChar == ',')
	{
		++currentChar;
		return make<ArgumentSeparator>();
	}

	if (*currentChar == '!')
	{
		++currentChar;
		if (currentChar != end(expression) && *currentChar == '=')
		{
			++currentChar;
			return make<Inequality>();
		}
		else
		{ 
			return make<Factorial>();
		}
	}

	if (*currentChar == '+')
	{
		++currentChar;
		if (dynamic_pointer_cast<RightParenthesis>(prevToken) || dynamic_pointer_cast<Operand>(prevToken) || dynamic_pointer_cast<Factorial>(prevToken))
			return make<Addition>();
		else
			return make<Identity>();
	}

	if (*currentChar == '-')
	{
		++currentChar;
		if (dynamic_pointer_cast<RightParenthesis>(prevToken) || dynamic_pointer_cast<Operand>(prevToken) || dynamic_pointer_cast<Factorial>(prevToken))
			return make<Subtraction>();
		else
			return make<Negation>();
	}

	if (*currentChar == '>')
	{
		++currentChar;
		if (currentChar != end(expression) && *currentChar == '=')
		{
			++currentChar;
			return make<GreaterEqual>();
		}
		else
		{
			return make<Greater>();
		}
	}

	if (*currentChar == '<')
	{
		++currentChar;
		if (currentChar != end(expression) && *currentChar == '=')
		{
			++currentChar;
			return make<LessEqual>();
		}
		else
		{
			return make<Less>();
		}
	}

	if (isalpha(*currentChar))
	{
		return _get_identifier(currentChar, expression);
	}

	// not a recognized token
	throw XBadCharacter(expression, currentChar - begin(expression));
}

Token::pointer_type Tokenizer::_getNextToken(Tokenizer::string_type::const_iterator& currentChar, Token::pointer_type& prevToken, Tokenizer::string_type const& expression)
{
	Token::pointer_type nextToken = _internalAnalyzer(currentChar, prevToken, expression);
	if (dynamic_pointer_cast<Function>(prevToken) && !(dynamic_pointer_cast<LeftParenthesis>(nextToken)))
		throw XBadCharacter(expression, currentChar - begin(expression));
	prevToken = nextToken;
	return nextToken;
}



/** Tokenize the expression.
	@return a TokenList containing the tokens from 'expression'. 
	@param expression [in] The expression to tokenize.
	@note Tokenizer dictionary may be updated if expression contains variables.
	@note Will throws 'BadCharacter' if the expression contains an un-tokenizable character.
	*/
TokenList Tokenizer::tokenize( string_type const& expression ) {
	TokenList tokenizedExpression;
	Token::pointer_type prevToken = (make<LeftParenthesis>());
	auto currentChar = expression.cbegin();

	for(;;)
	{
		while (currentChar != end(expression) && isspace(*currentChar))
			++currentChar;

		if (currentChar == end(expression))
			break;
		// strip whitespace

		tokenizedExpression.push_back(_getNextToken(currentChar, prevToken, expression));
	}

	if (tokenizedExpression.size() == 1 && is<Boolean>(tokenizedExpression[0]))
		if(is<False>(tokenizedExpression[0]))
			tokenizedExpression[0] = make<Boolean>(false);
		else
			tokenizedExpression[0] = make<Boolean>(true);

	return tokenizedExpression;
}

/*=============================================================

Revision History

Version 0.2.0: 2012-11-16
Added BitAnd, BitNot, BitOr, BitXOr, BitShiftLeft, BitShiftRight
Simplified CHECK_OP macros

Version 0.1.0: 2012-11-15
Replaced BadCharacter with XTokenizer, XBadCharacter, and XNumericOverflow
Added BinaryInteger, Binary <function>

Version 0.0.1: 2012-11-13
C++ 11 cleanup

Version 0.0.0: 2009-11-25
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
