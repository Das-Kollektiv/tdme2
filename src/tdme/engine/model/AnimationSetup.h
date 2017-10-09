#pragma once

#include <string>

#include <tdme.h>
#include <tdme/engine/model/fwd-tdme.h>

using std::wstring;

using tdme::engine::model::Model;

/** 
 * AnimationSetup
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::model::AnimationSetup final
{

private:
	Model* model {  };
	wstring id {  };
	int32_t startFrame {  };
	int32_t endFrame {  };
	int32_t frames {  };
	bool loop {  };
	wstring overlayFromGroupId {  };

public:

	/** 
	 * @return model this animation belongs to
	 */
	Model* getModel();

	/** 
	 * @return id
	 */
	const wstring& getId();

	/** 
	 * @return start frame
	 */
	int32_t getStartFrame();

	/** 
	 * @return end frame
	 */
	int32_t getEndFrame();

	/** 
	 * @return frames
	 */
	int32_t getFrames();

	/** 
	 * @return looping enabled
	 */
	bool isLoop();

	/** 
	 * If this is a overlay animation this returns a group id from which group the animation will start in the hierarchy
	 * @return group id from which the animation will start in the hierarchy
	 */
	const wstring& getOverlayFromGroupId();

	/** 
	 * @return animation duration in milliseconds
	 */
	int64_t computeDuration();

	/** 
	 * @param frames
	 * @return animation duration in milliseconds
	 */
	int64_t computeDuration(int32_t startFrame, int32_t endFrame);

	// Generated
	AnimationSetup(Model* model, const wstring& id, int32_t startFrame, int32_t endFrame, bool loop, const wstring& overlayFromGroupId);
};
