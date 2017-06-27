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


struct default_init_tag;
class java::nio::FloatBuffer
	: public Buffer
	, public virtual Comparable
{

public:
	typedef Buffer super;

public: /* package */
	floatArray* hb {  };
	bool isReadOnly_ {  };
	int32_t offset {  };

protected:
	void ctor(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3);
	void ctor(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, floatArray* arg4, int32_t arg5);

public:
	static FloatBuffer* allocate(int32_t arg0);
	floatArray* array() override;
	int32_t arrayOffset() override;
	virtual FloatBuffer* asReadOnlyBuffer() = 0;
	virtual FloatBuffer* compact() = 0;
	virtual int32_t compareTo(FloatBuffer* arg0);
	virtual FloatBuffer* duplicate() = 0;
	bool equals(Object* arg0) override;
	virtual float get() = 0;
	virtual float get(int32_t arg0) = 0;
	virtual FloatBuffer* get(floatArray* arg0);
	virtual FloatBuffer* get(floatArray* arg0, int32_t arg1, int32_t arg2);
	bool hasArray() override;
	int32_t hashCode() override;
	bool isDirect() = 0;
	virtual ByteOrder* order() = 0;
	virtual FloatBuffer* put(float arg0) = 0;
	virtual FloatBuffer* put(FloatBuffer* arg0);
	FloatBuffer* put(floatArray* arg0);
	virtual FloatBuffer* put(int32_t arg0, float arg1) = 0;
	virtual FloatBuffer* put(floatArray* arg0, int32_t arg1, int32_t arg2);
	virtual FloatBuffer* slice() = 0;
	String* toString() override;
	static FloatBuffer* wrap(floatArray* arg0);
	static FloatBuffer* wrap(floatArray* arg0, int32_t arg1, int32_t arg2);

	// Generated

public: /* package */
	FloatBuffer(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3);
	FloatBuffer(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, floatArray* arg4, int32_t arg5);
protected:
	FloatBuffer(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	virtual int32_t compareTo(Object* o) override;

private:
	virtual ::java::lang::Class* getClass0();
};
