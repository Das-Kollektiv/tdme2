// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/lang/Object.h>
#include <java/io/Serializable.h>

using java::lang::Object;
using java::io::Serializable;
using java::io::ObjectOutputStream;
using java::io::PrintStream;
using java::io::PrintWriter;
using java::lang::StackTraceElement;
using java::lang::String;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::StackTraceElement, ObjectArray, ::java::io::SerializableArray > StackTraceElementArray;
}  // namespace lang
}  // namespace java

using java::io::SerializableArray;
using java::lang::ObjectArray;
using java::lang::StackTraceElementArray;

struct default_init_tag;
class java::lang::Throwable
	: public virtual Object
	, public virtual Serializable
{

public:
	typedef Object super;

private:
	Object* backtrace {  };
	Throwable* cause {  };
	String* detailMessage {  };
	static constexpr int64_t serialVersionUID { -3042686055658047285LL };
	StackTraceElementArray* stackTrace {  };

protected:
	void ctor();
	void ctor(String* arg0);
	void ctor(Throwable* arg0);
	void ctor(String* arg0, Throwable* arg1);

public:
	virtual Throwable* fillInStackTrace();
	virtual Throwable* getCause();
	virtual String* getLocalizedMessage();
	virtual String* getMessage();
	/*StackTraceElementArray* getOurStackTrace(); (private) */
	virtual StackTraceElementArray* getStackTrace();

public: /* package */
	virtual int32_t getStackTraceDepth();
	virtual StackTraceElement* getStackTraceElement(int32_t arg0);

public:
	virtual Throwable* initCause(Throwable* arg0);
	virtual void printStackTrace();
	virtual void printStackTrace(PrintStream* arg0);
	virtual void printStackTrace(PrintWriter* arg0);
	/*void printStackTraceAsCause(PrintStream* arg0, StackTraceElementArray* arg1); (private) */
	/*void printStackTraceAsCause(PrintWriter* arg0, StackTraceElementArray* arg1); (private) */
	virtual void setStackTrace(StackTraceElementArray* arg0);
	String* toString() override;
	/*void writeObject(ObjectOutputStream* arg0); (private) */

	// Generated
	Throwable();
	Throwable(String* arg0);
	Throwable(Throwable* arg0);
	Throwable(String* arg0, Throwable* arg1);
protected:
	Throwable(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
