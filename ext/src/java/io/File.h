// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/net/fwd-tdme.h>
#include <java/lang/Object.h>
#include <java/io/Serializable.h>
#include <java/lang/Comparable.h>

using java::lang::Object;
using java::io::Serializable;
using java::lang::Comparable;
using java::io::FileFilter;
using java::io::FileSystem;
using java::io::FilenameFilter;
using java::io::ObjectInputStream;
using java::io::ObjectOutputStream;
using java::lang::CharSequence;
using java::lang::SecurityManager;
using java::lang::String;
using java::net::URI;
using java::net::URL;
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

using java::io::FileArray;
using java::io::SerializableArray;
using java::lang::CharSequenceArray;
using java::lang::ComparableArray;
using java::lang::ObjectArray;
using java::lang::StringArray;

struct default_init_tag;
class java::io::File
	: public virtual Object
	, public virtual Serializable
	, public virtual Comparable
{

public:
	typedef Object super;

public: /* package */
	static bool $assertionsDisabled;

private:
	static FileSystem* fs;
	String* path {  };

public:
	static String* pathSeparator;
	static char16_t pathSeparatorChar;

private:
	int32_t prefixLength {  };

public:
	static String* separator;
	static char16_t separatorChar;

private:
	static constexpr int64_t serialVersionUID { 301077366599181567LL };

protected:
	void ctor(String* arg0);
	void ctor(URI* arg0);
	/*void ctor(String* arg0, int32_t arg1); (private) */
	/*void ctor(String* arg0, File* arg1); (private) */
	void ctor(String* arg0, String* arg1);
	void ctor(File* arg0, String* arg1);

public:
	virtual bool canExecute();
	virtual bool canRead();
	virtual bool canWrite();
	/*static bool checkAndCreate(String* arg0, SecurityManager* arg1, bool arg2); (private) */
	virtual int32_t compareTo(File* arg0);
	virtual bool createNewFile();
	static File* createTempFile(String* arg0, String* arg1);
	static File* createTempFile(String* arg0, String* arg1, File* arg2);
	/*static File* createTempFile0(String* arg0, String* arg1, File* arg2, bool arg3); (private) */
	virtual bool delete_();
	virtual void deleteOnExit();
	bool equals(Object* arg0) override;
	virtual bool exists();
	/*static File* generateFile(String* arg0, String* arg1, File* arg2); (private) */
	virtual File* getAbsoluteFile();
	virtual String* getAbsolutePath();
	virtual File* getCanonicalFile();
	virtual String* getCanonicalPath();
	virtual int64_t getFreeSpace();
	virtual String* getName();
	virtual String* getParent();
	virtual File* getParentFile();
	virtual String* getPath();

public: /* package */
	virtual int32_t getPrefixLength();

public:
	virtual int64_t getTotalSpace();
	virtual int64_t getUsableSpace();
	int32_t hashCode() override;
	virtual bool isAbsolute();
	virtual bool isDirectory();
	virtual bool isFile();
	virtual bool isHidden();
	virtual int64_t lastModified();
	virtual int64_t length();
	virtual StringArray* list();
	virtual StringArray* list(FilenameFilter* arg0);
	virtual FileArray* listFiles();
	virtual FileArray* listFiles(FilenameFilter* arg0);
	virtual FileArray* listFiles(FileFilter* arg0);
	static FileArray* listRoots();
	virtual bool mkdir();
	virtual bool mkdirs();
	/*void readObject(ObjectInputStream* arg0); (private) */
	virtual bool renameTo(File* arg0);
	virtual bool setExecutable(bool arg0);
	virtual bool setExecutable(bool arg0, bool arg1);
	virtual bool setLastModified(int64_t arg0);
	virtual bool setReadOnly();
	virtual bool setReadable(bool arg0);
	virtual bool setReadable(bool arg0, bool arg1);
	virtual bool setWritable(bool arg0);
	virtual bool setWritable(bool arg0, bool arg1);
	/*static String* slashify(String* arg0, bool arg1); (private) */
	String* toString() override;
	virtual URI* toURI();
	virtual URL* toURL();
	/*void writeObject(ObjectOutputStream* arg0); (private) */

	// Generated
	File(String* arg0);
	File(URI* arg0);
	File(String* arg0, String* arg1);
	File(File* arg0, String* arg1);
protected:
	File(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	virtual int32_t compareTo(Object* arg0) override;

private:
	virtual ::java::lang::Class* getClass0();
};
