#if !defined(GUARD_function_hpp20091126_)
#define GUARD_function_hpp20091126_

/** @file: function.hpp
	@author Garth Santor/Trinh Han
	@author garth.santor@sympatico.ca
	@author http://www.gats.ca/
	@version 1.0.0
	@date 2012-11-13
	@note Compiles under Visaul C++ v120

	@brief function token declarations.
	*/

#include "operation.hpp"
#include "integer.hpp"
#include "Real.hpp"
#include "Variable.hpp"
#include "Boolean.hpp"
#include "operator.hpp"

using namespace boost::multiprecision;
using namespace std;

/** Function token base class. */
class Function : public Operation { };

		/** One argument function token base class. */
		class OneArgFunction : public Function {
		public:
			virtual unsigned number_of_args() const { return 1; }
		};

				/** Absolute value function token. */
				class Abs : public OneArgFunction {
					DEF_IS_CONVERTABLE_FROM(Abs)
					Operand::pointer_type perform(OperandList valueStack)
					{
						if (is<Real>(valueStack.front()))
						{
							Real::value_type oldVal = get_value<Real>(valueStack.front());
							Real::value_type newVal = abs(oldVal);
							return convert<Operand>(make<Real>(newVal));
						}
						else if (is<Integer>(valueStack.front()))
						{
							Integer::value_type oldVal = get_value<Integer>(valueStack.front());
							Integer::value_type newVal = abs(oldVal);
							return convert<Operand>(make<Integer>(newVal));
						}
						else
							throw XBadOperand("Abs()", "Boolean");
					}
				};

				class Arccos : public OneArgFunction {
					DEF_IS_CONVERTABLE_FROM(Arccos)
					Operand::pointer_type perform(OperandList valueStack)
					{
						if (is<Real>(valueStack.front()))
						{
							Real::value_type oldVal = get_value<Real>(valueStack.front());
							Real::value_type newVal = acos(oldVal);
							return convert<Operand>(make<Real>(newVal));
						}
						else if (is<Integer>(valueStack.front()))
						{
							Real::value_type oldVal = convert_to_real(valueStack.front())->get_value();
							Real::value_type newVal = acos(oldVal);
							return convert<Operand>(make<Real>(newVal));
						}
						else
							throw XBadOperand("Arccos()", "Boolean");
					}
				};

				class Arcsin : public OneArgFunction {
					DEF_IS_CONVERTABLE_FROM(Arcsin)
					Operand::pointer_type perform(OperandList valueStack)
					{
						if (is<Real>(valueStack.front()))
						{
							Real::value_type oldVal = get_value<Real>(valueStack.front());
							Real::value_type newVal = asin(oldVal);
							return convert<Operand>(make<Real>(newVal));
						}
						else if (is<Integer>(valueStack.front()))
						{
							Real::value_type oldVal = convert_to_real(valueStack.front())->get_value();
							Real::value_type newVal = asin(oldVal);
							return convert<Operand>(make<Real>(newVal));
						}
						else
							throw XBadOperand("Arcsin()", "Boolean");
					}
				};

				class Arctan : public OneArgFunction {
					DEF_IS_CONVERTABLE_FROM(Arctan)
					Operand::pointer_type perform(OperandList valueStack)
					{
						if (is<Real>(valueStack.front()))
						{
							Real::value_type oldVal = get_value<Real>(valueStack.front());
							Real::value_type newVal = atan(oldVal);
							return convert<Operand>(make<Real>(newVal));
						}
						else if (is<Integer>(valueStack.front()))
						{
							Real::value_type oldVal = convert_to_real(valueStack.front())->get_value();
							Real::value_type newVal = atan(oldVal);
							return convert<Operand>(make<Real>(newVal));
						}
						else
							throw XBadOperand("Arctan()", "Boolean");
					}
				};

				class Ceil : public OneArgFunction {
					DEF_IS_CONVERTABLE_FROM(Ceil)
					Operand::pointer_type perform(OperandList valueStack)
					{
						if (is<Real>(valueStack.front()))
						{
							Real::value_type oldVal = get_value<Real>(valueStack.front());
							Real::value_type newVal = ceil(oldVal);
							return convert<Operand>(make<Real>(newVal));
						}
						else if (is<Integer>(valueStack.front()))
							return convert<Operand>(convert_to_real(valueStack.front()));
						else
							throw XBadOperand("Ceil()", "Boolean");
					}
				};

				class Cos : public OneArgFunction {
					DEF_IS_CONVERTABLE_FROM(Cos)
					Operand::pointer_type perform(OperandList valueStack)
					{
						if (is<Real>(valueStack.front()))
						{
							Real::value_type oldVal = get_value<Real>(valueStack.front());
							Real::value_type newVal = cos(oldVal);
							return convert<Operand>(make<Real>(newVal));
						}
						else if (is<Integer>(valueStack.front()))
						{
							Real::value_type oldVal = convert_to_real(valueStack.front())->get_value();
							Real::value_type newVal = cos(oldVal);
							return convert<Operand>(make<Real>(newVal));
						}
						else
							throw XBadOperand("cos()", "Boolean");
					}
				};

				class Exp : public OneArgFunction {
					DEF_IS_CONVERTABLE_FROM(Exp)
					Operand::pointer_type perform(OperandList valueStack)
					{
						if (is<Real>(valueStack.front()))
						{
							Real::value_type oldVal = get_value<Real>(valueStack.front());
							Real::value_type newVal = exp(oldVal);
							return convert<Operand>(make<Real>(newVal));
						}
						else if (is<Integer>(valueStack.front()))
						{
							Real::value_type oldVal = convert_to_real(valueStack.front())->get_value();
							Real::value_type newVal = exp(oldVal);
							return convert<Operand>(make<Real>(newVal));
						}
						else
							throw XBadOperand("exp()", "Boolean");
					}
				};

				class Floor : public OneArgFunction {
					DEF_IS_CONVERTABLE_FROM(Floor)
					Operand::pointer_type perform(OperandList valueStack)
					{
						if (is<Real>(valueStack.front()))
						{
							Real::value_type oldVal = get_value<Real>(valueStack.front());
							Real::value_type newVal = floor(oldVal);
							return convert<Operand>(make<Real>(newVal));
						}
						else if (is<Integer>(valueStack.front()))
							return convert<Operand>(convert_to_real(valueStack.front()));
						else
							throw XBadOperand("Floor()", "Boolean");
					}
				};

				class Lb : public OneArgFunction {
					DEF_IS_CONVERTABLE_FROM(Lb)
					Operand::pointer_type perform(OperandList valueStack)
					{
						if (is<Real>(valueStack.front()))
						{
							Real::value_type oldVal = get_value<Real>(valueStack.front());
							Real::value_type logVal = (log(oldVal));
							Real::value_type log2 = (log(2));
							Real::value_type newVal = round(logVal / log2);
							return convert<Operand>(make<Real>(newVal));
						}
						else if (is<Integer>(valueStack.front()))
						{
							Real::value_type oldVal = convert_to_real(valueStack.front())->get_value();
							Real::value_type logVal = (log(oldVal));
							Real::value_type log2 = (log(2));
							Real::value_type newVal = round(logVal / log2);
							return convert<Operand>(make<Real>(newVal));
						}
						else
							throw XBadOperand("Lb()", "Boolean");
					}
				};

				class Ln : public OneArgFunction {
					DEF_IS_CONVERTABLE_FROM(Ln)
					Operand::pointer_type perform(OperandList valueStack)
					{
						if (is<Real>(valueStack.front()))
						{
							Real::value_type oldVal = get_value<Real>(valueStack.front());
							Real::value_type newVal = log(oldVal);
							return convert<Operand>(make<Real>(newVal));
						}
						else if (is<Integer>(valueStack.front()))
						{
							Real::value_type oldVal = convert_to_real(valueStack.front())->get_value();
							Real::value_type newVal = log(oldVal);
							return convert<Operand>(make<Real>(newVal));
						}
						else
							throw XBadOperand("Ln()", "Boolean");
					}
				};

				class Log : public OneArgFunction {
					DEF_IS_CONVERTABLE_FROM(Log)
					Operand::pointer_type perform(OperandList valueStack)
					{
						if (is<Real>(valueStack.front()))
						{
							Real::value_type oldVal = get_value<Real>(valueStack.front());
							Real::value_type newVal = log10(oldVal);
							return convert<Operand>(make<Real>(newVal));
						}
						else if (is<Integer>(valueStack.front()))
						{
							Real::value_type oldVal = convert_to_real(valueStack.front())->get_value();
							Real::value_type newVal = log(oldVal);
							return convert<Operand>(make<Real>(newVal));
						}
						else
							throw XBadOperand("Log()", "Boolean");
					}
				};

				class Sin : public OneArgFunction {
					DEF_IS_CONVERTABLE_FROM(Sin)
					Operand::pointer_type perform(OperandList valueStack)
					{
						if (is<Real>(valueStack.front()))
						{
							Real::value_type oldVal = get_value<Real>(valueStack.front());
							Real::value_type newVal = sin(oldVal);
							return convert<Operand>(make<Real>(newVal));
						}
						else if (is<Integer>(valueStack.front()))
						{
							Real::value_type oldVal = convert_to_real(valueStack.front())->get_value();
							Real::value_type newVal = sin(oldVal);
							return convert<Operand>(make<Real>(newVal));
						}
						else
							throw XBadOperand("Sin()", "Boolean");
					}
				};

				class Sqrt : public OneArgFunction {
					DEF_IS_CONVERTABLE_FROM(Sqrt)
					Operand::pointer_type perform(OperandList valueStack)
					{
						if (is<Real>(valueStack.front()))
						{
							Real::value_type oldVal = get_value<Real>(valueStack.front());
							Real::value_type newVal = sqrt(oldVal);
							return convert<Operand>(make<Real>(newVal));
						}
						else if (is<Integer>(valueStack.front()))
						{
							Real::value_type oldVal = convert_to_real(valueStack.front())->get_value();
							Real::value_type newVal = sqrt(oldVal);
							return convert<Operand>(make<Real>(newVal));
						}
						else
							throw XBadOperand("Sqrt()", "Boolean");
					}
				};

				class Tan : public OneArgFunction {
					DEF_IS_CONVERTABLE_FROM(Tan)
					Operand::pointer_type perform(OperandList valueStack)
					{
						if (is<Real>(valueStack.front()))
						{
							Real::value_type oldVal = get_value<Real>(valueStack.front());
							Real::value_type newVal = tan(oldVal);
							return convert<Operand>(make<Real>(newVal));
						}
						else if (is<Integer>(valueStack.front()))
						{
							Real::value_type oldVal = convert_to_real(valueStack.front())->get_value();
							Real::value_type newVal = tan(oldVal);
							return convert<Operand>(make<Real>(newVal));
						}
						else
							throw XBadOperand("Tan()", "Boolean");
					}
				};

				class Binary : public OneArgFunction {
					DEF_IS_CONVERTABLE_FROM(Binary)
					Operand::pointer_type perform(OperandList valueStack)
					{
						return NULL;
					}
					
				};


		class MultiArgFunction : public Function {
		public:
			virtual unsigned number_of_args() const { return 2; }
		};

				class Pow : public MultiArgFunction {
					DEF_IS_CONVERTABLE_FROM(Pow)
					Operand::pointer_type perform(OperandList valueStack)
					{
						valueStack = matchOperandTypes(valueStack);
						if (is<Real>(valueStack.front()))
						{
							Real::value_type param1 = get_value<Real>(valueStack.front());
							Real::value_type param2 = get_value<Real>(valueStack.back());
							Real::value_type result = pow(param1, param2);
							return convert<Operand>(make<Real>(result));
						}
						else if (is<Integer>(valueStack.front()))
						{
							Integer::value_type param1 = get_value<Integer>(valueStack.front());
							Integer::value_type bigInt = get_value<Integer>(valueStack.back());
							int param2 = bigInt.convert_to<int>();
							if (param2 < 0)
							{
								Real::value_type result = pow(param1.convert_to<Real::value_type>(), param2);
								return convert<Operand>(make<Real>(result));
							}
							else
								return convert<Operand>(make<Integer>(pow(param1, param2)));
						}
						else
							throw XBadOperand("addition(+)", "Boolean");
					}
				};

				class Min : public MultiArgFunction {
					DEF_IS_CONVERTABLE_FROM(Min)
					Operand::pointer_type perform(OperandList valueStack)
					{
						valueStack = matchOperandTypes(valueStack);
						if (is<Real>(valueStack.front()))
						{
							Real::value_type param1 = get_value<Real>(valueStack.front());
							Real::value_type param2 = get_value<Real>(valueStack.back());
							Real::value_type result = min(param1, param2);
							return convert<Operand>(make<Real>(result));
						}
						else if (is<Integer>(valueStack.front()))
						{
							Integer::value_type param1 = get_value<Integer>(valueStack.front());
							Integer::value_type param2 = get_value<Integer>(valueStack.back());
							Integer::value_type result = min(param1, param2);
							return convert<Operand>(make<Integer>(result));
						}
						else
							throw XBadOperand("addition(+)", "Boolean");
					}
				};

				class Max : public MultiArgFunction {
					DEF_IS_CONVERTABLE_FROM(Max)
					Operand::pointer_type perform(OperandList valueStack)
					{
						valueStack = matchOperandTypes(valueStack);
						if (is<Real>(valueStack.front()))
						{
							Real::value_type param1 = get_value<Real>(valueStack.front());
							Real::value_type param2 = get_value<Real>(valueStack.back());
							Real::value_type result = max(param1, param2);
							return convert<Operand>(make<Real>(result));
						}
						else if (is<Integer>(valueStack.front()))
						{
							Integer::value_type param1 = get_value<Integer>(valueStack.front());
							Integer::value_type param2 = get_value<Integer>(valueStack.back());
							Integer::value_type result = max(param1, param2);
							return convert<Operand>(make<Integer>(result));
						}
						else
							throw XBadOperand("addition(+)", "Boolean");
					}
				};

				class Arctan2 : public MultiArgFunction {
					DEF_IS_CONVERTABLE_FROM(Arctan2)
					Operand::pointer_type perform(OperandList valueStack)
					{
						valueStack = matchOperandTypes(valueStack);
						if (is<Real>(valueStack.front()))
						{
							Real::value_type param1 = get_value<Real>(valueStack.front());
							Real::value_type param2 = get_value<Real>(valueStack.back());
							Real::value_type result = atan2(param1, param2);
							return convert<Operand>(make<Real>(result));
						}
						else if (is<Integer>(valueStack.front()))
						{
							Real::value_type param1 = convert_to_real(valueStack.front())->get_value();
							Real::value_type param2 = convert_to_real(valueStack.back())->get_value();
							Real::value_type result = atan2(param1, param2);
							return convert<Operand>(make<Real>(result));
						}
						else
							throw XBadOperand("addition(+)", "Boolean");
					}
				};


/*=============================================================

Revision History
Version 1.0.0: 2014-10-30
Removed binary function

Version 0.0.1: 2012-11-13
C++ 11 cleanup

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
#endif // GUARD_function_hpp20091126_
