// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/net/URL.h>

using java::net::URL;
template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
namespace reflect {
typedef ::SubArray< ::java::lang::reflect::GenericDeclaration, ::java::lang::ObjectArray > GenericDeclarationArray;
typedef ::SubArray< ::java::lang::reflect::Type, ::java::lang::ObjectArray > TypeArray;
typedef ::SubArray< ::java::lang::reflect::AnnotatedElement, ::java::lang::ObjectArray > AnnotatedElementArray;
}  // namespace reflect
typedef ::SubArray< ::java::lang::Class, ObjectArray, ::java::io::SerializableArray, ::java::lang::reflect::GenericDeclarationArray, ::java::lang::reflect::TypeArray, ::java::lang::reflect::AnnotatedElementArray > ClassArray;
}  // namespace lang
}  // namespace java

extern void unimplemented_(const char16_t* name);
java::net::URL::URL(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::net::URL::URL(String* arg0)
	: URL(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

java::net::URL::URL(URL* arg0, String* arg1)
	: URL(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1);
}

java::net::URL::URL(String* arg0, String* arg1, String* arg2)
	: URL(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1, arg2);
}

java::net::URL::URL(URL* arg0, String* arg1, URLStreamHandler* arg2)
	: URL(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1, arg2);
}

java::net::URL::URL(String* arg0, String* arg1, int32_t arg2, String* arg3)
	: URL(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1, arg2, arg3);
}

java::net::URL::URL(String* arg0, String* arg1, int32_t arg2, String* arg3, URLStreamHandler* arg4)
	: URL(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1, arg2, arg3, arg4);
}

String* java::net::URL::ENABLE_GOPHER_PROP;
String* java::net::URL::GOPHER;
String* java::net::URL::JDK_PACKAGE_PREFIX;
bool java::net::URL::enableGopher;
URLStreamHandlerFactory* java::net::URL::factory;
Hashtable* java::net::URL::handlers;
String* java::net::URL::protocolPathProp;
constexpr int64_t java::net::URL::serialVersionUID;
Object* java::net::URL::streamHandlerLock;

void URL::ctor(String* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void URL::ctor(String* arg0)");
}

void URL::ctor(URL* arg0, String* arg1)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void URL::ctor(URL* arg0, String* arg1)");
}

void URL::ctor(String* arg0, String* arg1, String* arg2)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void URL::ctor(String* arg0, String* arg1, String* arg2)");
}

void URL::ctor(URL* arg0, String* arg1, URLStreamHandler* arg2)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void URL::ctor(URL* arg0, String* arg1, URLStreamHandler* arg2)");
}

void URL::ctor(String* arg0, String* arg1, int32_t arg2, String* arg3)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void URL::ctor(String* arg0, String* arg1, int32_t arg2, String* arg3)");
}

void URL::ctor(String* arg0, String* arg1, int32_t arg2, String* arg3, URLStreamHandler* arg4)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void URL::ctor(String* arg0, String* arg1, int32_t arg2, String* arg3, URLStreamHandler* arg4)");
}

/* private: void URL::checkSpecifyHandler(SecurityManager* arg0) */
bool URL::equals(Object* arg0)
{ /* stub */
	unimplemented_(u"bool URL::equals(Object* arg0)");
	return 0;
}

String* URL::getAuthority()
{ /* stub */
return authority ; /* getter */
}

Object* URL::getContent()
{ /* stub */
	unimplemented_(u"Object* URL::getContent()");
	return 0;
}

Object* URL::getContent(ClassArray* arg0)
{ /* stub */
	unimplemented_(u"Object* URL::getContent(ClassArray* arg0)");
	return 0;
}

int32_t URL::getDefaultPort()
{ /* stub */
	unimplemented_(u"int32_t URL::getDefaultPort()");
	return 0;
}

String* URL::getFile()
{ /* stub */
return file ; /* getter */
}

String* URL::getHost()
{ /* stub */
return host ; /* getter */
}

String* URL::getPath()
{ /* stub */
return path ; /* getter */
}

int32_t URL::getPort()
{ /* stub */
return port ; /* getter */
}

String* URL::getProtocol()
{ /* stub */
return protocol ; /* getter */
}

String* URL::getQuery()
{ /* stub */
return query ; /* getter */
}

String* URL::getRef()
{ /* stub */
return ref ; /* getter */
}

URLStreamHandler* URL::getURLStreamHandler(String* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"URLStreamHandler* URL::getURLStreamHandler(String* arg0)");
	return 0;
}

String* URL::getUserInfo()
{ /* stub */
return userInfo ; /* getter */
}

int32_t URL::hashCode()
{ /* stub */
	unimplemented_(u"int32_t URL::hashCode()");
	return 0;
}

/* private: bool URL::isValidProtocol(String* arg0) */
URLConnection* URL::openConnection()
{ /* stub */
	unimplemented_(u"URLConnection* URL::openConnection()");
	return 0;
}

URLConnection* URL::openConnection(Proxy* arg0)
{ /* stub */
	unimplemented_(u"URLConnection* URL::openConnection(Proxy* arg0)");
	return 0;
}

InputStream* URL::openStream()
{ /* stub */
	unimplemented_(u"InputStream* URL::openStream()");
	return 0;
}

/* private: void URL::readObject(ObjectInputStream* arg0) */
bool URL::sameFile(URL* arg0)
{ /* stub */
	unimplemented_(u"bool URL::sameFile(URL* arg0)");
	return 0;
}

void URL::set(String* arg0, String* arg1, int32_t arg2, String* arg3, String* arg4)
{ /* stub */
	unimplemented_(u"void URL::set(String* arg0, String* arg1, int32_t arg2, String* arg3, String* arg4)");
}

void URL::set(String* arg0, String* arg1, int32_t arg2, String* arg3, String* arg4, String* arg5, String* arg6, String* arg7)
{ /* stub */
	unimplemented_(u"void URL::set(String* arg0, String* arg1, int32_t arg2, String* arg3, String* arg4, String* arg5, String* arg6, String* arg7)");
}

void URL::setURLStreamHandlerFactory(URLStreamHandlerFactory* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"void URL::setURLStreamHandlerFactory(URLStreamHandlerFactory* arg0)");
}

String* URL::toExternalForm()
{ /* stub */
	unimplemented_(u"String* URL::toExternalForm()");
	return 0;
}

String* URL::toString()
{ /* stub */
	unimplemented_(u"String* URL::toString()");
	return 0;
}

URI* URL::toURI()
{ /* stub */
	unimplemented_(u"URI* URL::toURI()");
	return 0;
}

/* private: void URL::writeObject(ObjectOutputStream* arg0) */
extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* URL::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.net.URL", 12);
    return c;
}

java::lang::Class* URL::getClass0()
{
	return class_();
}

