// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/util/zip/fwd-tdme.h>
#include <java/io/FilterInputStream.h>

using java::io::FilterInputStream;
using java::io::InputStream;
using java::util::zip::Inflater;


struct default_init_tag;
class java::util::zip::InflaterInputStream
	: public FilterInputStream
{

public:
	typedef FilterInputStream super;

private:
	int8_tArray* b {  };

public: /* protected */
	int8_tArray* buf {  };

private:
	bool closed {  };

public: /* protected */
	Inflater* inf {  };
	int32_t len {  };

private:
	bool reachEOF {  };
	int8_tArray* singleByteBuf {  };

public: /* package */
	bool usesDefaultInflater {  };

protected:
	void ctor(InputStream* arg0);
	void ctor(InputStream* arg0, Inflater* arg1);
	void ctor(InputStream* arg0, Inflater* arg1, int32_t arg2);

public:
	int32_t available() override;
	void close() override;
	/*void ensureOpen(); (private) */

public: /* protected */
	virtual void fill();

public:
	void mark(int32_t arg0) override;
	bool markSupported() override;
	int32_t read() override;
	int32_t read(int8_tArray* arg0, int32_t arg1, int32_t arg2) override;
	void reset() override;
	int64_t skip(int64_t arg0) override;

	// Generated
	InflaterInputStream(InputStream* arg0);
	InflaterInputStream(InputStream* arg0, Inflater* arg1);
	InflaterInputStream(InputStream* arg0, Inflater* arg1, int32_t arg2);
protected:
	InflaterInputStream(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	int32_t read(int8_tArray* arg0);

private:
	virtual ::java::lang::Class* getClass0();
};
