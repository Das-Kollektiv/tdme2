#include <tdme/engine/subsystems/rendering/ObjectBuffer.h>

#include <memory>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/Engine.h>
#include <tdme/utilities/ByteBuffer.h>
#include <tdme/utilities/Console.h>

using tdme::engine::subsystems::rendering::ObjectBuffer;

using std::unique_ptr;
using std::vector;

using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::Engine;
using tdme::utilities::ByteBuffer;
using tdme::utilities::Console;

vector<unique_ptr<ByteBuffer>> ObjectBuffer::byteBuffers;

void ObjectBuffer::initialize() {
	auto renderer = Engine::getRenderer();
	byteBuffers.resize(renderer->isSupportingMultithreadedRendering() == true?Engine::getThreadCount():1);
}

void ObjectBuffer::dispose() {
	byteBuffers.clear();
}

ByteBuffer* ObjectBuffer::getByteBuffer(int contextIdx, int32_t bytes)
{
	auto renderer = Engine::getRenderer();
	if (byteBuffers[contextIdx] == nullptr || bytes > byteBuffers[contextIdx]->getCapacity()) {
		byteBuffers[contextIdx] = unique_ptr<ByteBuffer>(ByteBuffer::allocate(bytes));
	} else {
		byteBuffers[contextIdx]->clear();
	}
	return byteBuffers[contextIdx].get();
}
