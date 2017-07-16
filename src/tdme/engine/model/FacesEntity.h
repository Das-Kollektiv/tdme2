// Generated from /tdme/src/tdme/engine/model/FacesEntity.java

#pragma once

#include <vector>

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>

using std::vector;

using java::lang::Object;
using java::lang::String;
using tdme::engine::model::Face;
using tdme::engine::model::Group;
using tdme::engine::model::Material;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace tdme {
namespace engine {
namespace model {
typedef ::SubArray< ::tdme::engine::model::Face, ::java::lang::ObjectArray > FaceArray;
}  // namespace model
}  // namespace engine
}  // namespace tdme

using java::lang::ObjectArray;
using tdme::engine::model::FaceArray;

struct default_init_tag;

/** 
 * Group faces entity
 * A group can have multiple entities containing faces and a applied material
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::model::FacesEntity final
	: public Object
{

public:
	typedef Object super;

private:
	String* id {  };
	Group* group {  };
	Material* material {  };
	FaceArray* faces {  };
	bool textureCoordinatesAvailable {  };
	bool tangentBitangentAvailable {  };
protected:

	/** 
	 * Public constructor
	 * @param id 
	 * @param group
	 */
	void ctor(Group* group, String* id);

public:

	/** 
	 * @return faces entity id
	 */
	String* getId();

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
	FaceArray* getFaces();

	/** 
	 * Set up entity's faces
	 * @param faces
	 */
	void setFaces(const vector<Face*>& faces);

	/** 
	 * Set up entity's faces
	 * @param faces
	 */
	void setFaces(FaceArray* faces);

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
	 * @return string representation
	 */
	String* toString() override;

	// Generated
	FacesEntity(Group* group, String* id);
protected:
	FacesEntity(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
