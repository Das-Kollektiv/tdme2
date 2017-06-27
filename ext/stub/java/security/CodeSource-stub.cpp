// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/security/CodeSource.h>

using java::security::CodeSource;
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

extern void unimplemented_(const char16_t* name);
java::security::CodeSource::CodeSource(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::security::CodeSource::CodeSource(URL* arg0, CertificateArray* arg1)
	: CodeSource(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1);
}

java::security::CodeSource::CodeSource(URL* arg0, CodeSignerArray* arg1)
	: CodeSource(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1);
}

constexpr int64_t java::security::CodeSource::serialVersionUID;

void CodeSource::ctor(URL* arg0, CertificateArray* arg1)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void CodeSource::ctor(URL* arg0, CertificateArray* arg1)");
}

void CodeSource::ctor(URL* arg0, CodeSignerArray* arg1)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void CodeSource::ctor(URL* arg0, CodeSignerArray* arg1)");
}

/* private: CodeSignerArray* CodeSource::convertCertArrayToSignerArray(CertificateArray* arg0) */
bool CodeSource::equals(Object* arg0)
{ /* stub */
	unimplemented_(u"bool CodeSource::equals(Object* arg0)");
	return 0;
}

CertificateArray* CodeSource::getCertificates()
{ /* stub */
	unimplemented_(u"CertificateArray* CodeSource::getCertificates()");
	return 0;
}

CodeSignerArray* CodeSource::getCodeSigners()
{ /* stub */
	unimplemented_(u"CodeSignerArray* CodeSource::getCodeSigners()");
	return 0;
}

URL* CodeSource::getLocation()
{ /* stub */
return location ; /* getter */
}

int32_t CodeSource::hashCode()
{ /* stub */
	unimplemented_(u"int32_t CodeSource::hashCode()");
	return 0;
}

bool CodeSource::implies(CodeSource* arg0)
{ /* stub */
	unimplemented_(u"bool CodeSource::implies(CodeSource* arg0)");
	return 0;
}

/* private: bool CodeSource::matchCerts(CodeSource* arg0, bool arg1) */
/* private: bool CodeSource::matchLocation(CodeSource* arg0) */
/* private: void CodeSource::readObject(ObjectInputStream* arg0) */
String* CodeSource::toString()
{ /* stub */
	unimplemented_(u"String* CodeSource::toString()");
	return 0;
}

/* private: void CodeSource::writeObject(ObjectOutputStream* arg0) */
extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* CodeSource::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.security.CodeSource", 24);
    return c;
}

java::lang::Class* CodeSource::getClass0()
{
	return class_();
}

