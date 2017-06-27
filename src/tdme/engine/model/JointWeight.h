// Generated from /tdme/src/tdme/engine/model/JointWeight.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;


struct default_init_tag;

/** 
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::engine::model::JointWeight final
	: public Object
{

public:
	typedef Object super;

private:
	int32_t jointIndex {  };
	int32_t weightIndex {  };
protected:

	/** 
	 * Public constructor
	 * @param joint index
	 * @param weight index
	 */
	void ctor(int32_t jointIndex, int32_t weightIndex);

public:

	/** 
	 * @returns joint index
	 */
	int32_t getJointIndex();

	/** 
	 * @returns weight index
	 */
	int32_t getWeightIndex();

	/** 
	 * @return string representation
	 */
	String* toString() override;

	// Generated
	JointWeight(int32_t jointIndex, int32_t weightIndex);
protected:
	JointWeight(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
