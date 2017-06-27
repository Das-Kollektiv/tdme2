// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::Class;
using java::lang::String;


struct default_init_tag;
class java::lang::ClassLoader_NativeLibrary
	: public virtual Object
{

public:
	typedef Object super;

private:
	Class* fromClass {  };

public: /* package */
	int64_t handle {  };

private:
	int32_t jniVersion {  };

public: /* package */
	String* name {  };

protected:
	void ctor(Class* arg0, String* arg1);

public: /* protected */
	void finalize() override;

public: /* package */
	virtual int64_t find(String* arg0);
	static Class* getFromClass();
	virtual void load(String* arg0);
	virtual void unload();

	// Generated

public:
	ClassLoader_NativeLibrary(Class* arg0, String* arg1);
protected:
	ClassLoader_NativeLibrary(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
