// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/nio/fwd-tdme.h>
#include <java/nio/Buffer.h>
#include <java/lang/Comparable.h>
#include <Array.h>

using java::nio::Buffer;
using java::lang::Comparable;
using java::lang::Object;
using java::lang::String;
using java::nio::ByteOrder;
using java::nio::CharBuffer;
using java::nio::DoubleBuffer;
using java::nio::FloatBuffer;
using java::nio::IntBuffer;
using java::nio::LongBuffer;
using java::nio::ShortBuffer;


struct default_init_tag;
class java::nio::ByteBuffer
	: public Buffer
	, public virtual Comparable
{

public:
	typedef Buffer super;

public: /* package */
	bool bigEndian {  };
	int8_tArray* hb {  };
	bool isReadOnly_ {  };
	bool nativeByteOrder {  };
	int32_t offset {  };

protected:
	void ctor(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3);
	void ctor(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, int8_tArray* arg4, int32_t arg5);

public: /* package */
	virtual int8_t _get(int32_t arg0) = 0;
	virtual void _put(int32_t arg0, int8_t arg1) = 0;

public:
	static ByteBuffer* allocate(int32_t arg0);
	static ByteBuffer* allocateDirect(int32_t arg0);
	int8_tArray* array() override;
	int32_t arrayOffset() override;
	virtual CharBuffer* asCharBuffer() = 0;
	virtual DoubleBuffer* asDoubleBuffer() = 0;
	virtual FloatBuffer* asFloatBuffer() = 0;
	virtual IntBuffer* asIntBuffer() = 0;
	virtual LongBuffer* asLongBuffer() = 0;
	virtual ByteBuffer* asReadOnlyBuffer() = 0;
	virtual ShortBuffer* asShortBuffer() = 0;
	virtual ByteBuffer* compact() = 0;
	virtual int32_t compareTo(ByteBuffer* arg0);
	virtual ByteBuffer* duplicate() = 0;
	bool equals(Object* arg0) override;
	virtual int8_t get() = 0;
	virtual int8_t get(int32_t arg0) = 0;
	virtual ByteBuffer* get(int8_tArray* arg0);
	virtual ByteBuffer* get(int8_tArray* arg0, int32_t arg1, int32_t arg2);
	virtual char16_t getChar() = 0;
	virtual char16_t getChar(int32_t arg0) = 0;
	virtual double getDouble() = 0;
	virtual double getDouble(int32_t arg0) = 0;
	virtual float getFloat() = 0;
	virtual float getFloat(int32_t arg0) = 0;
	virtual int32_t getInt() = 0;
	virtual int32_t getInt(int32_t arg0) = 0;
	virtual int64_t getLong() = 0;
	virtual int64_t getLong(int32_t arg0) = 0;
	virtual int16_t getShort() = 0;
	virtual int16_t getShort(int32_t arg0) = 0;
	bool hasArray() override;
	int32_t hashCode() override;
	bool isDirect() = 0;
	ByteOrder* order();
	ByteBuffer* order(ByteOrder* arg0);
	virtual ByteBuffer* put(int8_t arg0) = 0;
	virtual ByteBuffer* put(ByteBuffer* arg0);
	ByteBuffer* put(int8_tArray* arg0);
	virtual ByteBuffer* put(int32_t arg0, int8_t arg1) = 0;
	virtual ByteBuffer* put(int8_tArray* arg0, int32_t arg1, int32_t arg2);
	virtual ByteBuffer* putChar(char16_t arg0) = 0;
	virtual ByteBuffer* putChar(int32_t arg0, char16_t arg1) = 0;
	virtual ByteBuffer* putDouble(double arg0) = 0;
	virtual ByteBuffer* putDouble(int32_t arg0, double arg1) = 0;
	virtual ByteBuffer* putFloat(float arg0) = 0;
	virtual ByteBuffer* putFloat(int32_t arg0, float arg1) = 0;
	virtual ByteBuffer* putInt(int32_t arg0) = 0;
	virtual ByteBuffer* putInt(int32_t arg0, int32_t arg1) = 0;
	virtual ByteBuffer* putLong(int64_t arg0) = 0;
	virtual ByteBuffer* putLong(int32_t arg0, int64_t arg1) = 0;
	virtual ByteBuffer* putShort(int16_t arg0) = 0;
	virtual ByteBuffer* putShort(int32_t arg0, int16_t arg1) = 0;
	virtual ByteBuffer* slice() = 0;
	String* toString() override;
	static ByteBuffer* wrap(int8_tArray* arg0);
	static ByteBuffer* wrap(int8_tArray* arg0, int32_t arg1, int32_t arg2);

	// Generated

public: /* package */
	ByteBuffer(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3);
	ByteBuffer(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, int8_tArray* arg4, int32_t arg5);
protected:
	ByteBuffer(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	virtual int32_t compareTo(Object* o) override;

private:
	virtual ::java::lang::Class* getClass0();
};
