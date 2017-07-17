// Generated from /tdme/src/tdme/engine/subsystems/object/Object3DGroup.java

#pragma once

#include <vector>

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/subsystems/object/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>

using std::vector;

using java::lang::Object;
using java::lang::String;
using tdme::engine::Engine_AnimationProcessingTarget;
using tdme::engine::model::Group;
using tdme::engine::subsystems::object::Object3DBase;
using tdme::engine::subsystems::object::Object3DGroupMesh;
using tdme::engine::subsystems::object::Object3DGroupVBORenderer;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Matrix4x4;
using tdme::utils::_HashMap;
using tdme::engine::subsystems::object::Object3DGroup;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace tdme {
namespace engine {
namespace subsystems {
namespace object {
typedef ::SubArray< ::tdme::engine::subsystems::object::Object3DGroup, ::java::lang::ObjectArray > Object3DGroupArray;
}  // namespace object
}  // namespace subsystems
}  // namespace engine
}  // namespace tdme

using java::lang::ObjectArray;
using tdme::engine::subsystems::object::Object3DGroupArray;

struct default_init_tag;

/** 
 * Object 3d render group 
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::object::Object3DGroup final
	: public Object
{

public:
	typedef Object super;

private:
	static int64_t counter;

public: /* protected */
	static constexpr int32_t GLTEXTUREID_NONE { -1 };
	static constexpr int32_t GLTEXTUREID_NOTUSED { 0 };
	String* id {  };
	Object3DBase* object {  };
	Group* group {  };
	bool animated {  };
	int32_tArray* materialDiffuseTextureIdsByEntities {  };
	int32_tArray* dynamicDiffuseTextureIdsByEntities {  };
	int32_tArray* materialSpecularTextureIdsByEntities {  };
	int32_tArray* materialDisplacementTextureIdsByEntities {  };
	int32_tArray* materialNormalTextureIdsByEntities {  };
	Object3DGroupVBORenderer* renderer {  };
	Object3DGroupMesh* mesh {  };
	Matrix4x4* groupTransformationsMatrix {  };

	/** 
	 * Creates object 3d groups from given object3d base object
	 * @param object 3d base
	 * @param use mesh manager
	 * @return object 3d group array
	 */
	static Object3DGroupArray* createGroups(Object3DBase* object, bool useMeshManager, Engine_AnimationProcessingTarget* animationProcessingTarget);

private:

	/** 
	 * Creates a object 3d groups recursively for given group and it sub groups
	 * @param object 3D base
	 * @param object 3D groups
	 * @param groups
	 * @param animated
	 * @param use mesh manager
	 */
	static void createGroups(Object3DBase* object3D, vector<Object3DGroup*>& object3DGroups, _HashMap* groups, bool animated, bool useMeshManager, Engine_AnimationProcessingTarget* animationProcessingTarget);

public: /* protected */

	/** 
	 * Applies transformations to meshes for given object 3d groups
	 * @param group render data list
	 * @param transformation matrices
	 */
	static void computeTransformations(Object3DGroupArray* object3DGroups, _HashMap* transformationMatrices);

	/** 
	 * Set up textures for given object3d group and faces entity
	 * @param renderer
	 * @param object 3D group
	 * @param faces entity idx
	 */
	static void setupTextures(GLRenderer* renderer, Object3DGroup* object3DGroup, int32_t facesEntityIdx);

	/** 
	 * Dispose
	 */
	void dispose();

	// Generated

public:
	Object3DGroup();
protected:
	void ctor();
	Object3DGroup(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static void clinit();

private:
	void init();
	virtual ::java::lang::Class* getClass0();
};
