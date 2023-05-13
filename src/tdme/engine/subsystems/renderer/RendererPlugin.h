#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>

using std::string;

/**
 * Renderer plugin base class
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::renderer::RendererPlugin
{
public:
	/**
	 * @return renderer version
	 */
	inline static string getRendererVersion() {
		return "1.9.179";
	}

};
