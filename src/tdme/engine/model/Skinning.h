// Generated from /tdme/src/tdme/engine/model/Skinning.java

#pragma once

#include <map>
#include <string>
#include <vector>

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>

using std::map;
using std::wstring;
using std::vector;

using java::lang::Object;
using java::io::Serializable;
using java::lang::Cloneable;
using java::lang::String;
using tdme::engine::model::Joint;
using tdme::engine::model::JointWeight;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::Cloneable, ObjectArray > CloneableArray;
}  // namespace lang
}  // namespace java

namespace tdme {
namespace engine {
namespace model {
typedef ::SubArray< ::tdme::engine::model::Joint, ::java::lang::ObjectArray > JointArray;
typedef ::SubArray< ::tdme::engine::model::JointWeight, ::java::lang::ObjectArray > JointWeightArray;
typedef ::SubArray< ::tdme::engine::model::JointWeightArray, ::java::lang::CloneableArray, ::java::io::SerializableArray > JointWeightArrayArray;
}  // namespace model
}  // namespace engine
}  // namespace tdme

using java::io::SerializableArray;
using java::lang::CloneableArray;
using java::lang::ObjectArray;
using tdme::engine::model::JointArray;
using tdme::engine::model::JointWeightArray;
using tdme::engine::model::JointWeightArrayArray;

struct default_init_tag;

/** 
 * Skinning definition for groups
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::engine::model::Skinning final
	: public Object
{

public:
	typedef Object super;

private:
	floatArray* weights {  };
	JointArray* joints {  };
	JointWeightArrayArray* verticesJointsWeights {  };
	map<wstring, Joint*> jointsByName {  };
protected:

	/** 
	 * Public constructor
	 */
	void ctor();

public:

	/** 
	 * @return weights
	 */
	floatArray* getWeights();

	/** 
	 * Set up weights
	 * @param weights
	 */
	void setWeights(floatArray* weights);

	/** 
	 * Set up weights
	 * @param weights
	 */
	void setWeights(const vector<float>& weights);

	/** 
	 * @return all joints
	 */
	JointArray* getJoints();

	/** 
	 * Set up joints
	 * @param joints
	 */
	void setJoints(JointArray* joints);

	/** 
	 * Set up joints
	 * @param joints
	 */
	void setJoints(const vector<Joint*>& joints);

	/** 
	 * @return all vertex joints
	 */
	JointWeightArrayArray* getVerticesJointsWeights();

	/** 
	 * Set vertices joints weight
	 * @param verticesJointsWeights
	 */
	void setVerticesJointsWeights(JointWeightArrayArray* verticesJointsWeights);

	/** 
	 * Sets up vertices joints weights 
	 * @param verticesJointsWeights
	 */
	void setVerticesJointsWeights(const vector<vector<JointWeight*>>& verticesJointsWeights);

private:

	/** 
	 * Set up joints by name
	 */
	void setupJointsByName();

public:

	/** 
	 * Get joint by name
	 * @param name
	 * @return joint
	 */
	Joint* getJointByName(String* name);

	/** 
	 * @return string representation
	 */
	String* toString() override;

	// Generated
	Skinning();
protected:
	Skinning(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
