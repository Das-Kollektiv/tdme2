// Generated from /tdme/lib/joal.jar
#include <com/jogamp/openal/util/ALut.h>

using com::jogamp::openal::util::ALut;
template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace lang {
typedef ::SubArray< ::java::lang::Comparable, ObjectArray > ComparableArray;
}  // namespace lang

namespace nio {
typedef ::SubArray< ::java::nio::Buffer, ::java::lang::ObjectArray > BufferArray;
typedef ::SubArray< ::java::nio::ByteBuffer, BufferArray, ::java::lang::ComparableArray > ByteBufferArray;
}  // namespace nio
}  // namespace java

extern void unimplemented_(const char16_t* name);
com::jogamp::openal::util::ALut::ALut(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

ALC* com::jogamp::openal::util::ALut::alc;
ALCcontext* com::jogamp::openal::util::ALut::context;
ALCdevice* com::jogamp::openal::util::ALut::device;
Thread* com::jogamp::openal::util::ALut::initializingThread;

/* private: void ALut::ctor() */
void ALut::alutExit()
{ /* stub */
	clinit();
	unimplemented_(u"void ALut::alutExit()");
}

void ALut::alutInit()
{ /* stub */
	clinit();
	unimplemented_(u"void ALut::alutInit()");
}

void ALut::alutLoadWAVFile(String* arg0, int32_tArray* arg1, ByteBufferArray* arg2, int32_tArray* arg3, int32_tArray* arg4, int32_tArray* arg5)
{ /* stub */
	clinit();
	unimplemented_(u"void ALut::alutLoadWAVFile(String* arg0, int32_tArray* arg1, ByteBufferArray* arg2, int32_tArray* arg3, int32_tArray* arg4, int32_tArray* arg5)");
}

void ALut::alutLoadWAVFile(InputStream* arg0, int32_tArray* arg1, ByteBufferArray* arg2, int32_tArray* arg3, int32_tArray* arg4, int32_tArray* arg5)
{ /* stub */
	clinit();
	unimplemented_(u"void ALut::alutLoadWAVFile(InputStream* arg0, int32_tArray* arg1, ByteBufferArray* arg2, int32_tArray* arg3, int32_tArray* arg4, int32_tArray* arg5)");
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* ALut::class_()
{
    static ::java::lang::Class* c = ::class_(u"com.jogamp.openal.util.ALut", 27);
    return c;
}

java::lang::Class* ALut::getClass0()
{
	return class_();
}

