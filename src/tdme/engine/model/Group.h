#pragma once

#include <map>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/utils/fwd-tdme.h>

using std::map;
using std::vector;
using std::string;

using tdme::engine::model::Animation;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Model;
using tdme::engine::model::Skinning;
using tdme::engine::model::TextureCoordinate;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

/** 
 * Model group
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::engine::model::Group final
{
private:
	Model* model {  };
	Group* parentGroup {  };
	string id {  };
	string name {  };
	bool isJoint_ {  };
	Matrix4x4 transformationsMatrix {  };
	vector<Vector3> vertices;
	vector<Vector3> normals;
	vector<TextureCoordinate> textureCoordinates;
	vector<Vector3> tangents;
	vector<Vector3> bitangents;
	Animation* animation {  };
	Skinning* skinning {  };
	vector<FacesEntity> facesEntities;
	map<string, Group*> subGroups {  };
public:
	/** 
	 * @return model
	 */
	Model* getModel();

	/** 
	 * @return parent group
	 */
	Group* getParentGroup();

	/** 
	 * Returns id
	 * @return id
	 */
	const string& getId();

	/** 
	 * @return group's name
	 */
	const string& getName();

	/** 
	 * @return if this group is a joint/bone
	 */
	bool isJoint();

	/** 
	 * Sets up if this group is a joint or not 
	 * @param isJoint isbone
	 */
	void setJoint(bool isJoint);

	/** 
	 * @return transformations matrix related to parent group
	 */
	Matrix4x4& getTransformationsMatrix();

	/** 
	 * @return vertices
	 */
	vector<Vector3>* getVertices();

	/** 
	 * Set vertices
	 * @param vertices vertices
	 */
	void setVertices(const vector<Vector3>& vertices);

	/** 
	 * @return normals
	 */
	vector<Vector3>* getNormals();

	/** 
	 * Set normals
	 * @param normals normals
	 */
	void setNormals(const vector<Vector3>& normals);

	/** 
	 * @return texture coordinates or null (optional)
	 */
	vector<TextureCoordinate>* getTextureCoordinates();

	/** 
	 * Set texture coordinates
	 * @param textureCoordinates texture coordinates
	 */
	void setTextureCoordinates(const vector<TextureCoordinate>& textureCoordinates);

	/** 
	 * @return tangents
	 */
	vector<Vector3>* getTangents();

	/** 
	 * Set tangents
	 * @param tangents tangents
	 */
	void setTangents(const vector<Vector3>& tangents);

	/** 
	 * @return bitangents
	 */
	vector<Vector3>* getBitangents();

	/** 
	 * Set bitangents
	 * @param bitangents bitangents
	 */
	void setBitangents(const vector<Vector3>& bitangents);

	/** 
	 * @return animation
	 */
	Animation* getAnimation();

	/** 
	 * Creates an empty animation object
	 * @param frames frames
	 * @return animation
	 */
	Animation* createAnimation(int32_t frames);

	/** 
	 * @return skinning or null
	 */
	Skinning* getSkinning();

	/** 
	 * Creates an empty skinning object
	 * @return skinning
	 */
	Skinning* createSkinning();

	/** 
	 * @return number of faces in group
	 */
	int32_t getFaceCount();

	/** 
	 * @return faces entities
	 */
	vector<FacesEntity>* getFacesEntities();

	/** 
	 * Set up faces entities
	 * @param facesEntities faces entity
	 */
	void setFacesEntities(const vector<FacesEntity>& facesEntities);

	/** 
	 * @return sub sub groups of this group
	 */
	map<string, Group*>* getSubGroups();

	/** 
	 * Returns a sub group by id
	 * @param groupId groupId
	 * @return sub group or null
	 */
	Group* getSubGroupById(const string& groupId);

	/** 
	 * Post set up faces
	 * TODO: move me into model helper
	 */
	void determineFeatures();

	/**
	 * Public constructor
	 * @param model model
	 * @param parentGroup parent group
	 * @param id id
	 * @param name name
	 */
	Group(Model* model, Group* parentGroup, const string& id, const string& name);

	/**
	 * Destructor
	 */
	~Group();
};
