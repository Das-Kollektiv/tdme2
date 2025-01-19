#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>

using std::string;

/**
 * RendererBackend plugin base class
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::renderer::RendererPlugin
{
public:
	/**
	 * @return rendererBackend version
	 */
	inline static const string getRendererVersion() {
		return "1.9.200";
	}

};
