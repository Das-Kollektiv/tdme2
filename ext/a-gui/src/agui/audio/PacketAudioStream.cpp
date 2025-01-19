#include <agui/audio/PacketAudioStream.h>

#include <string>
#include <vector>

#include <agui/agui.h>
#include <agui/utilities/ByteBuffer.h>
#include <agui/utilities/Console.h>

using agui::audio::PacketAudioStream;

using std::string;
using std::to_string;
using std::vector;

using agui::utilities::ByteBuffer;
using agui::utilities::Console;

void PacketAudioStream::rewind()
{
	Console::printLine("PacketAudioStream::rewind(): Not supported!");
}

bool PacketAudioStream::initialize()
{
	if (initiated == true) return true;

	// check if underlying audio stream did initialize
	if (AudioStream::initialize() == false) {
		dispose();
		return false;
	}

	// success
	initiated = true;
	return true;
}

void PacketAudioStream::addPacket(ByteBuffer* byteBuffer) {
	if (byteBuffer->getPosition() == 0LL) return;
	packets.emplace_back(byteBuffer->getPosition());
	auto& packet = packets[packets.size() - 1];
	// TODO: use memcpy or similar
	for (auto i = 0LL; i < byteBuffer->getPosition(); i++) {
		packet[i] = byteBuffer->get(i);
	}
}

void PacketAudioStream::fillBuffer(ByteBuffer* data) {
	// TODO: optimize me
	while (data->getPosition() < data->getCapacity() && packets.empty() == false) {
		data->put(packets[0][position++]);
		if (position == packets[0].size()) {
			position = 0LL;
			packets.erase(packets.begin());
		}
	}
}

void PacketAudioStream::dispose()
{
	if (initiated == false) return;

	// dispose audio stream
	AudioStream::dispose();

	//
	initiated = false;
}
