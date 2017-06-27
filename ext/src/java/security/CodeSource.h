// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/net/fwd-tdme.h>
#include <java/security/fwd-tdme.h>
#include <java/security/cert/fwd-tdme.h>
#include <java/lang/Object.h>
#include <java/io/Serializable.h>

using java::lang::Object;
using java::io::Serializable;
using java::io::ObjectInputStream;
using java::io::ObjectOutputStream;
using java::lang::String;
using java::net::SocketPermission;
using java::net::URL;
using java::security::CodeSigner;
using java::security::cert::Certificate;
using java::security::cert::CertificateFactory;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace security {
typedef ::SubArray< ::java::security::CodeSigner, ::java::lang::ObjectArray, ::java::io::SerializableArray > CodeSignerArray;

namespace cert {
typedef ::SubArray< ::java::security::cert::Certificate, ::java::lang::ObjectArray, ::java::io::SerializableArray > CertificateArray;
}  // namespace cert
}  // namespace security
}  // namespace java

using java::io::SerializableArray;
using java::lang::ObjectArray;
using java::security::CodeSignerArray;
using java::security::cert::CertificateArray;

struct default_init_tag;
class java::security::CodeSource
	: public virtual Object
	, public virtual Serializable
{

public:
	typedef Object super;

private:
	CertificateArray* certs {  };
	CertificateFactory* factory {  };
	URL* location {  };
	static constexpr int64_t serialVersionUID { 4977541819976013951LL };
	CodeSignerArray* signers {  };
	SocketPermission* sp {  };

protected:
	void ctor(URL* arg0, CertificateArray* arg1);
	void ctor(URL* arg0, CodeSignerArray* arg1);
	/*CodeSignerArray* convertCertArrayToSignerArray(CertificateArray* arg0); (private) */

public:
	bool equals(Object* arg0) override;
	CertificateArray* getCertificates();
	CodeSignerArray* getCodeSigners();
	URL* getLocation();
	int32_t hashCode() override;
	virtual bool implies(CodeSource* arg0);
	/*bool matchCerts(CodeSource* arg0, bool arg1); (private) */
	/*bool matchLocation(CodeSource* arg0); (private) */
	/*void readObject(ObjectInputStream* arg0); (private) */
	String* toString() override;
	/*void writeObject(ObjectOutputStream* arg0); (private) */

	// Generated
	CodeSource(URL* arg0, CertificateArray* arg1);
	CodeSource(URL* arg0, CodeSignerArray* arg1);
protected:
	CodeSource(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
