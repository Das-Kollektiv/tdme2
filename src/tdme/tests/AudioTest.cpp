#include <tdme/tests/AudioTest.h>

#include <java/lang/String.h>
#include <tdme/audio/Audio.h>
#include <tdme/audio/AudioEntity.h>
#include <tdme/utils/_Console.h>

using tdme::tests::AudioTest;
using java::lang::String;
using java::lang::Thread;
using tdme::audio::Audio;
using tdme::audio::AudioEntity;
using tdme::tests::AudioTest_main_1;
using tdme::utils::_Console;

void AudioTest::main()
{
	_Console::println(wstring(L"Starting playing sound"));
	auto test = Audio::getInstance()->addSound(L"test", L"resources/tests/music", L"memento-sanchez_monate_spaeter.ogg");
	test->setLooping(false);
	test->setFixed(true);
	test->play();
	while(test->isPlaying() == true) { Audio::getInstance()->update(); };
	_Console::println(wstring(L"Finished playing sound"));
}
