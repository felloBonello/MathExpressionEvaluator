#if !defined(GUARD_operator_hpp20091126_)
#define GUARD_operator_hpp20091126_

/** @file: operator.hpp
	@author Garth Santor/Trinh Han
	@author garth.santor@sympatico.ca
	@author http://www.gats.ca/
	@date 2012-11-16
	@version 0.2.0
	@note Compiles under Visaul C++ v110

	@brief Operator class declarations
	*/

#include <boost/math/special_functions/factorials.hpp>
#include "operation.hpp"
#include "operand.hpp"
#include "real.hpp"
#include "Integer.hpp"
#include "Variable.hpp"
#include "Boolean.hpp"
#include <math.h>
#include <cmath>
#include <list>
#include <boost/multiprecision/cpp_int.hpp>



/** Operator Precedence values. */
typedef enum { MIN = 0, 
	ASSIGNMENT, LOGOR, LOGXOR, LOGAND, BITOR, 
	BITXOR, BITAND, EQUALITY, RELATIONAL, BITSHIFT, 
	ADDITIVE, MULTIPLICATIVE,  POWER, UNARY, POSTFIX, 
	MAX } precedence_type;



/** Defines a precedence category method.  Used inside a class declaration. */
#define DEF_PRECEDENCE(category)	public: precedence_type get_precedence() const { return category; }

using namespace boost::multiprecision;
using namespace std;


const int INTEGER = 0;
const int REAL = 1;
const int BOOLEAN = 2;
const int VARIABLE = 3;

inline Real::pointer_type convert_to_real(Operand::pointer_type operand)
{
	Integer::value_type i = get_value<Integer>(operand);
	Real::pointer_type R = dynamic_pointer_cast<Real>(make<Real>(i.convert_to<Real::value_type>()));
	return R;
}

inline Variable::pointer_type convert_to_variable(Operand::pointer_type operand)
{
	return dynamic_pointer_cast<Variable>(operand);
}

inline OperandList matchOperandTypes(OperandList params)
{
	int param1_t = -1;
	int param2_t = -1;
	Operand::pointer_type param1 = params.front();
	Operand::pointer_type param2 = params.back();

	if (is<Integer>(param1))
		param1_t = INTEGER;
	else if (is<Real>(param1))
		param1_t = REAL;
	else if (is<Boolean>(param1))
		param1_t = BOOLEAN;
	else if (is<Variable>(param1))
	{
		Variable::pointer_type var = convert_to_variable(param1);
		OperandList newList = { var->get_value(), param2 };
		params = matchOperandTypes(newList);
		param1_t = VARIABLE;
	}
		

	if (is<Integer>(param2))
		param2_t = INTEGER;
	else if (is<Real>(param2))
		param2_t = REAL;
	else if (is<Boolean>(param2))
		param2_t = BOOLEAN;
	else if (is<Variable>(param2))
	{
		Variable::pointer_type var = convert_to_variable(param1);
		OperandList newList = { var->get_value(), param2 };
		params = matchOperandTypes(newList);
		param2_t = VARIABLE;
	}

	if ((param1_t == param2_t) || (param1_t == VARIABLE || param2_t == VARIABLE))
		return params;
	else if (param1_t == INTEGER && param2_t == REAL)
	{
		Real::pointer_type R = convert_to_real(param1);
		OperandList newList = { R, param2 };
		param1_t = REAL;
		return newList;
	}
	else if (param1_t == REAL && param2_t == INTEGER)
	{
		Real::pointer_type R = convert_to_real(param2);
		OperandList newList = { param1, R };
		param2_t = REAL;
		return newList;
	}
	else
		throw Operation::XTypeMismatch("", "");
}

/** Operator token base class. */
class Operator : public Operation {
public:
	DEF_POINTER_TYPE(Operator)
	virtual precedence_type get_precedence() = 0;
};

		/** Binary operator token base class. */
		class BinaryOperator : public Operator {
		public:
			virtual unsigned number_of_args() const { return 2; }
		};

				/** Right-associative operator base class. */
				class RAssocOperator : public BinaryOperator { };

						/** Power token. */
						class Power : public RAssocOperator {
							DEF_IS_CONVERTABLE_FROM(Power)
							DEF_PRECEDENCE(POWER)
						public:
							precedence_type get_precedence() { return POWER; }
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
									throw XBadOperand("power(#)", "Boolean");
							}
						};

						class Assignment : public RAssocOperator {
							DEF_IS_CONVERTABLE_FROM(Assignment)
							DEF_PRECEDENCE(ASSIGNMENT)
						public:
							precedence_type get_precedence() { return ASSIGNMENT; }
							Operand::pointer_type perform(list<Operand::pointer_type> valueStack)
							{
								if (is<Variable>(valueStack.front()))
								{
									if (is<Real>(valueStack.back()) || is<Integer>(valueStack.back()) || is<Boolean>(valueStack.back()))
									{
										Variable::pointer_type var_p = dynamic_pointer_cast<Variable>(valueStack.front());
										var_p->set_value(valueStack.back());
										return convert<Operand>(var_p);
									}
									else if (is<Variable>(valueStack.back()))
									{
										Variable::pointer_type var_p = dynamic_pointer_cast<Variable>(valueStack.front());
										Variable::pointer_type var_p_2 = dynamic_pointer_cast<Variable>(valueStack.back());
										var_p->set_value(var_p_2->get_value());
										return convert<Operand>(var_p_2);
									}
									throw XBadOperand("assignment(=)", "unknown type");
								}
								throw XNonVariable("assignment(=)", "unknown type");
							}
						};

				/** Right-associative operator base class. */
				class LAssocOperator : public BinaryOperator { };

					class Addition : public LAssocOperator {
						DEF_IS_CONVERTABLE_FROM(Addition)
						DEF_PRECEDENCE(ADDITIVE)
					public:
						precedence_type get_precedence() { return ADDITIVE; }
						Operand::pointer_type perform(OperandList valueStack)
						{
							valueStack = matchOperandTypes(valueStack);
							if (is<Real>(valueStack.front()))
							{
								Real::value_type param1 = get_value<Real>(valueStack.front());
								Real::value_type param2 = get_value<Real>(valueStack.back());
								Real::value_type result = param1 + param2;
								return convert<Operand>(make<Real>(result));
							}
							else if (is<Integer>(valueStack.front()))
							{
								Integer::value_type param1 = get_value<Integer>(valueStack.front());
								Integer::value_type param2 = get_value<Integer>(valueStack.back());
								Integer::value_type result = param1 + param2;
								return convert<Operand>(make<Integer>(result));
							}
							else if (is<Boolean>(valueStack.front()))
							{
								Boolean::value_type param1 = get_value<Boolean>(valueStack.front());
								Boolean::value_type param2 = get_value<Boolean>(valueStack.back());
								return convert<Operand>(make<Boolean>(param1 || param2));
							}
							else
								throw XBadOperand("addition(+)", "Unkown");
						}
					};

					class Subtraction : public LAssocOperator {
						DEF_IS_CONVERTABLE_FROM(Subtraction)
						DEF_PRECEDENCE(ADDITIVE)
					public:
						precedence_type get_precedence() { return ADDITIVE; }
						Operand::pointer_type perform(OperandList valueStack)
						{
							valueStack = matchOperandTypes(valueStack);
							if (is<Real>(valueStack.front()))
							{
								Real::value_type param1 = get_value<Real>(valueStack.front());
								Real::value_type param2 = get_value<Real>(valueStack.back());
								Real::value_type result = param1 - param2;
								return convert<Operand>(make<Real>(result));
							}
							else if (is<Integer>(valueStack.front()))
							{
								Integer::value_type param1 = get_value<Integer>(valueStack.front());
								Integer::value_type param2 = get_value<Integer>(valueStack.back());
								Integer::value_type result = param1 - param2;
								return convert<Operand>(make<Integer>(result));
							}
							else
								throw XBadOperand("subtraction(-)", "Boolean");
						}
					};

					class Multiplication : public LAssocOperator {
						DEF_IS_CONVERTABLE_FROM(Multiplication)
						DEF_PRECEDENCE(MULTIPLICATIVE)
					public:
						precedence_type get_precedence() { return MULTIPLICATIVE; }
						Operand::pointer_type perform(OperandList valueStack)
						{
							valueStack = matchOperandTypes(valueStack);
							if (is<Real>(valueStack.front()))
							{
								Real::value_type param1 = get_value<Real>(valueStack.front());
								Real::value_type param2 = get_value<Real>(valueStack.back());
								Real::value_type result = param1 * param2;
								return convert<Operand>(make<Real>(result));
							}
							else if (is<Integer>(valueStack.front()))
							{
								Integer::value_type param1 = get_value<Integer>(valueStack.front());
								Integer::value_type param2 = get_value<Integer>(valueStack.back());
								Integer::value_type result = param1 * param2;
								return convert<Operand>(make<Integer>(result));
							}
							else if (is<Boolean>(valueStack.front()))
							{
								Boolean::value_type param1 = get_value<Boolean>(valueStack.front());
								Boolean::value_type param2 = get_value<Boolean>(valueStack.back());
								return convert<Operand>(make<Boolean>(param1 && param2));
							}
							else
								throw XBadOperand("multiplication(/)", "Unknown");
						}
					};

					class Division : public LAssocOperator {
						DEF_IS_CONVERTABLE_FROM(Division)
						DEF_PRECEDENCE(MULTIPLICATIVE)
					public:
						precedence_type get_precedence() { return MULTIPLICATIVE; }
						Operand::pointer_type perform(OperandList valueStack)
						{
							valueStack = matchOperandTypes(valueStack);
							if (is<Real>(valueStack.front()))
							{
								Real::value_type param1 = get_value<Real>(valueStack.front());
								Real::value_type param2 = get_value<Real>(valueStack.back());
								if (param2 == Real::value_type("0")) { throw XDivideByZero("Real", "division"); }
								Real::value_type result = param1 / param2;
								return convert<Operand>(make<Real>(result));
							}
							else if (is<Integer>(valueStack.front()))
							{
								Integer::value_type param1 = get_value<Integer>(valueStack.front());
								Integer::value_type param2 = get_value<Integer>(valueStack.back());
								if (param2 == 0) { throw XDivideByZero("Integer", "division"); }
								Integer::value_type result = param1 / param2;
								return convert<Operand>(make<Integer>(result));
							}
							else
								throw XBadOperand("division(/)", "Boolean");
						}
					};

					class Modulus : public LAssocOperator {
						DEF_IS_CONVERTABLE_FROM(Modulus)
						DEF_PRECEDENCE(MULTIPLICATIVE)
					public:
						precedence_type get_precedence() { return MULTIPLICATIVE; }
						Operand::pointer_type perform(OperandList valueStack)
						{
							valueStack = matchOperandTypes(valueStack);
							if (is<Integer>(valueStack.front()))
							{
								Integer::value_type param1 = get_value<Integer>(valueStack.front());
								Integer::value_type param2 = get_value<Integer>(valueStack.back());
								Integer::value_type result = param1 % param2;
								return convert<Operand>(make<Integer>(result));
							}
							else
								throw XBadOperand("modulus(%)", "must be integer");
						}
					};

					class And : public LAssocOperator {
						DEF_IS_CONVERTABLE_FROM(And)
						DEF_PRECEDENCE(LOGAND)
					public:
						precedence_type get_precedence() { return LOGAND; }
						Operand::pointer_type perform(OperandList valueStack)
						{
							valueStack = matchOperandTypes(valueStack);
							if (is<Boolean>(valueStack.front()))
							{
								Boolean::value_type param1 = get_value<Boolean>(valueStack.front());
								Boolean::value_type param2 = get_value<Boolean>(valueStack.back());
								return convert<Operand>(make<Boolean>((param1 && param2)));
							}
							else
								throw XBadOperand("And", "Real/Integer");
						}
					};

					class Nand : public LAssocOperator {
						DEF_IS_CONVERTABLE_FROM(Nand)
						DEF_PRECEDENCE(LOGAND)
					public:
						precedence_type get_precedence() { return LOGAND; }
						Operand::pointer_type perform(OperandList valueStack)
						{
							valueStack = matchOperandTypes(valueStack);
							if (is<Boolean>(valueStack.front()))
							{
								Boolean::value_type param1 = get_value<Boolean>(valueStack.front());
								Boolean::value_type param2 = get_value<Boolean>(valueStack.back());
								return convert<Operand>(make<Boolean>(!(param1 && param2)));
							}
							else
								throw XBadOperand("Nand", "Real/Integer");
						}
					};

					class Nor : public LAssocOperator {
						DEF_IS_CONVERTABLE_FROM(Nor)
						DEF_PRECEDENCE(LOGOR)
					public:
						precedence_type get_precedence() { return LOGOR; }
						Operand::pointer_type perform(OperandList valueStack)
						{
							valueStack = matchOperandTypes(valueStack);
							if (is<Boolean>(valueStack.front()))
							{
								Boolean::value_type param1 = get_value<Boolean>(valueStack.front());
								Boolean::value_type param2 = get_value<Boolean>(valueStack.back());
								return convert<Operand>(make<Boolean>(!(param1 || param2)));
							}
							else
								throw XBadOperand("Nor", "Real/Integer");
						}
					};

					class Or : public LAssocOperator {
						DEF_IS_CONVERTABLE_FROM(Or)
						DEF_PRECEDENCE(LOGOR)
					public:
						precedence_type get_precedence() { return LOGOR; }
						Operand::pointer_type perform(OperandList valueStack)
						{
							valueStack = matchOperandTypes(valueStack);
							if (is<Boolean>(valueStack.front()))
							{
								Boolean::value_type param1 = get_value<Boolean>(valueStack.front());
								Boolean::value_type param2 = get_value<Boolean>(valueStack.back());
								return convert<Operand>(make<Boolean>(param1 || param2));
							}
							else
								throw XBadOperand("or", "Real/Integer");
						}
					};

					class Xor : public LAssocOperator {
						DEF_IS_CONVERTABLE_FROM(Xor)
						DEF_PRECEDENCE(LOGXOR)
					public:
						precedence_type get_precedence() { return LOGXOR; }
						Operand::pointer_type perform(OperandList valueStack)
						{
							valueStack = matchOperandTypes(valueStack);
							if (is<Boolean>(valueStack.front()))
							{
								Boolean::value_type param1 = get_value<Boolean>(valueStack.front());
								Boolean::value_type param2 = get_value<Boolean>(valueStack.back());
								return convert<Operand>(make<Boolean>((param1 && !param2) || (!param1 && param2)));
							}
							else
								throw XBadOperand("Xor", "Real/Integer");
						}
					};

					class Xnor : public LAssocOperator {
						DEF_IS_CONVERTABLE_FROM(Xnor)
						DEF_PRECEDENCE(LOGXOR)
					public:
						precedence_type get_precedence() { return LOGXOR; }
						Operand::pointer_type perform(OperandList valueStack)
						{
							valueStack = matchOperandTypes(valueStack);
							if (is<Boolean>(valueStack.front()))
							{
								Boolean::value_type param1 = get_value<Boolean>(valueStack.front());
								Boolean::value_type param2 = get_value<Boolean>(valueStack.back());
								return convert<Operand>(make<Boolean>( !((param1 && !param2) || (!param1 && param2)) ));
							}
							else
								throw XBadOperand("XNor", "Real/Integer");
						}
					};

					//RELATIONAL OPERATORS
					class Equality : public LAssocOperator {
						DEF_IS_CONVERTABLE_FROM(Equality)
						DEF_PRECEDENCE(EQUALITY)
					public:
						precedence_type get_precedence() { return EQUALITY; }
						Operand::pointer_type perform(OperandList valueStack)
						{
							valueStack = matchOperandTypes(valueStack);
							if (is<Boolean>(valueStack.front()))
							{
								Boolean::value_type param1 = get_value<Boolean>(valueStack.front());
								Boolean::value_type param2 = get_value<Boolean>(valueStack.back());
								return convert<Operand>(make<Boolean>(param1 == param2));
							}
							else if (is<Integer>(valueStack.front()))
							{
								Integer::value_type param1 = get_value<Integer>(valueStack.front());
								Integer::value_type param2 = get_value<Integer>(valueStack.back());
								return convert<Operand>(make<Boolean>(param1 == param2));
							}
							else if (is<Real>(valueStack.front()))
							{
								Real::value_type param1 = get_value<Real>(valueStack.front());
								Real::value_type param2 = get_value<Real>(valueStack.back());
								return convert<Operand>(make<Boolean>(param1 == param2));
							}
							else
								throw XBadOperand("Equality(==)", "unknown");
						}
					};

					class Inequality : public LAssocOperator {
						DEF_IS_CONVERTABLE_FROM(Inequality)
						DEF_PRECEDENCE(EQUALITY)
					public:
						precedence_type get_precedence() { return EQUALITY; }
						Operand::pointer_type perform(OperandList valueStack)
						{
							valueStack = matchOperandTypes(valueStack);
							if (is<Boolean>(valueStack.front()))
							{
								Boolean::value_type param1 = get_value<Boolean>(valueStack.front());
								Boolean::value_type param2 = get_value<Boolean>(valueStack.back());
								return convert<Operand>(make<Boolean>(param1 != param2));
							}
							else if (is<Integer>(valueStack.front()))
							{
								Integer::value_type param1 = get_value<Integer>(valueStack.front());
								Integer::value_type param2 = get_value<Integer>(valueStack.back());
								return convert<Operand>(make<Boolean>(param1 != param2));
							}
							else if (is<Real>(valueStack.front()))
							{
								Real::value_type param1 = get_value<Real>(valueStack.front());
								Real::value_type param2 = get_value<Real>(valueStack.back());
								return convert<Operand>(make<Boolean>(param1 != param2));
							}
							else
								throw XBadOperand("Inequality(!=)", "unknown");
						}
					};

					class Greater : public LAssocOperator {
						DEF_IS_CONVERTABLE_FROM(Greater)
						DEF_PRECEDENCE(RELATIONAL)
					public:
						precedence_type get_precedence() { return RELATIONAL; }
						Operand::pointer_type perform(OperandList valueStack)
						{
							valueStack = matchOperandTypes(valueStack);
							if (is<Boolean>(valueStack.front()))
							{
								Boolean::value_type param1 = get_value<Boolean>(valueStack.front());
								Boolean::value_type param2 = get_value<Boolean>(valueStack.back());
								return convert<Operand>(make<Boolean>(param1 > param2));
							}
							else if (is<Integer>(valueStack.front()))
							{
								Integer::value_type param1 = get_value<Integer>(valueStack.front());
								Integer::value_type param2 = get_value<Integer>(valueStack.back());
								return convert<Operand>(make<Boolean>(param1 > param2));
							}
							else if (is<Real>(valueStack.front()))
							{
								Real::value_type param1 = get_value<Real>(valueStack.front());
								Real::value_type param2 = get_value<Real>(valueStack.back());
								return convert<Operand>(make<Boolean>(param1 > param2));
							}
							else
								throw XBadOperand("Greater(>)", "unknown");
						}
					};

					class GreaterEqual : public LAssocOperator {
						DEF_IS_CONVERTABLE_FROM(GreaterEqual)
						DEF_PRECEDENCE(RELATIONAL)
					public:
						precedence_type get_precedence() { return RELATIONAL; }
						Operand::pointer_type perform(OperandList valueStack)
						{
							valueStack = matchOperandTypes(valueStack);
							if (is<Boolean>(valueStack.front()))
							{
								Boolean::value_type param1 = get_value<Boolean>(valueStack.front());
								Boolean::value_type param2 = get_value<Boolean>(valueStack.back());
								return convert<Operand>(make<Boolean>(param1 >= param2));
							}
							else if (is<Integer>(valueStack.front()))
							{
								Integer::value_type param1 = get_value<Integer>(valueStack.front());
								Integer::value_type param2 = get_value<Integer>(valueStack.back());
								return convert<Operand>(make<Boolean>(param1 >= param2));
							}
							else if (is<Real>(valueStack.front()))
							{
								Real::value_type param1 = get_value<Real>(valueStack.front());
								Real::value_type param2 = get_value<Real>(valueStack.back());
								return convert<Operand>(make<Boolean>(param1 >= param2));
							}
							else
								throw XBadOperand("GreaterEqual(>=)", "unknown");
						}
					};

					class Less : public LAssocOperator {
						DEF_IS_CONVERTABLE_FROM(Less)
						DEF_PRECEDENCE(RELATIONAL)
					public:
						precedence_type get_precedence() { return RELATIONAL; }
						Operand::pointer_type perform(OperandList valueStack)
						{
							valueStack = matchOperandTypes(valueStack);
							if (is<Boolean>(valueStack.front()))
							{
								Boolean::value_type param1 = get_value<Boolean>(valueStack.front());
								Boolean::value_type param2 = get_value<Boolean>(valueStack.back());
								return convert<Operand>(make<Boolean>(param1 < param2));
							}
							else if (is<Integer>(valueStack.front()))
							{
								Integer::value_type param1 = get_value<Integer>(valueStack.front());
								Integer::value_type param2 = get_value<Integer>(valueStack.back());
								return convert<Operand>(make<Boolean>(param1 < param2));
							}
							else if (is<Real>(valueStack.front()))
							{
								Real::value_type param1 = get_value<Real>(valueStack.front());
								Real::value_type param2 = get_value<Real>(valueStack.back());
								return convert<Operand>(make<Boolean>(param1 < param2));
							}
							else
								throw XBadOperand("Less(<)", "unknown");
						}
					};

					class LessEqual : public LAssocOperator {
						DEF_IS_CONVERTABLE_FROM(LessEqual)
						DEF_PRECEDENCE(RELATIONAL)
					public:
						precedence_type get_precedence() { return RELATIONAL; }
						Operand::pointer_type perform(OperandList valueStack)
						{
							valueStack = matchOperandTypes(valueStack);
							if (is<Boolean>(valueStack.front()))
							{
								Boolean::value_type param1 = get_value<Boolean>(valueStack.front());
								Boolean::value_type param2 = get_value<Boolean>(valueStack.back());
								return convert<Operand>(make<Boolean>(param1 <= param2));
							}
							else if (is<Integer>(valueStack.front()))
							{
								Integer::value_type param1 = get_value<Integer>(valueStack.front());
								Integer::value_type param2 = get_value<Integer>(valueStack.back());
								return convert<Operand>(make<Boolean>(param1 <= param2));
							}
							else if (is<Real>(valueStack.front()))
							{
								Real::value_type param1 = get_value<Real>(valueStack.front());
								Real::value_type param2 = get_value<Real>(valueStack.back());
								return convert<Operand>(make<Boolean>(param1 <= param2));
							}
							else
								throw XBadOperand("LessEqual(<=)", "unknown");
						}
					};



		class UnaryOperator : public Operator {
		public:
			virtual unsigned number_of_args() const { return 1; }
		};

			class Negation : public UnaryOperator {
					DEF_IS_CONVERTABLE_FROM(Negation)
					DEF_PRECEDENCE(UNARY)
			public:
				precedence_type get_precedence() { return UNARY; }
				Operand::pointer_type perform(OperandList valueStack)
				{
					if (is<Real>(valueStack.front()))
					{
						Real::value_type oldVal = get_value<Real>(valueStack.front());
						Real::value_type newVal = -oldVal;
						return convert<Operand>(make<Real>(newVal));
					}
					else if (is<Integer>(valueStack.front()))
					{
						Integer::value_type oldVal = get_value<Integer>(valueStack.front());
						Integer::value_type newVal = -oldVal;
						return convert<Operand>(make<Integer>(newVal));
					}
					else
						throw XBadOperand("negation(-)", "Boolean");
				}
			};

			class Identity : public UnaryOperator {
				DEF_IS_CONVERTABLE_FROM(Identity)
				DEF_PRECEDENCE(UNARY)
			public:
				precedence_type get_precedence() { return UNARY; }
				Operand::pointer_type perform(OperandList valueStack)
				{
					if (is<Real>(valueStack.front()))
					{
						Real::value_type oldVal = get_value<Real>(valueStack.front());
						Real::value_type newVal = oldVal;
						return convert<Operand>(make<Real>(newVal));
					}						
					else if (is<Integer>(valueStack.front()))
					{
						Integer::value_type oldVal = get_value<Integer>(valueStack.front());
						Integer::value_type newVal = oldVal;
						return convert<Operand>(make<Integer>(newVal));
					}					
					else
						throw XBadOperand("identity(+)", "Boolean");
				}
			};

			class Not : public UnaryOperator {
				DEF_IS_CONVERTABLE_FROM(Not)
				DEF_PRECEDENCE(UNARY)
			public:
				precedence_type get_precedence() { return UNARY; }
				Operand::pointer_type perform(OperandList valueStack)
				{
					if (is<Boolean>(valueStack.front()))
					{
						Boolean::value_type oldVal = get_value<Boolean>(valueStack.front());
						Boolean::value_type newVal = !oldVal;
						return convert<Operand>(make<Boolean>(newVal));
					}
					else
						throw XBadOperand("Not(!)", "Real/Integer");
				}
			};

			class Factorial : public UnaryOperator {
				DEF_IS_CONVERTABLE_FROM(Factorial)
					DEF_PRECEDENCE(UNARY)
			public:
				precedence_type get_precedence() { return UNARY; }
				Operand::pointer_type perform(OperandList valueStack)
				{ 
					if (is<Integer>(valueStack.front()))
					{
						Integer::value_type oldVal = get_value<Integer>(valueStack.front());
						if (oldVal >= 0)
						{
							Integer::value_type newVal = 1;
							for (Integer::value_type i = oldVal; i > 1; --i) { newVal *= i; }
							return convert<Operand>(make<Integer>(newVal));
						}			
						else 
							throw XBadOperand("factorial(!)", "Use of negative");
					}
					else
						throw XBadOperand("factorial(!)", "Boolean/Real");
				}
			};




/*=============================================================

Revision History
Version 1.0.0: 2014-10-30
Removed bitwise operators.

Version 0.2.0: 2012-11-16
Added BitAnd, BitNot, BitOr, BitShiftLeft, BitShiftRight

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
#endif // GUARD_operator_hpp20091126_
