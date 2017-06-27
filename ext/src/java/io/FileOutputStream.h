// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <atomic>
#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/nio/channels/fwd-tdme.h>
#include <java/io/OutputStream.h>

using java::io::OutputStream;
using java::io::File;
using java::io::FileDescriptor;
using java::lang::Object;
using java::lang::String;
using java::lang::ThreadLocal;
using java::nio::channels::FileChannel;


struct default_init_tag;
class java::io::FileOutputStream
	: public OutputStream
{

public:
	typedef OutputStream super;

private:
	bool append {  };
	FileChannel* channel {  };
	Object* closeLock {  };
	std::atomic< bool > closed {  };
	FileDescriptor* fd {  };
	static ThreadLocal* runningFinalize;

protected:
	void ctor(String* arg0);
	void ctor(File* arg0);
	void ctor(FileDescriptor* arg0);
	void ctor(String* arg0, bool arg1);
	void ctor(File* arg0, bool arg1);

public:
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
	/*void openAppend(String* arg0); (private) */
	void write(int32_t arg0) override;
	void write(int8_tArray* arg0) override;
	void write(int8_tArray* arg0, int32_t arg1, int32_t arg2) override;
	/*void writeBytes(int8_tArray* arg0, int32_t arg1, int32_t arg2); (private) */

	// Generated
	FileOutputStream(String* arg0);
	FileOutputStream(File* arg0);
	FileOutputStream(FileDescriptor* arg0);
	FileOutputStream(String* arg0, bool arg1);
	FileOutputStream(File* arg0, bool arg1);
protected:
	FileOutputStream(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
