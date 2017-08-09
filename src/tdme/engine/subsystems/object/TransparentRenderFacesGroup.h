// Generated from /tdme/src/tdme/engine/subsystems/object/TransparentRenderFacesGroup.java

#pragma once

#include <vector>
#include <string>

#include <fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/subsystems/object/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>

using std::vector;
using std::wstring;

using tdme::engine::model::Color4;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::model::TextureCoordinate;
using tdme::engine::subsystems::object::Object3DGroup;
using tdme::engine::subsystems::object::Object3DVBORenderer;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

/** 
 * Transparent render faces group
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::engine::subsystems::object::TransparentRenderFacesGroup final
{
private:
	static Matrix4x4* modelViewMatrix;
	Object3DVBORenderer* object3DVBORenderer {  };
	vector<BatchVBORendererTriangles*> batchVBORenderers {  };
	Model* model {  };
	Object3DGroup* object3DGroup {  };
	int32_t facesEntityIdx {  };

public: /* protected */
	Color4* effectColorAdd {  };
	Color4* effectColorMul {  };

private:
	Material* material {  };
	bool textureCoordinates {  };

public: /* protected */

	/** 
	 * Set transparent render faces group
	 * @param object3D VBO renderer
	 * @param batch VBO renderer
	 * @param model
	 * @param object 3D group
	 * @param faces entity idx
	 * @param effect color add
	 * @param effect color mul
	 * @param material
	 * @param texture coordinates
	 */
	void set(Object3DVBORenderer* object3DVBORenderer, Model* model, Object3DGroup* object3DGroup, int32_t facesEntityIdx, Color4* effectColorAdd, Color4* effectColorMul, Material* material, bool textureCoordinates);

	/** 
	 * Creates a key for given transparent render faces group attributes
	 * @param model
	 * @param object 3D group
	 * @param faces entity idx
	 * @param effect color add
	 * @param effect color mul
	 * @param material
	 * @param texture coordinates
	 * @return
	 */
	static const wstring createKey(Model* model, Object3DGroup* object3DGroup, int32_t facesEntityIdx, Color4* effectColorAdd, Color4* effectColorMul, Material* material, bool textureCoordinates);

	/** 
	 * Adds a vertex to this transparent render faces group
	 * @param vertex
	 * @param normal
	 * @param texture coordinate
	 */
	void addVertex(Vector3* vertex, Vector3* normal, TextureCoordinate* textureCoordinate);

	/** 
	 * Render this transparent render faces group
	 * @param renderer
	 */
	void render(GLRenderer* renderer);

public: /* protected */
	/**
	 * Public constructor
	 */
	TransparentRenderFacesGroup();
};
