#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/tests/fwd-tdme.h>

using std::string;

/**
 * Math operator test
 * @author mahula
 * @version $Id$
 */
class tdme::tests::MathOperatorTest final
{
public:
	static void main();

	MathOperatorTest();

	void testVector2Operators();
	void testVector3Operators();
	void testVector4Operators();
	void testQuaternionOperators();

private:
	string success = "Success";
	string fail = "Fail";
};
