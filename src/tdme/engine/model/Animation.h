// Generated from /tdme/src/tdme/engine/model/Animation.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using tdme::math::Matrix4x4;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace tdme {
namespace math {
typedef ::SubArray< ::tdme::math::Matrix4x4, ::java::lang::ObjectArray > Matrix4x4Array;
}  // namespace math
}  // namespace tdme

using java::lang::ObjectArray;
using tdme::math::Matrix4x4Array;

struct default_init_tag;

/** 
 * AnimationSetup
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::engine::model::Animation final
	: public Object
{

public:
	typedef Object super;

private:
	int32_t frames {  };
	Matrix4x4Array* transformationsMatrices {  };
protected:

	/** 
	 * Public constructor
	 * @param frames
	 */
	void ctor(int32_t frames);

public:

	/** 
	 * @return number of frames
	 */
	int32_t getFrames();

	/** 
	 * Returns transformation matrices
	 * @return transformation matrices
	 */
	Matrix4x4Array* getTransformationsMatrices();

	/** 
	 * @return string representation
	 */
	String* toString() override;

	// Generated
	Animation(int32_t frames);
protected:
	Animation(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
