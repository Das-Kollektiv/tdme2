// Generated from /tdme/src/tdme/tests/AudioTest.java
#include <tdme/tests/AudioTest.h>

#include <java/io/BufferedReader.h>
#include <java/io/InputStreamReader.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/System.h>
#include <java/lang/Thread.h>
#include <tdme/audio/Audio.h>
#include <tdme/audio/AudioEntity.h>
#include <tdme/tests/AudioTest_main_1.h>
#include <tdme/utils/_Console.h>

using tdme::tests::AudioTest;
using java::io::BufferedReader;
using java::io::InputStreamReader;
using java::lang::Object;
using java::lang::String;
using java::lang::System;
using java::lang::Thread;
using tdme::audio::Audio;
using tdme::audio::AudioEntity;
using tdme::tests::AudioTest_main_1;
using tdme::utils::_Console;

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

AudioTest::AudioTest(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

AudioTest::AudioTest()
	: AudioTest(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void AudioTest::main(StringArray* args) /* throws(Exception) */
{
	clinit();
	auto test = Audio::getInstance()->addStream(u"test"_j, u"resources/tests/music"_j, u"memento-sanchez_monate_spaeter.ogg"_j);
	test->setLooping(true);
	test->setFixed(true);
	test->play();
	Thread* audioUpdateThread = new AudioTest_main_1();
	audioUpdateThread->start();
	_Console::println(static_cast< Object* >(u"Press 'enter' to quit"_j));
	auto buf = new BufferedReader(new InputStreamReader(System::in));
	buf->readLine();
	audioUpdateThread->interrupt();
	Audio::getInstance()->shutdown();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* AudioTest::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.tests.AudioTest", 20);
    return c;
}

java::lang::Class* AudioTest::getClass0()
{
	return class_();
}

