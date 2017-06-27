// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/io/DataInputStream.h>

using java::io::DataInputStream;
extern void unimplemented_(const char16_t* name);
java::io::DataInputStream::DataInputStream(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::io::DataInputStream::DataInputStream(InputStream* arg0)
	: DataInputStream(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}


void DataInputStream::ctor(InputStream* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void DataInputStream::ctor(InputStream* arg0)");
}

int32_t DataInputStream::read(int8_tArray* arg0)
{ /* stub */
	unimplemented_(u"int32_t DataInputStream::read(int8_tArray* arg0)");
	return 0;
}

int32_t DataInputStream::read(int8_tArray* arg0, int32_t arg1, int32_t arg2)
{ /* stub */
	unimplemented_(u"int32_t DataInputStream::read(int8_tArray* arg0, int32_t arg1, int32_t arg2)");
	return 0;
}

bool DataInputStream::readBoolean()
{ /* stub */
	unimplemented_(u"bool DataInputStream::readBoolean()");
	return 0;
}

int8_t DataInputStream::readByte()
{ /* stub */
	unimplemented_(u"int8_t DataInputStream::readByte()");
	return 0;
}

char16_t DataInputStream::readChar()
{ /* stub */
	unimplemented_(u"char16_t DataInputStream::readChar()");
	return 0;
}

double DataInputStream::readDouble()
{ /* stub */
	unimplemented_(u"double DataInputStream::readDouble()");
	return 0;
}

float DataInputStream::readFloat()
{ /* stub */
	unimplemented_(u"float DataInputStream::readFloat()");
	return 0;
}

void DataInputStream::readFully(int8_tArray* arg0)
{ /* stub */
	unimplemented_(u"void DataInputStream::readFully(int8_tArray* arg0)");
}

void DataInputStream::readFully(int8_tArray* arg0, int32_t arg1, int32_t arg2)
{ /* stub */
	unimplemented_(u"void DataInputStream::readFully(int8_tArray* arg0, int32_t arg1, int32_t arg2)");
}

int32_t DataInputStream::readInt()
{ /* stub */
	unimplemented_(u"int32_t DataInputStream::readInt()");
	return 0;
}

String* DataInputStream::readLine()
{ /* stub */
	unimplemented_(u"String* DataInputStream::readLine()");
	return 0;
}

int64_t DataInputStream::readLong()
{ /* stub */
	unimplemented_(u"int64_t DataInputStream::readLong()");
	return 0;
}

int16_t DataInputStream::readShort()
{ /* stub */
	unimplemented_(u"int16_t DataInputStream::readShort()");
	return 0;
}

String* DataInputStream::readUTF()
{ /* stub */
	unimplemented_(u"String* DataInputStream::readUTF()");
	return 0;
}

String* DataInputStream::readUTF(DataInput* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"String* DataInputStream::readUTF(DataInput* arg0)");
	return 0;
}

int32_t DataInputStream::readUnsignedByte()
{ /* stub */
	unimplemented_(u"int32_t DataInputStream::readUnsignedByte()");
	return 0;
}

int32_t DataInputStream::readUnsignedShort()
{ /* stub */
	unimplemented_(u"int32_t DataInputStream::readUnsignedShort()");
	return 0;
}

int32_t DataInputStream::skipBytes(int32_t arg0)
{ /* stub */
	unimplemented_(u"int32_t DataInputStream::skipBytes(int32_t arg0)");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* DataInputStream::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.io.DataInputStream", 23);
    return c;
}

int32_t DataInputStream::read()
{
	return super::read();
}

java::lang::Class* DataInputStream::getClass0()
{
	return class_();
}

