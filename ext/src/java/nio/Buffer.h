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

public: /* package */
	int64_t address {  };

private:
	int32_t capacity_ {  };
	int32_t limit_ {  };
	int32_t mark_ {  };
	int32_t position_ {  };

protected:
	void ctor(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3);

public:
	virtual Object* array() = 0;
	virtual int32_t arrayOffset() = 0;
	int32_t capacity();

public: /* package */
	static void checkBounds(int32_t arg0, int32_t arg1, int32_t arg2);
	int32_t checkIndex(int32_t arg0);
	int32_t checkIndex(int32_t arg0, int32_t arg1);

public:
	Buffer* clear();
	Buffer* flip();
	virtual bool hasArray() = 0;
	bool hasRemaining();
	virtual bool isDirect() = 0;
	virtual bool isReadOnly() = 0;
	int32_t limit();
	Buffer* limit(int32_t arg0);
	Buffer* mark();

public: /* package */
	int32_t markValue();
	int32_t nextGetIndex();
	int32_t nextGetIndex(int32_t arg0);
	int32_t nextPutIndex();
	int32_t nextPutIndex(int32_t arg0);

public:
	int32_t position();
	Buffer* position(int32_t arg0);
	int32_t remaining();
	Buffer* reset();
	Buffer* rewind();

public: /* package */
	void truncate();

	// Generated
	Buffer(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3);
protected:
	Buffer(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
