#pragma once

#include <vector>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/subsystems/object/fwd-tdme.h>
#include <tdme/engine/subsystems/object/BatchVBORendererTriangles.h>
#include <tdme/engine/subsystems/object/Object3DVBORenderer.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
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
using tdme::engine::subsystems::object::BatchVBORendererTriangles;
using tdme::engine::subsystems::object::Object3DGroup;
using tdme::engine::subsystems::object::Object3DVBORenderer;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::utils::Console;

/** 
 * Transparent render faces group
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::engine::subsystems::object::TransparentRenderFacesGroup final
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
	void set(Object3DVBORenderer* object3DVBORenderer, Model* model, Object3DGroup* object3DGroup, int32_t facesEntityIdx, Color4& effectColorAdd, Color4& effectColorMul, Material* material, bool textureCoordinates);

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
	static const string createKey(Model* model, Object3DGroup* object3DGroup, int32_t facesEntityIdx, Color4& effectColorAdd, Color4& effectColorMul, Material* material, bool textureCoordinates);

	/** 
	 * Adds a vertex to this transparent render faces group
	 * @param vertex
	 * @param normal
	 * @param texture coordinate
	 */
	inline void addVertex(const Vector3& vertex, const Vector3& normal, TextureCoordinate* textureCoordinate) {
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
		auto batchVBORendererTriangles = batchVBORenderers.at(batchVBORenderers.size() - 1);
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
	 * @param renderer
	 */
	void render(GLRenderer* renderer);

	/**
	 * Public constructor
	 */
	TransparentRenderFacesGroup();

};
