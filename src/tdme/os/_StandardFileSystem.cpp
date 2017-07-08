// Generated from /tdme/src/tdme/os/_StandardFileSystem.java
#include <tdme/os/_StandardFileSystem.h>

#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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

using std::getline;
using std::string;
using std::vector;

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

String* _StandardFileSystem::getFileName(String* path, String* fileName) /* throws(IOException) */ {
	return new String(path->getCPPWString() + L"/" + fileName->getCPPWString());
}

InputStream* _StandardFileSystem::getInputStream(String* path, String* fileName) /* throws(IOException) */
{
	return nullptr;
}

OutputStream* _StandardFileSystem::getOutputStream(String* path, String* fileName) /* throws(IOException) */
{
	return nullptr;
}

StringArray* _StandardFileSystem::list(String* path, FilenameFilter* filter) /* throws(IOException) */
{
	auto files = new _ArrayList();

	DIR *dir;
	struct dirent *dirent;
	if ((dir = opendir(StringConverter::toString(path->getCPPWString()).c_str())) == NULL) {
		return nullptr;
	}
	while ((dirent = readdir(dir)) != NULL) {
		String* file = new String(StringConverter::toWideString(dirent->d_name));
		if (filter != nullptr && filter->accept(path, file) == false) continue;
		files->add(file);
	}
	closedir(dir);

	auto _files = new StringArray(files->size());
	files->toArray(_files);
	return _files;
}

bool _StandardFileSystem::isPath(String* path) /* throws(IOException) */ {
	struct stat s;
	if (stat(StringConverter::toString(path->getCPPWString()).c_str(), &s) == 0) {
		return (s.st_mode & S_IFDIR) == S_IFDIR;
	} else {
		return false;
	}
}

int8_tArray* _StandardFileSystem::getContent(String* path, String* fileName) /* throws(IOException) */
{
	ifstream fl(StringConverter::toString(getFileName(path, fileName)->getCPPWString()).c_str());
	fl.seekg( 0, ios::end );
	size_t size = fl.tellg();
	int8_tArray* data = new int8_tArray(size);
	fl.seekg(0, ios::beg);
	fl.read((char *)data->getPointer(), size);
	fl.close();
	return data;
}

void _StandardFileSystem::setContent(String* path, String* fileName, int8_tArray* data, int32_t size) /* throws(IOException)*/ {
	ofstream fl(StringConverter::toString(getFileName(path, fileName)->getCPPWString()).c_str());
	fl.write((char *)data->getPointer(), size == -1?data->length:size);
	fl.close();
}

StringArray* _StandardFileSystem::getContentAsStringArray(String* path, String* fileName) /* throws(IOException) */
{
	ifstream ifs(StringConverter::toString(getFileName(path, fileName)->getCPPWString()).c_str());
	if(ifs.is_open() == false) return nullptr;

	vector<string> lines;
	string line;
	while (getline(ifs, line)) {
		lines.push_back(line);
	}

	StringArray* result = new StringArray(lines.size());
	int lineIdx = 0;
	for (const string& tmpLine: lines) {
		result->set(lineIdx++, new String(StringConverter::toWideString(tmpLine)));
	}

	return result;
}

void _StandardFileSystem::setContentFromStringArray(String* path, String* fileName, StringArray* stringArray) /* throws(IOException) */
{
	ofstream ofs(StringConverter::toString(getFileName(path, fileName)->getCPPWString()).c_str());
	if(ofs.is_open() == false) return;

	for (int i = 0; i < stringArray->length; i++) {
		auto line = stringArray->get(i);
		ofs << StringConverter::toString(line->getCPPWString()) << "\n";
	}

	ofs.close();
	return;
}

String* _StandardFileSystem::getCanonicalPath(String* path, String* fileName) /* throws(IOException) */ {
	// cwd
	char cwdBuffer[PATH_MAX + 1];
	char* cwdPtr = getcwd(cwdBuffer, sizeof(cwdBuffer));
	wstring cwdString = StringConverter::toWideString(cwdPtr);

	// add cwd to path string
	wstring pathString = getFileName(path, fileName)->getCPPWString();
	if (pathString.size() > 0 && pathString[0] == L'/') {
		// no op
	} else {
		pathString = cwdString + L"/" + pathString;
	}

	// realpath
	const string nonCanonicalPathString = StringConverter::toString(pathString);
	const char* nonCanonicalPath = nonCanonicalPathString.c_str();
	char realpathBuffer[PATH_MAX + 1];
	char* realPathPtr = realpath(nonCanonicalPath, realpathBuffer);
	if (realPathPtr == nullptr) {
		return nullptr;
	}
	return new String(StringConverter::toWideString(realPathPtr));
}

String* _StandardFileSystem::getCurrentWorkingPath() /* throws(IOException) */ {
	// cwd
	char cwdBuffer[PATH_MAX + 1];
	char* cwdPtr = getcwd(cwdBuffer, sizeof(cwdBuffer));
	return new String(StringConverter::toWideString(cwdPtr));
}

String* _StandardFileSystem::getPathName(String* fileName) {
	String* unixFileName = fileName->replace(L'\\', L'/');
	int32_t lastPathSeparator = unixFileName->lastIndexOf(L'/');
	if (lastPathSeparator == -1) return new String(u"."_j);
	return unixFileName->substring(0, lastPathSeparator);
}

String* _StandardFileSystem::getFileName(String* fileName) {
	String* unixFileName = fileName->replace(L'\\', L'/');
	int32_t lastPathSeparator = unixFileName->lastIndexOf(L'/');
	if (lastPathSeparator == -1) return new String(fileName);
	return unixFileName->substring(lastPathSeparator + 1, unixFileName->length());
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

