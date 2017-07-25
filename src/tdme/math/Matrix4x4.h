// Generated from /tdme/src/tdme/math/Matrix4x4.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using tdme::math::Vector3;
using tdme::math::Vector4;


struct default_init_tag;

/** 
 * 4x4 Matrix class
 * @author Andreas Drewke, Song Ho Ahn <song.ahn@gmail.com>
 * @version $Id$
 */
class tdme::math::Matrix4x4 final
	: public Object
{

public:
	typedef Object super;

public: /* protected */
	floatArray* data {  };
	floatArray* _data {  };
	Vector3* tmpVector3 {  };
protected:

	/** 
	 * Public constructor
	 */
	void ctor();

	/** 
	 * Public constructor
	 * @param float array m
	 */
	void ctor(floatArray* m);

	/** 
	 * Public constructor
	 * @param matrix
	 */
	void ctor(Matrix4x4* matrix);

	/** 
	 * Public constructor
	 * @param row 0, column 0
	 * @param row 1, column 0
	 * @param row 2, column 0
	 * @param row 3, column 0
	 * @param row 0, column 1
	 * @param row 1, column 1
	 * @param row 2, column 1
	 * @param row 3, column 1
	 * @param row 0, column 2
	 * @param row 1, column 2
	 * @param row 2, column 2
	 * @param row 3, column 2
	 * @param row 0, column 3
	 * @param row 1, column 3
	 * @param row 2, column 3
	 * @param row 3, column 3
	 */
	void ctor(float r0c0, float r1c0, float r2c0, float r3c0, float r0c1, float r1c1, float r2c1, float r3c1, float r0c2, float r1c2, float r2c2, float r3c2, float r0c3, float r1c3, float r2c3, float r3c3);

public:
	/** 
	 * Set up matrix by values
	 * @param row 0, column 0
	 * @param row 1, column 0
	 * @param row 2, column 0
	 * @param row 3, column 0
	 * @param row 0, column 1
	 * @param row 1, column 1
	 * @param row 2, column 1
	 * @param row 3, column 1
	 * @param row 0, column 2
	 * @param row 1, column 2
	 * @param row 2, column 2
	 * @param row 3, column 2
	 * @param row 0, column 3
	 * @param row 1, column 3
	 * @param row 2, column 3
	 * @param row 3, column 3
	 * @return this matrix
	 */
	Matrix4x4* set(float r0c0, float r1c0, float r2c0, float r3c0, float r0c1, float r1c1, float r2c1, float r3c1, float r0c2, float r1c2, float r2c2, float r3c2, float r0c3, float r1c3, float r2c3, float r3c3);

	/** 
	 * Sets up this matrix by matrix m
	 * @param m
	 * @return this matrix
	 */
	Matrix4x4* set(floatArray* m);

	/** 
	 * Sets up this matrix by matrix m
	 * @param m
	 * @return
	 */
	Matrix4x4* set(Matrix4x4* m);

	/**
	 * Get coordinate system axes
	 * @param x axis
	 * @param y axis
	 * @param z axis
	 * @return this matrix
	 */
	Matrix4x4* getAxes(Vector3* xAxis, Vector3* yAxis, Vector3* zAxis);

	/** 
	 * Set coordinate system axes
	 * @param x axis
	 * @param y axis
	 * @param z axis
	 * @return this matrix
	 */
	Matrix4x4* setAxes(Vector3* xAxis, Vector3* yAxis, Vector3* zAxis);

	/** 
	 * Get translation
	 * @param translation
	 * @return this matrix
	 */
	Matrix4x4* getTranslation(Vector3* translation);

	/** 
	 * Set translation
	 * @param translation
	 * @return this matrix
	 */
	Matrix4x4* setTranslation(Vector3* translation);

	/** 
	 * Get scale
	 * @param scale
	 * @return this matrix
	 */
	Matrix4x4* getScale(Vector3* scale);

	/** 
	 * Get scale
	 * @param scale
	 * @return this matrix
	 */
	Matrix4x4* setScale(Vector3* scale);

	/** 
	 * Setup identity matrix
	 * @return this matrix
	 */
	Matrix4x4* identity();

	/** 
	 * Multiplies a vector3 with this matrix into destination vector
	 * @param vector 3
	 * @param destination vector 3
	 * @return vector 3
	 */
	Vector3* multiply(Vector3* v, Vector3* dest);

	/** 
	 * Multiplies a vector3 with this matrix ignoring translation
	 * @param vector 3
	 * @param destination vector 3
	 * @return vector 3 dest
	 */
	Vector3* multiplyNoTranslation(Vector3* v, Vector3* dest);

	/** 
	 * Multiplies a vector4 with this matrix into destination vector
	 * @param vector 4
	 * @param destination vector4
	 * @return destination vector 4
	 */
	Vector4* multiply(Vector4* v, Vector4* dest);

	/** 
	 * Multiplies this matrix with another matrix
	 * @param m
	 * @return this matrix
	 */
	Matrix4x4* multiply(Matrix4x4* m);

	/** 
	 * Scales this matrix
	 * @param s
	 * @returns this matrix
	 */
	Matrix4x4* scale(float s);

	/** 
	 * Scales this matrix by given vector
	 * @param v
	 * @return this matrix
	 */
	Matrix4x4* scale(Vector3* v);

	/** 
	 * Sets up a translation matrix
	 * @param v
	 * @return this matrix
	 */
	Matrix4x4* translate(Vector3* v);

	/** 
	 * Creates a rotation matrix
	 * @param angle
	 * @param vector v
	 * @return this matrix
	 */
	Matrix4x4* rotate(float angle, Vector3* v);

	/** 
	 * Transposes this matrix
	 * @return this matrix
	 */
	Matrix4x4* transpose();

	/** 
	 * Inverts the matrix
	 * Taken from MESA GLU implementation
	 * Copyright (C) 1999-2007  Brian Paul   All Rights Reserved. 
	 * Permission is hereby granted, free of charge, to any person obtaining a
	 * copy of this software and associated documentation files (the "Software"),
	 * to 	deal in the Software without restriction, including without limitation
	 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
	 * and/or sell copies of the Software, and to permit persons to whom the
	 * Software is furnished to do so, subject to the following conditions:
	 * The above copyright notice and this permission notice shall be included
	 * in all copies or substantial portions of the Software.
	 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
	 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
	 * BRIAN PAUL BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
	 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
	 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
	 * @return this matrix
	 */
	Matrix4x4* invert();

	/** 
	 * Returns if this matrix equals m
	 * @param m
	 * @return equals
	 */
	bool equals(Matrix4x4* m);

	/** 
	 * Returns array data
	 * @return array data
	 */
	floatArray* getArray();

	/** 
	 * Clones this matrix
	 * @return new cloned matrix
	 */
	Matrix4x4* clone() override;

	/** 
	 * Interpolates between matrix 1 and matrix 2 by 0f<=t<=1f linearly 
	 * @param matrix 1
	 * @param matrix 2
	 * @param t
	 * @param destination matrix
	 * @return interpolated matrix
	 */
	static Matrix4x4* interpolateLinear(Matrix4x4* m1, Matrix4x4* m2, float t, Matrix4x4* dest);

	/** 
	 * Compute Euler angles (rotation around x, y, z axes)
	 * @see https://github.com/erich666/GraphicsGems/tree/master/gemsiv/euler_angle
	 * This code repository predates the concept of Open Source, and predates most licenses along such lines. 
	 * As such, the official license truly is:
	 * EULA: The Graphics Gems code is copyright-protected. 
	 * In other words, you cannot claim the text of the code as your own and resell it. 
	 * Using the code is permitted in any program, product, or library, non-commercial or commercial. 
	 * Giving credit is not required, though is a nice gesture. 
	 * The code comes as-is, and if there are any flaws or problems with any Gems code, 
	 * nobody involved with Gems - authors, editors, publishers, or webmasters - are to be held responsible. 
	 * Basically, don't be a jerk, and remember that anything free comes with no guarantee.
	 * @param euler
	 */
	void computeEulerAngles(Vector3* euler);

	/** 
	 * @return string representation
	 */
	String* toString() override;

	// Generated
	Matrix4x4();
	Matrix4x4(floatArray* m);
	Matrix4x4(Matrix4x4* matrix);
	Matrix4x4(float r0c0, float r1c0, float r2c0, float r3c0, float r0c1, float r1c1, float r2c1, float r3c1, float r0c2, float r1c2, float r2c2, float r3c2, float r0c3, float r1c3, float r2c3, float r3c3);
protected:
	Matrix4x4(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	virtual bool equals(Object* obj);

private:
	virtual ::java::lang::Class* getClass0();
};
