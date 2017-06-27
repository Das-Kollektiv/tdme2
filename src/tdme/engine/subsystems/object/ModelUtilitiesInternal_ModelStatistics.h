// Generated from /tdme/src/tdme/engine/subsystems/object/ModelUtilitiesInternal.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/subsystems/object/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using tdme::engine::subsystems::object::ModelUtilitiesInternal;


struct default_init_tag;

/** 
 * Model statistics class
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::object::ModelUtilitiesInternal_ModelStatistics
	: public virtual Object
{

public:
	typedef Object super;

private:
	int32_t opaqueFaceCount {  };
	int32_t transparentFaceCount {  };
	int32_t materialCount {  };
protected:

	/** 
	 * Constructor
	 * @param solid face count
	 * @param transparent face count
	 * @param material count
	 */
	void ctor(int32_t opaqueFaceCount, int32_t transparentFaceCount, int32_t materialCount);

public:

	/** 
	 * @return opaque face count
	 */
	virtual int32_t getOpaqueFaceCount();

	/** 
	 * @return transparent face count
	 */
	virtual int32_t getTransparentFaceCount();

	/** 
	 * @return material count
	 */
	virtual int32_t getMaterialCount();
	String* toString() override;

	// Generated
	ModelUtilitiesInternal_ModelStatistics(int32_t opaqueFaceCount, int32_t transparentFaceCount, int32_t materialCount);
protected:
	ModelUtilitiesInternal_ModelStatistics(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
	friend class ModelUtilitiesInternal;
};
