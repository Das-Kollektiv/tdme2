#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>

using std::string;

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
	string id {  };
	int32_t startFrame {  };
	int32_t endFrame {  };
	int32_t frames {  };
	bool loop {  };
	string overlayFromGroupId {  };

public:

	/** 
	 * @return model this animation belongs to
	 */
	Model* getModel();

	/** 
	 * @return id
	 */
	const string& getId();

	/** 
	 * @return start frame
	 */
	int32_t getStartFrame();

	/**
	 * Set start frame
	 * @param start frame
	 */
	void setStartFrame(int32_t startFrame);

	/** 
	 * @return end frame
	 */
	int32_t getEndFrame();

	/**
	 * Set end frame
	 * @param end frame
	 */
	void setEndFrame(int32_t endFrame);

	/** 
	 * @return frames
	 */
	int32_t getFrames();

	/** 
	 * @return looping enabled
	 */
	bool isLoop();

	/** 
	 * Set loop
	 * @param loop
	 */
	bool setLoop(bool loop);

	/**
	 * If this is a overlay animation this returns a group id from which group the animation will start in the hierarchy
	 * @return group id from which the animation will start in the hierarchy
	 */
	const string& getOverlayFromGroupId();

	/**
	 * Set overlay from group id
	 * @param overlay from group id
	 */
	void setOverlayFromGroupId(const string& overlayFromGroupId);

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
	AnimationSetup(Model* model, const string& id, int32_t startFrame, int32_t endFrame, bool loop, const string& overlayFromGroupId);
};
