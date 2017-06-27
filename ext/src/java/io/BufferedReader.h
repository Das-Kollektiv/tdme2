// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/nio/fwd-tdme.h>
#include <java/io/Reader.h>

using java::io::Reader;
using java::lang::String;
using java::nio::CharBuffer;


struct default_init_tag;
class java::io::BufferedReader
	: public Reader
{

public:
	typedef Reader super;

private:
	static constexpr int32_t INVALIDATED { -2 };
	static constexpr int32_t UNMARKED { -1 };
	char16_tArray* cb {  };
	static int32_t defaultCharBufferSize;
	static int32_t defaultExpectedLineLength;
	Reader* in {  };
	int32_t markedChar {  };
	bool markedSkipLF {  };
	int32_t nChars {  };
	int32_t nextChar {  };
	int32_t readAheadLimit {  };
	bool skipLF {  };

protected:
	void ctor(Reader* arg0);
	void ctor(Reader* arg0, int32_t arg1);

public:
	void close() override;
	/*void ensureOpen(); (private) */
	/*void fill(); (private) */
	void mark(int32_t arg0) override;
	bool markSupported() override;
	int32_t read() override;
	int32_t read(char16_tArray* arg0, int32_t arg1, int32_t arg2) override;
	/*int32_t read1(char16_tArray* arg0, int32_t arg1, int32_t arg2); (private) */
	virtual String* readLine();

public: /* package */
	virtual String* readLine(bool arg0);

public:
	bool ready() override;
	void reset() override;
	int64_t skip(int64_t arg0) override;

	// Generated
	BufferedReader(Reader* arg0);
	BufferedReader(Reader* arg0, int32_t arg1);
protected:
	BufferedReader(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	int32_t read(CharBuffer* arg0);
	virtual int32_t read(char16_tArray* arg0);

private:
	virtual ::java::lang::Class* getClass0();
};
