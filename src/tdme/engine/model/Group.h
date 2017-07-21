// Generated from /tdme/src/tdme/engine/model/Group.java

#pragma once

#include <map>
#include <string>
#include <vector>

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>

using std::map;
using std::vector;
using std::wstring;

using java::lang::Object;
using java::lang::String;
using tdme::engine::model::Animation;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Model;
using tdme::engine::model::Skinning;
using tdme::engine::model::TextureCoordinate;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace tdme {
namespace engine {
namespace model {
typedef ::SubArray< ::tdme::engine::model::FacesEntity, ::java::lang::ObjectArray > FacesEntityArray;
typedef ::SubArray< ::tdme::engine::model::TextureCoordinate, ::java::lang::ObjectArray > TextureCoordinateArray;
}  // namespace model
}  // namespace engine

namespace math {
typedef ::SubArray< ::tdme::math::Vector3, ::java::lang::ObjectArray > Vector3Array;
}  // namespace math
}  // namespace tdme

using java::lang::ObjectArray;
using tdme::engine::model::FacesEntityArray;
using tdme::engine::model::TextureCoordinateArray;
using tdme::math::Vector3Array;

struct default_init_tag;

/** 
 * 3d object group
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::engine::model::Group final
	: public Object
{

public:
	typedef Object super;

private:
	Model* model {  };
	Group* parentGroup {  };
	String* id {  };
	String* name {  };
	bool isJoint_ {  };
	Matrix4x4* transformationsMatrix {  };
	Vector3Array* vertices {  };
	Vector3Array* normals {  };
	TextureCoordinateArray* textureCoordinates {  };
	Vector3Array* tangents {  };
	Vector3Array* bitangents {  };
	Animation* animation {  };
	Skinning* skinning {  };
	FacesEntityArray* facesEntities {  };
	map<wstring, Group*> subGroups {  };
protected:

	/** 
	 * Public constructor
	 * @param model
	 * @param parent group 
	 * @param id
	 * @param name
	 */
	void ctor(Model* model, Group* parentGroup, String* id, String* name);

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
	String* getId();

	/** 
	 * @return group's name
	 */
	String* getName();

	/** 
	 * @return if this group is a joint/bone
	 */
	bool isJoint();

	/** 
	 * Sets up if this group is a joint or not 
	 * @param isbone
	 */
	void setJoint(bool isJoint);

	/** 
	 * @return transformations matrix related to parent group
	 */
	Matrix4x4* getTransformationsMatrix();

	/** 
	 * Set up vertices
	 * @param vertices
	 */
	void setVertices(const vector<Vector3*>& vertices);

	/** 
	 * @return vertices
	 */
	Vector3Array* getVertices();

	/** 
	 * Set vertices
	 * @param vertices
	 */
	void setVertices(Vector3Array* vertices);

	/** 
	 * @return normals
	 */
	Vector3Array* getNormals();

	/** 
	 * Set normals
	 * @param normals
	 */
	void setNormals(Vector3Array* normals);

	/** 
	 * Set up normals
	 * @param normals
	 */
	void setNormals(const vector<Vector3*>& normals);

	/** 
	 * @return texture coordinates or null (optional)
	 */
	TextureCoordinateArray* getTextureCoordinates();

	/** 
	 * Set texture coordinates
	 * @param texture coordinates
	 */
	void setTextureCoordinates(TextureCoordinateArray* textureCoordinates);

	/** 
	 * Set texture coordinates
	 * @param textureCoordinates
	 */
	void setTextureCoordinates(const vector<TextureCoordinate*>& textureCoordinates);

	/** 
	 * @return tangents
	 */
	Vector3Array* getTangents();

	/** 
	 * Set tangents
	 * @param tangents
	 */
	void setTangents(Vector3Array* tangents);

	/** 
	 * Set up tangents
	 * @param tangents
	 */
	void setTangents(const vector<Vector3*>& tangents);

	/** 
	 * @return bitangents
	 */
	Vector3Array* getBitangents();

	/** 
	 * Set bitangents
	 * @param bitangents
	 */
	void setBitangents(Vector3Array* bitangents);

	/** 
	 * Set up bitangents
	 * @param bitangents
	 */
	void setBitangents(const vector<Vector3*>& bitangents);

	/** 
	 * @return animation
	 */
	Animation* getAnimation();

	/** 
	 * Creates an empty animation object
	 * @param frames
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
	FacesEntityArray* getFacesEntities();

	/** 
	 * Set up faces entities
	 * @param faces entity
	 */
	void setFacesEntities(const vector<FacesEntity*>& facesEntities);

	/** 
	 * Set up faces entities
	 * @param faces entity
	 */
	void setFacesEntities(FacesEntityArray* facesEntities);

	/** 
	 * @return sub sub groups of this group
	 */
	map<wstring, Group*>* getSubGroups();

	/** 
	 * Returns a sub group by id
	 * @param groupId
	 * @return sub group or null
	 */
	Group* getSubGroupById(String* groupId);

	/** 
	 * Post set up faces
	 * TODO: move me into model helper
	 */
	void determineFeatures();

	/** 
	 * @return string representation
	 */
	String* toString() override;

	// Generated
	Group(Model* model, Group* parentGroup, String* id, String* name);
protected:
	Group(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
