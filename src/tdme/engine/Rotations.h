// Generated from /tdme/src/tdme/engine/Rotations.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using tdme::engine::Rotation;
using tdme::math::Quaternion;
using tdme::utils::_ArrayList;


struct default_init_tag;

/** 
 * Rotations
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::Rotations final
	: public Object
{

public:
	typedef Object super;

public: /* protected */
	Quaternion* quaternion {  };
	_ArrayList* rotations {  };
protected:
	void ctor();

public:

	/** 
	 * @return number of rotations
	 */
	int32_t size();

	/** 
	 * Get rotation at given index
	 * @param index
	 * @return rotation
	 */
	Rotation* get(int32_t index);

	/** 
	 * Add rotation
	 * @param e
	 * @return
	 */
	void add(Rotation* rotation);

	/** 
	 * Set up a rotation at given index
	 * @param index
	 * @param element
	 * @return rotation
	 */
	void set(int32_t index, Rotation* rotation);

	/** 
	 * Remove rotation at given index
	 * @param index
	 * @return rotation
	 */
	Rotation* remove(int32_t index);

	/** 
	 * @return rotation quaternion
	 */
	Quaternion* getQuaternion();

	/** 
	 * Set up this transformations from given transformations
	 * @param transformations
	 */
	void fromRotations(Rotations* transformations);

	/** 
	 * Update rotation quaternion
	 */
	void update();
	String* toString() override;

	// Generated
	Rotations();
protected:
	Rotations(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
