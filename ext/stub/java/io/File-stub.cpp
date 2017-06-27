// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/io/File.h>

using java::io::File;
template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::Comparable, ObjectArray > ComparableArray;
}  // namespace lang

namespace io {
typedef ::SubArray< ::java::io::File, ::java::lang::ObjectArray, SerializableArray, ::java::lang::ComparableArray > FileArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::CharSequence, ObjectArray > CharSequenceArray;
typedef ::SubArray< ::java::lang::String, ObjectArray, ::java::io::SerializableArray, ComparableArray, CharSequenceArray > StringArray;
}  // namespace lang
}  // namespace java

extern void unimplemented_(const char16_t* name);
java::io::File::File(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::io::File::File(String* arg0)
	: File(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

java::io::File::File(URI* arg0)
	: File(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

java::io::File::File(String* arg0, String* arg1)
	: File(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1);
}

java::io::File::File(File* arg0, String* arg1)
	: File(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1);
}

bool java::io::File::$assertionsDisabled;
FileSystem* java::io::File::fs;
String* java::io::File::pathSeparator;
char16_t java::io::File::pathSeparatorChar;
String* java::io::File::separator;
char16_t java::io::File::separatorChar;
constexpr int64_t java::io::File::serialVersionUID;

void File::ctor(String* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void File::ctor(String* arg0)");
}

void File::ctor(URI* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void File::ctor(URI* arg0)");
}

/* private: void File::ctor(String* arg0, int32_t arg1) */
/* private: void File::ctor(String* arg0, File* arg1) */
void File::ctor(String* arg0, String* arg1)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void File::ctor(String* arg0, String* arg1)");
}

void File::ctor(File* arg0, String* arg1)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void File::ctor(File* arg0, String* arg1)");
}

bool File::canExecute()
{ /* stub */
	unimplemented_(u"bool File::canExecute()");
	return 0;
}

bool File::canRead()
{ /* stub */
	unimplemented_(u"bool File::canRead()");
	return 0;
}

bool File::canWrite()
{ /* stub */
	unimplemented_(u"bool File::canWrite()");
	return 0;
}

/* private: bool File::checkAndCreate(String* arg0, SecurityManager* arg1, bool arg2) */
int32_t File::compareTo(File* arg0)
{ /* stub */
	unimplemented_(u"int32_t File::compareTo(File* arg0)");
	return 0;
}

int32_t File::compareTo(Object* arg0)
{ 
	return compareTo(dynamic_cast< File* >(arg0));
}

bool File::createNewFile()
{ /* stub */
	unimplemented_(u"bool File::createNewFile()");
	return 0;
}

File* File::createTempFile(String* arg0, String* arg1)
{ /* stub */
	clinit();
	unimplemented_(u"File* File::createTempFile(String* arg0, String* arg1)");
	return 0;
}

File* File::createTempFile(String* arg0, String* arg1, File* arg2)
{ /* stub */
	clinit();
	unimplemented_(u"File* File::createTempFile(String* arg0, String* arg1, File* arg2)");
	return 0;
}

/* private: File* File::createTempFile0(String* arg0, String* arg1, File* arg2, bool arg3) */
bool File::delete_()
{ /* stub */
	unimplemented_(u"bool File::delete_()");
	return 0;
}

void File::deleteOnExit()
{ /* stub */
	unimplemented_(u"void File::deleteOnExit()");
}

bool File::equals(Object* arg0)
{ /* stub */
	unimplemented_(u"bool File::equals(Object* arg0)");
	return 0;
}

bool File::exists()
{ /* stub */
	unimplemented_(u"bool File::exists()");
	return 0;
}

/* private: File* File::generateFile(String* arg0, String* arg1, File* arg2) */
File* File::getAbsoluteFile()
{ /* stub */
	unimplemented_(u"File* File::getAbsoluteFile()");
	return 0;
}

String* File::getAbsolutePath()
{ /* stub */
	unimplemented_(u"String* File::getAbsolutePath()");
	return 0;
}

File* File::getCanonicalFile()
{ /* stub */
	unimplemented_(u"File* File::getCanonicalFile()");
	return 0;
}

String* File::getCanonicalPath()
{ /* stub */
	unimplemented_(u"String* File::getCanonicalPath()");
	return 0;
}

int64_t File::getFreeSpace()
{ /* stub */
	unimplemented_(u"int64_t File::getFreeSpace()");
	return 0;
}

String* File::getName()
{ /* stub */
	unimplemented_(u"String* File::getName()");
	return 0;
}

String* File::getParent()
{ /* stub */
	unimplemented_(u"String* File::getParent()");
	return 0;
}

File* File::getParentFile()
{ /* stub */
	unimplemented_(u"File* File::getParentFile()");
	return 0;
}

String* File::getPath()
{ /* stub */
return path ; /* getter */
}

int32_t File::getPrefixLength()
{ /* stub */
return prefixLength ; /* getter */
}

int64_t File::getTotalSpace()
{ /* stub */
	unimplemented_(u"int64_t File::getTotalSpace()");
	return 0;
}

int64_t File::getUsableSpace()
{ /* stub */
	unimplemented_(u"int64_t File::getUsableSpace()");
	return 0;
}

int32_t File::hashCode()
{ /* stub */
	unimplemented_(u"int32_t File::hashCode()");
	return 0;
}

bool File::isAbsolute()
{ /* stub */
	unimplemented_(u"bool File::isAbsolute()");
	return 0;
}

bool File::isDirectory()
{ /* stub */
	unimplemented_(u"bool File::isDirectory()");
	return 0;
}

bool File::isFile()
{ /* stub */
	unimplemented_(u"bool File::isFile()");
	return 0;
}

bool File::isHidden()
{ /* stub */
	unimplemented_(u"bool File::isHidden()");
	return 0;
}

int64_t File::lastModified()
{ /* stub */
	unimplemented_(u"int64_t File::lastModified()");
	return 0;
}

int64_t File::length()
{ /* stub */
	unimplemented_(u"int64_t File::length()");
	return 0;
}

StringArray* File::list()
{ /* stub */
	unimplemented_(u"StringArray* File::list()");
	return 0;
}

StringArray* File::list(FilenameFilter* arg0)
{ /* stub */
	unimplemented_(u"StringArray* File::list(FilenameFilter* arg0)");
	return 0;
}

FileArray* File::listFiles()
{ /* stub */
	unimplemented_(u"FileArray* File::listFiles()");
	return 0;
}

FileArray* File::listFiles(FilenameFilter* arg0)
{ /* stub */
	unimplemented_(u"FileArray* File::listFiles(FilenameFilter* arg0)");
	return 0;
}

FileArray* File::listFiles(FileFilter* arg0)
{ /* stub */
	unimplemented_(u"FileArray* File::listFiles(FileFilter* arg0)");
	return 0;
}

FileArray* File::listRoots()
{ /* stub */
	clinit();
	unimplemented_(u"FileArray* File::listRoots()");
	return 0;
}

bool File::mkdir()
{ /* stub */
	unimplemented_(u"bool File::mkdir()");
	return 0;
}

bool File::mkdirs()
{ /* stub */
	unimplemented_(u"bool File::mkdirs()");
	return 0;
}

/* private: void File::readObject(ObjectInputStream* arg0) */
bool File::renameTo(File* arg0)
{ /* stub */
	unimplemented_(u"bool File::renameTo(File* arg0)");
	return 0;
}

bool File::setExecutable(bool arg0)
{ /* stub */
	unimplemented_(u"bool File::setExecutable(bool arg0)");
	return 0;
}

bool File::setExecutable(bool arg0, bool arg1)
{ /* stub */
	unimplemented_(u"bool File::setExecutable(bool arg0, bool arg1)");
	return 0;
}

bool File::setLastModified(int64_t arg0)
{ /* stub */
	unimplemented_(u"bool File::setLastModified(int64_t arg0)");
	return 0;
}

bool File::setReadOnly()
{ /* stub */
	unimplemented_(u"bool File::setReadOnly()");
	return 0;
}

bool File::setReadable(bool arg0)
{ /* stub */
	unimplemented_(u"bool File::setReadable(bool arg0)");
	return 0;
}

bool File::setReadable(bool arg0, bool arg1)
{ /* stub */
	unimplemented_(u"bool File::setReadable(bool arg0, bool arg1)");
	return 0;
}

bool File::setWritable(bool arg0)
{ /* stub */
	unimplemented_(u"bool File::setWritable(bool arg0)");
	return 0;
}

bool File::setWritable(bool arg0, bool arg1)
{ /* stub */
	unimplemented_(u"bool File::setWritable(bool arg0, bool arg1)");
	return 0;
}

/* private: String* File::slashify(String* arg0, bool arg1) */
String* File::toString()
{ /* stub */
	unimplemented_(u"String* File::toString()");
	return 0;
}

URI* File::toURI()
{ /* stub */
	unimplemented_(u"URI* File::toURI()");
	return 0;
}

URL* File::toURL()
{ /* stub */
	unimplemented_(u"URL* File::toURL()");
	return 0;
}

/* private: void File::writeObject(ObjectOutputStream* arg0) */
extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* File::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.io.File", 12);
    return c;
}

java::lang::Class* File::getClass0()
{
	return class_();
}

