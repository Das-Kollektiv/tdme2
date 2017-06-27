// Generated from /tdme/src/tdme/engine/subsystems/object/TransparentRenderPointsPool.java

#pragma once

#include <fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/subsystems/object/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using tdme::engine::model::Color4;
using tdme::math::Vector3;
using tdme::utils::_ArrayList;


struct default_init_tag;

/** 
 * Transparent render points pool
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::engine::subsystems::object::TransparentRenderPointsPool final
	: public Object
{

public:
	typedef Object super;

private:
	_ArrayList* transparentRenderPoints {  };
	int32_t poolIdx {  };
protected:

	/** 
	 * Default constructor
	 */
	void ctor(int32_t pointsMax);

public:

	/** 
	 * Creates an transparent render point entity in pool
	 * @param point
	 * @param color
	 */
	void addPoint(Vector3* point, Color4* color, float distanceFromCamera);

	/** 
	 * Merge another pool into this pool
	 * @param pool
	 */
	void merge(TransparentRenderPointsPool* pool2);

	/** 
	 * Reset
	 */
	void reset();

	/** 
	 * @return transparent render points vector
	 */
	_ArrayList* getTransparentRenderPoints();

	/** 
	 * Sort transparent render points
	 */
	void sort();

	// Generated
	TransparentRenderPointsPool(int32_t pointsMax);
protected:
	TransparentRenderPointsPool(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	void init();
	virtual ::java::lang::Class* getClass0();
};
