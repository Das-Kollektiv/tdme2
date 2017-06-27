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
class java::nio::ShortBuffer
	: public Buffer
	, public virtual Comparable
{

public:
	typedef Buffer super;

public: /* package */
	int16_tArray* hb {  };
	bool isReadOnly_ {  };
	int32_t offset {  };

protected:
	void ctor(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3);
	void ctor(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, int16_tArray* arg4, int32_t arg5);

public:
	static ShortBuffer* allocate(int32_t arg0);
	int16_tArray* array() override;
	int32_t arrayOffset() override;
	virtual ShortBuffer* asReadOnlyBuffer() = 0;
	virtual ShortBuffer* compact() = 0;
	virtual int32_t compareTo(ShortBuffer* arg0);
	virtual ShortBuffer* duplicate() = 0;
	bool equals(Object* arg0) override;
	virtual int16_t get() = 0;
	virtual int16_t get(int32_t arg0) = 0;
	virtual ShortBuffer* get(int16_tArray* arg0);
	virtual ShortBuffer* get(int16_tArray* arg0, int32_t arg1, int32_t arg2);
	bool hasArray() override;
	int32_t hashCode() override;
	bool isDirect() = 0;
	virtual ByteOrder* order() = 0;
	virtual ShortBuffer* put(int16_t arg0) = 0;
	virtual ShortBuffer* put(ShortBuffer* arg0);
	ShortBuffer* put(int16_tArray* arg0);
	virtual ShortBuffer* put(int32_t arg0, int16_t arg1) = 0;
	virtual ShortBuffer* put(int16_tArray* arg0, int32_t arg1, int32_t arg2);
	virtual ShortBuffer* slice() = 0;
	String* toString() override;
	static ShortBuffer* wrap(int16_tArray* arg0);
	static ShortBuffer* wrap(int16_tArray* arg0, int32_t arg1, int32_t arg2);

	// Generated

public: /* package */
	ShortBuffer(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3);
	ShortBuffer(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, int16_tArray* arg4, int32_t arg5);
protected:
	ShortBuffer(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	virtual int32_t compareTo(Object* o) override;

private:
	virtual ::java::lang::Class* getClass0();
};
