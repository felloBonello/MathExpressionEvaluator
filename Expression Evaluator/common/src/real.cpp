/** @file: real.cpp
	@author Garth Santor/Trinh Han
	@author garth.santor@sympatico.ca
	@author http://www.gats.ca/
	@date 2012-11-13
	@version 1.0.0
	@note Compiles under Visaul C++ v120

	@brief Real class implementation.
	*/

#include "real.hpp"
#include "boolean.hpp"
#include "function.hpp"
#include "operator.hpp"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <sstream>
using namespace std;

//Token::pointer_type Real::perform_pow(Operand::pointer_type val)
//{
//	Real::value_type param1 = this->get_value();
//	Real::value_type param2 = dynamic_pointer_cast<Real>(val)->get_value();
//	Real::value_type result = pow(param1, param2);
//	return make<Real>(result);
//}

Real::string_type Real::to_string() const {
	ostringstream oss;
	oss << /*"Real: " << */fixed << setprecision(numeric_limits<value_type>::digits10) << value_;
	return oss.str();
}






/*=============================================================

Revision History
Version 1.0.0: 2014-10-29
C++ 11 refactor.
Switched value_type to boost::multiprecision::cpp_dec_float_100

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
