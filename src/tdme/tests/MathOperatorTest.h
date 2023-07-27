#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/tests/fwd-tdme.h>

using std::string;

/**
 * Math operator test
 * @author mahula
 */
class tdme::tests::MathOperatorTest final
{
public:
	static void main();

	// forbid class copy
	FORBID_CLASS_COPY(MathOperatorTest)

	//
	MathOperatorTest();

	void testVector2Operators();
	void testVector3Operators();
	void testVector4Operators();
	void testQuaternionOperators();
	void testMatrix2D3x3Operators();
	void testMatrix4x4Operators();

private:
	string success = "Success";
	string fail = "Fail";
};
