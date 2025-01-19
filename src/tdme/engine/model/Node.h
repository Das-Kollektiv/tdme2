#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector2.h>
#include <tdme/math/Vector3.h>

using std::string;
using std::unique_ptr;
using std::unordered_map;
using std::vector;

using tdme::engine::model::Animation;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Model;
using tdme::engine::model::Skinning;
using tdme::math::Matrix4x4;
using tdme::math::Vector2;
using tdme::math::Vector3;

/**
 * Model node
 * @author andreas.drewke
 */
class tdme::engine::model::Node final
{
private:
	Model* model;
	Node* parentNode;
	string id;
	string name;
	bool joint;
	Matrix4x4 transformMatrix;
	vector<Vector3> vertices;
	vector<Vector3> normals;
	vector<Vector2> textureCoordinates;
	vector<Vector3> tangents;
	vector<Vector3> bitangents;
	unique_ptr<Animation> animation;
	unique_ptr<Skinning> skinning;
	vector<FacesEntity> facesEntities;
	vector<Vector3> origins;
	unordered_map<string, Node*> subNodes;

	bool verticesUpdated;
	bool normalsUpdated;
public:
	// forbid class copy
	FORBID_CLASS_COPY(Node)

	/**
	 * Public constructor
	 * @param model model
	 * @param parentNode parent node
	 * @param id id
	 * @param name name
	 */
	Node(Model* model, Node* parentNode, const string& id, const string& name);

	/**
	 * Destructor
	 */
	~Node();

	/**
	 * @returns model
	 */
	inline Model* getModel() {
		return model;
	}

	/**
	 * @returns parent node
	 */
	inline Node* getParentNode() {
		return parentNode;
	}

	/**
	 * Returns id
	 * @returns id
	 */
	inline const string& getId() {
		return id;
	}

	/**
	 * @returns node's name
	 */
	inline const string& getName() {
		return name;
	}

	/**
	 * @returns if this node is empty
	 */
	inline bool isEmpty() const {
		return vertices.empty() == true;
	}

	/**
	 * @returns if this node is a joint/bone
	 */
	inline bool isJoint() const {
		return joint;
	}

	/**
	 * Sets up if this node is a joint or not
	 * @param isJoint isbone
	 */
	inline void setJoint(bool isJoint) {
		joint = isJoint;
	}

	/**
	 * @returns transform matrix related to parent node
	 */
	inline const Matrix4x4& getTransformMatrix() const {
		return transformMatrix;
	}

	/**
	 * @returns transform matrix related to parent node
	 */
	inline void setTransformMatrix(const Matrix4x4& transformMatrix) {
		this->transformMatrix = transformMatrix;
	}

	/**
	 * @returns if vertices or normals have been changed
	 */
	inline bool hasUpdate() {
		return verticesUpdated == true || normalsUpdated == true;
	}

	/**
	 * @returns if vertices have been updated
	 */
	inline bool hasVerticesUpdate() {
		auto updated = verticesUpdated;
		verticesUpdated = false;
		return updated;
	}

	/**
	 * @returns vertices
	 */
	inline const vector<Vector3>& getVertices() const {
		return vertices;
	}

	/**
	 * Set vertices
	 * @param vertices vertices
	 */
	void setVertices(const vector<Vector3>& vertices);

	/**
	 * @returns if normals have been updated
	 */
	inline bool hasNormalsUpdate() {
		auto updated = normalsUpdated;
		normalsUpdated = false;
		return updated;
	}

	/**
	 * @returns normals
	 */
	inline const vector<Vector3>& getNormals() const {
		return normals;
	}

	/**
	 * Set normals
	 * @param normals normals
	 */
	void setNormals(const vector<Vector3>& normals);

	/**
	 * @returns texture coordinates or null (optional)
	 */
	inline const vector<Vector2>& getTextureCoordinates() const {
		return textureCoordinates;
	}

	/**
	 * Set texture coordinates
	 * @param textureCoordinates texture coordinates
	 */
	void setTextureCoordinates(const vector<Vector2>& textureCoordinates);

	/**
	 * @returns tangents
	 */
	inline const vector<Vector3>& getTangents() const {
		return tangents;
	}

	/**
	 * Set tangents
	 * @param tangents tangents
	 */
	void setTangents(const vector<Vector3>& tangents);

	/**
	 * @returns bitangents
	 */
	inline const vector<Vector3>& getBitangents() const {
		return bitangents;
	}

	/**
	 * Set bitangents
	 * @param bitangents bitangents
	 */
	void setBitangents(const vector<Vector3>& bitangents);

	/**
	 * @returns animation
	 */
	inline Animation* getAnimation() {
		return animation.get();
	}

	/**
	 * Sets animation object
	 * @param animation animation
	 */
	void setAnimation(Animation* animation);

	/**
	 * @returns skinning or null
	 */
	inline Skinning* getSkinning() {
		return skinning.get();
	}

	/**
	 * Sets skinning object
	 * @param skinning skinning
	 */
	void setSkinning(Skinning* skinning);

	/**
	 * @returns number of faces in node
	 */
	int32_t getFaceCount() const;

	/**
	 * @returns faces entities
	 */
	inline const vector<FacesEntity>& getFacesEntities() const {
		return facesEntities;
	}

	/**
	 * Find faces entity by id
	 * @param id id
	 * @returns faces entity
	 */
	FacesEntity* getFacesEntity(const string& id);

	/**
	 * Set up faces entities
	 * @param facesEntities faces entity
	 */
	void setFacesEntities(const vector<FacesEntity>& facesEntities);

	/**
	 * @returns origins
	 */
	inline const vector<Vector3>& getOrigins() const {
		return origins;
	}

	/**
	 * Set origins
	 * @param origins render node object origins
	 */
	void setOrigins(const vector<Vector3>& origins);

	/**
	 * @returns sub sub nodes of this node
	 */
	inline unordered_map<string, Node*>& getSubNodes() {
		return subNodes;
	}

};
