// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::io::InputStream;
using java::io::Reader;
using java::util::Properties;


struct default_init_tag;
class java::util::Properties_LineReader
	: public virtual Object
{

public:
	typedef Object super;

public: /* package */
	int8_tArray* inByteBuf {  };
	char16_tArray* inCharBuf {  };
	int32_t inLimit {  };
	int32_t inOff {  };
	InputStream* inStream {  };
	char16_tArray* lineBuf {  };
	Reader* reader {  };
	Properties* this$0 {  };

protected:
	void ctor(InputStream* arg0);
	void ctor(Reader* arg0);

public: /* package */
	virtual int32_t readLine();

	// Generated

public:
	Properties_LineReader(Properties *Properties_this, InputStream* arg0);
	Properties_LineReader(Properties *Properties_this, Reader* arg0);
protected:
	Properties_LineReader(Properties *Properties_this, const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	Properties *Properties_this;

private:
	virtual ::java::lang::Class* getClass0();
};
