// Generated from /tdme/src/tdme/os/_StandardFileSystem.java

#pragma once

#include <Array.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/os/fwd-tdme.h>
#include <java/lang/Object.h>
#include <tdme/os/_FileSystemInterface.h>

using java::lang::Object;
using tdme::os::_FileSystemInterface;
using java::io::FilenameFilter;
using java::io::Serializable;
using java::lang::CharSequence;
using java::lang::Comparable;
using java::lang::String;

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

using java::io::SerializableArray;
using java::lang::CharSequenceArray;
using java::lang::ComparableArray;
using java::lang::ObjectArray;
using java::lang::StringArray;

struct default_init_tag;
class tdme::os::_StandardFileSystem final
	: public virtual Object
	, public _FileSystemInterface
{

public:
	typedef Object super;
	String* getFileName(String* path, String* fileName) throw (_FileSystemException) override;
	StringArray* list(String* pathName, FilenameFilter* filter) throw (_FileSystemException) override;
	bool isPath(String* pathName) throw (_FileSystemException) override;
	bool fileExists(String* fileName) throw (_FileSystemException) override;
	String* getContentAsString(String* pathName, String* fileName) throw (_FileSystemException) override;
	void setContentFromString(String* pathName, String* fileName, String* string) throw (_FileSystemException) override;
	int8_tArray* getContent(String* pathName, String* fileName) throw (_FileSystemException) override;
	void setContent(String* pathName, String* fileName, int8_tArray* data, int32_t size = -1) throw (_FileSystemException) override;
	StringArray* getContentAsStringArray(String* pathName, String* fileName) throw (_FileSystemException) override;
	void setContentFromStringArray(String* pathName, String* fileName, StringArray* stringArray) throw (_FileSystemException) override;
	String* getCanonicalPath(String* pathName, String* fileName) throw (_FileSystemException) override;
	String* getCurrentWorkingPathName() throw (_FileSystemException) override;
	String* getPathName(String* fileName) throw (_FileSystemException) override;
	String* getFileName(String* fileName) throw (_FileSystemException) override;
	void createPath(String* pathName) throw (_FileSystemException) override;
	void removePath(String* pathName) throw (_FileSystemException) override;
	void removeFile(String* pathName, String* fileName) throw (_FileSystemException) override;

	// Generated
	_StandardFileSystem();
protected:
	_StandardFileSystem(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
