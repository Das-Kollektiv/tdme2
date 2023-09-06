#pragma once

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Node.h>

using std::string;
using std::vector;

using tdme::engine::model::Face;
using tdme::engine::model::Material;
using tdme::engine::model::Node;

/**
 * Node faces entity
 * A node can have multiple entities containing faces and a applied material
 * @author Andreas Drewke
 */
class tdme::engine::model::FacesEntity final
{
private:
	string id;
	Node* node;
	Material* material;
	vector<Face> faces;
	bool textureCoordinatesAvailable;
	bool tangentBitangentAvailable;
	vector<int32_t> lod1Indices;
	vector<int32_t> lod2Indices;
	vector<int32_t> lod3Indices;
	float lod1Distance;
	float lod2Distance;
	float lod3Distance;

	/**
	 * Determine features
	 */
	void determineFeatures();

public:
	/**
	 * Public constructor
	 */
	FacesEntity();

	/**
	 * Public constructor
	 * @param node node
	 * @param id id
	 */
	FacesEntity(Node* node, const string& id);

	/**
	 * @return faces entity id
	 */
	inline const string& getId() const {
		return id;
	}

	/**
	 * Set up the entity's material
	 * @param material material
	 */
	inline void setMaterial(Material* material) {
		this->material = material;
	}

	/**
	 * @return entity's material
	 */
	inline const Material* getMaterial() const {
		return material;
	}

	/**
	 * @return entity's faces
	 */
	inline const vector<Face>& getFaces() const {
		return faces;
	}

	/**
	 * Set up entity's faces
	 * @param faces faces
	 */
	void setFaces(const vector<Face>& faces);

	/**
	 * @return if texture coordinates are available for the whole entity
	 */
	inline bool isTextureCoordinatesAvailable() const {
		return textureCoordinatesAvailable == true && node->getTextureCoordinates().size() > 0;
	}

	/**
	 * @return if tangents and bitangents are available for the whole entity
	 */
	inline bool isTangentBitangentAvailable() const {
		return tangentBitangentAvailable == true && node->getTangents().size() > 0 && node->getBitangents().size() > 0;
	}

	/**
	 * @return LOD1 distance
	 */
	inline float getLOD1Distance() const {
		return lod1Distance;
	}

	/**
	 * Set LOD1 distance
	 * @param lod1Distance LOD1 distance
	 */
	inline void setLOD1Distance(float lod1Distance) {
		this->lod1Distance = lod1Distance;
	}

	/**
	 * @return LOD1 indices
	 */
	inline const vector<int32_t>& getLOD1Indices() const {
		return lod1Indices;
	}

	/**
	 * Set LOD1 indices
	 * @param lod1Indices lod1 indices
	 */
	void setLOD1Indices(const vector<int32_t>& lod1Indices);

	/**
	 * @return LOD2 distance
	 */
	inline float getLOD2Distance() const {
		return lod2Distance;
	}

	/**
	 * Set LOD2 distance
	 * @param lod2Distance LOD2 distance
	 */
	inline void setLOD2Distance(float lod2Distance) {
		this->lod2Distance = lod2Distance;
	}

	/**
	 * @return LOD2 indices
	 */
	inline const vector<int32_t>& getLOD2Indices() const {
		return lod2Indices;
	}

	/**
	 * Set LOD2 indices
	 * @param lod1Indices lod1 indices
	 */
	void setLOD2Indices(const vector<int32_t>& lod2Indices);

	/**
	 * @return LOD3 distance
	 */
	inline float getLOD3Distance() const {
		return lod3Distance;
	}

	/**
	 * Set LOD3 distance
	 * @param lod3Distance LOD1 distance
	 */
	inline void setLOD3Distance(float lod3Distance) {
		this->lod3Distance = lod3Distance;
	}

	/**
	 * @return LOD3 indices
	 */
	inline const vector<int32_t>& getLOD3Indices() const {
		return lod3Indices;
	}

	/**
	 * Set LOD3 indices
	 * @param lod3Indices lod3 indices
	 */
	void setLOD3Indices(const vector<int32_t>& lod3Indices);

};
