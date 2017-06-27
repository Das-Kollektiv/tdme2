// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/nio/Buffer.h>

using java::nio::Buffer;
extern void unimplemented_(const char16_t* name);
java::nio::Buffer::Buffer(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::nio::Buffer::Buffer(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3)
	: Buffer(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1, arg2, arg3);
}


void Buffer::ctor(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Buffer::ctor(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3)");
}

int32_t Buffer::capacity()
{ /* stub */
	unimplemented_(u"int32_t Buffer::capacity()");
	return 0;
}

void Buffer::checkBounds(int32_t arg0, int32_t arg1, int32_t arg2)
{ /* stub */
	clinit();
	unimplemented_(u"void Buffer::checkBounds(int32_t arg0, int32_t arg1, int32_t arg2)");
}

int32_t Buffer::checkIndex(int32_t arg0)
{ /* stub */
	unimplemented_(u"int32_t Buffer::checkIndex(int32_t arg0)");
	return 0;
}

int32_t Buffer::checkIndex(int32_t arg0, int32_t arg1)
{ /* stub */
	unimplemented_(u"int32_t Buffer::checkIndex(int32_t arg0, int32_t arg1)");
	return 0;
}

Buffer* Buffer::clear()
{ /* stub */
	unimplemented_(u"Buffer* Buffer::clear()");
	return 0;
}

Buffer* Buffer::flip()
{ /* stub */
	unimplemented_(u"Buffer* Buffer::flip()");
	return 0;
}

bool Buffer::hasRemaining()
{ /* stub */
	unimplemented_(u"bool Buffer::hasRemaining()");
	return 0;
}

int32_t Buffer::limit()
{ /* stub */
	unimplemented_(u"int32_t Buffer::limit()");
	return 0;
}

Buffer* Buffer::limit(int32_t arg0)
{ /* stub */
	unimplemented_(u"Buffer* Buffer::limit(int32_t arg0)");
	return 0;
}

Buffer* Buffer::mark()
{ /* stub */
	unimplemented_(u"Buffer* Buffer::mark()");
	return 0;
}

int32_t Buffer::markValue()
{ /* stub */
	unimplemented_(u"int32_t Buffer::markValue()");
	return 0;
}

int32_t Buffer::nextGetIndex()
{ /* stub */
	unimplemented_(u"int32_t Buffer::nextGetIndex()");
	return 0;
}

int32_t Buffer::nextGetIndex(int32_t arg0)
{ /* stub */
	unimplemented_(u"int32_t Buffer::nextGetIndex(int32_t arg0)");
	return 0;
}

int32_t Buffer::nextPutIndex()
{ /* stub */
	unimplemented_(u"int32_t Buffer::nextPutIndex()");
	return 0;
}

int32_t Buffer::nextPutIndex(int32_t arg0)
{ /* stub */
	unimplemented_(u"int32_t Buffer::nextPutIndex(int32_t arg0)");
	return 0;
}

int32_t Buffer::position()
{ /* stub */
	unimplemented_(u"int32_t Buffer::position()");
	return 0;
}

Buffer* Buffer::position(int32_t arg0)
{ /* stub */
	unimplemented_(u"Buffer* Buffer::position(int32_t arg0)");
	return 0;
}

int32_t Buffer::remaining()
{ /* stub */
	unimplemented_(u"int32_t Buffer::remaining()");
	return 0;
}

Buffer* Buffer::reset()
{ /* stub */
	unimplemented_(u"Buffer* Buffer::reset()");
	return 0;
}

Buffer* Buffer::rewind()
{ /* stub */
	unimplemented_(u"Buffer* Buffer::rewind()");
	return 0;
}

void Buffer::truncate()
{ /* stub */
	unimplemented_(u"void Buffer::truncate()");
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Buffer::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.nio.Buffer", 15);
    return c;
}

java::lang::Class* Buffer::getClass0()
{
	return class_();
}

