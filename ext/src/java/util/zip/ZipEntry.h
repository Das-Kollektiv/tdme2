// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/zip/fwd-tdme.h>
#include <java/lang/Object.h>
#include <java/util/zip/ZipConstants.h>
#include <java/lang/Cloneable.h>

using java::lang::Object;
using java::util::zip::ZipConstants;
using java::lang::Cloneable;
using java::lang::String;


struct default_init_tag;
class java::util::zip::ZipEntry
	: public virtual Object
	, public virtual ZipConstants
	, public virtual Cloneable
{

public:
	typedef Object super;
	static constexpr int32_t DEFLATED { 8 };
	static constexpr int32_t STORED { 0 };

public: /* package */
	String* comment {  };
	int64_t crc {  };
	int64_t csize {  };
	int8_tArray* extra {  };
	int32_t method {  };
	String* name {  };
	int64_t size {  };
	int64_t time {  };

protected:
	void ctor(String* arg0);
	void ctor(ZipEntry* arg0);
	void ctor(int64_t arg0);
	void ctor(String* arg0, int64_t arg1);

public:
	Object* clone() override;
	/*static int64_t dosToJavaTime(int64_t arg0); (private) */
	virtual String* getComment();
	virtual int64_t getCompressedSize();
	virtual int64_t getCrc();
	virtual int8_tArray* getExtra();
	virtual int32_t getMethod();
	virtual String* getName();
	virtual int64_t getSize();
	virtual int64_t getTime();
	int32_t hashCode() override;
	/*void initFields(int64_t arg0); (private) */
	/*static void initIDs(); (private) */
	virtual bool isDirectory();
	/*static int64_t javaToDosTime(int64_t arg0); (private) */
	virtual void setComment(String* arg0);
	virtual void setCompressedSize(int64_t arg0);
	virtual void setCrc(int64_t arg0);
	virtual void setExtra(int8_tArray* arg0);
	virtual void setMethod(int32_t arg0);
	virtual void setSize(int64_t arg0);
	virtual void setTime(int64_t arg0);
	String* toString() override;

	// Generated
	ZipEntry(String* arg0);
	ZipEntry(ZipEntry* arg0);

public: /* package */
	ZipEntry(int64_t arg0);
	ZipEntry(String* arg0, int64_t arg1);
protected:
	ZipEntry(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
