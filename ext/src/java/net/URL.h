// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/lang/reflect/fwd-tdme.h>
#include <java/net/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/lang/Object.h>
#include <java/io/Serializable.h>

using java::lang::Object;
using java::io::Serializable;
using java::io::InputStream;
using java::io::ObjectInputStream;
using java::io::ObjectOutputStream;
using java::lang::Class;
using java::lang::SecurityManager;
using java::lang::String;
using java::lang::reflect::AnnotatedElement;
using java::lang::reflect::GenericDeclaration;
using java::lang::reflect::Type;
using java::net::InetAddress;
using java::net::Proxy;
using java::net::URI;
using java::net::URLConnection;
using java::net::URLStreamHandler;
using java::net::URLStreamHandlerFactory;
using java::util::Hashtable;

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

using java::io::SerializableArray;
using java::lang::ClassArray;
using java::lang::ObjectArray;
using java::lang::reflect::AnnotatedElementArray;
using java::lang::reflect::GenericDeclarationArray;
using java::lang::reflect::TypeArray;

struct default_init_tag;
class java::net::URL final
	: public virtual Object
	, public Serializable
{

public:
	typedef Object super;

private:
	static String* ENABLE_GOPHER_PROP;
	static String* GOPHER;
	static String* JDK_PACKAGE_PREFIX;
	String* authority {  };
	static bool enableGopher;

public: /* package */
	static URLStreamHandlerFactory* factory;

private:
	String* file {  };

public: /* package */
	URLStreamHandler* handler {  };
	static Hashtable* handlers;

private:
	int32_t hashCode_ {  };
	String* host {  };

public: /* package */
	InetAddress* hostAddress {  };

private:
	String* path {  };
	int32_t port {  };
	String* protocol {  };
	static String* protocolPathProp;
	String* query {  };
	String* ref {  };

public: /* package */
	static constexpr int64_t serialVersionUID { -7627629688361524110LL };

private:
	static Object* streamHandlerLock;
	String* userInfo {  };

protected:
	void ctor(String* arg0);
	void ctor(URL* arg0, String* arg1);
	void ctor(String* arg0, String* arg1, String* arg2);
	void ctor(URL* arg0, String* arg1, URLStreamHandler* arg2);
	void ctor(String* arg0, String* arg1, int32_t arg2, String* arg3);
	void ctor(String* arg0, String* arg1, int32_t arg2, String* arg3, URLStreamHandler* arg4);
	/*void checkSpecifyHandler(SecurityManager* arg0); (private) */

public:
	bool equals(Object* arg0) override;
	String* getAuthority();
	Object* getContent();
	Object* getContent(ClassArray* arg0);
	int32_t getDefaultPort();
	String* getFile();
	String* getHost();
	String* getPath();
	int32_t getPort();
	String* getProtocol();
	String* getQuery();
	String* getRef();

public: /* package */
	static URLStreamHandler* getURLStreamHandler(String* arg0);

public:
	String* getUserInfo();
	int32_t hashCode() override;
	/*bool isValidProtocol(String* arg0); (private) */
	URLConnection* openConnection();
	URLConnection* openConnection(Proxy* arg0);
	InputStream* openStream();
	/*void readObject(ObjectInputStream* arg0); (private) */
	bool sameFile(URL* arg0);

public: /* protected */
	void set(String* arg0, String* arg1, int32_t arg2, String* arg3, String* arg4);
	void set(String* arg0, String* arg1, int32_t arg2, String* arg3, String* arg4, String* arg5, String* arg6, String* arg7);

public:
	static void setURLStreamHandlerFactory(URLStreamHandlerFactory* arg0);
	String* toExternalForm();
	String* toString() override;
	URI* toURI();
	/*void writeObject(ObjectOutputStream* arg0); (private) */

	// Generated
	URL(String* arg0);
	URL(URL* arg0, String* arg1);
	URL(String* arg0, String* arg1, String* arg2);
	URL(URL* arg0, String* arg1, URLStreamHandler* arg2);
	URL(String* arg0, String* arg1, int32_t arg2, String* arg3);
	URL(String* arg0, String* arg1, int32_t arg2, String* arg3, URLStreamHandler* arg4);
protected:
	URL(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
