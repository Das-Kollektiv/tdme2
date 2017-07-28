#pragma once

#include <array>

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/nio/fwd-tdme.h>
#include <java/nio/Buffer.h>
#include <Array.h>

using std::array;

using java::nio::Buffer;
using java::lang::Object;

struct default_init_tag;
class java::nio::FloatBuffer
	: public Buffer
{

public:
	typedef Buffer super;

protected:
	void ctor(int32_t capacity);
	void ctor(Buffer* buffer);

public:
	float get(int32_t position);
	Buffer* put(float arg0);
	Buffer* put(floatArray* arg0);
	Buffer* put(array<float, 2>* arg0);
	Buffer* put(array<float, 3>* arg0);
	Buffer* put(array<float, 4>* arg0);

public: /* package */
	FloatBuffer(int32_t capacity);
	FloatBuffer(Buffer* buffer);
protected:
	FloatBuffer(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
