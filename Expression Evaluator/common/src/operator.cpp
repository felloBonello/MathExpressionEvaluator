/** @file: operator.cpp
	@author Garth Santor/Trinh Han
	@author garth.santor@sympatico.ca
	@author http://www.gats.ca/
	@date 2012-11-13
	@version 0.1.1
	@note Compiles under Visaul C++ v110

	@brief Operator class implementations.
	*/

#include "operator.hpp"
#include "operand.hpp"
#include "integer.hpp"
#include "real.hpp"
#include "variable.hpp"
#include <cassert>



/*=============================================================

Revision History

Version 0.1.1: 2012-11-13
C++ 11 cleanup

Version 0.1.0: 2010-11-08
Added exception for assignment to a non-variable.

Version 0.0.0: 2009-12-14
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
