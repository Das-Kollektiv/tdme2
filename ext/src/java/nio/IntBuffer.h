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
class java::nio::IntBuffer
	: public Buffer
	, public virtual Comparable
{

public:
	typedef Buffer super;

public: /* package */
	int32_tArray* hb {  };
	bool isReadOnly_ {  };
	int32_t offset {  };

protected:
	void ctor(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3);
	void ctor(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, int32_tArray* arg4, int32_t arg5);

public:
	static IntBuffer* allocate(int32_t arg0);
	int32_tArray* array() override;
	int32_t arrayOffset() override;
	virtual IntBuffer* asReadOnlyBuffer() = 0;
	virtual IntBuffer* compact() = 0;
	virtual int32_t compareTo(IntBuffer* arg0);
	virtual IntBuffer* duplicate() = 0;
	bool equals(Object* arg0) override;
	virtual int32_t get() = 0;
	virtual int32_t get(int32_t arg0) = 0;
	virtual IntBuffer* get(int32_tArray* arg0);
	virtual IntBuffer* get(int32_tArray* arg0, int32_t arg1, int32_t arg2);
	bool hasArray() override;
	int32_t hashCode() override;
	bool isDirect() = 0;
	virtual ByteOrder* order() = 0;
	virtual IntBuffer* put(int32_t arg0) = 0;
	virtual IntBuffer* put(IntBuffer* arg0);
	IntBuffer* put(int32_tArray* arg0);
	virtual IntBuffer* put(int32_t arg0, int32_t arg1) = 0;
	virtual IntBuffer* put(int32_tArray* arg0, int32_t arg1, int32_t arg2);
	virtual IntBuffer* slice() = 0;
	String* toString() override;
	static IntBuffer* wrap(int32_tArray* arg0);
	static IntBuffer* wrap(int32_tArray* arg0, int32_t arg1, int32_t arg2);

	// Generated

public: /* package */
	IntBuffer(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3);
	IntBuffer(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, int32_tArray* arg4, int32_t arg5);
protected:
	IntBuffer(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	virtual int32_t compareTo(Object* o) override;

private:
	virtual ::java::lang::Class* getClass0();
};
