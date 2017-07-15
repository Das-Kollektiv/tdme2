// Generated from /tdme/src/tdme/tests/AudioTest.java
#include <tdme/tests/AudioTest_main_1.h>

#include <java/lang/Thread.h>
#include <tdme/audio/Audio.h>

using tdme::tests::AudioTest_main_1;
using java::lang::Thread;
using tdme::audio::Audio;

AudioTest_main_1::AudioTest_main_1()
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
	ctor();
}

AudioTest_main_1::AudioTest_main_1(Runnable* arg0)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
	ctor(arg0);
}

AudioTest_main_1::AudioTest_main_1(String* arg0)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
	ctor(arg0);
}

AudioTest_main_1::AudioTest_main_1(Runnable* arg0, AccessControlContext* arg1)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
	ctor(arg0, arg1);
}

AudioTest_main_1::AudioTest_main_1(ThreadGroup* arg0, Runnable* arg1)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
	ctor(arg0, arg1);
}

AudioTest_main_1::AudioTest_main_1(ThreadGroup* arg0, String* arg1)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
	ctor(arg0, arg1);
}

AudioTest_main_1::AudioTest_main_1(Runnable* arg0, String* arg1)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
	ctor(arg0, arg1);
}

AudioTest_main_1::AudioTest_main_1(ThreadGroup* arg0, Runnable* arg1, String* arg2)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
	ctor(arg0, arg1, arg2);
}

AudioTest_main_1::AudioTest_main_1(ThreadGroup* arg0, Runnable* arg1, String* arg2, int64_t arg3)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
	ctor(arg0, arg1, arg2, arg3);
}

void AudioTest_main_1::run()
{
	while (this->isInterrupted() == false) {
		Audio::getInstance()->update();
		Thread::sleep(17LL);
	}
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* AudioTest_main_1::class_()
{
    static ::java::lang::Class* c = ::class_(u"", 0);
    return c;
}

java::lang::Class* AudioTest_main_1::getClass0()
{
	return class_();
}

