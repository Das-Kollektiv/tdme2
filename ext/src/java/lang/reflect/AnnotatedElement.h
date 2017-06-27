// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/lang/annotation/fwd-tdme.h>
#include <java/lang/reflect/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::Class;
using java::lang::annotation::Annotation;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace lang {
namespace annotation {
typedef ::SubArray< ::java::lang::annotation::Annotation, ::java::lang::ObjectArray > AnnotationArray;
}  // namespace annotation
}  // namespace lang
}  // namespace java

using java::lang::ObjectArray;
using java::lang::annotation::AnnotationArray;

struct java::lang::reflect::AnnotatedElement
	: public virtual Object
{

	virtual Annotation* getAnnotation(Class* arg0) = 0;
	virtual AnnotationArray* getAnnotations() = 0;
	virtual AnnotationArray* getDeclaredAnnotations() = 0;
	virtual bool isAnnotationPresent(Class* arg0) = 0;

	// Generated
	static ::java::lang::Class *class_();
};
