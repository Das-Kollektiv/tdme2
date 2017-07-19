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

#include <java/io/FilenameFilter.h>
#include <java/io/Serializable.h>
#include <java/lang/CharSequence.h>
#include <java/lang/Class.h>
#include <java/lang/ClassLoader.h>
#include <java/lang/Comparable.h>
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
#include <tdme/utils/StringConverter.h>
#include <tdme/utils/_Console.h>
#include <Array.h>
#include <SubArray.h>
#include <ObjectArray.h>

using std::getline;
using std::string;
using std::vector;
using std::to_string;

using tdme::os::_StandardFileSystem;
using java::io::BufferedReader;
using java::io::FilenameFilter;
using java::io::Serializable;
using java::lang::CharSequence;
using java::lang::Class;
using java::lang::ClassLoader;
using java::lang::Comparable;
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
using tdme::utils::StringConverter;
using tdme::utils::_Console;

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

String* _StandardFileSystem::getFileName(String* pathName, String* fileName) throw (_FileSystemException) {
	return new String(pathName->getCPPWString() + L"/" + fileName->getCPPWString());
}

StringArray* _StandardFileSystem::list(String* pathName, FilenameFilter* filter) throw (_FileSystemException)
{
	vector<String*> files;

	DIR *dir;
	struct dirent *dirent;
	if ((dir = opendir(StringConverter::toString(pathName->getCPPWString()).c_str())) == NULL) {
		throw _FileSystemException("Unable to list path(" + to_string(errno) + ")");
	}
	while ((dirent = readdir(dir)) != NULL) {
		String* file = new String(StringConverter::toWideString(dirent->d_name));
		if (filter != nullptr && filter->accept(pathName, file) == false) continue;
		files.push_back(file);
	}
	closedir(dir);

	auto _files = new StringArray(files.size());
	int i = 0;
	for (auto file: files) {
		_files->set(i++, file);
	}
	return _files;
}

bool _StandardFileSystem::isPath(String* pathName) throw (_FileSystemException) {
	struct stat s;
	if (stat(StringConverter::toString(pathName->getCPPWString()).c_str(), &s) == 0) {
		return (s.st_mode & S_IFDIR) == S_IFDIR;
	} else {
		throw _FileSystemException("Unable to check if path(" + to_string(errno) + ")");
	}
}

bool _StandardFileSystem::fileExists(String* fileName) throw (_FileSystemException) {
	struct stat s;
	return stat(StringConverter::toString(fileName->getCPPWString()).c_str(), &s) == 0;
}

String* _StandardFileSystem::getContentAsString(String* pathName, String* fileName) throw (_FileSystemException) {
	return new String(getContent(pathName, fileName));
}

void _StandardFileSystem::setContentFromString(String* pathName, String* fileName, String* string) throw (_FileSystemException) {
	ofstream ofs(StringConverter::toString(getFileName(pathName, fileName)->getCPPWString()).c_str());
	if (ofs.is_open() == false) {
		throw _FileSystemException("Unable to open file for writing(" + to_string(errno) + ")");
	}

	ofs << StringConverter::toString(string->getCPPWString());

	ofs.close();
	return;
}

int8_tArray* _StandardFileSystem::getContent(String* pathName, String* fileName) throw (_FileSystemException)
{
	ifstream ifs(StringConverter::toString(getFileName(pathName, fileName)->getCPPWString()).c_str());
	if (ifs.is_open() == false) {
		throw _FileSystemException("Unable to open file for reading(" + to_string(errno) + ")");
	}
	ifs.seekg( 0, ios::end );
	size_t size = ifs.tellg();
	int8_tArray* data = new int8_tArray(size);
	ifs.seekg(0, ios::beg);
	ifs.read((char *)data->getPointer(), size);
	ifs.close();
	return data;
}

void _StandardFileSystem::setContent(String* pathName, String* fileName, int8_tArray* data, int32_t size) throw (_FileSystemException) {
	ofstream ofs(StringConverter::toString(getFileName(pathName, fileName)->getCPPWString()).c_str());
	if (ofs.is_open() == false) {
		throw _FileSystemException("Unable to open file for writing(" + to_string(errno) + ")");
	}
	ofs.write((char *)data->getPointer(), size == -1?data->length:size);
	ofs.close();
}

StringArray* _StandardFileSystem::getContentAsStringArray(String* pathName, String* fileName) throw (_FileSystemException)
{
	ifstream ifs(StringConverter::toString(getFileName(pathName, fileName)->getCPPWString()).c_str());
	if(ifs.is_open() == false) {
		throw _FileSystemException("Unable to open file for reading(" + to_string(errno) + ")");
	}

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

	ifs.close();

	return result;
}

void _StandardFileSystem::setContentFromStringArray(String* pathName, String* fileName, StringArray* stringArray) throw (_FileSystemException)
{
	ofstream ofs(StringConverter::toString(getFileName(pathName, fileName)->getCPPWString()).c_str());
	if(ofs.is_open() == false) {
		throw _FileSystemException("Unable to open file for writing(" + to_string(errno) + ")");
	}

	for (int i = 0; i < stringArray->length; i++) {
		auto line = stringArray->get(i);
		ofs << StringConverter::toString(line->getCPPWString()) << "\n";
	}

	ofs.close();
	return;
}

String* _StandardFileSystem::getCanonicalPath(String* pathName, String* fileName) throw (_FileSystemException) {
	String* unixPathName = pathName->replace(L'\\', L'/');
	String* unixFileName = fileName->replace(L'\\', L'/');

	auto pathString = getFileName(unixPathName, unixFileName);

	// separate into path components
	vector<String*> pathComponents;
	auto t = new StringTokenizer(pathString, u"/"_j);
	while (t->hasMoreTokens()) {
		pathComponents.push_back(t->nextToken());
	}

	// process path components
	for (int i = 0; i < pathComponents.size(); i++) {
		auto pathComponent = pathComponents.at(i);
		if (pathComponent->equals(u"."_j) == true) {
			pathComponents[i] = nullptr;
		} else
		if (pathComponent->equals(u".."_j) == true) {
			pathComponents[i]= nullptr;
			int j = i - 1;
			for (int pathComponentReplaced = 0; pathComponentReplaced < 1 && j >= 0; ) {
				if (pathComponents.at(j) != nullptr) {
					pathComponents[j] = nullptr;
					pathComponentReplaced++;
				}
				j--;
			}
		}
	}

	// process path components
	wstring canonicalPath = L"";
	bool slash = pathString->startsWith(u"/"_j);
	for (int i = 0; i < pathComponents.size(); i++) {
		auto pathComponent = pathComponents.at(i);
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

String* _StandardFileSystem::getCurrentWorkingPathName() throw (_FileSystemException) {
	// cwd
	char cwdBuffer[PATH_MAX + 1];
	char* cwdPtr = getcwd(cwdBuffer, sizeof(cwdBuffer));
	if (cwdPtr == nullptr) {
		throw _FileSystemException("Unable to get current working path(" + to_string(errno) + ")");
	}
	return new String(StringConverter::toWideString(cwdPtr));
}

String* _StandardFileSystem::getPathName(String* fileName) throw (_FileSystemException) {
	String* unixFileName = fileName->replace(L'\\', L'/');
	int32_t lastPathSeparator = unixFileName->lastIndexOf(L'/');
	if (lastPathSeparator == -1) return new String(u"."_j);
	return unixFileName->substring(0, lastPathSeparator);
}

String* _StandardFileSystem::getFileName(String* fileName) throw (_FileSystemException) {
	String* unixFileName = fileName->replace(L'\\', L'/');
	int32_t lastPathSeparator = unixFileName->lastIndexOf(L'/');
	if (lastPathSeparator == -1) return new String(fileName);
	return unixFileName->substring(lastPathSeparator + 1, unixFileName->length());
}

void _StandardFileSystem::createPath(String* pathName) throw (_FileSystemException) {
	int32_t status = mkdir(StringConverter::toString(pathName->getCPPWString()).c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	if (status == -1) {
		throw _FileSystemException("Unable to create path(" + to_string(errno) + ")");
	}
}

void _StandardFileSystem::removePath(String* pathName) throw (_FileSystemException) {
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
	int32_t status = rmdir(StringConverter::toString(pathName->getCPPWString()).c_str());
	if (status == -1) {
		throw _FileSystemException("Unable to delete folder(" + to_string(errno) + ")");
	}
}

void _StandardFileSystem::removeFile(String* pathName, String* fileName) throw (_FileSystemException) {
	_Console::println(wstring(L"_StandardFileSystem::removeFile(): Removing ") + getFileName(pathName, fileName)->getCPPWString());
	int32_t status = unlink(StringConverter::toString(getFileName(pathName, fileName)->getCPPWString()).c_str());
	if (status == -1) {
		throw _FileSystemException("Unable to delete file(" + to_string(errno) + ")");
	}
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

