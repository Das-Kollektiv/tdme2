#include <tdme/tests/AudioTest.h>

#include <tdme/os/threading/Thread.h>
#include <tdme/audio/Audio.h>
#include <tdme/audio/AudioEntity.h>
#include <tdme/utils/Console.h>

using tdme::tests::AudioTest;
using tdme::audio::Audio;
using tdme::audio::AudioEntity;
using tdme::os::threading::Thread;
using tdme::tests::AudioTest_main_1;
using tdme::utils::Console;

void AudioTest::main()
{
	Console::println(string("Starting playing sound"));
	auto sound = Audio::getInstance()->addSound("sound", "resources/tests/sounds", "water.ogg");
	sound->setLooping(false);
	sound->setFixed(true);
	sound->play();
	while(sound->isPlaying() == true) { Audio::getInstance()->update(); Thread::sleep(100L); };
	Console::println(string("Finished playing sound"));
	Console::println(string("Starting playing music"));
	auto stream = Audio::getInstance()->addSound("music", "resources/tests/music", "memento-sanchez_monate_spaeter.ogg");
	stream->setLooping(false);
	stream->setFixed(true);
	stream->play();
	while(stream->isPlaying() == true) { Audio::getInstance()->update(); Thread::sleep(100L); };
	Console::println(string("Finished playing music"));
	Audio::getInstance()->shutdown();
}
