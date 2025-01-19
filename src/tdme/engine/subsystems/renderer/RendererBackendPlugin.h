#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>

using std::string;

/**
 * Renderer backend plugin base class
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::renderer::RendererBackendPlugin
{
public:
	/**
	 * @returns renderer version
	 */
	inline static const string getRendererVersion() {
		return "1.9.200";
	}

};
