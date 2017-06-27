// Generated from /tdme/lib/gluegen-rt.jar

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/common/nio/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/nio/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using java::nio::Buffer;
using java::nio::ByteBuffer;
using java::nio::CharBuffer;
using java::nio::DoubleBuffer;
using java::nio::FloatBuffer;
using java::nio::IntBuffer;
using java::nio::LongBuffer;
using java::nio::ShortBuffer;


struct default_init_tag;
class com::jogamp::common::nio::Buffers
	: public virtual Object
{

public:
	typedef Object super;
	static constexpr int32_t SIZEOF_BYTE { 1 };
	static constexpr int32_t SIZEOF_CHAR { 2 };
	static constexpr int32_t SIZEOF_DOUBLE { 8 };
	static constexpr int32_t SIZEOF_FLOAT { 4 };
	static constexpr int32_t SIZEOF_INT { 4 };
	static constexpr int32_t SIZEOF_LONG { 8 };
	static constexpr int32_t SIZEOF_SHORT { 2 };

protected:
	void ctor();

public:
	static ByteBuffer* copyByteBuffer(ByteBuffer* arg0);
	static FloatBuffer* copyFloatBuffer(FloatBuffer* arg0);
	static ByteBuffer* copyFloatBufferAsByteBuffer(FloatBuffer* arg0);
	static IntBuffer* copyIntBuffer(IntBuffer* arg0);
	static ByteBuffer* copyIntBufferAsByteBuffer(IntBuffer* arg0);
	static ShortBuffer* copyShortBuffer(ShortBuffer* arg0);
	static ByteBuffer* copyShortBufferAsByteBuffer(ShortBuffer* arg0);
	static Object* getArray(Object* arg0);
	static int32_t getDirectBufferByteOffset(Object* arg0);
	static doubleArray* getDoubleArray(floatArray* arg0, int32_t arg1, doubleArray* arg2, int32_t arg3, int32_t arg4);
	static DoubleBuffer* getDoubleBuffer(FloatBuffer* arg0, DoubleBuffer* arg1);
	static floatArray* getFloatArray(doubleArray* arg0, int32_t arg1, floatArray* arg2, int32_t arg3, int32_t arg4);
	static FloatBuffer* getFloatBuffer(DoubleBuffer* arg0, FloatBuffer* arg1);
	static int32_t getIndirectBufferByteOffset(Object* arg0);
	static bool isDirect(Object* arg0);
	static ByteBuffer* nativeOrder(ByteBuffer* arg0);
	static ByteBuffer* newDirectByteBuffer(int32_t arg0);
	static ByteBuffer* newDirectByteBuffer(int8_tArray* arg0);
	static ByteBuffer* newDirectByteBuffer(int8_tArray* arg0, int32_t arg1);
	static ByteBuffer* newDirectByteBuffer(int8_tArray* arg0, int32_t arg1, int32_t arg2);
	static CharBuffer* newDirectCharBuffer(int32_t arg0);
	static CharBuffer* newDirectCharBuffer(char16_tArray* arg0);
	static CharBuffer* newDirectCharBuffer(char16_tArray* arg0, int32_t arg1);
	static CharBuffer* newDirectCharBuffer(char16_tArray* arg0, int32_t arg1, int32_t arg2);
	static DoubleBuffer* newDirectDoubleBuffer(int32_t arg0);
	static DoubleBuffer* newDirectDoubleBuffer(doubleArray* arg0);
	static DoubleBuffer* newDirectDoubleBuffer(doubleArray* arg0, int32_t arg1);
	static DoubleBuffer* newDirectDoubleBuffer(doubleArray* arg0, int32_t arg1, int32_t arg2);
	static FloatBuffer* newDirectFloatBuffer(int32_t arg0);
	static FloatBuffer* newDirectFloatBuffer(floatArray* arg0);
	static FloatBuffer* newDirectFloatBuffer(floatArray* arg0, int32_t arg1);
	static FloatBuffer* newDirectFloatBuffer(floatArray* arg0, int32_t arg1, int32_t arg2);
	static IntBuffer* newDirectIntBuffer(int32_t arg0);
	static IntBuffer* newDirectIntBuffer(int32_tArray* arg0);
	static IntBuffer* newDirectIntBuffer(int32_tArray* arg0, int32_t arg1);
	static IntBuffer* newDirectIntBuffer(int32_tArray* arg0, int32_t arg1, int32_t arg2);
	static LongBuffer* newDirectLongBuffer(int32_t arg0);
	static LongBuffer* newDirectLongBuffer(int64_tArray* arg0);
	static LongBuffer* newDirectLongBuffer(int64_tArray* arg0, int32_t arg1);
	static LongBuffer* newDirectLongBuffer(int64_tArray* arg0, int32_t arg1, int32_t arg2);
	static ShortBuffer* newDirectShortBuffer(int32_t arg0);
	static ShortBuffer* newDirectShortBuffer(int16_tArray* arg0);
	static ShortBuffer* newDirectShortBuffer(int16_tArray* arg0, int32_t arg1);
	static ShortBuffer* newDirectShortBuffer(int16_tArray* arg0, int32_t arg1, int32_t arg2);
	static Buffer* put(Buffer* arg0, Buffer* arg1);
	static Buffer* putNb(Buffer* arg0, bool arg1, int8_t arg2, bool arg3);
	static Buffer* putNf(Buffer* arg0, bool arg1, float arg2);
	static Buffer* putNi(Buffer* arg0, bool arg1, int32_t arg2, bool arg3);
	static Buffer* putNs(Buffer* arg0, bool arg1, int16_t arg2, bool arg3);
	static Buffer* putb(Buffer* arg0, int8_t arg1);
	static Buffer* putd(Buffer* arg0, double arg1);
	static Buffer* putf(Buffer* arg0, float arg1);
	static Buffer* puti(Buffer* arg0, int32_t arg1);
	static Buffer* puts(Buffer* arg0, int16_t arg1);
	static void rangeCheck(Buffer* arg0, int32_t arg1);
	static void rangeCheck(int8_tArray* arg0, int32_t arg1, int32_t arg2);
	static void rangeCheck(char16_tArray* arg0, int32_t arg1, int32_t arg2);
	static void rangeCheck(int16_tArray* arg0, int32_t arg1, int32_t arg2);
	static void rangeCheck(int32_tArray* arg0, int32_t arg1, int32_t arg2);
	static void rangeCheck(int64_tArray* arg0, int32_t arg1, int32_t arg2);
	static void rangeCheck(floatArray* arg0, int32_t arg1, int32_t arg2);
	static void rangeCheck(doubleArray* arg0, int32_t arg1, int32_t arg2);
	static void rangeCheckBytes(Object* arg0, int32_t arg1);
	static int32_t remainingBytes(Object* arg0);
	static int32_t remainingElem(Object* arg0);
	static int32_t sizeOfBufferElem(Object* arg0);
	static Buffer* slice(Buffer* arg0);
	static Buffer* slice(Buffer* arg0, int32_t arg1, int32_t arg2);
	static FloatBuffer* slice2Float(Buffer* arg0, int32_t arg1, int32_t arg2);
	static FloatBuffer* slice2Float(floatArray* arg0, int32_t arg1, int32_t arg2);
	static StringBuilder* toString(StringBuilder* arg0, String* arg1, Buffer* arg2);

	// Generated

public: /* protected */
	Buffers();
protected:
	Buffers(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
