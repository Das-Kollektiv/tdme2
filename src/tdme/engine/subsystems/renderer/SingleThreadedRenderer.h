#pragma once

#include <array>
#include <map>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/EntityShaderParameters.h>
#include <tdme/engine/Engine.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix2D3x3.h>
#include <tdme/math/Matrix4x4.h>

using std::array;
using std::map;
using std::string;

using tdme::engine::subsystems::renderer::Renderer;

using tdme::engine::Engine;
using tdme::engine::EntityShaderParameters;
using tdme::math::Matrix2D3x3;
using tdme::math::Matrix4x4;

/**
 * Single threaded renderer
 * @author Andreas Drewke
 * @ersion $Id$
 */
class tdme::engine::subsystems::renderer::SingleThreadedRenderer: public Renderer
{
public:
	/**
	 * Public constructor
	 */
	SingleThreadedRenderer();

	/**
	 * Destructor
	 */
	virtual ~SingleThreadedRenderer();

	// overridden methods
	const Renderer_Statistics getStatistics() override;

};
