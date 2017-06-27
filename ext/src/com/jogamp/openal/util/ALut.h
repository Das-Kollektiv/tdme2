// Generated from /tdme/lib/joal.jar

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/openal/fwd-tdme.h>
#include <com/jogamp/openal/util/fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/nio/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using com::jogamp::openal::ALC;
using com::jogamp::openal::ALCcontext;
using com::jogamp::openal::ALCdevice;
using java::io::InputStream;
using java::lang::Comparable;
using java::lang::String;
using java::lang::Thread;
using java::nio::Buffer;
using java::nio::ByteBuffer;

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

using java::lang::ComparableArray;
using java::lang::ObjectArray;
using java::nio::BufferArray;
using java::nio::ByteBufferArray;

struct default_init_tag;
class com::jogamp::openal::util::ALut final
	: public Object
{

public:
	typedef Object super;

private:
	static ALC* alc;
	static ALCcontext* context;
	static ALCdevice* device;
	static Thread* initializingThread;

	/*void ctor(); (private) */

public:
	static void alutExit();
	static void alutInit();
	static void alutLoadWAVFile(String* arg0, int32_tArray* arg1, ByteBufferArray* arg2, int32_tArray* arg3, int32_tArray* arg4, int32_tArray* arg5);
	static void alutLoadWAVFile(InputStream* arg0, int32_tArray* arg1, ByteBufferArray* arg2, int32_tArray* arg3, int32_tArray* arg4, int32_tArray* arg5);

	// Generated
	ALut();
protected:
	ALut(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
