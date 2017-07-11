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
#include <java/util/StringTokenizer.h>
#include <java/util/zip/ZipEntry.h>
#include <java/util/zip/ZipInputStream.h>
#include <tdme/utils/StringConverter.h>
#include <tdme/utils/_ArrayList.h>
#include <tdme/utils/_Console.h>
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
using java::util::StringTokenizer;
using java::util::zip::ZipEntry;
using java::util::zip::ZipInputStream;
using tdme::utils::StringConverter;
using tdme::utils::_Console;
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

String* _StandardFileSystem::getFileName(String* pathName, String* fileName) /* throws(IOException) */ {
	return new String(pathName->getCPPWString() + L"/" + fileName->getCPPWString());
}

InputStream* _StandardFileSystem::getInputStream(String* pathName, String* fileName) /* throws(IOException) */
{
	return nullptr;
}

OutputStream* _StandardFileSystem::getOutputStream(String* pathName, String* fileName) /* throws(IOException) */
{
	return nullptr;
}

StringArray* _StandardFileSystem::list(String* pathName, FilenameFilter* filter) /* throws(IOException) */
{
	auto files = new _ArrayList();

	DIR *dir;
	struct dirent *dirent;
	if ((dir = opendir(StringConverter::toString(pathName->getCPPWString()).c_str())) == NULL) {
		return nullptr;
	}
	while ((dirent = readdir(dir)) != NULL) {
		String* file = new String(StringConverter::toWideString(dirent->d_name));
		if (filter != nullptr && filter->accept(pathName, file) == false) continue;
		files->add(file);
	}
	closedir(dir);

	auto _files = new StringArray(files->size());
	files->toArray(_files);
	return _files;
}

bool _StandardFileSystem::isPath(String* pathName) /* throws(IOException) */ {
	struct stat s;
	if (stat(StringConverter::toString(pathName->getCPPWString()).c_str(), &s) == 0) {
		return (s.st_mode & S_IFDIR) == S_IFDIR;
	} else {
		return false;
	}
}

bool _StandardFileSystem::fileExists(String* fileName) /* throws(IOException) */ {
	struct stat s;
	return stat(StringConverter::toString(fileName->getCPPWString()).c_str(), &s) == 0;
}

String* _StandardFileSystem::getContentAsString(String* pathName, String* fileName) /* throws(IOException) */ {
	return new String(getContent(pathName, fileName));
}

void _StandardFileSystem::setContentFromString(String* pathName, String* fileName, String* string) /* throws(IOException) */ {
	ofstream ofs(StringConverter::toString(getFileName(pathName, fileName)->getCPPWString()).c_str());
	if(ofs.is_open() == false) return;

	ofs << StringConverter::toString(string->getCPPWString());

	ofs.close();
	return;
}

int8_tArray* _StandardFileSystem::getContent(String* pathName, String* fileName) /* throws(IOException) */
{
	ifstream fl(StringConverter::toString(getFileName(pathName, fileName)->getCPPWString()).c_str());
	fl.seekg( 0, ios::end );
	size_t size = fl.tellg();
	int8_tArray* data = new int8_tArray(size);
	fl.seekg(0, ios::beg);
	fl.read((char *)data->getPointer(), size);
	fl.close();
	return data;
}

void _StandardFileSystem::setContent(String* pathName, String* fileName, int8_tArray* data, int32_t size) /* throws(IOException)*/ {
	ofstream fl(StringConverter::toString(getFileName(pathName, fileName)->getCPPWString()).c_str());
	fl.write((char *)data->getPointer(), size == -1?data->length:size);
	fl.close();
}

StringArray* _StandardFileSystem::getContentAsStringArray(String* pathName, String* fileName) /* throws(IOException) */
{
	ifstream ifs(StringConverter::toString(getFileName(pathName, fileName)->getCPPWString()).c_str());
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

void _StandardFileSystem::setContentFromStringArray(String* pathName, String* fileName, StringArray* stringArray) /* throws(IOException) */
{
	ofstream ofs(StringConverter::toString(getFileName(pathName, fileName)->getCPPWString()).c_str());
	if(ofs.is_open() == false) return;

	for (int i = 0; i < stringArray->length; i++) {
		auto line = stringArray->get(i);
		ofs << StringConverter::toString(line->getCPPWString()) << "\n";
	}

	ofs.close();
	return;
}

String* _StandardFileSystem::getCanonicalPath(String* pathName, String* fileName) /* throws(IOException) */ {
	String* unixPathName = pathName->replace(L'\\', L'/');
	String* unixFileName = fileName->replace(L'\\', L'/');

	auto pathString = getFileName(unixPathName, unixFileName);

	// separate into path components
	auto pathComponents = new _ArrayList();
	auto t = new StringTokenizer(pathString, u"/"_j);
	while (t->hasMoreTokens()) {
		pathComponents->add(t->nextToken());
	}

	// process path components
	for (int i = 0; i < pathComponents->size(); i++) {
		auto pathComponent = pathComponents->get(i);
		if (pathComponent->equals(u"."_j) == true) {
			pathComponents->set(i, nullptr);
		} else
		if (pathComponent->equals(u".."_j) == true) {
			pathComponents->set(i, nullptr);
			int j = i - 1;
			for (int pathComponentReplaced = 0; pathComponentReplaced < 1 && j >= 0; ) {
				if (pathComponents->get(j) != nullptr) {
					pathComponents->set(j, nullptr);
					pathComponentReplaced++;
				}
				j--;
			}
		}
	}

	// process path components
	wstring canonicalPath = L"";
	bool slash = pathString->startsWith(u"/"_j);
	for (int i = 0; i < pathComponents->size(); i++) {
		auto pathComponent = java_cast<String*>(pathComponents->get(i));
		if (pathComponent == nullptr) {
			// no op
		} else {
			canonicalPath = canonicalPath + (slash == true?L"/":L"") + pathComponent->getCPPWString();
			slash = true;
		}
	}

	// add cwd if required
	auto canonicalPathString = new String(canonicalPath);
	if (canonicalPathString->length() == 0 ||
		canonicalPathString->startsWith(u"/"_j) == false) {
		canonicalPathString = new String(getCurrentWorkingPathName()->getCPPWString() + L"/" + canonicalPathString->getCPPWString());
	}

	//
	return new String(canonicalPathString);
}

String* _StandardFileSystem::getCurrentWorkingPathName() /* throws(IOException) */ {
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

bool _StandardFileSystem::createPath(String* pathName) {
	const int dir_err = mkdir(StringConverter::toString(pathName->getCPPWString()).c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	return dir_err != -1;
}

bool _StandardFileSystem::removePath(String* pathName) {
	auto files = list(pathName, nullptr);
	for (int i = 0; i < files->length; i++) {
		auto file = files->get(i);
		if (file->equals(u"."_j) || file->equals(u".."_j)) {
			continue;
		}
		auto completeFileName = getFileName(pathName, file);
		if (isPath(completeFileName)) {
			removePath(completeFileName);
		} else {
			removeFile(pathName, file);
		}
	}
	_Console::println(wstring(L"_StandardFileSystem::removePath(): Removing ") + pathName->getCPPWString());
	rmdir(StringConverter::toString(pathName->getCPPWString()).c_str());
}

bool _StandardFileSystem::removeFile(String* pathName, String* fileName) {
	_Console::println(wstring(L"_StandardFileSystem::removeFile(): Removing ") + getFileName(pathName, fileName)->getCPPWString());
	unlink(StringConverter::toString(getFileName(pathName, fileName)->getCPPWString()).c_str());
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

