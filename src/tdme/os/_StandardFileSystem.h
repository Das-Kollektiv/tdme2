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
using java::io::InputStream;
using java::io::OutputStream;
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
	InputStream* getInputStream(String* path, String* fileName) /* throws(IOException) */ override;
	OutputStream* getOutputStream(String* path, String* fileName) /* throws(IOException) */ override;
	StringArray* list(String* path, FilenameFilter* filter) /* throws(IOException) */ override;
	bool isPath(String* path) /* throws(IOException) */ override;
	int8_tArray* getContent(String* path, String* fileName) /* throws(IOException) */ override;
	StringArray* getContentAsStringArray(String* path, String* fileName) /* throws(IOException) */ override;
	void setContentFromStringArray(String* path, String* fileName, StringArray* stringArray) /* throws(IOException) */ override;
	String* getCanonicalPath(String* path, String* fileName) /* throws(IOException) */ override;
	String* getCurrentWorkingPath() /* throws(IOException) */ override;
	String* getPathName(String* fileName) /* throws(IOException) */ override;
	String* getFileName(String* fileName) /* throws(IOException) */ override;


	// Generated
	_StandardFileSystem();
protected:
	_StandardFileSystem(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
