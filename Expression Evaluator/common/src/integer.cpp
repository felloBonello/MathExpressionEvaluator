/** @file: integer.cpp
	@author Garth Santor/Trinh Han
	@author garth.santor@sympatico.ca
	@author http://www.gats.ca/
	@date 2012-11-16
	@version 1.0.0
	@note Compiles under Visaul C++ v120

	@brief Integer class implementation.
	*/

#include "integer.hpp"
#include "function.hpp"
#include "operator.hpp"
#include "boolean.hpp"
#include "operand.hpp"
#include "real.hpp"
#include <boost/lexical_cast.hpp>
#include <array>
using namespace std;

//Token::pointer_type Integer::perform_pow(Operand::pointer_type val)
//{ 
//	Integer::value_type param1 = this->get_value();
//	Integer::value_type param2 = dynamic_pointer_cast<Integer>(val)->get_value();
//	Integer::value_type result = param1;
//	for (int i = 1; i < param2; ++i)
//	{
//		result = result * param1;
//		cout << result.str() << endl;
//	}
//	return make<Integer>(result);
//}

Integer::string_type Integer::to_string() const {
	return /*string_type("Integer: ") + */boost::lexical_cast<string_type>( get_value() );
}




/*=============================================================

Revision History
Version 1.0.0: 2014-10-29
C++ 11 refactor.
Converted Integer::value_type to boost::multiprecision::cpp_int

Version 0.2.0: 2012-11-16
Added Bit operators, Pow

Version 0.1.0: 2012-11-15
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
