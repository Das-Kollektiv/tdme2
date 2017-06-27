// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/Object.h>
#include <java/io/Closeable.h>
#include <java/io/Flushable.h>

using java::lang::Object;
using java::io::Closeable;
using java::io::Flushable;


struct default_init_tag;
class java::io::OutputStream
	: public virtual Object
	, public virtual Closeable
	, public virtual Flushable
{

public:
	typedef Object super;

protected:
	void ctor();

public:
	void close() override;
	void flush() override;
	virtual void write(int32_t arg0) = 0;
	virtual void write(int8_tArray* arg0);
	virtual void write(int8_tArray* arg0, int32_t arg1, int32_t arg2);

	// Generated
	OutputStream();
protected:
	OutputStream(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
