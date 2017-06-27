// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/nio/fwd-tdme.h>
#include <java/lang/Object.h>
#include <java/lang/Readable.h>
#include <java/io/Closeable.h>

using java::lang::Object;
using java::lang::Readable;
using java::io::Closeable;
using java::nio::CharBuffer;


struct default_init_tag;
class java::io::Reader
	: public virtual Object
	, public virtual Readable
	, public virtual Closeable
{

public:
	typedef Object super;

public: /* protected */
	Object* lock {  };

private:
	static constexpr int32_t maxSkipBufferSize { 8192 };
	char16_tArray* skipBuffer {  };

protected:
	void ctor();
	void ctor(Object* arg0);
	/*void close(); (already declared) */

public:
	virtual void mark(int32_t arg0);
	virtual bool markSupported();
	virtual int32_t read();
	int32_t read(CharBuffer* arg0) override;
	virtual int32_t read(char16_tArray* arg0);
	virtual int32_t read(char16_tArray* arg0, int32_t arg1, int32_t arg2) = 0;
	virtual bool ready();
	virtual void reset();
	virtual int64_t skip(int64_t arg0);

	// Generated

public: /* protected */
	Reader();
	Reader(Object* arg0);
protected:
	Reader(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
