// Generated from /tdme/src/tdme/engine/model/Joint.java

#pragma once

#include <string>

#include <java/lang/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using tdme::math::Matrix4x4;

using std::wstring;

struct default_init_tag;

/** 
 * Joint / Bone
 * @author andreas.drewke
 */
class tdme::engine::model::Joint final
	: public Object
{

public:
	typedef Object super;

private:
	wstring groupId {  };
	Matrix4x4* bindMatrix {  };
protected:

	/** 
	 * Public constructor
	 * @param group id
	 * @param bind matrix
	 */
	void ctor(const wstring& groupId);

public:

	/** 
	 * Associated group or bone id
	 * @return group id
	 */
	const wstring& getGroupId();

	/** 
	 * Bind matrix
	 * @return matrix
	 */
	Matrix4x4* getBindMatrix();

	/** 
	 * @return string representation
	 */
	String* toString() override;

	// Generated
	Joint(const wstring& groupId);
protected:
	Joint(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
