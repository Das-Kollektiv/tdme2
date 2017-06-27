// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/io/FilterInputStream.h>
#include <java/io/DataInput.h>

using java::io::FilterInputStream;
using java::io::DataInput;
using java::io::InputStream;
using java::lang::String;


struct default_init_tag;
class java::io::DataInputStream
	: public FilterInputStream
	, public virtual DataInput
{

public:
	typedef FilterInputStream super;

private:
	int8_tArray* bytearr {  };
	char16_tArray* chararr {  };
	char16_tArray* lineBuffer {  };
	int8_tArray* readBuffer {  };

protected:
	void ctor(InputStream* arg0);

public:
	int32_t read(int8_tArray* arg0) override;
	int32_t read(int8_tArray* arg0, int32_t arg1, int32_t arg2) override;
	bool readBoolean() override;
	int8_t readByte() override;
	char16_t readChar() override;
	double readDouble() override;
	float readFloat() override;
	void readFully(int8_tArray* arg0) override;
	void readFully(int8_tArray* arg0, int32_t arg1, int32_t arg2) override;
	int32_t readInt() override;
	String* readLine() override;
	int64_t readLong() override;
	int16_t readShort() override;
	String* readUTF() override;
	static String* readUTF(DataInput* arg0);
	int32_t readUnsignedByte() override;
	int32_t readUnsignedShort() override;
	int32_t skipBytes(int32_t arg0) override;

	// Generated
	DataInputStream(InputStream* arg0);
protected:
	DataInputStream(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	int32_t read();

private:
	virtual ::java::lang::Class* getClass0();
};
