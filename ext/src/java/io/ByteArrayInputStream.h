// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/io/InputStream.h>

using java::io::InputStream;


struct default_init_tag;
class java::io::ByteArrayInputStream
	: public InputStream
{

public:
	typedef InputStream super;

public: /* protected */
	int8_tArray* buf {  };
	int32_t count {  };
	int32_t mark_ {  };
	int32_t pos {  };

protected:
	void ctor(int8_tArray* arg0);
	void ctor(int8_tArray* arg0, int32_t arg1, int32_t arg2);

public:
	int32_t available() override;
	void close() override;
	void mark(int32_t arg0) override;
	bool markSupported() override;
	int32_t read() override;
	int32_t read(int8_tArray* arg0, int32_t arg1, int32_t arg2) override;
	void reset() override;
	int64_t skip(int64_t arg0) override;

	// Generated
	ByteArrayInputStream(int8_tArray* arg0);
	ByteArrayInputStream(int8_tArray* arg0, int32_t arg1, int32_t arg2);
protected:
	ByteArrayInputStream(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	virtual int32_t read(int8_tArray* arg0);

private:
	virtual ::java::lang::Class* getClass0();
};
