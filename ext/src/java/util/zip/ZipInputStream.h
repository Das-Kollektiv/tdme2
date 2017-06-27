// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/zip/fwd-tdme.h>
#include <java/util/zip/InflaterInputStream.h>
#include <java/util/zip/ZipConstants.h>

using java::util::zip::InflaterInputStream;
using java::util::zip::ZipConstants;
using java::io::InputStream;
using java::lang::String;
using java::util::zip::CRC32;
using java::util::zip::ZipEntry;


struct default_init_tag;
class java::util::zip::ZipInputStream
	: public InflaterInputStream
	, public virtual ZipConstants
{

public:
	typedef InflaterInputStream super;

private:
	static constexpr int32_t DEFLATED { 8 };
	static constexpr int32_t STORED { 0 };
	int8_tArray* b {  };
	bool closed {  };
	CRC32* crc {  };
	ZipEntry* entry {  };
	bool entryEOF {  };
	static String* fileEncoding;
	int32_t flag {  };
	int64_t remaining {  };
	int8_tArray* tmpbuf {  };

protected:
	void ctor(InputStream* arg0);

public:
	int32_t available() override;
	void close() override;
	virtual void closeEntry();

public: /* protected */
	virtual ZipEntry* createZipEntry(String* arg0);
	/*void ensureOpen(); (private) */
	/*static int32_t get16(int8_tArray* arg0, int32_t arg1); (private) */
	/*static int64_t get32(int8_tArray* arg0, int32_t arg1); (private) */
	/*String* getFileName(int8_tArray* arg0, int32_t arg1); (private) */

public:
	virtual ZipEntry* getNextEntry();
	/*static String* getUTF8String(int8_tArray* arg0, int32_t arg1, int32_t arg2); (private) */
	int32_t read(int8_tArray* arg0, int32_t arg1, int32_t arg2) override;
	/*void readEnd(ZipEntry* arg0); (private) */
	/*void readFully(int8_tArray* arg0, int32_t arg1, int32_t arg2); (private) */
	/*ZipEntry* readLOC(); (private) */
	int64_t skip(int64_t arg0) override;

	// Generated
	ZipInputStream(InputStream* arg0);
protected:
	ZipInputStream(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	int32_t read();
	int32_t read(int8_tArray* arg0);

private:
	virtual ::java::lang::Class* getClass0();
};
