#if !defined(GUARD_variable_hpp20091126_)
#define GUARD_variable_hpp20091126_

/** @file: variable.hpp
	@author Garth Santor/Trinh Han
	@author garth.santor@sympatico.ca
	@author http://www.gats.ca/
	@date 2012-11-13
	@version 0.1.1
	@note Compiles under Visaul C++ v110

	@brief Variable class declaration.
	*/

#include "operand.hpp"

class Variable : public Operand
{
public:
	using value_type = Operand::pointer_type;
private:
	value_type val_pointer_;
public:
	Variable() : val_pointer_(NULL) {}
	Variable(value_type p) : val_pointer_(p) {}

	value_type get_value() const { return val_pointer_; }

	string_type to_string () const
	{
		if (val_pointer_ == NULL)
			return ("Variable: null");
		else
			return (val_pointer_->to_string()); 
	}
	
	void set_value(value_type p) { val_pointer_ = p; }
	DEF_POINTER_TYPE(Variable)
	DEF_IS_CONVERTABLE_FROM(Variable)
};

class Result : public Operand
{
public:
	//static vector<Operand::pointer_type> val_pointer_v_[];
	//Result() {}

	////vector<Operand::pointer_type> get_value() { return val_pointer_v_; }

	//static void push(Operand::pointer_type val_p) { val_pointer_v_.push_back(val_p); }
	//static void clear() { val_pointer_v_.push_back(NULL);  val_pointer_v_.clear(); }

	////string_type to_string()
	////{
	////	if (val_pointer_v_ == NULL)
	////		return ("Result: null");
	////	else
	//		return ("Result: " + val_pointer_v_->to_string());
	//}

	//void set_value(Operand::pointer_type p) { val_pointer_v_ = p; }
	DEF_POINTER_TYPE(Result)
	DEF_IS_CONVERTABLE_FROM(Result)
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
#endif // GUARD_variable_hpp20091126_
