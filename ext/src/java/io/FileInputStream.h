// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <atomic>
#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/nio/channels/fwd-tdme.h>
#include <java/io/InputStream.h>

using java::io::InputStream;
using java::io::File;
using java::io::FileDescriptor;
using java::lang::Object;
using java::lang::String;
using java::lang::ThreadLocal;
using java::nio::channels::FileChannel;


struct default_init_tag;
class java::io::FileInputStream
	: public InputStream
{

public:
	typedef InputStream super;

private:
	FileChannel* channel {  };
	Object* closeLock {  };
	std::atomic< bool > closed {  };
	FileDescriptor* fd {  };
	static ThreadLocal* runningFinalize;

protected:
	void ctor(String* arg0);
	void ctor(File* arg0);
	void ctor(FileDescriptor* arg0);

public:
	int32_t available() override;
	void close() override;
	/*void close0(); (private) */

public: /* protected */
	void finalize() override;

public:
	virtual FileChannel* getChannel();
	FileDescriptor* getFD();
	/*static void initIDs(); (private) */
	/*static bool isRunningFinalize(); (private) */
	/*void open(String* arg0); (private) */
	int32_t read() override;
	int32_t read(int8_tArray* arg0) override;
	int32_t read(int8_tArray* arg0, int32_t arg1, int32_t arg2) override;
	/*int32_t readBytes(int8_tArray* arg0, int32_t arg1, int32_t arg2); (private) */
	int64_t skip(int64_t arg0) override;

	// Generated
	FileInputStream(String* arg0);
	FileInputStream(File* arg0);
	FileInputStream(FileDescriptor* arg0);
protected:
	FileInputStream(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
