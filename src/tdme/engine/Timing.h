// Generated from /tdme/src/tdme/engine/Timing.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;


struct default_init_tag;

/** 
 * Timing
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::Timing final
	: public Object
{

public:
	typedef Object super;
	static constexpr int64_t UNDEFINED { -1LL };

private:
	int32_t frame {  };
	int64_t startTime {  };
	int64_t lastFrameAtTime {  };
	int64_t currentFrameAtTime {  };
	float currentFPS {  };
protected:

	/** 
	 * Public default constructor
	 */
	void ctor();

public: /* protected */

	/** 
	 * Updates timing
	 */
	void updateTiming();

public:

	/** 
	 * @return frames that have been rendered
	 */
	int32_t getFrame();

	/** 
	 * @return start time
	 */
	int64_t getStartTime();

	/** 
	 * @return time last frame has been rendered in ms
	 */
	int64_t getLastFrameAtTime();

	/** 
	 * @return time current frame has been rendered in ms
	 */
	int64_t getCurrentFrameAtTime();

	/** 
	 * Gets the time passed between last and current frame
	 * @return delta time
	 */
	int64_t getDeltaTime();

	/** 
	 * @return current fps
	 */
	float getCurrentFPS();

	/** 
	 * @return average fps
	 */
	float getAverageFPS();
	String* toString() override;

	// Generated

public: /* protected */
	Timing();
protected:
	Timing(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	void init();
	virtual ::java::lang::Class* getClass0();
};
