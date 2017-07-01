#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/nio/fwd-tdme.h>
#include <java/nio/Buffer.h>
#include <Array.h>

using java::nio::Buffer;
using java::lang::Object;

struct default_init_tag;
class java::nio::IntBuffer
	: public Buffer
{

public:
	typedef Buffer super;

protected:
	void ctor(int32_t capacity);
	void ctor(Buffer* buffer);

public:
	int32_t get(int32_t position);
	Buffer* put(int32_t arg0);
	Buffer* put(int32_tArray* arg0);

public: /* package */
	IntBuffer(int32_t capacity);
	IntBuffer(Buffer* buffer);
protected:
	IntBuffer(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
