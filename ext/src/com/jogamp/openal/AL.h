// Generated from /tdme/lib/joal.jar

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/openal/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/nio/fwd-tdme.h>
#include <com/jogamp/openal/ALConstants.h>

using com::jogamp::openal::ALConstants;
using java::lang::String;
using java::nio::Buffer;
using java::nio::ByteBuffer;
using java::nio::DoubleBuffer;
using java::nio::FloatBuffer;
using java::nio::IntBuffer;


struct com::jogamp::openal::AL
	: public virtual ALConstants
{
	static constexpr int32_t HAS_STDDEF { 1 };

	virtual void alBuffer3f(int32_t arg0, int32_t arg1, float arg2, float arg3, float arg4) = 0;
	virtual void alBuffer3i(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, int32_t arg4) = 0;
	virtual void alBufferData(int32_t arg0, int32_t arg1, Buffer* arg2, int32_t arg3, int32_t arg4) = 0;
	virtual void alBufferf(int32_t arg0, int32_t arg1, float arg2) = 0;
	virtual void alBufferfv(int32_t arg0, int32_t arg1, FloatBuffer* arg2) = 0;
	virtual void alBufferfv(int32_t arg0, int32_t arg1, floatArray* arg2, int32_t arg3) = 0;
	virtual void alBufferi(int32_t arg0, int32_t arg1, int32_t arg2) = 0;
	virtual void alBufferiv(int32_t arg0, int32_t arg1, IntBuffer* arg2) = 0;
	virtual void alBufferiv(int32_t arg0, int32_t arg1, int32_tArray* arg2, int32_t arg3) = 0;
	virtual void alDeleteBuffers(int32_t arg0, IntBuffer* arg1) = 0;
	virtual void alDeleteBuffers(int32_t arg0, int32_tArray* arg1, int32_t arg2) = 0;
	virtual void alDeleteSources(int32_t arg0, IntBuffer* arg1) = 0;
	virtual void alDeleteSources(int32_t arg0, int32_tArray* arg1, int32_t arg2) = 0;
	virtual void alDisable(int32_t arg0) = 0;
	virtual void alDistanceModel(int32_t arg0) = 0;
	virtual void alDopplerFactor(float arg0) = 0;
	virtual void alDopplerVelocity(float arg0) = 0;
	virtual void alEnable(int32_t arg0) = 0;
	virtual void alGenBuffers(int32_t arg0, IntBuffer* arg1) = 0;
	virtual void alGenBuffers(int32_t arg0, int32_tArray* arg1, int32_t arg2) = 0;
	virtual void alGenSources(int32_t arg0, IntBuffer* arg1) = 0;
	virtual void alGenSources(int32_t arg0, int32_tArray* arg1, int32_t arg2) = 0;
	virtual bool alGetBoolean(int32_t arg0) = 0;
	virtual void alGetBooleanv(int32_t arg0, ByteBuffer* arg1) = 0;
	virtual void alGetBooleanv(int32_t arg0, int8_tArray* arg1, int32_t arg2) = 0;
	virtual void alGetBuffer3f(int32_t arg0, int32_t arg1, FloatBuffer* arg2, FloatBuffer* arg3, FloatBuffer* arg4) = 0;
	virtual void alGetBuffer3f(int32_t arg0, int32_t arg1, floatArray* arg2, int32_t arg3, floatArray* arg4, int32_t arg5, floatArray* arg6, int32_t arg7) = 0;
	virtual void alGetBuffer3i(int32_t arg0, int32_t arg1, IntBuffer* arg2, IntBuffer* arg3, IntBuffer* arg4) = 0;
	virtual void alGetBuffer3i(int32_t arg0, int32_t arg1, int32_tArray* arg2, int32_t arg3, int32_tArray* arg4, int32_t arg5, int32_tArray* arg6, int32_t arg7) = 0;
	virtual void alGetBufferf(int32_t arg0, int32_t arg1, FloatBuffer* arg2) = 0;
	virtual void alGetBufferf(int32_t arg0, int32_t arg1, floatArray* arg2, int32_t arg3) = 0;
	virtual void alGetBufferfv(int32_t arg0, int32_t arg1, FloatBuffer* arg2) = 0;
	virtual void alGetBufferfv(int32_t arg0, int32_t arg1, floatArray* arg2, int32_t arg3) = 0;
	virtual void alGetBufferi(int32_t arg0, int32_t arg1, IntBuffer* arg2) = 0;
	virtual void alGetBufferi(int32_t arg0, int32_t arg1, int32_tArray* arg2, int32_t arg3) = 0;
	virtual void alGetBufferiv(int32_t arg0, int32_t arg1, IntBuffer* arg2) = 0;
	virtual void alGetBufferiv(int32_t arg0, int32_t arg1, int32_tArray* arg2, int32_t arg3) = 0;
	virtual double alGetDouble(int32_t arg0) = 0;
	virtual void alGetDoublev(int32_t arg0, DoubleBuffer* arg1) = 0;
	virtual void alGetDoublev(int32_t arg0, doubleArray* arg1, int32_t arg2) = 0;
	virtual int32_t alGetEnumValue(String* arg0) = 0;
	virtual int32_t alGetError() = 0;
	virtual float alGetFloat(int32_t arg0) = 0;
	virtual void alGetFloatv(int32_t arg0, FloatBuffer* arg1) = 0;
	virtual void alGetFloatv(int32_t arg0, floatArray* arg1, int32_t arg2) = 0;
	virtual int32_t alGetInteger(int32_t arg0) = 0;
	virtual void alGetIntegerv(int32_t arg0, IntBuffer* arg1) = 0;
	virtual void alGetIntegerv(int32_t arg0, int32_tArray* arg1, int32_t arg2) = 0;
	virtual void alGetListener3f(int32_t arg0, FloatBuffer* arg1, FloatBuffer* arg2, FloatBuffer* arg3) = 0;
	virtual void alGetListener3f(int32_t arg0, floatArray* arg1, int32_t arg2, floatArray* arg3, int32_t arg4, floatArray* arg5, int32_t arg6) = 0;
	virtual void alGetListener3i(int32_t arg0, IntBuffer* arg1, IntBuffer* arg2, IntBuffer* arg3) = 0;
	virtual void alGetListener3i(int32_t arg0, int32_tArray* arg1, int32_t arg2, int32_tArray* arg3, int32_t arg4, int32_tArray* arg5, int32_t arg6) = 0;
	virtual void alGetListenerf(int32_t arg0, FloatBuffer* arg1) = 0;
	virtual void alGetListenerf(int32_t arg0, floatArray* arg1, int32_t arg2) = 0;
	virtual void alGetListenerfv(int32_t arg0, FloatBuffer* arg1) = 0;
	virtual void alGetListenerfv(int32_t arg0, floatArray* arg1, int32_t arg2) = 0;
	virtual void alGetListeneri(int32_t arg0, IntBuffer* arg1) = 0;
	virtual void alGetListeneri(int32_t arg0, int32_tArray* arg1, int32_t arg2) = 0;
	virtual void alGetListeneriv(int32_t arg0, IntBuffer* arg1) = 0;
	virtual void alGetListeneriv(int32_t arg0, int32_tArray* arg1, int32_t arg2) = 0;
	virtual void alGetSource3f(int32_t arg0, int32_t arg1, FloatBuffer* arg2, FloatBuffer* arg3, FloatBuffer* arg4) = 0;
	virtual void alGetSource3f(int32_t arg0, int32_t arg1, floatArray* arg2, int32_t arg3, floatArray* arg4, int32_t arg5, floatArray* arg6, int32_t arg7) = 0;
	virtual void alGetSource3i(int32_t arg0, int32_t arg1, IntBuffer* arg2, IntBuffer* arg3, IntBuffer* arg4) = 0;
	virtual void alGetSource3i(int32_t arg0, int32_t arg1, int32_tArray* arg2, int32_t arg3, int32_tArray* arg4, int32_t arg5, int32_tArray* arg6, int32_t arg7) = 0;
	virtual void alGetSourcef(int32_t arg0, int32_t arg1, FloatBuffer* arg2) = 0;
	virtual void alGetSourcef(int32_t arg0, int32_t arg1, floatArray* arg2, int32_t arg3) = 0;
	virtual void alGetSourcefv(int32_t arg0, int32_t arg1, FloatBuffer* arg2) = 0;
	virtual void alGetSourcefv(int32_t arg0, int32_t arg1, floatArray* arg2, int32_t arg3) = 0;
	virtual void alGetSourcei(int32_t arg0, int32_t arg1, IntBuffer* arg2) = 0;
	virtual void alGetSourcei(int32_t arg0, int32_t arg1, int32_tArray* arg2, int32_t arg3) = 0;
	virtual void alGetSourceiv(int32_t arg0, int32_t arg1, IntBuffer* arg2) = 0;
	virtual void alGetSourceiv(int32_t arg0, int32_t arg1, int32_tArray* arg2, int32_t arg3) = 0;
	virtual String* alGetString(int32_t arg0) = 0;
	virtual bool alIsBuffer(int32_t arg0) = 0;
	virtual bool alIsEnabled(int32_t arg0) = 0;
	virtual bool alIsExtensionPresent(String* arg0) = 0;
	virtual bool alIsSource(int32_t arg0) = 0;
	virtual void alListener3f(int32_t arg0, float arg1, float arg2, float arg3) = 0;
	virtual void alListener3i(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3) = 0;
	virtual void alListenerf(int32_t arg0, float arg1) = 0;
	virtual void alListenerfv(int32_t arg0, FloatBuffer* arg1) = 0;
	virtual void alListenerfv(int32_t arg0, floatArray* arg1, int32_t arg2) = 0;
	virtual void alListeneri(int32_t arg0, int32_t arg1) = 0;
	virtual void alListeneriv(int32_t arg0, IntBuffer* arg1) = 0;
	virtual void alListeneriv(int32_t arg0, int32_tArray* arg1, int32_t arg2) = 0;
	virtual void alSource3f(int32_t arg0, int32_t arg1, float arg2, float arg3, float arg4) = 0;
	virtual void alSource3i(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, int32_t arg4) = 0;
	virtual void alSourcePause(int32_t arg0) = 0;
	virtual void alSourcePausev(int32_t arg0, IntBuffer* arg1) = 0;
	virtual void alSourcePausev(int32_t arg0, int32_tArray* arg1, int32_t arg2) = 0;
	virtual void alSourcePlay(int32_t arg0) = 0;
	virtual void alSourcePlayv(int32_t arg0, IntBuffer* arg1) = 0;
	virtual void alSourcePlayv(int32_t arg0, int32_tArray* arg1, int32_t arg2) = 0;
	virtual void alSourceQueueBuffers(int32_t arg0, int32_t arg1, IntBuffer* arg2) = 0;
	virtual void alSourceQueueBuffers(int32_t arg0, int32_t arg1, int32_tArray* arg2, int32_t arg3) = 0;
	virtual void alSourceRewind(int32_t arg0) = 0;
	virtual void alSourceRewindv(int32_t arg0, IntBuffer* arg1) = 0;
	virtual void alSourceRewindv(int32_t arg0, int32_tArray* arg1, int32_t arg2) = 0;
	virtual void alSourceStop(int32_t arg0) = 0;
	virtual void alSourceStopv(int32_t arg0, IntBuffer* arg1) = 0;
	virtual void alSourceStopv(int32_t arg0, int32_tArray* arg1, int32_t arg2) = 0;
	virtual void alSourceUnqueueBuffers(int32_t arg0, int32_t arg1, IntBuffer* arg2) = 0;
	virtual void alSourceUnqueueBuffers(int32_t arg0, int32_t arg1, int32_tArray* arg2, int32_t arg3) = 0;
	virtual void alSourcef(int32_t arg0, int32_t arg1, float arg2) = 0;
	virtual void alSourcefv(int32_t arg0, int32_t arg1, FloatBuffer* arg2) = 0;
	virtual void alSourcefv(int32_t arg0, int32_t arg1, floatArray* arg2, int32_t arg3) = 0;
	virtual void alSourcei(int32_t arg0, int32_t arg1, int32_t arg2) = 0;
	virtual void alSourceiv(int32_t arg0, int32_t arg1, IntBuffer* arg2) = 0;
	virtual void alSourceiv(int32_t arg0, int32_t arg1, int32_tArray* arg2, int32_t arg3) = 0;
	virtual void alSpeedOfSound(float arg0) = 0;

	// Generated
	static ::java::lang::Class *class_();
};
