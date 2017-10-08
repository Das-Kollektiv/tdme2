
#pragma once

#include <map>
#include <string>
#include <vector>

#include <tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Joint.h>
#include <tdme/engine/model/JointWeight.h>
#include <tdme/utils/fwd-tdme.h>

using std::map;
using std::wstring;
using std::vector;

using tdme::engine::model::Joint;
using tdme::engine::model::JointWeight;

/** 
 * Skinning definition for groups
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::engine::model::Skinning final
{
private:
	vector<float> weights {  };
	vector<Joint> joints {  };
	vector<vector<JointWeight>> verticesJointsWeights {  };
	map<wstring, Joint*> jointsByName {  };
public:

	/** 
	 * @return weights
	 */
	vector<float>* getWeights();


	/** 
	 * Set up weights
	 * @param weights
	 */
	void setWeights(const vector<float>& weights);

	/** 
	 * @return all joints
	 */
	vector<Joint>* getJoints();

	/** 
	 * Set up joints
	 * @param joints
	 */
	void setJoints(const vector<Joint>* joints);

	/** 
	 * @return all vertex joints
	 */
	vector<vector<JointWeight>>* getVerticesJointsWeights();

	/** 
	 * Sets up vertices joints weights 
	 * @param verticesJointsWeights
	 */
	void setVerticesJointsWeights(const vector<vector<JointWeight>>* verticesJointsWeights);

	/** 
	 * Get joint by name
	 * @param name
	 * @return joint
	 */
	Joint* getJointByName(const wstring& name);

	/**
	 * Public constructor
	 */
	Skinning();
private:

	/**
	 * Set up joints by name
	 */
	void setupJointsByName();
};
