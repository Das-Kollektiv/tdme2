#pragma once

#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/framebuffer/fwd-tdme.h>
#include <tdme/engine/subsystems/lines/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/engine/subsystems/skinning/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>

using tdme::utilities::ByteBuffer;

using std::vector;

/**
 * Buffers used to transfer data between main memory to graphics board memory
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::rendering::ObjectBuffer final
{
	friend class ObjectNodeMesh;
	friend class EntityRenderer;
	friend class BatchRendererTriangles;
	friend class tdme::engine::Engine;
	friend class tdme::engine::subsystems::framebuffer::FrameBufferRenderShader;
	friend class tdme::engine::subsystems::framebuffer::FrameBufferRenderShader;
	friend class tdme::engine::subsystems::lines::LinesObjectInternal;
	friend class tdme::engine::subsystems::rendering::ObjectNodeRenderer;
	friend class tdme::engine::subsystems::skinning::SkinningShader;

private:
	STATIC_DLL_IMPEXT static vector<ByteBuffer*> byteBuffers;

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
	 * @return byte buffer
	 */
	static ByteBuffer* getByteBuffer(int contextIdx, int32_t bytes);

};
