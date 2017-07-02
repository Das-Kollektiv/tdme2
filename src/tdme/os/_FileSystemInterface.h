// Generated from /tdme/src/tdme/os/_FileSystemInterface.java

#pragma once

#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/os/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
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


/** 
 * Interface to file system
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::os::_FileSystemInterface
	: public virtual Object
{

	/** 
	 * Creates input stream by given path name and file name
	 * @param path
	 * @param file name
	 * @return input stream
	 * @throws IOException
	 */
	virtual InputStream* getInputStream(String* path, String* fileName) /* throws(IOException) */ = 0;

	/** 
	 * Creates output stream by given path name and file name
	 * @param path
	 * @param file name
	 * @return output stream
	 * @throws IOException
	 */
	virtual OutputStream* getOutputStream(String* path, String* fileName) /* throws(IOException) */ = 0;

	/** 
	 * Get file content
	 * @param path
	 * @param file name
	 * @return byte array
	 * @throws IOException
	 */
	virtual int8_tArray* getContent(String* path, String* fileName) /* throws(IOException) */ = 0;

	/** 
	 * List files for given path and filter by a file name filter if not null 
	 * @param path
	 * @param filter or null
	 * @return file names 
	 */
	virtual StringArray* list(String* path, FilenameFilter* filter) /* throws(IOException) */ = 0;

	// Generated
	static ::java::lang::Class *class_();
};
