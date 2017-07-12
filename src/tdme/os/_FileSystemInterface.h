// Generated from /tdme/src/tdme/os/_FileSystemInterface.java

#pragma once

#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/os/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::io::Serializable;
using java::io::FilenameFilter;
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
	 * Get file name
	 * @param path name
	 * @param file name
	 * @return complete filename with path and file
	 */
	virtual String* getFileName(String* pathName, String* fileName) /* throws(IOException) */ = 0;

	/**
	 * Get content as string
	 * @param path name
	 * @param file name
	 * @return string
	 */
	virtual String* getContentAsString(String* pathName, String* fileName) /* throws(IOException) */ = 0;

	/**
	 * Set content from string
	 * @param path name
	 * @param file name
	 * @return string
	 */
	virtual void setContentFromString(String* pathName, String* fileName, String* string) /* throws(IOException) */ = 0;

	/** 
	 * Get file content
	 * @param path name
	 * @param file name
	 * @return byte array
	 * @throws IOException
	 */
	virtual int8_tArray* getContent(String* pathName, String* fileName) /* throws(IOException) */ = 0;

	/** 
	 * Get file content
	 * @param path name
	 * @param file name
	 * @param data
	 * @param length or -1 if data length should be used
	 * @throws IOException
	 */
	virtual void setContent(String* pathName, String* fileName, int8_tArray* data, int32_t size = -1) /* throws(IOException) */ = 0;

	/**
	 * Get file content as string array
	 * @param path name
	 * @param file name
	 * @return byte array
	 * @throws IOException
	 */
	virtual StringArray* getContentAsStringArray(String* pathName, String* fileName) /* throws(IOException) */ = 0;

	/**
	 * Set file content as string array
	 * @param path name
	 * @param file name
	 * @param string array
	 * @return byte array
	 * @throws IOException
	 */
	virtual void setContentFromStringArray(String* pathName, String* fileName, StringArray* stringArray) /* throws(IOException) */ = 0;

	/**
	 * List files for given path and filter by a file name filter if not null 
	 * @param path name
	 * @param filter or null
	 * @return file names 
	 */
	virtual StringArray* list(String* pathName, FilenameFilter* filter) /* throws(IOException) */ = 0;

	/**
	 * Check if file is a path
	 * @param path name
	 * @return if file is a path
	 */
	virtual bool isPath(String* pathName) /* throws(IOException) */ = 0;

	/**
	 * Check if file exists
	 * @param file name
	 * @return bool if file exists
	 */
	virtual bool fileExists(String* fileName) /* throws(IOException) */ = 0;

	/**
	 * Get canonical path name
	 * @param path name
	 * @param file name
	 * @return canonical path
	 */
	virtual String* getCanonicalPath(String* pathName, String* fileName) /* throws(IOException) */ = 0;

	/**
	 * Get current working path name
	 * @return current working path
	 */
	virtual String* getCurrentWorkingPathName() /* throws(IOException) */ = 0;

	/**
	 * Get path name
	 * @param file name
	 * @return canonical path
	 */
	virtual String* getPathName(String* fileName) /* throws(IOException) */ = 0;

	/**
	 * Get file name
	 * @param file name
	 * @return canonical path
	 */
	virtual String* getFileName(String* fileName) /* throws(IOException) */ = 0;

	/**
	 * Create path
	 * @param path name
	 */
	virtual bool createPath(String* pathName) /* throws(IOException) */ = 0;

	/**
	 * Remove path
	 * @param path name
	 * @return success
	 */
	virtual bool removePath(String* pathName) /* throws(IOException) */ = 0;

	/**
	 * Remove file
	 * @param path name
	 * @param file name
	 * @return success
	 */
	virtual bool removeFile(String* pathName, String* fileName) /* throws(IOException) */ = 0;

	// Generated
	static ::java::lang::Class *class_();
};
