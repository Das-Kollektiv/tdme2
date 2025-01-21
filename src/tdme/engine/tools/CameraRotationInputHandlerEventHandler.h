#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/tools/fwd-tdme.h>

/**
 * Camera Rotation Input Handler Event Handler
 * @author Andreas Drewke
 */
struct tdme::engine::tools::CameraRotationInputHandlerEventHandler
{
	/**
	 * Destructor
	 */
	virtual ~CameraRotationInputHandlerEventHandler() {}

	/**
	 * On rotation event to be overloaded
	 */
	virtual void onCameraRotation() = 0;

	/**
	 * On scale event to be overloaded
	 */
	virtual void onCameraScale() = 0;


};
