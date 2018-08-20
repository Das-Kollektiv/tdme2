#pragma once

#include <vector>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/BatchVBORendererTriangles.h>
#include <tdme/engine/subsystems/rendering/Object3DVBORenderer.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector2.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/utils/Console.h>

using std::vector;
using std::string;

using tdme::engine::model::Color4;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::model::TextureCoordinate;
using tdme::engine::subsystems::rendering::BatchVBORendererTriangles;
using tdme::engine::subsystems::rendering::Object3DGroup;
using tdme::engine::subsystems::rendering::Object3DVBORenderer;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Matrix4x4;
using tdme::math::Vector2;
using tdme::math::Vector3;
using tdme::utils::Console;

/** 
 * Transparent render faces group
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::engine::subsystems::rendering::TransparentRenderFacesGroup final
{
	friend class Object3DVBORenderer;
	friend class Object3DVBORenderer_TransparentRenderFacesGroupPool;

private:
	Object3DVBORenderer* object3DVBORenderer {  };
	vector<BatchVBORendererTriangles*> batchVBORenderers {  };
	Model* model {  };
	Object3DGroup* object3DGroup {  };
	int32_t facesEntityIdx {  };

	Color4 effectColorAdd {  };
	Color4 effectColorMul {  };

	Material* material {  };
	bool textureCoordinates {  };

	/** 
	 * Set transparent render faces group
	 * @param object3DVBORenderer object3D VBO renderer
	 * @param model model
	 * @param object3DGroup object 3D group
	 * @param facesEntityIdx faces entity idx
	 * @param effectColorAdd effect color add
	 * @param effectColorMul effect color mul
	 * @param material material
	 * @param textureCoordinates texture coordinates
	 */
	void set(Object3DVBORenderer* object3DVBORenderer, Model* model, Object3DGroup* object3DGroup, int32_t facesEntityIdx, const Color4& effectColorAdd, const Color4& effectColorMul, Material* material, bool textureCoordinates);

	/** 
	 * Creates a key for given transparent render faces group attributes
	 * @param model model
	 * @param object3DGroup object 3D group
	 * @param facesEntityIdx faces entity idx
	 * @param effectColorAdd effect color add
	 * @param effectColorMul effect color mul
	 * @param material material
	 * @param textureCoordinates texture coordinates
	 * @return
	 */
	static const string createKey(Model* model, Object3DGroup* object3DGroup, int32_t facesEntityIdx, const Color4& effectColorAdd, const Color4& effectColorMul, Material* material, bool textureCoordinates);

	/** 
	 * Adds a vertex to this transparent render faces group
	 * @param vertex vertex
	 * @param normal normal
	 * @param textureCoordinate texture coordinate
	 */
	inline void addVertex(const Vector3& vertex, const Vector3& normal, const Vector2& textureCoordinate) {
		// check if we have a batch renderer already?
		if (batchVBORenderers.size() == 0) {
			// nope, add first one
			auto batchVBORendererTriangles = object3DVBORenderer->acquireTrianglesBatchVBORenderer();
			if (batchVBORendererTriangles == nullptr) {
				Console::println(string("TransparentRenderFacesGroup::addVertex(): could not acquire triangles batch vbo renderer"));
				return;
			}
			batchVBORenderers.push_back(batchVBORendererTriangles);
		}
		// try to add vertex
		auto batchVBORendererTriangles = batchVBORenderers[batchVBORenderers.size() - 1];
		if (batchVBORendererTriangles->addVertex(vertex, normal, textureCoordinate) == true)
			return;
		// failed, acquire additionally one
		batchVBORendererTriangles = object3DVBORenderer->acquireTrianglesBatchVBORenderer();
		if (batchVBORendererTriangles == nullptr) {
			Console::println(string("TransparentRenderFacesGroup::addVertex(): could not acquire triangles batch vbo renderer"));
			return;
		}
		// 	add it
		batchVBORenderers.push_back(batchVBORendererTriangles);
		// 	add vertex
		batchVBORendererTriangles->addVertex(vertex, normal, textureCoordinate);
	}

	/**
	 * Render this transparent render faces group
	 * @param renderer renderer
	 */
	void render(GLRenderer* renderer);

	/**
	 * Public constructor
	 */
	TransparentRenderFacesGroup();

};
