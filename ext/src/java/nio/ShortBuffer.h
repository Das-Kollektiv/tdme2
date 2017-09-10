#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/nio/fwd-tdme.h>
#include <java/nio/Buffer.h>
#include <Array.h>

using java::nio::Buffer;
using java::lang::Object;

struct default_init_tag;
class java::nio::ShortBuffer
	: public Buffer
{

public:
	typedef Buffer super;

protected:
	void ctor(int32_t capacity);
	void ctor(Buffer* buffer);

public:
	virtual int32_t position();
	short get(int32_t position);
	Buffer* put(int16_t arg0);
	Buffer* put(int16_tArray* arg0);

public: /* package */
	ShortBuffer(int32_t capacity);
	ShortBuffer(Buffer* buffer);
protected:
	ShortBuffer(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
