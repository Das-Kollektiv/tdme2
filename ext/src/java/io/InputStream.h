// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/Object.h>
#include <java/io/Closeable.h>

using java::lang::Object;
using java::io::Closeable;


struct default_init_tag;
class java::io::InputStream
	: public virtual Object
	, public virtual Closeable
{

public:
	typedef Object super;

private:
	static constexpr int32_t MAX_SKIP_BUFFER_SIZE { 2048 };

protected:
	void ctor();

public:
	virtual int32_t available();
	void close() override;
	virtual void mark(int32_t readlimit);
	virtual bool markSupported();
	virtual int32_t read() = 0;
	virtual int32_t read(int8_tArray* b);
	virtual int32_t read(int8_tArray* b, int32_t off, int32_t len);
	virtual void reset();
	virtual int64_t skip(int64_t n);

	// Generated
	InputStream();
protected:
	InputStream(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
