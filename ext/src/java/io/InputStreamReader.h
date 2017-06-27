// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/nio/fwd-tdme.h>
#include <java/nio/charset/fwd-tdme.h>
#include <sun/nio/cs/fwd-tdme.h>
#include <java/io/Reader.h>

using java::io::Reader;
using java::io::InputStream;
using java::lang::String;
using java::nio::CharBuffer;
using java::nio::charset::Charset;
using java::nio::charset::CharsetDecoder;
using sun::nio::cs::StreamDecoder;


struct default_init_tag;
class java::io::InputStreamReader
	: public Reader
{

public:
	typedef Reader super;

private:
	StreamDecoder* sd {  };

protected:
	void ctor(InputStream* arg0);
	void ctor(InputStream* arg0, String* arg1);
	void ctor(InputStream* arg0, Charset* arg1);
	void ctor(InputStream* arg0, CharsetDecoder* arg1);

public:
	void close() override;
	virtual String* getEncoding();
	int32_t read() override;
	int32_t read(char16_tArray* arg0, int32_t arg1, int32_t arg2) override;
	bool ready() override;

	// Generated
	InputStreamReader(InputStream* arg0);
	InputStreamReader(InputStream* arg0, String* arg1);
	InputStreamReader(InputStream* arg0, Charset* arg1);
	InputStreamReader(InputStream* arg0, CharsetDecoder* arg1);
protected:
	InputStreamReader(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	int32_t read(CharBuffer* target);
	virtual int32_t read(char16_tArray* cbuf);

private:
	virtual ::java::lang::Class* getClass0();
};
