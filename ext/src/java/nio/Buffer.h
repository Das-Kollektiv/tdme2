// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/nio/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;


struct default_init_tag;
class java::nio::Buffer
	: public virtual Object
{

public:
	typedef Object super;

private:
	int32_t capacity_ { 0 };
	int32_t position_ { 0 };
	int8_t* buffer { nullptr };

protected:
	void ctor(int32_t capacity);
	void ctor(Buffer* buffer);
	void ctor(int32_t capacity, int8_t* data);

public:
	int32_t capacity();

public:
	Buffer* clear();
	int32_t position();

	int8_t get(int32_t position);
	Buffer* put(int8_t arg0);
	Buffer* put(int8_tArray* arg0);

	const int8_t* getBuffer();

public: /* package */
	// Generated
	Buffer(int32_t capacity);
	Buffer(Buffer* buffer);
	Buffer(int32_t capacity, int8_t* data);
protected:
	Buffer(const ::default_init_tag&);

public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
