#if !defined(GUARD_real_hpp20091125_)
#define GUARD_real_hpp20091125_

/** @file: real.hpp
	@author Garth Santor/Trinh Han
	@author garth.santor@sympatico.ca
	@author http://www.gats.ca/
	@date 2012-11-13
	@version 1.0.0
	@note Compiles under Visaul C++ v120

	@brief Real class declaration.
	*/

#include "operand.hpp"
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/math/constants/constants.hpp>



/** Real number token. */
class Real : public Operand {
public:
	DEF_POINTER_TYPE(Real)
	using value_type = boost::multiprecision::number < boost::multiprecision::cpp_dec_float<1000, int32_t, void> > ;
private:
	value_type	value_;
public:
	Real( value_type value = value_type(0) ) : value_( value ) { }
	value_type				get_value() const { return value_; }
	string_type				to_string() const;

	DEF_IS_CONVERTABLE_FROM(Real)

	//Token::pointer_type perform_pow(Operand::pointer_type);
};


/** Pi constant token. */
class Pi : public Real {
public:
	Pi() : Real( boost::math::constants::pi<value_type>() ) { }
	DEF_IS_CONVERTABLE_FROM(Pi)
};


/** Euler constant token. */
class E : public Real {
public:
	E() : Real(boost::math::constants::e<value_type>() ) { }

	DEF_IS_CONVERTABLE_FROM(E)

	Operand::pointer_type perform_power(OperandList valueStack) {}
};

/*=============================================================

Revision History
Version 1.0.0: 2014-10-29
C++ 11 refactor.
Switched value_type to boost::multiprecision::cpp_dec_float_100

Version 0.1.1: 2012-11-13
C++ 11 cleanup

Version 0.1.0: 2010-11-09
Switched boost::shared_ptr<> to std::shared_ptr<>.
Added TOKEN_PTR_TYPE macro.

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
#endif // GUARD_real_hpp20091125_
