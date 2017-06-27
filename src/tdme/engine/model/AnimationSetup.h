// Generated from /tdme/src/tdme/engine/model/AnimationSetup.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using tdme::engine::model::Model;


struct default_init_tag;

/** 
 * AnimationSetup
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::model::AnimationSetup final
	: public Object
{

public:
	typedef Object super;

private:
	Model* model {  };
	String* id {  };
	int32_t startFrame {  };
	int32_t endFrame {  };
	int32_t frames {  };
	bool loop {  };
	String* overlayFromGroupId {  };
protected:

	/** 
	 * Public constructor
	 * @param model
	 * @param id
	 * @param start frame
	 * @param end frame
	 * @param loop
	 * @param overlay from group id / optional 
	 */
	void ctor(Model* model, String* id, int32_t startFrame, int32_t endFrame, bool loop, String* overlayFromGroupId);

public:

	/** 
	 * @return model this animation belongs to
	 */
	Model* getModel();

	/** 
	 * @return id
	 */
	String* getId();

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
	String* getOverlayFromGroupId();

	/** 
	 * @return animation duration in milliseconds
	 */
	int64_t computeDuration();

	/** 
	 * @param frames
	 * @return animation duration in milliseconds
	 */
	int64_t computeDuration(int32_t startFrame, int32_t endFrame);
	String* toString() override;

	// Generated
	AnimationSetup(Model* model, String* id, int32_t startFrame, int32_t endFrame, bool loop, String* overlayFromGroupId);
protected:
	AnimationSetup(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
