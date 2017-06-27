// Generated from /tdme/src/tdme/tests/AudioTest.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/security/fwd-tdme.h>
#include <tdme/tests/fwd-tdme.h>
#include <java/lang/Thread.h>

using java::lang::Thread;
using java::lang::Runnable;
using java::lang::String;
using java::lang::ThreadGroup;
using java::security::AccessControlContext;
using tdme::tests::AudioTest;


struct default_init_tag;
class tdme::tests::AudioTest_main_1
	: public Thread
{

public:
	typedef Thread super;
	void run() override;

	// Generated
	AudioTest_main_1();
	AudioTest_main_1(Runnable* arg0);
	AudioTest_main_1(String* arg0);

public: /* package */
	AudioTest_main_1(Runnable* arg0, AccessControlContext* arg1);

public:
	AudioTest_main_1(ThreadGroup* arg0, Runnable* arg1);
	AudioTest_main_1(ThreadGroup* arg0, String* arg1);
	AudioTest_main_1(Runnable* arg0, String* arg1);
	AudioTest_main_1(ThreadGroup* arg0, Runnable* arg1, String* arg2);
	AudioTest_main_1(ThreadGroup* arg0, Runnable* arg1, String* arg2, int64_t arg3);
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
	friend class AudioTest;
};
