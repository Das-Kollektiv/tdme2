// Generated from /tdme/src/tdme/os/_StandardFileSystem.java
#include <tdme/os/_StandardFileSystem.h>

#include <iostream>
#include <fstream>

#include <java/io/BufferedReader.h>
#include <java/io/File.h>
#include <java/io/FileInputStream.h>
#include <java/io/FileNotFoundException.h>
#include <java/io/FileOutputStream.h>
#include <java/io/FilenameFilter.h>
#include <java/io/IOException.h>
#include <java/io/InputStream.h>
#include <java/io/InputStreamReader.h>
#include <java/io/Serializable.h>
#include <java/lang/ArrayStoreException.h>
#include <java/lang/CharSequence.h>
#include <java/lang/Class.h>
#include <java/lang/ClassCastException.h>
#include <java/lang/ClassLoader.h>
#include <java/lang/ClassNotFoundException.h>
#include <java/lang/Comparable.h>
#include <java/lang/NullPointerException.h>
#include <java/lang/Object.h>
#include <java/lang/StackTraceElement.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/lang/System.h>
#include <java/lang/Thread.h>
#include <java/net/URL.h>
#include <java/security/CodeSource.h>
#include <java/security/ProtectionDomain.h>
#include <java/util/Iterator.h>
#include <java/util/zip/ZipEntry.h>
#include <java/util/zip/ZipInputStream.h>
#include <tdme/utils/StringConverter.h>
#include <tdme/utils/_ArrayList.h>
#include <Array.h>
#include <SubArray.h>
#include <ObjectArray.h>

using tdme::os::_StandardFileSystem;
using java::io::BufferedReader;
using java::io::File;
using java::io::FileInputStream;
using java::io::FileNotFoundException;
using java::io::FileOutputStream;
using java::io::FilenameFilter;
using java::io::IOException;
using java::io::InputStream;
using java::io::InputStreamReader;
using java::io::Serializable;
using java::lang::ArrayStoreException;
using java::lang::CharSequence;
using java::lang::Class;
using java::lang::ClassCastException;
using java::lang::ClassLoader;
using java::lang::ClassNotFoundException;
using java::lang::Comparable;
using java::lang::NullPointerException;
using java::lang::Object;
using java::lang::StackTraceElement;
using java::lang::String;
using java::lang::StringBuilder;
using java::lang::System;
using java::lang::Thread;
using java::net::URL;
using java::security::CodeSource;
using java::security::ProtectionDomain;
using java::util::Iterator;
using java::util::zip::ZipEntry;
using java::util::zip::ZipInputStream;
using tdme::utils::StringConverter;
using tdme::utils::_ArrayList;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::CharSequence, ObjectArray > CharSequenceArray;
typedef ::SubArray< ::java::lang::Comparable, ObjectArray > ComparableArray;
typedef ::SubArray< ::java::lang::StackTraceElement, ObjectArray, ::java::io::SerializableArray > StackTraceElementArray;
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

namespace
{
template<typename F>
struct finally_
{
    finally_(F f) : f(f), moved(false) { }
    finally_(finally_ &&x) : f(x.f), moved(false) { x.moved = true; }
    ~finally_() { if(!moved) f(); }
private:
    finally_(const finally_&); finally_& operator=(const finally_&);
    F f;
    bool moved;
};

template<typename F> finally_<F> finally(F f) { return finally_<F>(f); }
}
_StandardFileSystem::_StandardFileSystem(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

_StandardFileSystem::_StandardFileSystem()
	: _StandardFileSystem(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

InputStream* _StandardFileSystem::getInputStream(String* path, String* fileName) /* throws(IOException) */
{
	path = path->replace(u'\\', u'/');
	auto currentPath = (new File(u""_j))->getCanonicalFile()->toString()->replace(u'\\', u'/');
	if (path->startsWith(currentPath)) {
		path = path->substring(currentPath->length() + 1);
	}
	auto _fileName = ::java::lang::StringBuilder().append(path)->append(File::separator)
		->append(fileName)->toString();
	try {
		return new FileInputStream(_fileName);
	} catch (IOException* ioe) {
	}
	InputStream* is;
	is = this->getClass()->getResourceAsStream(::java::lang::StringBuilder().append(path)->append(u"/"_j)
		->append(fileName)->toString());
	if (is != nullptr)
		return is;

	is = this->getClass()->getClassLoader()->getResourceAsStream(::java::lang::StringBuilder().append(path)->append(u"/"_j)
		->append(fileName)->toString());
	if (is != nullptr)
		return is;

	throw new FileNotFoundException(::java::lang::StringBuilder().append(path)->append(u"/"_j)
		->append(fileName)->toString());
}

OutputStream* _StandardFileSystem::getOutputStream(String* path, String* fileName) /* throws(IOException) */
{
	path = path->replace(u'\\', u'/');
	auto currentPath = (new File(u""_j))->getCanonicalFile()->toString()->replace(u'\\', u'/');
	if (path->startsWith(currentPath)) {
		path = path->substring(currentPath->length() + 1);
	}
	auto _fileName = ::java::lang::StringBuilder().append(path)->append(File::separator)
		->append(fileName)->toString();
	return new FileOutputStream(_fileName);
}

StringArray* _StandardFileSystem::list(String* path, FilenameFilter* filter) /* throws(IOException) */
{
	auto files = new _ArrayList();
	auto fileSystemFiles = (new File(path))->list(filter);
	if (fileSystemFiles != nullptr) {
		for (auto fileName : *fileSystemFiles) {
			files->add(fileName);
		}
	}
	try {
		path = path->replace(u'\\', u'/');
		auto stackTraceElements = Thread::currentThread()->getStackTrace();
		auto src = Class::forName((*stackTraceElements)[2]->getClassName())->getProtectionDomain()->getCodeSource();
		if (src != nullptr) {
			auto jar = src->getLocation();
			auto zip = new ZipInputStream(jar->openStream());
			while (true) {
				auto e = zip->getNextEntry();
				if (e == nullptr)
					break;

				auto name = e->getName();
				if (name->startsWith(path)) {
					auto fileName = name->substring(path->length() + 1);
					if (filter->accept(new File(path), fileName))
						files->add(fileName);

				}
			}
		}
	} catch (ClassNotFoundException* cnfe) {
	}
	auto filesNoDuplicates = new _ArrayList();
	for (auto _i = files->iterator(); _i->hasNext(); ) {
		String* file = java_cast< String* >(_i->next());
		{
			auto duplicate = false;
			for (auto _i = filesNoDuplicates->iterator(); _i->hasNext(); ) {
				String* _file = java_cast< String* >(_i->next());
				{
					if (file->equals(_file)) {
						duplicate = true;
						break;
					}
				}
			}
			if (duplicate == false)
				filesNoDuplicates->add(file);

		}
	}
	auto _files = new StringArray(filesNoDuplicates->size());
	filesNoDuplicates->toArray(_files);
	return _files;
}

int8_tArray* _StandardFileSystem::getContent(String* path, String* fileName) /* throws(IOException) */
{
	ifstream fl(StringConverter::toString(path->getCPPWString() + L"/" + fileName->getCPPWString()).c_str());
	fl.seekg( 0, ios::end );
	size_t size = fl.tellg();
	int8_tArray* data = new int8_tArray(size);
	fl.seekg(0, ios::beg);
	fl.read((char *)data->getPointer(), size);
	fl.close();
	return data;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* _StandardFileSystem::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.os._StandardFileSystem", 27);
    return c;
}

java::lang::Class* _StandardFileSystem::getClass0()
{
	return class_();
}

