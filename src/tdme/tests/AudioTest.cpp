#include <tdme/tests/AudioTest.h>

#include <java/lang/String.h>
#include <java/lang/Thread.h>
#include <tdme/audio/Audio.h>
#include <tdme/audio/AudioEntity.h>
#include <tdme/tests/AudioTest_main_1.h>
#include <tdme/utils/_Console.h>

using tdme::tests::AudioTest;
using java::lang::String;
using java::lang::Thread;
using tdme::audio::Audio;
using tdme::audio::AudioEntity;
using tdme::tests::AudioTest_main_1;
using tdme::utils::_Console;

void AudioTest::main() /* throws(Exception) */
{
	auto test = Audio::getInstance()->addStream(L"test", L"resources/tests/music", L"memento-sanchez_monate_spaeter.ogg");
	test->setLooping(true);
	test->setFixed(true);
	test->play();
	Thread* audioUpdateThread = new AudioTest_main_1();
	audioUpdateThread->start();
	_Console::println(static_cast< Object* >(u"Press 'enter' to quit"_j));
	// read char/line();
	audioUpdateThread->interrupt();
	Audio::getInstance()->shutdown();
}
