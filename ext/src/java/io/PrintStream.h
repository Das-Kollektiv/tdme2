// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/io/FilterOutputStream.h>
#include <java/lang/Appendable.h>
#include <java/io/Closeable.h>

using java::io::FilterOutputStream;
using java::lang::Appendable;
using java::io::Closeable;
using java::io::BufferedWriter;
using java::io::File;
using java::io::OutputStream;
using java::io::OutputStreamWriter;
using java::lang::CharSequence;
using java::lang::Object;
using java::lang::String;
using java::util::Formatter;
using java::util::Locale;

using java::lang::ObjectArray;

struct default_init_tag;
class java::io::PrintStream
	: public FilterOutputStream
	, public virtual Appendable
	, public virtual Closeable
{

public:
	typedef FilterOutputStream super;

private:
	bool autoFlush {  };
	OutputStreamWriter* charOut {  };
	bool closing {  };
	Formatter* formatter {  };
	BufferedWriter* textOut {  };
	bool trouble {  };

protected:
	void ctor(OutputStream* arg0);
	void ctor(String* arg0);
	void ctor(File* arg0);
	/*void ctor(bool arg0, OutputStream* arg1); (private) */
	void ctor(OutputStream* arg0, bool arg1);
	void ctor(String* arg0, String* arg1);
	void ctor(File* arg0, String* arg1);
	void ctor(OutputStream* arg0, bool arg1, String* arg2);

public:
	PrintStream* append(CharSequence* arg0) override;
	PrintStream* append(char16_t arg0) override;
	PrintStream* append(CharSequence* arg0, int32_t arg1, int32_t arg2) override;
	virtual bool checkError();

public: /* protected */
	virtual void clearError();

public:
	void close() override;
	/*void ensureOpen(); (private) */
	void flush() override;
	virtual PrintStream* format(String* arg0, ObjectArray* arg1);
	virtual PrintStream* format(Locale* arg0, String* arg1, ObjectArray* arg2);
	/*void init_(OutputStreamWriter* arg0); (private) */
	/*void newLine(); (private) */
	virtual void print(bool arg0);
	virtual void print(char16_t arg0);
	virtual void print(int32_t arg0);
	virtual void print(int64_t arg0);
	virtual void print(float arg0);
	virtual void print(double arg0);
	virtual void print(char16_tArray* arg0);
	virtual void print(String* arg0);
	virtual void print(Object* arg0);
	virtual PrintStream* printf(String* arg0, ObjectArray* arg1);
	virtual PrintStream* printf(Locale* arg0, String* arg1, ObjectArray* arg2);
	virtual void println();
	virtual void println(bool arg0);
	virtual void println(char16_t arg0);
	virtual void println(int32_t arg0);
	virtual void println(int64_t arg0);
	virtual void println(float arg0);
	virtual void println(double arg0);
	virtual void println(char16_tArray* arg0);
	virtual void println(String* arg0);
	virtual void println(Object* arg0);

public: /* protected */
	virtual void setError();

public:
	void write(int32_t arg0) override;
	/*void write(char16_tArray* arg0); (private) */
	/*void write(String* arg0); (private) */
	void write(int8_tArray* arg0, int32_t arg1, int32_t arg2) override;

	// Generated
	PrintStream(OutputStream* arg0);
	PrintStream(String* arg0);
	PrintStream(File* arg0);
	PrintStream(OutputStream* arg0, bool arg1);
	PrintStream(String* arg0, String* arg1);
	PrintStream(File* arg0, String* arg1);
	PrintStream(OutputStream* arg0, bool arg1, String* arg2);
protected:
	PrintStream(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	void write(int8_tArray* arg0);

private:
	virtual ::java::lang::Class* getClass0();
};
