// Generated from /tdme/src/tdme/engine/subsystems/object/Object3DVBORenderer.java

#pragma once

#include <fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/subsystems/object/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using tdme::engine::Engine;
using tdme::engine::model::Color4;
using tdme::engine::subsystems::object::BatchVBORendererPoints;
using tdme::engine::subsystems::object::BatchVBORendererTriangles;
using tdme::engine::subsystems::object::Object3DGroup;
using tdme::engine::subsystems::object::TransparentRenderFacesPool;
using tdme::engine::subsystems::object::TransparentRenderPointsPool;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Matrix4x4;
using tdme::math::Matrix4x4Negative;
using tdme::math::Vector3;
using tdme::utils::Key;
using tdme::utils::Pool;
using tdme::utils::_ArrayList;
using tdme::utils::_HashMap;


struct default_init_tag;

/** 
 * VBO renderer class
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::object::Object3DVBORenderer final
	: public Object
{

public:
	typedef Object super;

private:
	static constexpr int32_t BATCHVBORENDERER_MAX { 256 };

public: /* protected */
	Engine* engine {  };
	GLRenderer* renderer {  };
	_ArrayList* trianglesBatchVBORenderers {  };

private:
	_HashMap* visibleObjectsByModels {  };
	Pool* keyPool {  };
	_ArrayList* groupTransparentRenderFaces {  };
	Pool* transparentRenderFacesGroupPool {  };
	TransparentRenderFacesPool* transparentRenderFacesPool {  };
	_HashMap* transparentRenderFacesGroups {  };
	Pool* pseKeyPool {  };
	_ArrayList* pseKeys {  };
	TransparentRenderPointsPool* pseTransparentRenderPointsPool {  };
	BatchVBORendererPoints* psePointBatchVBORenderer {  };
	Matrix4x4* modelViewMatrixBackup {  };
	Matrix4x4* modelViewMatrix {  };
	Vector3* transformedVertex {  };
	Vector3* transformedNormal {  };
	Matrix4x4Negative* matrix4x4Negative {  };
protected:

	/** 
	 * Public constructor 
	 * @param renderer
	 */
	void ctor(Engine* engine, GLRenderer* renderer);

public:

	/** 
	 * Init
	 */
	void initialize();

	/** 
	 * Dispose
	 */
	void dispose();

	/** 
	 * @return batch vbo renderer for triangles
	 */
	BatchVBORendererTriangles* acquireTrianglesBatchVBORenderer();

	/** 
	 * Resets the object 3d vbo renderer
	 */
	void reset();

	/** 
	 * Renders all given objects
	 * @param objects
	 * @param render transparent faces  
	 */
	void render(_ArrayList* objects, bool renderTransparentFaces);

public: /* protected */

	/** 
	 * Renders transparent faces
	 * TODO:	guess this should be optimized regarding GL commands
	 * skinned mesh is not supported when using GPU
	 * @param transparent render faces
	 */
	void prepareTransparentFaces(_ArrayList* transparentRenderFaces);

	/** 
	 * Render transparent faces groups
	 * @param transparent render faces groups
	 * @param depth buffer mode
	 */
	void renderTransparentFacesGroups(_HashMap* transparentRenderFacesGroups);

	/** 
	 * Render transparent faces groups
	 * @param transparent render faces groups
	 * @param depth buffer mode
	 */
	void releaseTransparentFacesGroups();

	/** 
	 * Renders multiple objects of same type(with same model)
	 * @param engine
	 * @param objects of same type/ with same models
	 * @param collect render faces
	 * @param skinning shader
	 */
	void renderObjectsOfSameType(_ArrayList* objects, bool collectTransparentFaces);

	/** 
	 * Set ups a material for rendering
	 * @param object 3d group
	 * @param faces entity idx
	 */
	void setupMaterial(Object3DGroup* object3DGroup, int32_t facesEntityIdx);

	/** 
	 * Clear material for rendering
	 * @param gl
	 * @param material
	 */
	void clearMaterial();

private:

	/** 
	 * Creates a particle system entity key
	 * @param effect color add
	 * @param effect color mul
	 * @param depthBuffer
	 * @param sort
	 */
	static void createPseKey(Key* key, Color4* effectColorAdd, Color4* effectColorMul, bool depthBuffer, bool sort);

public:

	/** 
	 * Render batch VBO renderer points entities
	 * @param points batch VBO renderer points
	 */
	void render(_ArrayList* visiblePses);

	// Generated
	Object3DVBORenderer(Engine* engine, GLRenderer* renderer);
protected:
	Object3DVBORenderer(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	void init();
	virtual ::java::lang::Class* getClass0();
	friend class Object3DVBORenderer_1;
	friend class Object3DVBORenderer_Object3DVBORenderer_2;
	friend class Object3DVBORenderer_Object3DVBORenderer_3;
};
