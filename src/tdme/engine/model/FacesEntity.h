#pragma once

#include <string>
#include <vector>

#include <tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>

using std::vector;
using std::string;

using tdme::engine::model::Face;
using tdme::engine::model::Group;
using tdme::engine::model::Material;

/** 
 * Group faces entity
 * A group can have multiple entities containing faces and a applied material
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::model::FacesEntity final
{
private:
	string id {  };
	Group* group {  };
	Material* material {  };
	vector<Face> faces {  };
	bool textureCoordinatesAvailable {  };
	bool tangentBitangentAvailable {  };
public:

	/** 
	 * @return faces entity id
	 */
	const string& getId();

	/** 
	 * Set up the entity's material
	 * @param material
	 */
	void setMaterial(Material* material);

	/** 
	 * @return entity's material
	 */
	Material* getMaterial();

	/** 
	 * @return entity's faces
	 */
	vector<Face>* getFaces();

	/** 
	 * Set up entity's faces
	 * @param faces
	 */
	void setFaces(const vector<Face>* faces);

	/** 
	 * Post set up faces
	 */
	void determineFeatures();

	/** 
	 * @return if texture coordinates are available for the whole entity
	 */
	bool isTextureCoordinatesAvailable();

	/** 
	 * @return if tangents and bitangents are available for the whole entity
	 */
	bool isTangentBitangentAvailable();

	/**
	 * Public constructor
	 */
	FacesEntity();

	/**
	 * Public constructor
	 * @param group
	 * @param id
	 */
	FacesEntity(Group* group, const string& id);
};
