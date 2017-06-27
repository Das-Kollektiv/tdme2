// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;


struct java::io::DataInput
	: public virtual Object
{

	virtual bool readBoolean() = 0;
	virtual int8_t readByte() = 0;
	virtual char16_t readChar() = 0;
	virtual double readDouble() = 0;
	virtual float readFloat() = 0;
	virtual void readFully(int8_tArray* arg0) = 0;
	virtual void readFully(int8_tArray* arg0, int32_t arg1, int32_t arg2) = 0;
	virtual int32_t readInt() = 0;
	virtual String* readLine() = 0;
	virtual int64_t readLong() = 0;
	virtual int16_t readShort() = 0;
	virtual String* readUTF() = 0;
	virtual int32_t readUnsignedByte() = 0;
	virtual int32_t readUnsignedShort() = 0;
	virtual int32_t skipBytes(int32_t arg0) = 0;

	// Generated
	static ::java::lang::Class *class_();
};
