// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/util/Properties.h>

#include <java/lang/ClassCastException.h>

#include <ObjectArray.h>
#include <SubArray.h>
#include <java/io/Serializable.h>
#include <java/lang/CharSequence.h>
#include <java/lang/Comparable.h>
#include <java/lang/String.h>

#include <tdme/utils/_HashMap.h>
#include <tdme/utils/_HashMap_KeysIterator.h>

using java::util::Properties;
using java::lang::String;
using java::lang::StringArray;
using java::lang::ClassCastException;

using tdme::utils::_HashMap;
using tdme::utils::_HashMap_KeysIterator;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::CharSequence, ObjectArray > CharSequenceArray;
typedef ::SubArray< ::java::lang::Comparable, ObjectArray > ComparableArray;
typedef ::SubArray< ::java::lang::String, ObjectArray, ::java::io::SerializableArray, ComparableArray, CharSequenceArray > StringArray;
}  // namespace lang
}  // namespace java

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    if (!t) throw new ::java::lang::ClassCastException();
    return t;
}

extern void unimplemented_(const char16_t* name);
java::util::Properties::Properties(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::util::Properties::Properties()
	: Properties(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

java::util::Properties::Properties(Properties* arg0)
	: Properties(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

char16_tArray* java::util::Properties::hexDigit;
constexpr int64_t java::util::Properties::serialVersionUID;

void Properties::ctor()
{ /* stub */
	properties = new _HashMap();
}

void Properties::ctor(Properties* arg0)
{ /* stub */
	properties = java_cast< _HashMap* >(arg0->properties->clone());
}

/* private: void Properties::enumerate(Hashtable* arg0) */
/* private: void Properties::enumerateStringProperties(Hashtable* arg0) */
String* Properties::getProperty(String* arg0)
{
	return java_cast< String* >(properties->get(java_cast< Object* >(arg0)));
}

String* Properties::getProperty(String* arg0, String* arg1)
{
	String* tmp = nullptr;
	return (tmp = java_cast< String* >(properties->get(java_cast< Object* >(arg0)))) != nullptr?tmp:arg1;
}

void Properties::list(PrintStream* arg0)
{ /* stub */
	unimplemented_(u"void Properties::list(PrintStream* arg0)");
}

void Properties::list(PrintWriter* arg0)
{ /* stub */
	unimplemented_(u"void Properties::list(PrintWriter* arg0)");
}

void Properties::load(Reader* arg0)
{ /* stub */
	unimplemented_(u"void Properties::load(Reader* arg0)");
}

void Properties::load(InputStream* arg0)
{ /* stub */
	unimplemented_(u"void Properties::load(InputStream* arg0)");
}

void Properties::load(StringArray* arg0)
{
	if (arg0 == nullptr) return;
	for (int i = 0; i < arg0->length; i++) {
		String* line = arg0->get(i)->trim();
		if (line->length() == 0 || line->startsWith(u"#"_j)) continue;
		int separatorPos = line->indexOf('=');
		if (separatorPos == -1) continue;
		String* key = line->substring(0, separatorPos);
		String* value = line->substring(0, separatorPos);
		properties->put(key, value);
	}
}

/* private: void Properties::load0(Properties_LineReader* arg0) */
/* private: String* Properties::loadConvert(char16_tArray* arg0, int32_t arg1, int32_t arg2, char16_tArray* arg3) */
void Properties::loadFromXML(InputStream* arg0)
{ /* stub */
	unimplemented_(u"void Properties::loadFromXML(InputStream* arg0)");
}

Enumeration* Properties::propertyNames()
{ /* stub */
	unimplemented_(u"Enumeration* Properties::propertyNames()");
	return 0;
}

void Properties::save(OutputStream* arg0, String* arg1)
{ /* stub */
	unimplemented_(u"void Properties::save(OutputStream* arg0, String* arg1)");
}

/* private: String* Properties::saveConvert(String* arg0, bool arg1, bool arg2) */
Object* Properties::setProperty(String* arg0, String* arg1)
{ /* stub */
	unimplemented_(u"Object* Properties::setProperty(String* arg0, String* arg1)");
	return 0;
}

void Properties::store(Writer* arg0, String* arg1)
{ /* stub */
	unimplemented_(u"void Properties::store(Writer* arg0, String* arg1)");
}

void Properties::store(OutputStream* arg0, String* arg1)
{ /* stub */
	unimplemented_(u"void Properties::store(OutputStream* arg0, String* arg1)");
}

StringArray* Properties::storeToStringArray() {
	StringArray* result = new StringArray(properties->size());
	int32_t idx = 0;
	for (auto _i = properties->getKeysIterator()->iterator(); _i->hasNext(); ) {
		String* key = java_cast< String* >(_i->next());
		String* value = java_cast< String* >(properties->get(key));
		result->set(idx++, new String(key->getCPPWString() + L"=" + key->getCPPWString()));
	}
	return result;
}

/* private: void Properties::store0(BufferedWriter* arg0, String* arg1, bool arg2) */
void Properties::storeToXML(OutputStream* arg0, String* arg1)
{ /* stub */
	unimplemented_(u"void Properties::storeToXML(OutputStream* arg0, String* arg1)");
}

void Properties::storeToXML(OutputStream* arg0, String* arg1, String* arg2)
{ /* stub */
	unimplemented_(u"void Properties::storeToXML(OutputStream* arg0, String* arg1, String* arg2)");
}

Set* Properties::stringPropertyNames()
{ /* stub */
	unimplemented_(u"Set* Properties::stringPropertyNames()");
	return 0;
}

/* private: char16_t Properties::toHex(int32_t arg0) */
/* private: void Properties::writeComments(BufferedWriter* arg0, String* arg1) */
extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Properties::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.util.Properties", 20);
    return c;
}

java::lang::Class* Properties::getClass0()
{
	return class_();
}

