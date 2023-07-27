#pragma once

#include <map>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/utilities/fwd-tdme.h>

using std::map;
using std::string;
using std::vector;

using tdme::engine::model::Animation;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Model;
using tdme::engine::model::Skinning;
using tdme::engine::model::TextureCoordinate;
using tdme::math::Matrix4x4;
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
	vector<TextureCoordinate> textureCoordinates;
	vector<Vector3> tangents;
	vector<Vector3> bitangents;
	Animation* animation;
	Skinning* skinning;
	vector<FacesEntity> facesEntities;
	vector<Vector3> origins;
	map<string, Node*> subNodes;

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
	 * @return model
	 */
	inline Model* getModel() {
		return model;
	}

	/**
	 * @return parent node
	 */
	inline Node* getParentNode() {
		return parentNode;
	}

	/**
	 * Returns id
	 * @return id
	 */
	inline const string& getId() {
		return id;
	}

	/**
	 * @return node's name
	 */
	inline const string& getName() {
		return name;
	}

	/**
	 * @return if this node is empty
	 */
	inline bool isEmpty() const {
		return vertices.empty() == true;
	}

	/**
	 * @return if this node is a joint/bone
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
	 * @return transform matrix related to parent node
	 */
	inline const Matrix4x4& getTransformMatrix() const {
		return transformMatrix;
	}

	/**
	 * @return transform matrix related to parent node
	 */
	inline void setTransformMatrix(const Matrix4x4& transformMatrix) {
		this->transformMatrix = transformMatrix;
	}

	/**
	 * @return if vertices or normals have been changed
	 */
	inline bool hasUpdate() {
		return verticesUpdated == true || normalsUpdated == true;
	}

	/**
	 * @return if vertices have been updated
	 */
	inline bool hasVerticesUpdate() {
		auto updated = verticesUpdated;
		verticesUpdated = false;
		return updated;
	}

	/**
	 * @return vertices
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
	 * @return if normals have been updated
	 */
	inline bool hasNormalsUpdate() {
		auto updated = normalsUpdated;
		normalsUpdated = false;
		return updated;
	}

	/**
	 * @return normals
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
	 * @return texture coordinates or null (optional)
	 */
	inline const vector<TextureCoordinate>& getTextureCoordinates() const {
		return textureCoordinates;
	}

	/**
	 * Set texture coordinates
	 * @param textureCoordinates texture coordinates
	 */
	void setTextureCoordinates(const vector<TextureCoordinate>& textureCoordinates);

	/**
	 * @return tangents
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
	 * @return bitangents
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
	 * @return animation
	 */
	inline Animation* getAnimation() {
		return animation;
	}

	/**
	 * Sets animation object
	 * @param animation animation
	 */
	void setAnimation(Animation* animation);

	/**
	 * @return skinning or null
	 */
	inline Skinning* getSkinning() {
		return skinning;
	}

	/**
	 * Sets skinning object
	 * @param skinning skinning
	 */
	void setSkinning(Skinning* skinning);

	/**
	 * @return number of faces in node
	 */
	int32_t getFaceCount() const;

	/**
	 * @return faces entities
	 */
	inline const vector<FacesEntity>& getFacesEntities() const {
		return facesEntities;
	}

	/**
	 * Find faces entity by id
	 * @param id id
	 * @return faces entity
	 */
	FacesEntity* getFacesEntity(const string& id);

	/**
	 * Set up faces entities
	 * @param facesEntities faces entity
	 */
	void setFacesEntities(const vector<FacesEntity>& facesEntities);

	/**
	 * @return origins
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
	 * @return sub sub nodes of this node
	 */
	inline map<string, Node*>& getSubNodes() {
		return subNodes;
	}

	/**
	 * Returns a sub node by id
	 * @param nodeId nodeId
	 * @return sub node or null
	 */
	Node* getSubNodeById(const string& nodeId);
};
