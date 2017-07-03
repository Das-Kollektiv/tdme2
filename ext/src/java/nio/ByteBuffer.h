// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/nio/fwd-tdme.h>
#include <java/nio/Buffer.h>
#include <Array.h>

using java::nio::Buffer;
using java::lang::Object;
using java::lang::String;
using java::nio::FloatBuffer;
using java::nio::IntBuffer;
using java::nio::ShortBuffer;


struct default_init_tag;
class java::nio::ByteBuffer
	: public Buffer
{

public:
	typedef Buffer super;

protected:
	void ctor(int32_t _capacity);
	void ctor(Buffer* buffer);
	void ctor(int32_t _capacity, int8_t* data);

public:
	static ByteBuffer* allocateDirect(int32_t arg0);
	FloatBuffer* asFloatBuffer();
	IntBuffer* asIntBuffer();
	ShortBuffer* asShortBuffer();

	//
	ByteBuffer* put(int8_tArray* arg0);
public: /* package */
	ByteBuffer(int32_t capacity);
	ByteBuffer(Buffer* buffer);
	ByteBuffer(int32_t _capacity, int8_t* data);
protected:
	ByteBuffer(const ::default_init_tag&);

public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
