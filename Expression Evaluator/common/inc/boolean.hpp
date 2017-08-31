#if !defined(GUARD_boolean_hpp20091126_)
#define GUARD_boolean_hpp20091126_

/** @file: boolean.hpp
	@author Garth Santor/Trinh Han
	@author garth.santor@sympatico.ca
	@author http://www.gats.ca/
	@version 0.1.1
	@date 2012-11-13
	@note Compiles under Visaul C++ v110

	@brief Boolean class declaration.
	*/

#include "operand.hpp"

class Boolean : public Operand
{
public:
	using value_type = bool;
	DEF_POINTER_TYPE(Boolean)
private:
	bool val;
public:
	Boolean(bool b) : val(b) {}
	value_type get_value() const { return val; }
	string_type to_string() const { return val ? "true" : "false"; }
	DEF_IS_CONVERTABLE_FROM(Boolean)
};

	class False : public Boolean
	{
	public:
		False() : Boolean(false) {}
	/*	bool get_value() const { return false; }
		string_type to_string() const { return "false"; }*/
		DEF_POINTER_TYPE(False)
		DEF_IS_CONVERTABLE_FROM(False)
	};

	class True : public Boolean
	{
	public:
		True() : Boolean(true) {}
		//bool get_value() const { return true; }
		//string_type to_string() const { return "true"; }
		DEF_POINTER_TYPE(True)
		DEF_IS_CONVERTABLE_FROM(True)
	};

/*=============================================================

Revision History

Version 0.1.1: 2012-11-13
C++ 11 cleanup

Version 0.1.0: 2010-11-09
Switched boost::shared_ptr<> to std::shared_ptr<>.
Added TOKEN_PTR_TYPE macro.

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
#endif // GUARD_boolean_hpp20091126_
