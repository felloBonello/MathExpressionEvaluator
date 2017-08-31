#if !defined(GUARD_operation_hpp20091210_)
#define GUARD_operation_hpp20091210_

/** @file: operation.hpp
	@author Garth Santor/Trinh Han
	@author garth.santor@sympatico.ca
	@author http://www.gats.ca/
	@version 0.1.1
	@date 2012-11-13
	@note Compiles under Visaul C++ v110
	@brief Operation class declaration.
	*/


#include "token.hpp"
#include "operand.hpp"
#include <stack>
#include <list>



/** Operation token base class. */
class Operation : public Token {
public:
	DEF_POINTER_TYPE(Operation)
	virtual unsigned number_of_args() const = 0;
	virtual ~Operation() {}

	virtual Operand::pointer_type perform(OperandList) = 0;

	class XOperation : public std::exception {
		string_type	operation_;
		string_type	operand_;
	public:
		XOperation(string_type const& operand, string_type const& operation, char const* msg)
			: std::exception(msg)
			, operation_(operation)
			, operand_(operand)
		{ }

		/**	Gets the expression string containing the bad character. */
		string_type	get_operation() const { return operation_; }
	};

	/** Bad character exception class. */
	class XBadOperand : public XOperation
	{
	public:
			XBadOperand(string_type const& operand, string_type const& operation)
			: XOperation(operand, operation, "Error: Incompatible operand for operation.") { }
	};

	class XTypeMismatch : public XOperation
	{
	public:
		XTypeMismatch(string_type const& operand1, string_type const& operand2)
			: XOperation(operand1, operand2, "Error: Operand types are not compatible.") { }
	};

	class XNonVariable : public XOperation
	{
	public:
		XNonVariable(string_type const& operand, string_type const& operation)
			: XOperation(operand, operation, "Error: assignment to a non-variable.") { }
	};

	class XDivideByZero : public XOperation
	{
	public:
		XDivideByZero(string_type const& operand, string_type const& operation)
			: XOperation(operand, operation, "Error: cannot divide by 0.") { }
	};
};






/*=============================================================

Revision History

Version 0.1.1: 2012-11-13
C++ cleanup.

Version 0.1.0: 2010-11-09
Switched boost::shared_ptr<> to std::shared_ptr<>.
Added TOKEN_PTR_TYPE macro.

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
#endif // GUARD_operation_hpp20091210_
