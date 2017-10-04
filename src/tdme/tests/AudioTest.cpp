#include <tdme/tests/AudioTest.h>

#include <java/lang/Thread.h>
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
	auto sound = Audio::getInstance()->addSound(L"sound", L"resources/tests/sounds", L"water.ogg");
	sound->setLooping(false);
	sound->setFixed(true);
	sound->play();
	while(sound->isPlaying() == true) { Audio::getInstance()->update(); Thread::sleep(100L); };
	_Console::println(wstring(L"Finished playing sound"));
	_Console::println(wstring(L"Starting playing music"));
	auto stream = Audio::getInstance()->addSound(L"music", L"resources/tests/music", L"memento-sanchez_monate_spaeter.ogg");
	stream->setLooping(false);
	stream->setFixed(true);
	stream->play();
	while(stream->isPlaying() == true) { Audio::getInstance()->update(); Thread::sleep(100L); };
	_Console::println(wstring(L"Finished playing music"));
}
