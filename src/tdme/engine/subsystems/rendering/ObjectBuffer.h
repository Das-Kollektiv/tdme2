#pragma once

#include <memory>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/framebuffer/fwd-tdme.h>
#include <tdme/engine/subsystems/lines/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/engine/subsystems/skinning/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>

using tdme::utilities::ByteBuffer;

using std::unique_ptr;
using std::vector;

/**
 * Buffers used to transfer data between main memory to graphics board memory
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::rendering::ObjectBuffer final
{
	friend class ObjectNodeMesh;
	friend class EntityRenderer;
	friend class BatchRendererTriangles;
	friend class tdme::engine::Engine;
	friend class tdme::engine::subsystems::framebuffer::FrameBufferRenderShader;
	friend class tdme::engine::subsystems::framebuffer::FrameBufferRenderShader;
	friend class tdme::engine::subsystems::lines::LinesInternal;
	friend class tdme::engine::subsystems::rendering::ObjectNodeRenderer;
	friend class tdme::engine::subsystems::skinning::SkinningShader;

private:
	STATIC_DLL_IMPEXT static vector<unique_ptr<ByteBuffer>> byteBuffers;

	/**
	 * Initialize object buffer per thread
	 */
	static void initialize();

	/**
	 * Disposes object buffer per thread
	 */
	static void dispose();

public:
	/**
	 * Get byte buffer for given context
	 * @param bytes bytes
	 * @returns byte buffer
	 */
	static ByteBuffer* getByteBuffer(int contextIdx, int32_t bytes);

};
