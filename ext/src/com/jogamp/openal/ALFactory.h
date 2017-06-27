// Generated from /tdme/lib/joal.jar

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/openal/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using com::jogamp::openal::AL;
using com::jogamp::openal::ALC;
using com::jogamp::openal::ALExt;


struct default_init_tag;
class com::jogamp::openal::ALFactory
	: public virtual Object
{

public:
	typedef Object super;
	static bool DEBUG;
	static bool PREFER_SYSTEM_OPENAL;

private:
	static AL* al;
	static ALC* alc;
	static ALExt* alext;
	static bool initialized;

	/*void ctor(); (private) */

public:
	static AL* getAL();
	static ALC* getALC();
	static ALExt* getALExt();
	static bool getPreferSystemOpenAL();
	/*static void initialize(); (private) */

	// Generated
	ALFactory();
protected:
	ALFactory(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
